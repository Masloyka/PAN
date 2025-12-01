#include <iostream>
using namespace std;

class RocketStage{
    private:
        double thrust;
        double burnTime;
        double mass;
    public:
        RocketStage(double T, double B, double M) : thrust(T), burnTime(B), mass(M){}

        double getDeltaV(){
            return thrust*burnTime/mass;
        }

        void printinfo(){
            cout << "Данные ступени\n";
            cout << "Тяга: " << thrust << " Н | " << "Время работы: " << burnTime << " с | " << "Масса: " << mass << " кг\n";
            cout << "Приращение скорости: " << getDeltaV() << "м/с\n";
        }
};

int main(){
    RocketStage s1(5000, 10, 1000);
    RocketStage s2(7000, 8, 900);
    RocketStage s3(9000, 6, 800);
    
    double totalV = s1.getDeltaV()+s2.getDeltaV()+s3.getDeltaV();
    cout << "Итоговая скорость ракеты: " << totalV << "м/с\n";
}