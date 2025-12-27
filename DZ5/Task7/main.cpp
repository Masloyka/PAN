#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
<<<<<<< HEAD
#include <algorithm>
#include <cmath>
#include <iomanip>

/**
 * Класс WaypointSorter предназначен для сортировки точек маршрута ЛА (летательного аппарата)
 * по расстоянию от текущей позиции.
 * 
 * Основная цель: определить порядок посещения точек маршрута, начиная с ближайшей к текущей позиции.
 * 
 * Принцип работы:
 * 1. Загрузка точек маршрута из файла
 * 2. Вычисление расстояния от текущей позиции до каждой точки
 * 3. Сортировка точек по возрастанию расстояния
 * 4. Сохранение отсортированного списка в файл
 * 
 * Для чего нужно:
 * - Планирование оптимального маршрута (посещение ближайших точек первыми)
 * - Навигация и автономное управление ЛА
 * - Оптимизация времени полета
 */
class WaypointSorter {
private:
    /**
     * Структура Waypoint представляет одну точку маршрута.
     * 
     * Поля:
     *   id - уникальный идентификатор точки
     *   x, y, z - координаты точки в трехмерном пространстве
     *   name - название точки (например, CheckpointA)
     *   distance - расстояние от текущей позиции ЛА до этой точки (вычисляется)
     */
=======
#include <cmath>
#include <algorithm>

class WaypointSorter {
private:
>>>>>>> e7c8263cb2519c095a839cc42c64d52d22993de6
    struct Waypoint {
        int id;
        double x, y, z;
        std::string name;
<<<<<<< HEAD
        double distance;  // Расстояние от текущей позиции до этой точки
        
        // Конструктор для удобного создания точек
        Waypoint(int i, double x_val, double y_val, double z_val, const std::string& n)
            : id(i), x(x_val), y(y_val), z(z_val), name(n), distance(0.0) {}
    };
    
    // Вектор для хранения всех точек маршрута
    std::vector<Waypoint> waypoints;

public:
    /**
     * Загружает точки маршрута из текстового файла.
     * 
     * Параметры:
     *   filename - путь к файлу с точками маршрута (формат: id,x,y,z,name)
     * 
     * Возвращает:
     *   true - если файл успешно загружен
     *   false - если произошла ошибка (файл не найден, ошибка чтения)
     * 
     * Как работает:
     *   1. Открывает файл для чтения
     *   2. Читает каждую строку файла
     *   3. Разбивает строку на поля по запятой
     *   4. Создает объект Waypoint и добавляет его в вектор
     * 
     * Формат входных данных:
     *   1,1000,500,2000,CheckpointA
     *   2,2000,1500,2500,CheckpointB
     */
=======
        double distance; // Расстояние от текущей позиции
    };

    std::vector<Waypoint> waypoints;

public:
    // Загрузка точек маршрута из файла
>>>>>>> e7c8263cb2519c095a839cc42c64d52d22993de6
    bool loadWaypoints(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
            return false;
        }
<<<<<<< HEAD
        
        waypoints.clear();  // Очищаем предыдущие данные
        std::string line;
        
        // Читаем файл построчно
        while (std::getline(file, line)) {
            // Пропускаем пустые строки
            if (line.empty()) continue;
            
            // Удаляем пробелы в начале и конце строки
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t") + 1);
            
            if (line.empty()) continue;
            
            // Разбиваем строку на поля по запятой
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;
            
            while (std::getline(ss, field, ',')) {
                // Удаляем пробелы вокруг каждого поля
                field.erase(0, field.find_first_not_of(" \t"));
                field.erase(field.find_last_not_of(" \t") + 1);
                fields.push_back(field);
            }
            
            // Проверяем, что в строке достаточно полей (id, x, y, z, name)
            if (fields.size() >= 5) {
                try {
                    int id = std::stoi(fields[0]);
                    double x = std::stod(fields[1]);
                    double y = std::stod(fields[2]);
                    double z = std::stod(fields[3]);
                    std::string name = fields[4];
                    
                    // Создаем точку маршрута и добавляем в вектор
                    waypoints.push_back(Waypoint(id, x, y, z, name));
                } catch (...) {
                    std::cerr << "Предупреждение: не удалось обработать строку: " << line << std::endl;
                }
            }
        }
        
        file.close();
        return true;
    }
    
    /**
     * Вычисляет расстояние от текущей позиции ЛА до каждой точки маршрута.
     * 
     * Параметры:
     *   current_x, current_y, current_z - координаты текущей позиции ЛА
     * 
     * Как работает:
     *   1. Проходит по всем точкам маршрута
     *   2. Для каждой точки вычисляет евклидово расстояние в 3D пространстве
     *   3. Сохраняет вычисленное расстояние в поле distance структуры Waypoint
     * 
     * Формула расстояния:
     *   distance = sqrt((x2-x1)² + (y2-y1)² + (z2-z1)²)
     * 
     * Для чего нужно:
     *   Расстояние необходимо для определения, какая точка ближе всего к текущей позиции,
     *   что позволяет оптимизировать маршрут полета.
     */
    void calculateDistances(double current_x, double current_y, double current_z) {
        // Проходим по всем точкам маршрута
        for (auto& waypoint : waypoints) {
            // Вычисляем разности координат
            double dx = waypoint.x - current_x;
            double dy = waypoint.y - current_y;
            double dz = waypoint.z - current_z;
            
            // Вычисляем евклидово расстояние в трехмерном пространстве
            // Используем формулу: sqrt(dx² + dy² + dz²)
            waypoint.distance = std::sqrt(dx * dx + dy * dy + dz * dz);
        }
    }
    
    /**
     * Сортирует точки маршрута по расстоянию от текущей позиции (от ближайшей к дальнейшей).
     * 
     * Как работает:
     *   1. Использует стандартную функцию std::sort из библиотеки <algorithm>
     *   2. Применяет лямбда-функцию для сравнения точек по расстоянию
     *   3. Сортирует в порядке возрастания расстояния
     * 
     * Лямбда-функция compareByDistance:
     *   - Принимает две точки маршрута (a и b)
     *   - Возвращает true, если расстояние до точки a меньше, чем до точки b
     *   - Это обеспечивает сортировку по возрастанию расстояния
     * 
     * Для чего нужно:
     *   После сортировки ближайшие точки будут в начале списка,
     *   что позволяет ЛА посещать их в оптимальном порядке.
     */
    void sortByDistance() {
        // Лямбда-функция для сравнения точек по расстоянию
        // Возвращает true, если расстояние до точки a меньше, чем до точки b
        // Это обеспечивает сортировку по возрастанию расстояния
        auto compareByDistance = [](const Waypoint& a, const Waypoint& b) {
            return a.distance < b.distance;
        };
        
        // Сортируем вектор точек маршрута используя лямбда-функцию сравнения
        std::sort(waypoints.begin(), waypoints.end(), compareByDistance);
    }
    
    /**
     * Сохраняет отсортированные точки маршрута в файл.
     * 
     * Параметры:
     *   filename - путь к файлу, куда сохранить отсортированные данные
     * 
     * Возвращает:
     *   true - если данные успешно сохранены
     *   false - если произошла ошибка
     * 
     * Как работает:
     *   1. Открывает файл для записи
     *   2. Записывает каждую точку маршрута в формате: id,x,y,z,name,distance
     *   3. Поля разделяются запятыми
     * 
     * Формат выходных данных:
     *   3,500,1000,1500,CheckpointC,447.21
     *   1,1000,500,2000,CheckpointA,632.46
     *   ...
     */
    bool saveSortedWaypoints(const std::string& filename) {
        if (waypoints.empty()) {
            std::cerr << "Ошибка: нет данных для сохранения" << std::endl;
            return false;
        }
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл " << filename << std::endl;
            return false;
        }
        
        // Записываем каждую точку маршрута
        // Формат: id,x,y,z,name,distance
        for (const auto& waypoint : waypoints) {
            file << waypoint.id << ","
                 << std::fixed << std::setprecision(2)
                 << waypoint.x << ","
                 << waypoint.y << ","
                 << waypoint.z << ","
                 << waypoint.name << ","
                 << waypoint.distance << "\n";
        }
        
        file.close();
        return true;
    }
    
    /**
     * Выводит информацию о точках маршрута на экран.
     * 
     * Для чего нужно:
     *   Позволяет визуально проверить результаты сортировки,
     *   увидеть порядок точек и расстояния до них.
     */
    void printWaypoints() {
        std::cout << "\n=== Отсортированные точки маршрута ===" << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
                  << std::setw(12) << "X" << std::setw(12) << "Y" << std::setw(12) << "Z"
                  << std::setw(20) << "Название" << std::setw(15) << "Расстояние" << std::endl;
        std::cout << std::string(75, '-') << std::endl;
        
        for (const auto& waypoint : waypoints) {
            std::cout << std::left << std::setw(5) << waypoint.id
                      << std::fixed << std::setprecision(2)
                      << std::setw(12) << waypoint.x
                      << std::setw(12) << waypoint.y
                      << std::setw(12) << waypoint.z
                      << std::setw(20) << waypoint.name
                      << std::setw(15) << waypoint.distance << std::endl;
        }
        std::cout << "==========================================\n" << std::endl;
    }
};

/**
 * Главная функция программы.
 * 
 * Демонстрирует использование класса WaypointSorter:
 * 1. Создает объект сортировщика точек маршрута
 * 2. Загружает точки из файла waypoints.txt
 * 3. Вычисляет расстояния от текущей позиции ЛА (x=800, y=600, z=1800)
 * 4. Сортирует точки по расстоянию
 * 5. Сохраняет результат в sorted_waypoints.txt
 * 6. Выводит отсортированный список на экран
 */
int main() {
    // Создаем объект сортировщика точек маршрута
    WaypointSorter sorter;
    
    // Загружаем точки маршрута из файла
    std::cout << "Загрузка точек маршрута из waypoints.txt..." << std::endl;
    if (!sorter.loadWaypoints("waypoints.txt")) {
        std::cerr << "Не удалось загрузить точки маршрута. Убедитесь, что файл waypoints.txt существует." << std::endl;
        return 1;
    }
    
    // Текущая позиция ЛА (летательного аппарата)
    double current_x = 800.0;
    double current_y = 600.0;
    double current_z = 1800.0;
    
    std::cout << "Текущая позиция ЛА: x=" << current_x 
              << ", y=" << current_y 
              << ", z=" << current_z << std::endl;
    
    // Вычисляем расстояния от текущей позиции до каждой точки маршрута
    std::cout << "Вычисление расстояний..." << std::endl;
    sorter.calculateDistances(current_x, current_y, current_z);
    
    // Сортируем точки по расстоянию (от ближайшей к дальнейшей)
    std::cout << "Сортировка точек по расстоянию..." << std::endl;
    sorter.sortByDistance();
    
    // Сохраняем отсортированные точки в файл
    std::cout << "Сохранение отсортированных точек в sorted_waypoints.txt..." << std::endl;
    if (!sorter.saveSortedWaypoints("sorted_waypoints.txt")) {
        std::cerr << "Не удалось сохранить данные." << std::endl;
        return 1;
    }
    
    // Выводим отсортированный список на экран
    sorter.printWaypoints();
    
    std::cout << "Сортировка завершена успешно!" << std::endl;
    
    return 0;
}


=======

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
>>>>>>> e7c8263cb2519c095a839cc42c64d52d22993de6
