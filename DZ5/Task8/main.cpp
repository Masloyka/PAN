#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

class FuelAnalyzer {
private:
    std::vector<double> time_data;
    std::vector<double> fuel_data;
    std::vector<double> rpm_data;

public:
    // Загрузка данных из CSV-файла
    bool loadData(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
            return false;
        }

        // Очищаем предыдущие данные
        time_data.clear();
        fuel_data.clear();
        rpm_data.clear();

        std::string line;
        bool firstLine = true; // Пропускаем заголовок

        while (std::getline(file, line)) {
            if (firstLine) {
                firstLine = false;
                continue; // Пропускаем строку с заголовками
            }

            if (line.empty()) continue;

            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> tokens;

            // Разбиваем строку по запятым
            while (std::getline(iss, token, ',')) {
                tokens.push_back(token);
            }

            // Проверяем, что у нас есть ровно 3 поля
            if (tokens.size() != 3) {
                std::cerr << "Предупреждение: некорректная строка — пропущена: " << line << std::endl;
                continue;
            }

            try {
                double time_val = std::stod(tokens[0]);
                double fuel_val = std::stod(tokens[1]);
                double rpm_val = std::stod(tokens[2]);

                time_data.push_back(time_val);
                fuel_data.push_back(fuel_val);
                rpm_data.push_back(rpm_val);
            } catch (const std::exception& e) {
                std::cerr << "Ошибка при парсинге строки: " << line << " — " << e.what() << std::endl;
                continue;
            }
        }

        file.close();
        std::cout << "Загружено " << time_data.size() << " записей." << std::endl;
        return true;
    }

    // Вычисление среднего расхода топлива
    double calculateAverageConsumption() {
        if (fuel_data.empty()) {
            return 0.0;
        }

        double sum = 0.0;
        for (double consumption : fuel_data) {
            sum += consumption;
        }

        return sum / fuel_data.size();
    }

    // Обнаружение аномалий с использованием лямбды
    void detectAnomalies() {
        double avg = calculateAverageConsumption();
        double threshold = 1.5; // порог в 1.5 раза больше среднего

        auto isAnomaly = [avg, threshold](double consumption) {
            return consumption > avg * threshold;
        };

        std::cout << "\n=== Аномалии расхода топлива ===" << std::endl;
        bool foundAnomaly = false;

        for (size_t i = 0; i < fuel_data.size(); ++i) {
            if (isAnomaly(fuel_data[i])) {
                foundAnomaly = true;
                std::cout << "Время: " << time_data[i] 
                          << ", Расход: " << fuel_data[i]
                          << ", RPM: " << rpm_data[i]
                          << " — АНОМАЛИЯ!" << std::endl;
            }
        }

        if (!foundAnomaly) {
            std::cout << "Аномалий не обнаружено." << std::endl;
        }
    }

    // Генерация отчёта в файл
    void generateReport(const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл отчёта " << filename << std::endl;
            return;
        }

        double avg = calculateAverageConsumption();
        file << "Отчёт по анализу расхода топлива\n";
        file << "===============================\n";
        file << "Средний расход: " << std::fixed << std::setprecision(2) << avg << "\n\n";

        file << "Аномалии (расход > " << avg * 1.5 << "):\n";
        file << "----------------------------------------\n";

        auto isAnomaly = [avg](double consumption) {
            return consumption > avg * 1.5;
        };

        bool foundAnomaly = false;
        for (size_t i = 0; i < fuel_data.size(); ++i) {
            if (isAnomaly(fuel_data[i])) {
                foundAnomaly = true;
                file << "Время: " << time_data[i] 
                     << ", Расход: " << fuel_data[i]
                     << ", RPM: " << rpm_data[i]
                     << " — АНОМАЛИЯ!\n";
            }
        }

        if (!foundAnomaly) {
            file << "Аномалий не обнаружено.\n";
        }

        file.close();
        std::cout << "\nОтчёт успешно сохранён в файл: " << filename << std::endl;
    }
};

// Пример использования
int main() {
    FuelAnalyzer analyzer;

    // Загрузка данных
    if (!analyzer.loadData("data.txt")) {
        std::cerr << "Не удалось загрузить данные." << std::endl;
        return 1;
    }

    // Анализ и вывод аномалий
    analyzer.detectAnomalies();

    // Генерация отчёта
    analyzer.generateReport("fuel_analysis_report.txt");

    return 0;
}