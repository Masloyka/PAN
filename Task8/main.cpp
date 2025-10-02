#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define p 1.2048
#define g 9.81
struct Aircraft{
    char name[20];
    double weight;
    double s;
    double traction;
    double C_l;
    double C_d;
    double L;
    double a_y;
    double time_h;
};
int input_N(){
    int N;
    cout << "Введите количенство самолетов: ";
    cin >> N;
    return N-1; 
}
void input_plane(Aircraft* plane){
    cout << "Введите название самолета: ";
    cin >> plane->name;
    cout << "Введите вес самолета: ";
    cin >> plane->weight;
    cout << "Введите площадь крыла самолета: ";
    cin >> plane->s;
    cout << "Введите тягу двигателя самолета: ";
    cin >> plane->traction;
    cout << "Введите коэффициент подъемной силы: ";
    cin >> plane->C_l;
    cout << "Введите коэффициент силы сопротивление: ";
    cin >> plane->C_d;
}
void output_plane(Aircraft* plane){
    cout << "\n\nНазвание самолета: " << plane->name << "\n"
    << "Вес самолета: " << plane->weight << "\n"
    << "Площадь крыла самолета: " << plane->s << "\n"
    << "Тягу двигателя: " << plane->traction << "\n"
    << "Коэффициент подъемной силы: " << plane->C_l << "\n"
    << "Коэффициент силы сопротивления: " << plane->C_d << "\n"
    << "Подъемная сила: " << plane->L << '\n'
    << "Ускорение a_y: " << plane->a_y << "\n"
    << "Время до высоты: " << plane->time_h;
}
void calculate_up_force(Aircraft *plane, double V){
    plane->L = 0.5 * p * V * V * plane->s * plane->C_l;
}
void calculate_a_y(Aircraft *plane){
    plane->a_y = (plane->L - plane->weight * g) / plane->weight;
}
void calculate_time(Aircraft *plane, double h){
    plane->time_h = sqrt(2 * h / plane->a_y);
}
int main(){
    int N = input_N();
    double times[N+1];
    vector<Aircraft> plane(N+1);
    double V, h;
    cout << "Введите скорость движения самолетов: ";
    cin >> V;
    cout << "Введите высоту набора: ";
    cin >> h;
    for (int i = 0; i <= N; i++){
        input_plane(&plane[i]);
        calculate_up_force(&plane[i], V);
        calculate_a_y(&plane[i]);
        calculate_time(&plane[i], h);
        times[i] = plane[i].time_h;
    }

    sort(times, times + N + 1);
    
    for (int i = 0; i <= N; i++){
        for (int j = 0; j <= N; j++)
        if (times[i] ==  plane[j].time_h)
            output_plane(&plane[j]);
            continue;
    }
    cout << endl;
    return 0;
}