#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <any>
#include <sstream>
class TargetManager{
    private:
        struct Target{
            int id;
            std::string name;
            double x, y, z;
            double priority;
            double distance;

        };
        std::vector<Target> targets;
    public:
        void addTarget(int id, const std::string& name, double x, double y, double z, double priority, double distance){
            targets.push_back({id, name, x, y, z, priority, distance});
        }
        bool removeTarget(int target_id){
            for (int i = 0; i < targets.size(); i++){
                if (targets[i].id == target_id){
                    targets.erase(targets.begin()+i-1);
                    return true;
                }
            }
            std::cout << "ID: " << target_id << " не найден!";
            return false;
        }
        void saveTargetsToFile(){
            std::ofstream fout("targets.txt");
            if (!fout.is_open()){
                std::runtime_error("Невозможно открыть файл!");
            }
            fout << std::fixed << std::setw(5) << std::right << "ID "
            << std::setw(10) << "Name " << std::setw(5) << "X " << std::setw(5) << "Y " << std::setw(5) << "Z "
            << std::setw(10) << "Priority " << std::setw(10) << "Distance " << "\n";
            for (int i = 0; i < targets.size(); i++){
                fout  << targets[i].id << "," << targets[i].name << ","<<  targets[i].x << ","
                << targets[i].y << "," <<  targets[i].z << ","  << targets[i].priority<< ","  << targets[i].distance << "\n";

            }
            fout.close();
        }
        void loadTargetsFromFile(){
            std::ifstream fint("targets.txt");
            if (!fint.is_open()){
                std::runtime_error("Ошибка открытия файла!");
            }
            std::vector <std::any> values;
            std::string value;
            std::string line;
            std::getline(fint, line);
            int i = 0;
            while (std::getline(fint, line)){
                std::stringstream ss(line);
                std::getline(ss, value, ',');
                targets[i].id = std::stod(value);
                std::getline(ss, value, ','); targets[i].name = value;
                std::getline(ss, value, ','); targets[i].x = std::stod(value);
                std::getline(ss, value, ','); targets[i].y = std::stod(value);
                std::getline(ss, value, ','); targets[i].z = std::stod(value);
                std::getline(ss, value, ','); targets[i].priority = std::stod(value);
                std::getline(ss, value, ','); targets[i].distance = std::stod(value);
                i++;
            }    
        }
        std::vector <Target> getHighPriorityTargets(double min_priority){
            std::vector <Target> high_targets;
            for (int i = 0; i < targets.size(); i++){
                if (targets[i].priority >= min_priority)
                    high_targets.push_back(targets[i]);
            }
            return high_targets; 
        }
        void SortByDistance(){
            for (int i=0; i< targets.size(); i++){
                for (int j = 0; j < targets.size() - i - 1; j++){
                    if (targets[j].distance > targets[j+1].distance){
                        std::swap(targets[j], targets[j+1]);
                    }
                }
            }
        }
};

int main(){
    TargetManager man;
    man.addTarget(1, "Point1", 2.34, 4.34, 6.56, 0.8, 1000);
    man.addTarget(2, "Point2", 44, 1.34, 5.6, 0.9, 3000);
    man.addTarget(3, "Point3", 2.3324324, 65.323, 75.12, 1, 2000);
    man.saveTargetsToFile();
    man.loadTargetsFromFile();
    man.SortByDistance();
    man.saveTargetsToFile();
    return 0;
}