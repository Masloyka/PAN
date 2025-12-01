#include <iostream>
#include <vector>
#include <array>
#include <iomanip>

int main() {
    std::cout << "Задача 5" << std::endl;
    
    const double vx0 = 30.0; 
    const double vy0 = 20.0;  
    const double vz0 = 40.0;  
    
    const double dt = 0.5;    
    const double t_max = 10.0; 
    
    std::vector<double> times;
    std::vector<std::array<double, 3>> positions; 
    
    double x = 0.0, y = 0.0, z = 0.0;
    
    for (double t = 0.0; t <= t_max; t += dt) {

        x += vx0 * dt;
        y += vy0 * dt;
        z += vz0 * dt - 0.5 * 9.8 * t * dt; 
        
        times.push_back(t);
        positions.push_back({x, y, z});
    }
    

    std::cout << std::setw(8) << "Время" 
              << std::setw(12) << "X" 
              << std::setw(12) << "Y" 
              << std::setw(12) << "Z" << std::endl;
    std::cout << std::string(44, '-') << std::endl;
    
    for (int i = 0; i < times.size(); ++i) {
        std::cout << std::setw(8) << std::fixed << std::setprecision(1) << times[i]
                  << std::setw(12) << std::fixed << std::setprecision(2) << positions[i][0]
                  << std::setw(12) << positions[i][1]
                  << std::setw(12) << positions[i][2] << std::endl;
    }
    
    std::cout << "\nКонечное положение:" << std::endl;
    std::cout << "X = " << positions.back()[0] << " м" << std::endl;
    std::cout << "Y = " << positions.back()[1] << " м" << std::endl;
    std::cout << "Z = " << positions.back()[2] << " м" << std::endl;
    
    return 0;
}