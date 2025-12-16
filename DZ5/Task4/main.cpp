#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
class WaypointManager{
    private:
        struct Point
        {
           int id;
           double x, y, z;
           double speed;
           std::string description;
        };
        Point current_waypoint;
        std::vector <Point> points;
    public:
        void addWaypoint(int id, double x, double y, double z, double speed, const std::string& desc){
            points.push_back({id, x, y, z, speed, desc});
            if (points.size() == 1){
                current_waypoint = {points[0]};
            }
            std::cout << "Точка " << id << " добавлена в маршрут." << std::endl;
        }

        bool saveRoute(){
            std::ofstream fout("waypoints.txt");
            if (!fout.is_open()){
                std::runtime_error("Ошибка открытия файла!");
                return true;
            }
            for (int i = 0; i < points.size(); i++){
                fout << points[i].id << "," << points[i].x << "," << points[i].y << "," << points[i].z << "," << points[i].speed << ","
                << points[i].description << "\n";
            }
            std::cout << "Точки успешно записаны в файл!\n";
            fout.close();
            
            return true;
        }
        bool loadRoute(){
            std::ifstream fin("waypoints.txt");
            if (!fin.is_open()){
                std:: runtime_error("Ошибка при открытии файла!");
                return false;
            }
            std::string value;
            std::string line;
            int i = 0;
            while (std::getline(fin, line)){
                std::stringstream ss(line);
                std::getline(ss, value, ','); points[i].id = std::stod(value);
                std::getline(ss, value, ','); points[i].x = std::stod(value);
                std::getline(ss, value, ','); points[i].y = std::stod(value);
                std::getline(ss, value, ','); points[i].z = std::stod(value);
                std::getline(ss, value, ','); points[i].speed = std::stod(value);
                std::getline(ss, value, ','); points[i].description = value;
                std::cout <<  "Загруженые данные\n";
                std::cout << "ID: " << points[i].id << "\tX: " << points[i].x << "\tY: " << points[i].y << "\tZ: " << points[i].z
                << "\tSpeed: " << points[i].speed << "\tDescription: " << points[i].description << "\n"; 
                i++;
            }
            // std::cout << "Маршрут загружен: " << i << " точек\n";
            fin.close();
            std::cout << "Маршрут загружен: " << i << " точек\n";
            return true;
        }
        double CalculateTotalDistance(){
            double TotalDistance;
            for (int i = 0; i < points.size()-1; i++){
                double square_x = std::pow(points[i].x - points[i+1].x, 2);
                double square_y = std::pow(points[i].y - points[i+1].y, 2);
                double square_z = std::pow(points[i].z - points[i+1].z, 2);
                TotalDistance += std::pow(square_x+square_y+square_z, 0.5);
            }
            if (TotalDistance == 0){
                std::cout << "Невозможно рассчитать расстояние, не хватает точек!";
                return TotalDistance;
            }
            std::cout << "Общее расстояние: " << TotalDistance << " метров\n";
            return TotalDistance;
        }
        Point getCurrentWaypoint(){
            return current_waypoint;
        }
        Point getNextWaypoint(){
            for (int i = 0; i < points.size(); i++){
                std::cout << "Текущая точка: " << current_waypoint.description << "( " << current_waypoint.x << ", " << current_waypoint.y
                << ", " << current_waypoint.z << ")\n";
                if (current_waypoint.id == points[i].id){
                    if (i == points.size()){
                        std::cout << "Следующая точка: " << points[i].description << "( " << points[i].x << ", " << points[i].y
                << ", " << points[i].z << ")\n";
                        return points[i];
                    }
                    else{
                        std::cout << "Следующая точка: " << points[i+1].description << "( " << points[i+1].x << ", " << points[i+1].y
                << ", " << points[i+1].z << ")\n";
                        return points[i+1];
                    }
                }
            }
            return current_waypoint;
        }
};

int main(){
    WaypointManager way_man;
    way_man.addWaypoint(1,0.0,0.0,100.0,25.0,"Start");
    way_man.addWaypoint(2,100.0,50.0,150.0,30.0,"CheckpointA");
    way_man.addWaypoint(3,200.0,100.0,200.0,35.0,"CheckpointB");
    bool save = way_man.saveRoute();
    bool load = way_man.loadRoute();
    double total = way_man.CalculateTotalDistance();
    way_man.getNextWaypoint();
}