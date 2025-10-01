#include <iostream>
using namespace std;
#define p 1.2041
#define g 9.81
struct Plane {
    char name[20];
    double weight;
    double C_l;
    double C_d;
    double S;
    double T;
};
std::ostream& operator<<(std::ostream& os, const Plane& plane){
    os << "Название самолета: " << plane.name << '\n'
    <<  "Вес самолета: " << plane.weight 
    << "\n" << "Площадь крыла самолета: "<<plane.S 
    << "\n" << "Тяга двигателя самолета: " << plane.T 
    << "\n" << "Коэффициент сопротивления: " << plane.C_d 
    << "\n" << "Коэффициент подъема самолета: " << plane.C_l << "\n";
    return os;
}
double calculate_up_force(double S, double V, double C_l){
    double L;
    L = 0.5 * p * V * V * S * C_l;
    return L;
}
double calculate_resistance(double S, double C_d, double V){
    double L_d;
    L_d= 0.5 * p * V * V * S *C_d;
    return L_d;
}
double acceleration_y(double L, double m){
    double a_y;
    a_y = (L - m * g) / m;
    return a_y;
}
double acceleration_x(double T, double D, double m){
    double a_x;
    a_x = (T - D) / m;
    return a_x;
}
int main(){
    Plane plane;
    double cur_vel, a_y, L_d, L, a_x;
    cout << "Введите название самолета: ";
    cin >> plane.name;
    cout << "Введите вес самолета: ";
    cin >> plane.weight;
    cout << "Введите коэффициент подъемной силы: ";
    cin >> plane.C_l;
    cout << "Введите коэффициент сопротивления: ";
    cin >> plane.C_d;
    cout << "Введите площадь крыла самолета: ";
    cin >> plane.S;
    cout << "Введите тягу двигателя самолета: ";
    cin >> plane.T;
    cout << "Введите текущую скорость самолета: ";
    cin >> cur_vel;
    cout << plane;
    L = calculate_up_force(plane.S, cur_vel, plane.C_l);
    L_d = calculate_resistance(plane.S, plane.C_d, cur_vel);
    a_x = acceleration_x(plane.T, L_d, plane.weight);
    if (a_x < 0)
        cout << "Ошибка ускорение отрицательно!!!!";
    a_y = acceleration_y(L, plane.weight);
    if (a_y > 0.5)
        cout << "Режим 'Набор высоты'";
    else if (a_y > 0 && a_y <= 0.5)
        if (a_x == 0)
            cout << "Ошибка! Ускорение по оси X нулевое!!!'" << endl;
        else
            cout << "Режим 'Горизонтальный полет'" << endl;    
    else
        cout << "Режим 'Снижение'" << endl;       
    return 0;
}