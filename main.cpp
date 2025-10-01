#include <iostream>
#include <cmath>
using namespace std;
double Resistance_coeff( double L, double p, double V, double S){
    double C_d;
    C_d = 2 * L / p / S /V / V;
    return C_d;
}
double acceleration(double L){
    double T, D, m,a, a_y, g = 9.81;
    cout << "Введите тягу двигателя\n";
    cin >> T;
    cout << "Введите сопротивление D\n";
    cin >> D;
    cout << "Введите массу самолета\n";
    cin >> m;
    a = (T-D)/m;
    a_y = (L-m*g) / m;
    cout << "Ускорение a: " << a << "\nУскорение a_y: " << a_y << endl;
    return a_y;
}
double time_altitude(double a_y){
    double h, t;
    cout << "Введите высоту набора\n";
    cin >> h;
    if (h <= 0 || a_y <= 0){
        cout << "Ошибка, отрицательное значение";
        return 0;
    }
    t = sqrt(2*h/a_y);
    return t;
}
struct Plane{
    double weight;
    double s;
    double T;
    double C_d;
    double C_l;
};

int main(){
    double S, p, V, C_l, L, time_atl, a_y;
    cout << "Введите площадь крыла самолета: ";
    cin >> S;
    cout << "Введите скорость самолета: ";
    cin >> V;
    cout << "Введите коэффициент подъема: ";
    cin >> C_l;
    cout << "Введите плотность воздуха: ";
    cin >> p;
    L = 0.5 * p * V * V * C_l * S;
    cout << "Подъемная сила равна: " << L << endl;
    cout << "Коэффициент сопротивления: " << Resistance_coeff(L, p, V, S) << endl;
    a_y = acceleration(L);
    time_atl = time_altitude(a_y);
    cout << "Время набора заданной высоты будет равно: " << time_atl << endl;
    Plane planes[3];
    return 0;
}