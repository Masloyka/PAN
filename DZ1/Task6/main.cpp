#include <iostream>
#include <iomanip>
using namespace std;
double calculate_up_force(double S, double C_l, double V, double p){
    double L;
    L = 0.5 * p * V * V * S * C_l;
    return L;
}
int main(){
    double V[6] = {60.0, 90.0, 150.0, 230.0, 250.0, 260.0};
    double p[6] = {1.225, 1.059, 0.909, 0.590, 0.413, 0.364};
    double C_l, S, L;
    cout << "Введите коэффициент подъемной силы: ";
    cin >> C_l;
    cout << "Введите площадь крыла: ";
    cin >> S;
    cout << setw(6)<< "| Шаг "
    << setw(11) << "| Скорость " 
    << setw(11)<<"| Плотность "
    << setw(20)<<"| Подъемная сила |\n";
    for (int i = 0; i <= 5; i++){
        L = calculate_up_force(S, C_l, V[i], p[i]);
        cout << setw(6) << i + 1
        << setw(11) << setprecision(4) << V[i]
        << setw(12) << setprecision(7) << p[i]
        << setw(17) << setprecision(12) << L << endl;
    }
    return 0;
}