#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() {
    std::cout << "Задача 7" << std::endl;
    
    const double v0 = 50.0;
    const double g = 9.8;
    const double dt = 0.1; 
    
    std::vector<double> times;
    std::vector<double> heights;
    

    for (double t = 0.0; t <= 15.0; t += dt) {
        double h = v0 * t - 0.5 * g * t * t;
        times.push_back(t);
        heights.push_back(h);
        if (h < -1.0) 
            break; 
    }
    

    auto it = std::find_if(heights.begin(), heights.end(),
        [](double h) { return h <= 0.0; });
    
    if (it == heights.end()) {
        std::cout << "Падения не было в диапазоне измерений!" << std::endl;
    } else {
        size_t idx = std::distance(heights.begin(), it);
        double t_fall = times[idx];
        
        std::cout << "Момент падения: t = " << std::fixed << std::setprecision(2) 
                  << t_fall << " с" << std::endl;
        std::cout << "Высота в этот момент: " << heights[idx] << " м" << std::endl;
        
        std::cout << "\nОкрестности момента падения:" << std::endl;
        std::cout << std::setw(10) << "Время" << std::setw(15) << "Высота" << std::endl;
        
        int start = std::max(0, static_cast<int>(idx) - 3);
        int end = std::min(static_cast<int>(heights.size()), static_cast<int>(idx) + 4);
        
        for (int i = start; i < end; ++i) {
            std::cout << std::setw(10) << std::fixed << std::setprecision(2) << times[i]
                      << std::setw(15) << heights[i];
            if (i == idx) std::cout << " <-- падение";
            std::cout << std::endl;
        }
    }
    

    std::cout << "\n--- Альтернативный расчет ---" << std::endl;
    double t_theoretical_fall = 2.0 * v0 / g;
    std::cout << "Теоретическое время падения: " << t_theoretical_fall << " с" << std::endl;
    
    return 0;
}