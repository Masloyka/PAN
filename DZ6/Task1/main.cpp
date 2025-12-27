#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

class Trajectory {
private:
    std::vector<double> t; // время
    std::vector<double> x; // координата

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

            if (tokens.size() != 2) {
                std::cerr << "Предупреждение: некорректная строка — пропущена: " << line << std::endl;
                continue;
            }

            try {
                double time_val = std::stod(tokens[0]);
                double x_val = std::stod(tokens[1]);

                t.push_back(time_val);
                x.push_back(x_val);
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при парсинге строки: " << line << " — " << e.what() << std::endl;
                continue;
            }
        }

        file.close();
        std::cout << "Загружено " << t.size() << " точек траектории." << std::endl;
        return true;
    }

    // Вычисление скорости с использованием лямбды
    std::vector<double> calculateVelocities() const {
        if (t.size() < 2) {
            std::cerr << "Ошибка: недостаточно точек для вычисления скорости." << std::endl;
            return {};
        }

        std::vector<double> velocities;
        velocities.reserve(t.size() - 1);

        // Лямбда-функция для вычисления скорости между двумя точками
        auto computeVelocity = [](double x_next, double x_curr, double t_next, double t_curr) {
            if (t_next == t_curr) {
                throw std::runtime_error("Время не должно быть одинаковым для соседних точек.");
            }
            return (x_next - x_curr) / (t_next - t_curr);
        };

        for (size_t i = 0; i < t.size() - 1; ++i) {
            try {
                double v = computeVelocity(x[i + 1], x[i], t[i + 1], t[i]);
                velocities.push_back(v);
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при вычислении скорости на шаге " << i << ": " << e.what() << std::endl;
                continue;
            }
        }

        std::cout << "Вычислено " << velocities.size() << " значений скорости." << std::endl;
        return velocities;
    }

    // Генерация скрипта для Gnuplot
    void generateGnuplotScript(const std::string& script_filename) const {
        std::ofstream script(script_filename);
        if (!script.is_open()) {
            std::cerr << "Ошибка: не удалось создать скрипт " << script_filename << std::endl;
            return;
        }

        script << "# Gnuplot скрипт для построения графика x(t)\n";
        script << "set terminal png size 800,600\n";
        script << "set output 'trajectory_x_t.png'\n";
        script << "set grid\n";
        script << "set xlabel 'Время t (с)'\n";
        script << "set ylabel 'Координата x (м)'\n";
        script << "set title 'Траектория x(t)'\n";
        script << "set key right top\n";
        script << "plot 'traj.csv' using 1:2 with linespoints title 'x(t)' pointtype 7 linewidth 2\n";

        script.close();
        std::cout << "Скрипт для Gnuplot сохранён: " << script_filename << std::endl;
    }

    // Вывод данных для проверки
    void printData() const {
        std::cout << "\n=== Данные траектории ===" << std::endl;
        for (size_t i = 0; i < t.size(); ++i) {
            std::cout << "t=" << t[i] << ", x=" << x[i] << std::endl;
        }
    }

    // Получить копию векторов (если нужно)
    const std::vector<double>& getT() const { return t; }
    const std::vector<double>& getX() const { return x; }
};

// Пример использования
int main() {
    Trajectory traj;

    // Загрузка данных
    if (!traj.loadFromFile("traj.csv")) {
        std::cerr << "Не удалось загрузить данные." << std::endl;
        return 1;
    }

    // Вывод загруженных данных
    traj.printData();

    // Вычисление скоростей
    std::vector<double> velocities = traj.calculateVelocities();

    // Вывод скоростей (опционально)
    std::cout << "\n=== Скорости ===" << std::endl;
    for (size_t i = 0; i < velocities.size(); ++i) {
        std::cout << "v_" << i << " = " << velocities[i] << " м/с" << std::endl;
    }

    // Генерация скрипта для Gnuplot
    traj.generateGnuplotScript("plot_xt.gp");

    std::cout << "\n✅ Готово! " << std::endl;

    return 0;
}