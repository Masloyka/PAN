#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

// Структура для хранения одной точки траектории
struct TrajectoryPoint {
    double time;      // время, с
    double velocity;  // скорость, м/с
    double altitude;  // высота, м
    double distance;  // пройденное расстояние, м
    double fuel;      // расход топлива, кг
};

// Класс для хранения и сохранения траектории
class Trajectory {
private:
    std::vector<TrajectoryPoint> points;

public:
    // Метод для добавления точки (для примера — в реальной задаче будет заполняться расчетом)
    void addPoint(double time, double velocity, double altitude, double distance, double fuel) {
        points.push_back({time, velocity, altitude, distance, fuel});
    }

    // Сохранение траектории в CSV-файл
    bool saveToCSV(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл " << filename << std::endl;
            return false;
        }

        // Заголовок
        file << "time,velocity,altitude,distance,fuel\n";

        // Данные
        for (const auto& p : points) {
            file << p.time << "," 
                 << p.velocity << "," 
                 << p.altitude << "," 
                 << p.distance << "," 
                 << p.fuel << "\n";
        }

        file.close();
        std::cout << "Траектория успешно сохранена в файл: " << filename << std::endl;
        return true;
    }

    // Генерация скрипта для Gnuplot (опционально, но полезно)
    void generatePlotScript(const std::string& filename) {
        std::ofstream script(filename);
        if (!script.is_open()) {
            std::cerr << "Ошибка: не удалось создать скрипт " << filename << std::endl;
            return;
        }

        script << "# Gnuplot скрипт для визуализации траектории\n";
        script << "set terminal png size 800,600\n";
        script << "set output 'trajectory_plot.png'\n";
        script << "set grid\n";
        script << "set xlabel 'Время (с)'\n";
        script << "set ylabel 'Параметр'\n";
        script << "set title 'Оптимальная траектория'\n";
        script << "set key outside right top\n";
        script << "plot 'trajectory.csv' using 1:2 with lines title 'Скорость (м/с)', \\\n";
        script << "     'trajectory.csv' using 1:3 with lines title 'Высота (м)', \\\n";
        script << "     'trajectory.csv' using 1:4 with lines title 'Расстояние (м)', \\\n";
        script << "     'trajectory.csv' using 1:5 with lines title 'Расход топлива (кг)'\n";

        script.close();
        std::cout << "Скрипт для Gnuplot сохранён: " << filename << std::endl;
    }

    // Сохранение статистического отчёта
    void saveReport(const std::string& filename) {
        if (points.empty()) {
            std::cerr << "Ошибка: нет данных для генерации отчёта." << std::endl;
            return;
        }

        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл отчёта " << filename << std::endl;
            return;
        }

        // Вычисляем статистику
        double total_time = points.back().time - points.front().time;
        double total_fuel = points.back().fuel;
        double total_distance = points.back().distance;
        double avg_velocity = total_distance / total_time;

        // Форматируем вывод
        file << "Total flight time: " << std::fixed << std::setprecision(1) << total_time << " s\n";
        file << "Total fuel consumed: " << std::fixed << std::setprecision(1) << total_fuel << " kg\n";
        file << "Average velocity: " << std::fixed << std::setprecision(1) << avg_velocity << " m/s\n";

        file.close();
        std::cout << "Статистический отчёт сохранён в файл: " << filename << std::endl;
    }

    // Для демонстрации — метод получения точек (если нужно)
    const std::vector<TrajectoryPoint>& getPoints() const {
        return points;
    }
};

// Класс для решения задачи динамического программирования
class DynamicProgrammingSolver {
private:
    // Предположим, что у нас есть какие-то внутренние данные оптимизации
    double optimization_time = 0.0;
    int iterations = 0;
    double cost_function_value = 0.0;

public:
    // Установка тестовых данных для демонстрации
    void setOptimizationData(double time, int iter, double cost) {
        optimization_time = time;
        iterations = iter;
        cost_function_value = cost;
    }

    // Сохранение информации об оптимизации
    void saveOptimizationInfo(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл " << filename << std::endl;
            return;
        }

        file << "=== Информация об оптимизации ===\n";
        file << "Время выполнения: " << optimization_time << " сек\n";
        file << "Количество итераций: " << iterations << "\n";
        file << "Значение целевой функции: " << cost_function_value << "\n";

        file.close();
        std::cout << "Информация об оптимизации сохранена в файл: " << filename << std::endl;
    }
};

// Пример использования
int main() {
    Trajectory traj;
    DynamicProgrammingSolver solver;

    // Добавляем тестовые точки траектории (в реальном случае они рассчитываются)
    traj.addPoint(0.0, 250.0, 1000.0, 0.0, 0.0);
    traj.addPoint(1.0, 255.3, 1050.0, 252.5, 2.47);
    traj.addPoint(2.0, 260.7, 1101.8, 508.3, 4.92);

    // Сохраняем траекторию в CSV
    traj.saveToCSV("trajectory.csv");

    // Генерируем скрипт для Gnuplot (опционально)
    traj.generatePlotScript("plot_trajectory.gp");

    // Сохраняем отчёт
    traj.saveReport("report.txt");

    // Сохраняем информацию об оптимизации
    solver.setOptimizationData(1.25, 150, 845.2);
    solver.saveOptimizationInfo("optimization_info.txt");

    return 0;
}