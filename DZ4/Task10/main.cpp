#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class DroneFlight{
    private:
        vector <double> X, Y;
        double totalDistance;
    public:
        DroneFlight() : X{0}, Y{0}, totalDistance(0) {}

        void addPoint(double newX, double newY){
            X.push_back(newX);
            Y.push_back(newY);
            auto x_square = pow(X[X.size()]- X[X.size()-1], 2);
            auto y_square = pow(Y[Y.size()]- Y[Y.size()-1], 2);
            totalDistance += pow(x_square+y_square, 0.5);
        }
        double getTotalDistance(){
            return totalDistance;
        }

        void PrintPath(){
            cout << "Точки маршрута\n";
            for (int i = 0; i < X.size(); i++){
                cout << "(" << X[i] << ", " << Y[i] << ")\n";
            }
            cout << "Пройдено: " << getTotalDistance() << " м\n";
        }

};

int main(){

    DroneFlight d;
    d.addPoint(3,4);
    d.addPoint(6,8);
    d.PrintPath();
    return 0;
}
