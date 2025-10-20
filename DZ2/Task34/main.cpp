#include <iostream>
#include <vector>
#include <iomanip>
#include <numeric>
using namespace std;

int main(){
    const double v0 = 50.0, g = 9.8, dt = 1.0, t_max = 1000.0;
    double v;
    vector <double> times, velocities;
    times.reserve((int) (v0 / g));
    velocities.reserve((int) (v0/ g));
    for (double t = 0.0; t <= t_max; t += dt){
        v = v0 - g * t;
        if (v < 0)
            break;
        times.push_back(t);
        velocities.push_back(v);
    }
    cout << "Таблица скорости и времени\n";
    for (int i = 0; i < times.size(); i++){
        cout << setw(5) << times[i];
        cout << setw(8) << setprecision(4) << velocities[i] << endl;
    }
    // конец третий задачи
    // начало четвертой
    if (velocities.empty()){
        cout << "Данны в массиве скоростей нет" << endl;
        return 1;
    }
    double sum = accumulate(velocities.begin(), velocities.end(), 0.0);
    double avg = sum / velocities.size();
    cout << "Средняя скорость: " << setprecision(5) << avg << endl;
    // Средняя скорость как интегральное среднее
    double integral = 0.0;
    double T = times.back() - times.front();
    for (size_t i = 1; i <= times.size(); i++){
        double delta_time = times[i] - times[i-1];
        double v_avg = (velocities[i-1] + velocities[i]) / 2;
        integral += v_avg * delta_time;
    }
    double avg_integral = (1 / T) * integral;
    cout << "Интегральное среднее: " << setprecision(5) << avg_integral << endl;
}