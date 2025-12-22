#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <stdexcept>

// Класс для хранения параметров ЛА
class Aircraft {
private:
    double mass;
    double wing_area;
    double Cx;
    double Cy;
    double max_thrust;
    double specific_consumption;

public:
    // Метод загрузки параметров из файла
    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue; // пропускаем пустые строки и комментарии

            size_t pos = line.find('=');
            if (pos == std::string::npos) {
                std::cerr << "Предупреждение: некорректная строка — пропущена: " << line << std::endl;
                continue;
            }

            std::string key = line.substr(0, pos);
            std::string value_str = line.substr(pos + 1);

            try {
                double value = std::stod(value_str);

                if (key == "mass") {
                    mass = value;
                } else if (key == "wing_area") {
                    wing_area = value;
                } else if (key == "Cx") {
                    Cx = value;
                } else if (key == "Cy") {
                    Cy = value;
                } else if (key == "max_thrust") {
                    max_thrust = value;
                } else if (key == "specific_consumption") {
                    specific_consumption = value;
                } else {
                    std::cerr << "Предупреждение: неизвестный ключ '" << key << "' — пропущен." << std::endl;
                }
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при парсинге значения для ключа '" << key << "': " << e.what() << std::endl;
                continue;
            }
        }

        file.close();
        std::cout << "Параметры ЛА успешно загружены." << std::endl;
        return true;
    }

    // Геттеры для доступа к параметрам
    double getMass() const { return mass; }
    double getWingArea() const { return wing_area; }
    double getCx() const { return Cx; }
    double getCy() const { return Cy; }
    double getMaxThrust() const { return max_thrust; }
    double getSpecificConsumption() const { return specific_consumption; }

    // Вывод всех параметров
    void print() const {
        std::cout << "\n=== Параметры ЛА ===" << std::endl;
        std::cout << "Масса: " << mass << std::endl;
        std::cout << "Площадь крыла: " << wing_area << std::endl;
        std::cout << "Аэродинамический коэффициент Cx: " << Cx << std::endl;
        std::cout << "Аэродинамический коэффициент Cy: " << Cy << std::endl;
        std::cout << "Макс. тяга двигателя: " << max_thrust << std::endl;
        std::cout << "Удельный расход топлива: " << specific_consumption << std::endl;
    }
};

// Класс для хранения и интерполяции атмосферных данных
class Environment {
private:
    struct AtmospherePoint {
        double altitude;
        double density;
        double pressure;
    };

    std::vector<AtmospherePoint> table;

public:
    // Метод загрузки таблицы атмосферы из CSV
    bool loadAtmosphereTable(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
            return false;
        }

        std::string line;
        bool firstLine = true; // Пропускаем заголовок

        while (std::getline(file, line)) {
            if (firstLine) {
                firstLine = false;
                continue;
            }

            if (line.empty()) continue;

            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> tokens;

            while (std::getline(iss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() != 3) {
                std::cerr << "Предупреждение: некорректная строка — пропущена: " << line << std::endl;
                continue;
            }

            try {
                double alt = std::stod(tokens[0]);
                double dens = std::stod(tokens[1]);
                double press = std::stod(tokens[2]);

                table.push_back({alt, dens, press});
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при парсинге строки: " << line << " — " << e.what() << std::endl;
                continue;
            }
        }

        file.close();

        // Сортируем по высоте (на случай, если данные неупорядочены)
        std::sort(table.begin(), table.end(), [](const AtmospherePoint& a, const AtmospherePoint& b) {
            return a.altitude < b.altitude;
        });

        std::cout << "Таблица атмосферы загружена. Количество точек: " << table.size() << std::endl;
        return true;
    }

    // Интерполяция линейной функции: y = y1 + (y2 - y1) * (x - x1) / (x2 - x1)
    double interpolate(double target_altitude, const std::function<double(const AtmospherePoint&)>& extractor) const {
        if (table.empty()) {
            throw std::runtime_error("Таблица атмосферы пуста.");
        }

        // Если высота меньше минимальной — возвращаем значение на минимальной высоте
        if (target_altitude <= table.front().altitude) {
            return extractor(table.front());
        }

        // Если высота больше максимальной — возвращаем значение на максимальной высоте
        if (target_altitude >= table.back().altitude) {
            return extractor(table.back());
        }

        // Поиск двух соседних точек, между которыми находится целевая высота
        for (size_t i = 0; i < table.size() - 1; ++i) {
            double h1 = table[i].altitude;
            double h2 = table[i + 1].altitude;

            if (h1 <= target_altitude && target_altitude <= h2) {
                double val1 = extractor(table[i]);
                double val2 = extractor(table[i + 1]);

                // Линейная интерполяция
                double ratio = (target_altitude - h1) / (h2 - h1);
                return val1 + (val2 - val1) * ratio;
            }
        }

        // На всякий случай (не должно сработать, если данные корректны)
        throw std::runtime_error("Не удалось найти интерваль для интерполяции.");
    }

    // Получить плотность воздуха на заданной высоте
    double getDensity(double altitude) const {
        return interpolate(altitude, [](const AtmospherePoint& p) { return p.density; });
    }

    // Получить давление на заданной высоте
    double getPressure(double altitude) const {
        return interpolate(altitude, [](const AtmospherePoint& p) { return p.pressure; });
    }

    // Вывод таблицы (для отладки)
    void printTable() const {
        std::cout << "\n=== Таблица атмосферы ===" << std::endl;
        for (const auto& p : table) {
            std::cout << "Высота: " << p.altitude 
                      << ", Плотность: " << p.density 
                      << ", Давление: " << p.pressure << std::endl;
        }
    }
};

// Пример использования
int main() {
    Aircraft aircraft;
    Environment environment;

    // Загрузка параметров ЛА
    if (!aircraft.loadFromFile("aircraft_params.txt")) {
        std::cerr << "Не удалось загрузить параметры ЛА." << std::endl;
        return 1;
    }

    // Загрузка таблицы атмосферы
    if (!environment.loadAtmosphereTable("atmosphere.csv")) {
        std::cerr << "Не удалось загрузить таблицу атмосферы." << std::endl;
        return 1;
    }

    // Вывод параметров ЛА
    aircraft.print();

    // Вывод таблицы атмосферы (опционально)
    environment.printTable();

    // Пример интерполяции
    std::cout << "\n=== Интерполяция атмосферных параметров ===" << std::endl;
    double test_altitude = 500.0; // Высота, для которой хотим получить параметры

    double density_at_500 = environment.getDensity(test_altitude);
    double pressure_at_500 = environment.getPressure(test_altitude);

    std::cout << "На высоте " << test_altitude << " м:" << std::endl;
    std::cout << "  Плотность воздуха: " << density_at_500 << std::endl;
    std::cout << "  Давление: " << pressure_at_500 << std::endl;

    // Проверка границ
    std::cout << "\nНа высоте 0 м: " << environment.getDensity(0.0) << std::endl;
    std::cout << "На высоте 3000 м (за пределами таблицы): " << environment.getDensity(3000.0) << std::endl;

    return 0;
}