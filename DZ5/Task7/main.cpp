#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>

class WaypointSorter {
private:
    struct Waypoint {
        int id;
        double x, y, z;
        std::string name;
        double distance; // Расстояние от текущей позиции
    };

    std::vector<Waypoint> waypoints;

public:
    // Загрузка точек маршрута из файла
    bool loadWaypoints(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
            return false;
        }

        waypoints.clear();
        std::string line;

        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> tokens;

            // Разбиваем строку по запятым
            while (std::getline(iss, token, ',')) {
                tokens.push_back(token);
            }

            // Проверяем, что у нас есть все 5 полей
            if (tokens.size() != 5) {
                std::cerr << "Ошибка: неверный формат строки: " << line << std::endl;
                continue;
            }

            try {
                Waypoint wp;
                wp.id = std::stoi(tokens[0]);
                wp.x = std::stod(tokens[1]);
                wp.y = std::stod(tokens[2]);
                wp.z = std::stod(tokens[3]);
                wp.name = tokens[4];
                wp.distance = 0.0; // Инициализируем расстояние нулем

                waypoints.push_back(wp);
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при парсинге строки: " << line << " - " << e.what() << std::endl;
                continue;
            }
        }

        file.close();
        return true;
    }

    // Вычисление расстояний от текущей позиции
    void calculateDistances(double current_x, double current_y, double current_z) {
        for (auto& wp : waypoints) {
            // Евклидово расстояние в 3D пространстве
            double dx = wp.x - current_x;
            double dy = wp.y - current_y;
            double dz = wp.z - current_z;
            wp.distance = std::sqrt(dx * dx + dy * dy + dz * dz);
        }
    }

    // Сортировка по расстоянию с использованием лямбда-функции
    void sortByDistance() {
        auto compareByDistance = [](const Waypoint& a, const Waypoint& b) {
            return a.distance < b.distance;
        };
        std::sort(waypoints.begin(), waypoints.end(), compareByDistance);
    }

    // Сохранение отсортированных точек в файл
    void saveSortedWaypoints(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл " << filename << std::endl;
            return;
        }

        for (const auto& wp : waypoints) {
            file << wp.id << "," << wp.x << "," << wp.y << "," << wp.z << "," << wp.name << std::endl;
        }

        file.close();
        std::cout << "Отсортированные точки успешно сохранены в файл: " << filename << std::endl;
    }

    void printWaypoints() const {
        for (const auto& wp : waypoints) {
            std::cout << "ID: " << wp.id 
                      << ", Имя: " << wp.name 
                      << ", Координаты: (" << wp.x << ", " << wp.y << ", " << wp.z << ")"
                      << ", Расстояние: " << wp.distance << std::endl;
        }
    }
};

// Пример использования
int main() {
    WaypointSorter sorter;

    // Текущая позиция ЛА
    double current_x = 800.0;
    double current_y = 600.0;
    double current_z = 1800.0;

    // Загрузка данных
    if (!sorter.loadWaypoints("waypoints.txt")) {
        std::cerr << "Не удалось загрузить данные." << std::endl;
        return 1;
    }

    // Вычисление расстояний
    sorter.calculateDistances(current_x, current_y, current_z);

    // Сортировка
    sorter.sortByDistance();

    // Сохранение результата
    sorter.saveSortedWaypoints("sorted_waypoints.txt");

    // Вывод результатов в консоль для проверки
    sorter.printWaypoints();

    return 0;
}