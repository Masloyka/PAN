#include <iostream>
#include <cmath>
using namespace std;
#define p 1.2041
#define g 9.81
double acceleration_x(double T, double D, double m){
    double a_x;
    a_x = (T - D) / m;
    return a_x;
}
double acceleration_y(double L, double m){
    double a_y;
    a_y = (L - m * g) / m;
    return a_y;
}
double calculate_up_force(double S, double C_l, double V){
    double L;
    L = 0.5 * p * V * V * S * C_l;
    return L;
}
double calculate_resistance(double S, double C_d, double V){
    double L_d;
    L_d= 0.5 * p * V * V * S *C_d;
    return L_d;
}
double calculate_time_alt(double h, double a_y){
    double time;
    time = sqrt(2 * h / a_y);
    return time;
}
struct Plane{
    double weight;
    double s;
    double T;
    double C_d;
    double C_l;
};
std::ostream& operator<<(std::ostream& os, const Plane& plane){
    os <<  "Вес самолета: " << plane.weight 
    << "\n" << "Площадь крыла самолета: "<<plane.s 
    << "\n" << "Тяга двигателя самолета: " << plane.T 
    << "\n" << "Коэффициент сопротивления: " << plane.C_d 
    << "\n" << "Коэффициент подъема самолета: " << plane.C_l << "\n";
    return os;
}
int calculate_plane(Plane planes[]){
    int count = 0, index;
    double min_time, V, h, L, L_d, a_x, a_y, time;
    while (count != 3)
    {
        cout << "Введите массу самолета для " << count+1 <<" самолета: ";
        cin >> planes[count].weight;
        cout << "Введите площадь крыла для " << count+1 <<" самолета: ";
        cin >> planes[count].s;
        cout << "Введите тягу для " << count+1 << " самолета: ";
        cin >> planes[count].T;
        cout << "Введите коэффициент сопротивления для " << count+1 << " самолета: ";
        cin >> planes[count].C_d;
        cout << "Введите коэффициент подъемной силы для " << count+1 << " самолета: ";
        cin >> planes[count].C_l;
        count++;
    }
    count = 0;
    cout << "Введите скорость движения самолетов: ";
    cin >> V;
    cout << "Введите высоту набора: ";
    cin >> h;
    while (count != 3){
        cout << "Информация " << count+1 << " самолета\n";
        cout << planes[count];
        L = calculate_up_force(planes[count].s, planes[count].C_l, V);
        L_d = calculate_resistance(planes[count].s, planes[count].C_d, V);
        a_x = acceleration_x(planes[count].T, L_d, planes[count].weight);
        a_y = acceleration_y(L, planes[count].weight);
        time = calculate_time_alt(h, a_y);
        if (time < min_time)
            min_time = time;
            index = count;
        if (count == 0)
            min_time = time;
        cout << "Подъемная сила " << count + 1 << " самолета: " << L << '\n';
        cout << "Сопротивление " << count + 1 << " самолета: " << L_d << "\n";
        cout << "Ускорения " << count + 1 << " самолета\n" << "По оси X:" << a_x << " По оси Y:" << a_y << "\n";
        count++;
        if (count == 3)
            cout << "Самолет " << index + 1 << " наберет высоту за " << min_time << endl; 
    }
    return 1;
}

int main(){
    Plane plains[3];
    int status = calculate_plane(plains);
    return 0;
}