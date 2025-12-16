#include <iostream>
#include <string>
#include <vector>
class DataValidator{
    private:
        struct Coordinate{
            std::string name;
            double value;
        };
        struct ValidInfo {

            bool valid_coordinate = true;
            std::vector <Coordinate> coordinate;
            bool valid_speed = true;
            double speed_not_valid;
            bool valid_acc = true;
            double acc_not_valid;
            
            int getCountValid(){
                int i = 0;
                if (valid_coordinate == true) i++;
                if (valid_speed == true) i++;
                if (valid_acc == true) i++;
                return i;
            }
        };
        struct Rule
        {
            std::string field_rule;
            double min_value;
            double max_value;
        };
        std::vector <Rule> rules;
        ValidInfo infor;
        
    public:
        void addValidationRule(const std::string& field, double min, double max){
            rules.push_back({field, min, max});
        }
        bool validateCoordinates(double x, double y, double z){
            bool coordinate_check = true;
            for (size_t i = 0; i < rules.size(); i++){
                if(rules[i].field_rule == "x"){
                    if (x > rules[i].max_value || x <rules[i].min_value){
                        coordinate_check = false;
                        Coordinate cur_x = {"X", x};
                        infor.coordinate.push_back(cur_x);
                    }
                }
                if(rules[i].field_rule == "y"){
                    if (y > rules[i].max_value || y <rules[i].min_value){
                        coordinate_check = false;
                        Coordinate cur_y = {"Y", y};
                        infor.coordinate.push_back(cur_y);
                    }
                }
                if(rules[i].field_rule == "z"){
                    if (z > rules[i].max_value || z <rules[i].min_value){
                        coordinate_check = false;
                        Coordinate cur_z = {"Высота", z};
                        infor.coordinate.push_back(cur_z);
                    }
                }
            }
            infor.valid_coordinate = false;
            return coordinate_check;   
        }
        bool validateSpeed(double speed){
            for (size_t i = 0; i < rules.size(); i++){
                if (rules[i].field_rule == "speed"){
                    if(speed > rules[i].max_value || speed < rules[i].min_value){
                        infor.valid_speed = false;
                        infor.speed_not_valid = speed;
                        return false;
                    }
                }
            }
        }
        bool validateAcceleration(double acc){
            for (size_t i = 0; i < rules.size(); i++){
                if (rules[i].field_rule == "acc"){
                    if(acc > rules[i].max_value || acc < rules[i].min_value){
                        infor.valid_speed = false;
                        infor.speed_not_valid = acc;
                        return false;
                    }
                }
            }
        }
        void generateValidationReport(){
            std::cout << "===============================================\n";
            std::cout << "Отчет валидации:\n";
            if (!validateCoordinates){
                std::cout << "Координаты: Ошибка - ";
                for (size_t i = 0; i < infor.coordinate.size(); i++){
                    std::cout << infor.coordinate[i].name << " - " << infor.coordinate[i].value;
                }
                std::cout << "\n";
            }
            if (!validateSpeed){
                    
            }
        }

};