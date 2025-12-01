#include <iostream>

using namespace std;

class Sensor {
private:
    double signalStrength;
    bool isActive;
public:
    Sensor(double strength) : signalStrength(strength), isActive(true){}
    void activate(){
        isActive = true;
    }
    void deactivate(){
        isActive = false;
    }
    void setSignalStrengh(double s){
        if (s < 0)
            signalStrength = 0;
        else
            signalStrength = s;
    }

    double getSignalStrenth(){
        return signalStrength;
    }

    void PrintStatus(){
        cout << "Текущее состояние Датчика\n";
        if (isActive == true)
            cout << "Датчик активен " << "| Сила сигнала: " << signalStrength << " дБ\n";
        else
            cout << "Датчик выключен " << "| Сила сигнала: " << signalStrength << " дБ\n";
    }

};

int main(){
    Sensor s1(43);
    s1.PrintStatus();
    s1.deactivate();
    s1.setSignalStrengh(-2);
    auto current = s1.getSignalStrenth();
    cout << current;
    s1.PrintStatus();
    return 0;
}