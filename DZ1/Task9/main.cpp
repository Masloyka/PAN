#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
#define p 1.2048

struct Aircraft{
    double weight;
    double S;
    double T;
    double C_l;
    double C_d;
    double L;
    double D;
    double a;
};

int input_N(){
    int N;
    cout << "Введите количество самолетов: ";
    cin >> N;
    return N;
}
void input_plane(Aircraft* plane, int number){
    cout << "Введите массу " << number+1 << " самолета: ";
    cin >> plane->weight;
    cout << "Введите площадь крыла " << number+1 << " самолета: ";
    cin >> plane->S;
    cout << "Введите тягу двигателя " << number+1 << " самолета: ";
    cin >> plane->T;
    cout << "Введите коэффициент подъемной силы " << number+1 <<" самолета: ";
    cin >> plane->C_l;
    cout << "Введите коэффициент силы сопротивления " << number+1 << " самолета: ";
    cin >> plane->C_d;
    cout << endl;
}
void output_plane(Aircraft* plane, int number){
    cout << "Информация о " << number+1 << " самолете\n";
    cout << "Масса: " << plane->weight << "\n"
    << "Площадь крыла: " << plane->S << "\n"
    << "Тяга двигателя: " << plane->T << "\n"
    << "Коэффициент подъемной силы: " << plane->C_l << "\n"
    << "Коэффициент силы сопротивления: " << plane->C_d << "\n"
    << "Подъемная сила: " << plane->L << "\n"
    << "Сопротивление: " << plane->D << "\n"
    << "Ускорение: " << plane->a; 
}
double calculate_L(Aircraft* plane, double V){
    double L;
    L = 0.5 * p * V * V * plane->S * plane->C_l;
    return L;
}
double calculate_D(Aircraft* plane, double V){
    double D;
    D = 0.5 * p * V * V * plane->S * plane->C_d;
    return D;
}
double calculate_acc(Aircraft* plane){
    double a;
    a = (plane->T - plane->D) / plane->weight;
    return a;
}
int main(){
    int N = input_N();
    double V, acceleration[N];
    Aircraft*  planes = new Aircraft[N];

    cout << "Введите скорость самолетов: ";
    cin >> V;

    for (int i = 0; i < N; i++){
        input_plane(planes+i, i);
        (planes+i)->L = calculate_L(planes+i, V);
        (planes+i)->D = calculate_D(planes+i, V);
        (planes+i)->a = calculate_acc(planes+i);
        acceleration[i] = (planes+i)->a;
    }   
    sort(acceleration, acceleration+N);
    for (int i = 0; i < N; i++){
        output_plane(planes+i, i);
        if ((planes+i)->a == acceleration[N-1])
            cout << "\n\x1b[33mСамолет " << i+1 << " имеет наибольшее ускорение: " << (planes+i)->a << "\x1b[0m";
        cout << "\n";
    }
    delete[] planes;
    return 0;
}