#include <iostream>

using namespace std;

class Gyroscope{
    private:
        double angularVelocity;
        bool calibrationRequired;
    public:
        Gyroscope(double vel, bool calib) : angularVelocity(vel), calibrationRequired(calib) {}
        void calibrate(){
            if (calibrationRequired)
                calibrationRequired = false;
            else
                calibrationRequired = true;
        }
        void printStatus(){
            cout << "Скорость: " << angularVelocity << "°/с | ";
            if (calibrationRequired)
                cout << "Калибровка требуется\n";
            else 
                cout << "Калибровка не требуется\n";

        }
};
int main(){
    Gyroscope g1(120.5, true);
    g1.printStatus();
    g1.calibrate();
    g1.printStatus();
}