#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>


class TelemetryFilter {
private:

    std::vector<std::vector<std::string>> data;
    

    size_t originalRows = 0;  
    size_t filteredRows = 0;  

public:
    bool loadFromCSV(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
            return false;
        }
        
        data.clear(); 
        std::string line;
        
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            size_t commentPos = line.find("//");
            if (commentPos != std::string::npos) {
                line = line.substr(0, commentPos);
            }
            
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t") + 1);
            
            if (line.empty()) continue;
            
            std::vector<std::string> row;
            std::stringstream ss(line);
            std::string field;
            
            while (std::getline(ss, field, ',')) {
                field.erase(0, field.find_first_not_of(" \t"));
                field.erase(field.find_last_not_of(" \t") + 1);
                row.push_back(field);
            }
            
            if (!row.empty()) {
                data.push_back(row);
            }
        }
        
        file.close();
        originalRows = data.size();
        return true;
    }
    

    void filterData() {
        if (data.empty()) {
            std::cerr << "Ошибка: данные не загружены" << std::endl;
            return;
        }
        
        if (data.size() < 2) {
            std::cout << "Предупреждение: недостаточно данных для фильтрации" << std::endl;
            return;
        }
        
        int altitudeIndex = -1;
        int speedIndex = -1;
        
        for (size_t i = 0; i < data[0].size(); ++i) {
            if (data[0][i] == "altitude") {
                altitudeIndex = i;
            } else if (data[0][i] == "speed") {
                speedIndex = i;
            }
        }
        
        if (altitudeIndex == -1 || speedIndex == -1) {
            std::cerr << "Ошибка: не найдены столбцы altitude или speed" << std::endl;
            return;
        }
        

        auto isValidAltitude = [](double alt) { 
            return alt >= 0 && alt <= 20000; 
        };
        
        auto isValidSpeed = [](double speed) { 
            return speed >= 0 && speed <= 500; 
        };

        std::vector<std::vector<std::string>> filteredData;
        filteredData.push_back(data[0]); 
        
        for (size_t i = 1; i < data.size(); ++i) {
            bool isValid = true;
            
            if (altitudeIndex < static_cast<int>(data[i].size())) {
                try {
                    double altitude = std::stod(data[i][altitudeIndex]);
                    if (!isValidAltitude(altitude)) {
                        isValid = false;
                    }
                } catch (...) {

                    isValid = false;
                }
            }
            
            if (isValid && speedIndex < static_cast<int>(data[i].size())) {
                try {
                    double speed = std::stod(data[i][speedIndex]);
                    if (!isValidSpeed(speed)) {
                        isValid = false;
                    }
                } catch (...) {
                    isValid = false;
                }
            }
            
            if (isValid) {
                filteredData.push_back(data[i]);
            }
        }
        
        data = filteredData;
        filteredRows = data.size();
    }

    bool saveToCSV(const std::string& filename) {
        if (data.empty()) {
            std::cerr << "Ошибка: нет данных для сохранения" << std::endl;
            return false;
        }
        
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл " << filename << std::endl;
            return false;
        }
    
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[i].size(); ++j) {
                file << data[i][j];
                if (j < data[i].size() - 1) {
                    file << ",";
                }
            }
            file << "\n";
        }
        
        file.close();
        return true;
    }
    

    void printFilteredStats() {
        std::cout << "\n=== Статистика фильтрации ===" << std::endl;
        std::cout << "Исходное количество записей: " << originalRows << std::endl;
        std::cout << "Записей после фильтрации: " << filteredRows << std::endl;
        
        if (originalRows > 0) {
            size_t removedRows = originalRows - filteredRows;
            double percentage = (static_cast<double>(filteredRows) / originalRows) * 100.0;
            
            std::cout << "Удалено записей: " << removedRows << std::endl;
            std::cout << std::fixed << std::setprecision(2);
            std::cout << "Процент сохраненных данных: " << percentage << "%" << std::endl;
        }
        std::cout << "==============================\n" << std::endl;
    }
};


int main() {

    TelemetryFilter filter;
    

    std::cout << "Загрузка данных из telemetry.csv..." << std::endl;
    if (!filter.loadFromCSV("telemetry.csv")) {
        std::cerr << "Не удалось загрузить данные. Убедитесь, что файл telemetry.csv существует." << std::endl;
        return 1;
    }
    
    std::cout << "Фильтрация данных..." << std::endl;
    filter.filterData();
    
    std::cout << "Сохранение отфильтрованных данных в filtered_telemetry.csv..." << std::endl;
    if (!filter.saveToCSV("filtered_telemetry.csv")) {
        std::cerr << "Не удалось сохранить данные." << std::endl;
        return 1;
    }
    

    filter.printFilteredStats();
    
    std::cout << "Фильтрация завершена успешно!" << std::endl;
    
    return 0;
}

