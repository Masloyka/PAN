#include <iostream>
using namespace std;

class AutonomousControl{
    private:
        double altitude;
        double thrust;
        double targetAltitude;
    
    public:
        AutonomousControl(double alt, double T, double tarALT) : altitude(alt), thrust(T), targetAltitude(tarALT){}

        void updateControl(){
            if (altitude < targetAltitude)
                thrust += 100;
            else
                thrust -= 100;
        }

        void simulateStep(double dt){
            altitude += thrust/500*dt;
        }

        void PrintStatus(){
            cout << "Высота: " << altitude << "м, " << "Тяга: " << thrust << "Н.\n"; 
        }
};

int main(){
    AutonomousControl ac(0, 2000, 5000);
    for (int i = 0; i < 5; i++){
        ac.updateControl();
        ac.simulateStep(30);
        ac.PrintStatus();
    }
}