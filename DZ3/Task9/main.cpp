#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>

void addNoise(std::vector<double>& data, double noise_level) {
    for (size_t i = 0; i < data.size(); ++i) {
        double noise = (2.0 * rand() / RAND_MAX - 1.0) * noise_level;
        data[i] += noise;
    }
}

int main() {
    std::cout << "Задача 9" << std::endl;
    
    srand(time(nullptr));
    

    const double v0 = 50.0;
    const double g = 9.8;
    const double dt = 0.2;
    
    std::vector<double> h_ideal;
    std::vector<double> times;
    
    for (double t = 0.0; t <= 10.0; t += dt) {
        double height = v0 * t - 0.5 * g * t * t;
        if (height < 0) break;
        h_ideal.push_back(height);
        times.push_back(t);
    }
    

    std::vector<double> h_noisy = h_ideal;
    addNoise(h_noisy, 3.0); 
    

    std::vector<double> smoothed(h_noisy.size());
    
    size_t n = h_noisy.size();
    

    if (n > 0) smoothed[0] = h_noisy[0];
    if (n > 1) smoothed[1] = (h_noisy[0] + h_noisy[1]) / 2.0;
    

    for (int i = 2; i + 1 < n; ++i) {
        smoothed[i] = (h_noisy[i-1] + h_noisy[i] + h_noisy[i+1]) / 3.0;
    }
    

    if (n > 1) smoothed[n-1] = (h_noisy[n-2] + h_noisy[n-1]) / 2.0;
    

    std::cout << std::setw(8) << "Время " 
              << std::setw(12) << "Идеальная " 
              << std::setw(12) << "Зашумл. " 
              << std::setw(12) << "Сглажен. " 
              << std::setw(12) << "Ошибка " << std::endl;
    std::cout << std::string(56, '-') << std::endl;
    
    double total_error_noisy = 0.0;
    double total_error_smoothed = 0.0;
    
    for (int i = 0; i < n; ++i) {
        double error_noisy = std::abs(h_noisy[i] - h_ideal[i]);
        double error_smoothed = std::abs(smoothed[i] - h_ideal[i]);
        
        total_error_noisy += error_noisy;
        total_error_smoothed += error_smoothed;
        
        std::cout << std::setw(8) << std::fixed << std::setprecision(1) << times[i]
                  << std::setw(12) << std::setprecision(2) << h_ideal[i]
                  << std::setw(12) << h_noisy[i]
                  << std::setw(12) << smoothed[i]
                  << std::setw(12) << error_smoothed << std::endl;
    }
    

    std::cout << "\n=== Статистика ===" << std::endl;
    std::cout << "Средняя ошибка зашумленных данных: " 
              << total_error_noisy / n << " м" << std::endl;
    std::cout << "Средняя ошибка сглаженных данных: " 
              << total_error_smoothed / n << " м" << std::endl;
    std::cout << "Улучшение: " 
              << (total_error_noisy - total_error_smoothed) / total_error_noisy * 100.0 
              << "%" << std::endl;
    

    std::cout << "\n--- Сглаживание с окном 5 ---" << std::endl;
    int k = 2;
    
    std::vector<double> smoothed_window5(h_noisy.size(), 0.0);
    
    for (size_t i = 0; i < n; ++i) {
        int start = std::max(0, static_cast<int>(i) - k);
        int end = std::min(static_cast<int>(n) - 1, static_cast<int>(i) + k);
        
        double sum = 0.0;
        int count = 0;
        
        for (int j = start; j <= end; ++j) {
            sum += h_noisy[j];
            count++;
        }
        
        smoothed_window5[i] = sum / count;
    }
    

    std::cout << "Сравнение методов сглаживания для первых 5 точек:" << std::endl;
    for (int i = 0; i < 5 && i < n; ++i) {
        std::cout << "t=" << times[i] << ": Идеал=" << h_ideal[i]
                  << ", Окно3=" << smoothed[i]
                  << ", Окно5=" << smoothed_window5[i] << std::endl;
    }
    
    return 0;
}