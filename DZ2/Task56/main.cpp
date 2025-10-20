#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Point {
    double x, y, z;
};

int main(){
    const double Vx= 30, Vy = 20, Vz = 40, dt = 1.0, t_max = 100.0; 
    double x, y, z;
    size_t count = 0;
    vector <Point> traj;
    traj.reserve((int) t_max);
    cout << "Таблица времени и координат\n";
    cout << setw(5) << 't';
    cout << setw(5)<<'x'; 
    cout << setw(5) <<'y'; 
    cout <<  setw(5) <<'z\n';
    for (double t = 0.0; t <= t_max; t += dt){
        x += Vx * dt;
        y += Vy * dt;
        z += Vz * dt;
        traj.push_back({x, y, z});
        cout << setw(5) << t;
        cout << setw(5) << traj[count].x;
        cout << setw(5) << traj[count].y;
        cout << setw(5) << traj[count].z << endl;
        count++;
    }
    
}