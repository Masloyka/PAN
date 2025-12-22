#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath> // для abs()

class SensorData {
private:
    std::vector<double> t;   // время
    std::vector<double> h1;  // показания датчика 1
    std::vector<double> h2;  // показания датчика 2
    std::vector<double> dh;  // разница |h1 - h2|

public:
    // Метод загрузки данных из файла
    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
            return false;
        }

        std::string line;
        bool firstLine = true; // пропускаем заголовок

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
                double time_val = std::stod(tokens[0]);
                double h1_val = std::stod(tokens[1]);
                double h2_val = std::stod(tokens[2]);

                t.push_back(time_val);
                h1.push_back(h1_val);
                h2.push_back(h2_val);
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при парсинге строки: " << line << " — " << e.what() << std::endl;
                continue;
            }
        }

        file.close();
        std::cout << "Загружено " << t.size() << " точек данных." << std::endl;
        return true;
    }

    // Вычисление разницы Δh = |h1 - h2| с использованием лямбды
    void calculateDifference() {
        if (h1.size() != h2.size()) {
            std::cerr << "Ошибка: размеры массивов h1 и h2 не совпадают." << std::endl;
            return;
        }

        dh.clear();
        dh.reserve(h1.size());

        // Лямбда-функция для вычисления абсолютной разницы
        auto computeDeltaH = [](double a, double b) {
            return std::abs(a - b);
        };

        for (size_t i = 0; i < h1.size(); ++i) {
            double delta = computeDeltaH(h1[i], h2[i]);
            dh.push_back(delta);
        }

        std::cout << "Вычислено " << dh.size() << " значений разницы Δh." << std::endl;
    }

    // Сохранение разницы в файл diff.csv
    bool saveDifferenceToFile(const std::string& filename) {
        if (t.size() != dh.size()) {
            std::cerr << "Ошибка: данные не готовы для сохранения." << std::endl;
            return false;
        }

        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл " << filename << std::endl;
            return false;
        }

        // Заголовок
        file << "t,h1,h2,delta_h\n";

        // Данные
        for (size_t i = 0; i < t.size(); ++i) {
            file << t[i] << "," 
                 << h1[i] << "," 
                 << h2[i] << "," 
                 << dh[i] << "\n";
        }

        file.close();
        std::cout << "Разница успешно сохранена в файл: " << filename << std::endl;
        return true;
    }

    // Генерация скрипта для Gnuplot (три графика на одном поле)
    void generateGnuplotScript(const std::string& script_filename) const {
        std::ofstream script(script_filename);
        if (!script.is_open()) {
            std::cerr << "Ошибка: не удалось создать скрипт " << script_filename << std::endl;
            return;
        }

        script << "# Gnuplot скрипт для построения трёх графиков на одном поле\n";
        script << "set terminal png size 1000,600\n";
        script << "set output 'sensor_comparison.png'\n";
        script << "set grid\n";
        script << "set xlabel 'Время t (с)'\n";
        script << "set ylabel 'Значение'\n";
        script << "set title 'Сравнение двух датчиков'\n";
        script << "set key outside right top\n";
        script << "plot 'sensors.csv' using 1:2 with linespoints title 'h1(t)' pointtype 7 linewidth 2, \\\n";
        script << "     'sensors.csv' using 1:3 with linespoints title 'h2(t)' pointtype 5 linewidth 2, \\\n";
        script << "     'diff.csv' using 1:4 with linespoints title 'Δh(t)' pointtype 9 linewidth 2\n";

        script.close();
        std::cout << "Скрипт для Gnuplot сохранён: " << script_filename << std::endl;
    }

    // Вывод данных для проверки
    void printData() const {
        std::cout << "\n=== Данные датчиков ===" << std::endl;
        for (size_t i = 0; i < t.size(); ++i) {
            std::cout << "t=" << t[i] 
                      << ", h1=" << h1[i] 
                      << ", h2=" << h2[i] 
                      << ", Δh=" << dh[i] << std::endl;
        }
    }
};

// Пример использования
int main() {
    SensorData sensor;

    // Загрузка данных
    if (!sensor.loadFromFile("sensors.csv")) {
        std::cerr << "Не удалось загрузить данные." << std::endl;
        return 1;
    }

    // Вычисление разницы
    sensor.calculateDifference();

    // Сохранение разницы в файл
    if (!sensor.saveDifferenceToFile("diff.csv")) {
        std::cerr << "Не удалось сохранить разницу." << std::endl;
        return 1;
    }

    // Вывод данных
    sensor.printData();

    // Генерация скрипта для Gnuplot
    sensor.generateGnuplotScript("plot_sensors.gp");

    std::cout << "\n✅ Готово! " << std::endl;

    return 0;
}