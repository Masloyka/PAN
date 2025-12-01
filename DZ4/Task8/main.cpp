#include <iostream>
using namespace std;

class NavigationSystem{
    private:
        double X, Y;
        double velocityX, velocityY;
        bool gpsAvailable;

    public:
        NavigationSystem(double x, double y, double velX, double velY, bool avail) : X(x), Y(y), velocityX(velX), velocityY(velY), gpsAvailable(avail) {}

        void integratePosistion(double dt){
            X += velocityX*dt;
            Y += velocityY*dt;
        }

        void correctGPS(double realX, double realY){
            X = (realX+X)/2;
            Y = (realY+Y)/2;
        }

        void printPosition(){
            cout << "Скорректированные координаты: (" << X << "," << Y << ")\n";
        }
};

int main(){
    NavigationSystem nav(0, 0, 100, 50, true);
    nav.integratePosistion(1);
    nav.correctGPS(110, 60);
    nav.printPosition();
}