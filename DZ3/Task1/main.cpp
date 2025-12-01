#include <iostream>
#include <vector>
#include <iomanip>

int main(){
    std::cout << "Задача 1." << std::endl;
    
    const double v0 = 50.0;
    const double g = 9.8;    
    const double dt = 1.0;   
    
    if (v0 <= 0) {
        std::cout << "Предупреждение: начальная скорость должна быть положительной!" << std::endl;
        return 1;
    }
    
    std::vector<double> times;
    std::vector<double> heights;
    
    int estimated_size = (v0 * 2 / g / dt) + 1;
    times.reserve(estimated_size);
    heights.reserve(estimated_size);
    
    for (double t = 0.0; t <= 100.0; t += dt) {
        double h = v0 * t - 0.5 * g * t * t;
        
        if (h < 0) {
            std::cout << "Ракета упала на землю при t = " << t << " с" << std::endl;
            break;
        }
        
        times.push_back(t);
        heights.push_back(h);
    }
    
    std::cout << std::setw(10) << "Время (с)" << std::setw(15) << "Высота (м)" << std::endl;
    std::cout << std::string(25, '-') << std::endl;
    
    for (size_t i = 0; i < times.size(); ++i) {
        std::cout << std::setw(10) << std::fixed << std::setprecision(1) << times[i]
                  << std::setw(15) << std::fixed << std::setprecision(2) << heights[i] << std::endl;
    }
    
    // std::cout << "Всего точек: " << times.size() << std::endl;
    return 0;
}