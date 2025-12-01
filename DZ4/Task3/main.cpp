#include <iostream>
using namespace std;
class Engine{
    private:
        double thrust;
        double fuelFlow;
    public:
        Engine(double T, double F) : thrust(T), fuelFlow(F) {}

        double getSpecificlImpulse(){
            return thrust / (fuelFlow*9.81);
        }
        void PrintInfo(){
            cout << "Тяга: " << thrust << " Н" << " | Расход: " << fuelFlow << " кг/с | Удельный импульс: " << getSpecificlImpulse() << " c\n";
        }
};

int main(){
    Engine e1(5000, 2.5);
    e1.PrintInfo();
}