#include <iostream>
using namespace std;

class Autopilot{
    private:
        double courseAngle;
        double altitude;
    public:
        Autopilot (double course, double alt) : courseAngle(course), altitude(alt) {}
        void changeCourse(double delta){
            if (delta < 0){
                if ((courseAngle + delta) < 0){
                    courseAngle = 360+delta;
                }
                else
                    courseAngle += delta;
                }
            else
                if ((courseAngle + delta) > 360)
                    courseAngle = delta;
                else
                    courseAngle += delta;
        } 
        void changeAltitude(double delta){
            if (delta < 0)
                if (altitude + delta < 0) throw invalid_argument("Высота менньше 0!");
                else
                    altitude += delta;
            else
                altitude += delta;
        }
        void printStatus(){
            cout << "Курс: " << courseAngle << "° | высота: " << altitude << "м\n";
        }
};

int main(){
    Autopilot p(0, 1000);
    p.printStatus();
    p.changeCourse(-10);
    p.changeAltitude(-1000);
    p.changeAltitude(25);
    p.changeCourse(-20);
    p.printStatus();
}