#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() {
    std::cout << "Задача 6" << std::endl;
    

    std::vector<double> heights = {25.3, 8.7, 15.2, 5.1, 32.8, 9.9, 12.4, 45.6, 3.2, 18.7};
    
    std::cout << "Исходный вектор высот:" << std::endl;
    for (int i = 0; i < heights.size(); ++i) {
        std::cout << std::setw(6) << std::fixed << std::setprecision(1) << heights[i];
        if ((i + 1) % 5 == 0) std::cout << std::endl;
    }
    std::cout << "\nВсего элементов: " << heights.size() << std::endl;
    

    auto new_end = std::remove_if(heights.begin(), heights.end(),
        [](double h) { return h < 10.0; });
    
    heights.erase(new_end, heights.end());
    
    std::cout << "\nПосле удаления значений < 10 м:" << std::endl;
    if (heights.empty()) {
        std::cout << "Все значения были удалены!" << std::endl;
    } else {
        for (int i = 0; i < heights.size(); ++i) {
            std::cout << std::setw(6) << std::fixed << std::setprecision(1) << heights[i];
            if ((i + 1) % 5 == 0) std::cout << std::endl;
        }
        std::cout << "\nОсталось элементов: " << heights.size() << std::endl;
    }
    
    std::cout << "\n--- Тест 1: Все значения < 10 ---" << std::endl;
    std::vector<double> test1 = {5.0, 3.0, 7.0, 8.0, 2.0};
    new_end = std::remove_if(test1.begin(), test1.end(),
        [](double h) { return h < 10.0; });
    test1.erase(new_end, test1.end());
    std::cout << "Осталось элементов: " << test1.size() << std::endl;
    
    std::cout << "\n--- Тест 2: Все значения >= 10 ---" << std::endl;
    std::vector<double> test2 = {15.0, 23.0, 17.0, 28.0, 12.0};
    new_end = std::remove_if(test2.begin(), test2.end(),
        [](double h) { return h < 10.0; });
    test2.erase(new_end, test2.end());
    std::cout << "Осталось элементов: " << test2.size() << std::endl;
    
    return 0;
}