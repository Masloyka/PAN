#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>

int main() {
    std::cout << "Задача 4" << std::endl;
    
    const double v0 = 50.0;
    const double g = 9.8;
    const double dt = 1.0;
    const double t_max = 10.0;
    
    std::vector<double> times;
    std::vector<double> velocities;
    
    for (double t = 0.0; t <= t_max; t += dt) {
        double v = v0 - g * t;
        times.push_back(t);
        velocities.push_back(v);
    }
    
    if (velocities.empty()) {
        std::cout << "Нет данных для анализа!" << std::endl;
        return 0;
    }
    
    double sum = std::accumulate(velocities.begin(), velocities.end(), 0.0);
    double avg = sum / velocities.size();
    
    std::cout << "Сумма скоростей: " << sum << " м/с" << std::endl;
    std::cout << "Количество измерений: " << velocities.size() << std::endl;
    std::cout << "Средняя арифметическая скорость: " << std::fixed << std::setprecision(2) 
              << avg << " м/с" << std::endl;
    
    double integral = 0.0;
    for (int i = 0; i < velocities.size(); ++i) {
        integral += velocities[i] * dt;
    }
    double avg_integral = integral / t_max;
    
    std::cout << "Интегральное среднее: " << avg_integral << " м/с" << std::endl;

    double v_final = v0 - g * t_max;
    double theoretical_avg = (v0 + v_final) / 2.0;
    std::cout << "Теоретическое среднее (для равноускоренного движения): " 
              << theoretical_avg << " м/с" << std::endl;
    
    return 0;
}