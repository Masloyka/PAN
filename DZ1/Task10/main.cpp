#include <iostream>
using namespace std;
#define p 1.2048

struct Aircraft{
    double weight;
    double S;
    double T_min;
    double T_max;
    double delta_T;
    double C_l;
    double L;
    double a_y;
    double t;
};
void input_aircraft(Aircraft* plane){
    cout << "Введите вес самолета: ";
    cin >> plane->weight;
    cout << "Введите площадь крыла самолета: ";
    cin >> plane->S;
    cout << "Введите минимальную тягу двигателя: ";
    cin >> plane->T_min;
    cout << "Введите максимальную тягу двигателя: ";
    cin >> plane->T_max;
    cout << "Введите дельту тяги двигателя: ";
    cin >> plane->delta_T;
    cout << "Введите коэффициент поъемной силы: ";
    cin >> plane->C_l;
}
void calculate_up_force(Aircraft* plane, double V){
    plane->L = 0.5 * p * V * V * plane->S * plane->C_l;
}
void calculate_a_y(Aircraft* plane)
int main() {
    Aircraft* plane = new Aircraft;
    double V, h, t_min, optimum_T;
    input_aircraft(plane);
    cout << "Введи скорость движения самолета: ";
    cin >> V;
    cout << "Введите высоту набора: ";
    cin >> h;
    for (int i = plane->T_min; i <= plane->T_max; i = i + plane->delta_T){
        
    }
    return 0;
}