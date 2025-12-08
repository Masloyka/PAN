#include <iostream>
using namespace std;
class Engine{
    private:
        double thrust;
        double fuelFlow;
        double fuel;
    public:
        Engine(double T, double FuelF, double F) : thrust(T), fuelFlow(FuelF), fuel(F) {}
        double getThrust(){
            return thrust;
        }
        void setTrust(double T){
            thrust = T;
        }
        bool hasFuel(){
            return thrust > 0;
        }
        double getFuel(){
            return fuel;
        }
        void burn(double dt){
                fuel -= fuelFlow*dt;
        }

};

class Navigation{
    private:
        double altitude;
        double velocity;
        double acceleration;
        double mass;
    public:
        Navigation(double alt, double vel, double acc, double m) : altitude(alt), velocity(vel), acceleration(acc), mass(m) {}
        
        void update(double thrust, double dt){
            acceleration = thrust/mass - 9.81;
            if (acceleration <= 0 && altitude == 0){
                acceleration = 0;
            }
            else{
                velocity += acceleration * dt;
                altitude += velocity * dt;
            }
        }
        double getALT(){
            return altitude;
        }
        void PrintStatus(double time){
            cout << "t=" << time << " с "<< "| h=" << altitude << " м |" << " v= " << velocity << " м/c |" << " a=" << acceleration << "м/с^2\n";
        }

};

class AutonomousFlightSystem{
    private:
        Engine engine;
        Navigation nav;
        double time;
    public:
        AutonomousFlightSystem(Engine eng, Navigation n, double t): engine(eng), nav(n), time(t) {}
        void simulate(double dt, double TotalTime){
            while (time < TotalTime && engine.hasFuel() == true)
            {
                if (engine.getFuel() > 0){
                    engine.burn(dt);
                    nav.update(engine.getThrust(), dt);
                    nav.PrintStatus(time);
                }
                else {
                    nav.update(0, dt);
                    if (nav.getALT() <= 0){
                        cout << "Ракета упала!\n";
                        break;
                    }
                    nav.PrintStatus(time);
                }
                time += dt;
            }
            
        }

        void printSummary(){
            cout << "Итоговые текущие параметры\n";
            double current_alt =  (nav.getALT() > 0) ?  nav.getALT() : 0;
            cout << "Высота: " << current_alt << " м | " << "Топливо: " << engine.getFuel() << " кг\n";
            if (engine.getFuel() <= 0)
                cout << "--- Полет завершен ---\nОставшееся топливо: 0 кг.";
        }
};

int main(){
    Engine engine(500000, 10000, 100000);
    Navigation nav(0, 0, 0, 10000);
    AutonomousFlightSystem sys(engine, nav, 0);

    sys.simulate(1, 130);
    sys.printSummary();
    return 0;
    
}