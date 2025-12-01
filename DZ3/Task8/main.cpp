#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>


void createTrajectory(std::vector<double>& times, std::vector<double>& heights, 
                      double v0, double dt, double t_max) {
    const double g = 9.8;
    for (double t = 0.0; t <= t_max; t += dt) {
        double h = v0 * t - 0.5 * g * t * t;
        times.push_back(t);
        heights.push_back(h);
        if (h < 0) break;
    }
}


double findFallTime(const std::vector<double>& heights, const std::vector<double>& times) {
    auto it = std::find_if(heights.begin(), heights.end(),
        [](double h) { return h <= 0.0; });
    
    if (it == heights.end()) {
        return -1.0; // Не упала
    }
    
    int idx = std::distance(heights.begin(), it);
    return times[idx];
}

int main() {
    std::cout << "Задача 8" << std::endl;
    

    std::vector<double> times1, heights1;
    createTrajectory(times1, heights1, 60.0, 0.5, 20.0);
    

    std::vector<double> times2, heights2;
    createTrajectory(times2, heights2, 40.0, 0.5, 20.0);
    
 
    auto max_it1 = std::max_element(heights1.begin(), heights1.end());
    int idx_max1 = std::distance(heights1.begin(), max_it1);
    double max_height1 = *max_it1;
    double time_max1 = times1[idx_max1];
    
    auto max_it2 = std::max_element(heights2.begin(), heights2.end());
    int idx_max2 = std::distance(heights2.begin(), max_it2);
    double max_height2 = *max_it2;
    double time_max2 = times2[idx_max2];
    

    double fall_time1 = findFallTime(heights1, times1);
    double fall_time2 = findFallTime(heights2, times2);
    

    std::cout << "\nСравнение максимальных высот:" << std::endl;
    std::cout << "Ракета 1: " << max_height1 << " м (время: " << time_max1 << " с)" << std::endl;
    std::cout << "Ракета 2: " << max_height2 << " м (время: " << time_max2 << " с)" << std::endl;
    
    if (max_height1 > max_height2) {
        std::cout << "Ракета 1 поднялась выше!" << std::endl;
    } else if (max_height2 > max_height1) {
        std::cout << "Ракета 2 поднялась выше!" << std::endl;
    } else {
        std::cout << "Ракеты поднялись на одинаковую высоту!" << std::endl;
    }
    

    std::cout << "\nСравнение времени полета:" << std::endl;
    std::cout << "Ракета 1: ";
    if (fall_time1 >= 0) {
        std::cout << fall_time1 << " с до падения";
    } else {
        std::cout << "еще в полете";
    }
    std::cout << std::endl;
    
    std::cout << "Ракета 2: ";
    if (fall_time2 >= 0) {
        std::cout << fall_time2 << " с до падения";
    } else {
        std::cout << "еще в полете";
    }
    std::cout << std::endl;
    
    if (fall_time1 >= 0 && fall_time2 >= 0) {
        if (fall_time1 > fall_time2) {
            std::cout << "Ракета 1 дольше находилась в воздухе!" << std::endl;
        } else if (fall_time2 > fall_time1) {
            std::cout << "Ракета 2 дольше находилась в воздухе!" << std::endl;
        } else {
            std::cout << "Ракеты находились в воздухе одинаковое время!" << std::endl;
        }
    }
    

    std::cout << "\n=== Таблица сравнения ===" << std::endl;
    std::cout << std::setw(20) << "Параметр" 
              << std::setw(15) << "Ракета 1" 
              << std::setw(15) << "Ракета 2" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    std::cout << std::setw(20) << "Макс. высота (м)"
              << std::setw(15) << std::fixed << std::setprecision(1) << max_height1
              << std::setw(15) << max_height2 << std::endl;
    
    std::cout << std::setw(20) << "Время макс. высоты (с)"
              << std::setw(15) << time_max1
              << std::setw(15) << time_max2 << std::endl;
    
    std::cout << std::setw(20) << "Время падения (с)";
    if (fall_time1 >= 0) {
        std::cout << std::setw(15) << fall_time1;
    } else {
        std::cout << std::setw(15) << "N/A";
    }
    if (fall_time2 >= 0) {
        std::cout << std::setw(15) << fall_time2;
    } else {
        std::cout << std::setw(15) << "N/A";
    }
    std::cout << std::endl;
    
    return 0;
}