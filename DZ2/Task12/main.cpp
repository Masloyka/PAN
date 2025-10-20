#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;


int main(){
    const double v0 = 50.0, g = 9.8, dt = 1.0;
    double h;
    vector <double> times;
    vector <double> heights;
    heights.reserve((int)(v0*2/g/dt));
    times.reserve((int)(v0*2/g/dt));
    if (v0 < 0){
        cout << "Скорость отрицательна!";
    }
    for (double t = 0.0; t < 1000; t+= dt){
        h = v0 * t - 0.5 * g * t * t;
        if (h < 0){
            cout << "Ракета упала\n";
            break;
        }
        else{
            times.push_back(t);
            heights.push_back(h);
        }

    }
    cout << "Таблица времени и высоты\n";
    for (int i = 0; i < times.size(); i++){
        cout << setw(4) << left << times[i];
        cout << setprecision(4) << setw(5) << heights[i] << '\n';
    }
    //  Здесь заканчиваеться первая задача 
    // Начало 2 задачи
    if (heights.empty()){
        cout << "Данных нет в массиве heights";
        return 1;
    }
    else{
        int idx_max = 0;
        for (int i = 0; i < heights.size(); i++){
            if (heights[i] > heights[idx_max])
                idx_max = i;
            else if (heights[i] == heights[idx_max])
            {
                continue;
            }
            
        }         
        cout << "Максимальная высота: " << heights[idx_max] << " м в момент времени t = " << times[idx_max] << " c\n";  
    }
    return 0;
    // конец 2 задачи
}