#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

int main() {
    std::cout << "Задача 2" << std::endl;
    
    const double v0 = 50.0;
    const double g = 9.8;
    const double dt = 1.0;
    
    std::vector<double> times;
    std::vector<double> heights;
    
    for (double t = 0.0; t <= 100.0; t += dt) {
        double h = v0 * t - 0.5 * g * t * t;
        if (h < 0) break;
        times.push_back(t);
        heights.push_back(h);
    }
    
    if (heights.empty()) {
        std::cout << "Нет данных для анализа!" << std::endl;
        return 0;
    }
    
    int idx_max = 0;
    for (int i = 1; i < heights.size(); ++i) {
        if (heights[i] > heights[idx_max]) {
            idx_max = i;
        }
    }
    
    std::cout << "Способ 1:" << std::endl;
    std::cout << "Максимальная высота: " << std::fixed << std::setprecision(2) 
              << heights[idx_max] << " м" << std::endl;
    std::cout << "Время достижения: " << times[idx_max] << " с" << std::endl;
    
    auto it = std::max_element(heights.begin(), heights.end());
    int idx = std::distance(heights.begin(), it);
    
    std::cout << "\nСпособ 2:" << std::endl;
    std::cout << "Максимальная высота: " << *it << " м" << std::endl;
    std::cout << "Время достижения: " << times[idx] << " с" << std::endl;
    
    double t_theoretical = v0 / g;
    double h_theoretical = v0 * t_theoretical - 0.5 * g * t_theoretical * t_theoretical;
    std::cout << "\nТеоретические значения:" << std::endl;
    std::cout << "Время: " << t_theoretical << " с, Высота: " << h_theoretical << " м" << std::endl;
    
    return 0;
}