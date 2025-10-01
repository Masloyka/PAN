#include <iostream>
using namespace std;
double acceleration(int type_ac, double){}
struct Plane{
    double weight;
    double s;
    double T;
    double C_d;
    double C_l;
};
Plane calculate_plane(Plane planes[]){
    int count = 0;
    double min_time;
    while (count != 3)
    {
        cout << "Введите массу самолета для " << count <<" самолета: ";
        cin >> planes[count].weight;
        cout << "Введите площадь крыла для " << count <<" самолета: ";
        cin >> planes[count].s;
        cout << "Введите тягу для " << count << " самолета: ";
        cin >> planes[count].T;
        cout << "Введите коэффициент сопротивления для " << count << " самолета: ";
        cin >> planes[count].C_d;
        cout << "Введите коэффициент подъемной силы для " << count << " самолета: ";
        cin >> planes[count].C_l;
        count++;
    }
    count = 0;
    while (count != 3){

    }
    
}

int main(){
    return 0;
}