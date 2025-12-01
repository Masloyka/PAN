#include <iostream>
using namespace std;

class FlightComputer{
    private:
        double altitude;
        double velocity;
        double fuel;
        double thrust;
    
        public:
            double time = 0;
            FlightComputer(double alt, double vel, double f, double t) : altitude(alt), velocity(vel), fuel(f), thrust(t) {}
            void simulateStep(double dt){
                velocity += (thrust/1000 - 9.8) *dt;
                altitude += velocity* dt;
                fuel -= dt * 2;
                time += dt;
            }
            void printStatus(){
                cout << "Текущие значения\n";
                cout << "t=" << time << "c: " << "высота=" << altitude << "м, " << "скорость=" << velocity << "м/с, " << "топливо=" << fuel << "кг\n";
            }
};

int main(){
    FlightComputer fl(0,0,100,12000);
    for (int i = 0; i < 5; i++){
        fl.simulateStep(0.1);
        fl.printStatus();
    }
}