#include <iostream>
#include <vector>
#include <iomanip>

int main() {
    std::cout << "Задача 3" << std::endl;
    
    const double v0 = 50.0;  
    const double g = 9.8;    
    const double dt = 1.0;   
    const double t_max = 15.0; 
    
    std::vector<double> times;
    std::vector<double> velocities;
    
    times.reserve((t_max / dt) + 1);
    velocities.reserve((t_max / dt) + 1);
    
    for (double t = 0.0; t <= t_max; t += dt) {
        double v = v0 - g * t;
        times.push_back(t);
        velocities.push_back(v);
        
        if (v < -v0) break;
    }
    
    std::cout << std::setw(10) << "Время (с)" << std::setw(15) << " Скорость (м/с)" << std::endl;
    std::cout << std::string(25, '-') << std::endl;
    
    for (int i = 0; i < times.size(); ++i) {
        std::cout << std::setw(10) << std::fixed << std::setprecision(1) << times[i]
                  << std::setw(15) << std::fixed << std::setprecision(2) << velocities[i] << std::endl;
    }
    
    double t_zero_v = v0 / g;
    std::cout << "\nСкорость становится нулевой при t = " << t_zero_v << " с" << std::endl;
    
    return 0;
}