#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
class AltitudeFilter{
    private:
        std::vector<std::pair<double, double>> original_data;
        std::vector<std::pair<double,double>> filter_data;
    public:
        void LoadData(const std::string & filename){
            std::ifstream fin(filename);
            if (!fin.is_open()){
                std::cerr << "Не удалось открыть файл " << filename << "!\n";
            }
            
            std::string line;
            std::getline(fin,line);
            while(std::getline(fin, line)){
                std::stringstream ss(line);
                std::string token;
                std::vector <std::string> tokens;
                
                while (std::getline(ss,token,',')){
                    tokens.push_back(token);
                }

                original_data.push_back(std::make_pair(std::stod(tokens[0]),std::stod(tokens[1])));
            }
            fin.close();
            std::cout << "Данные успешно загружены!\n";
        }

        void SortData(){
            auto isValidHeight = [](const std::pair<double, double>& point) {
                double h = point.second;
                return h > 900.0 && h < 1100.0;
            };
            filter_data.clear();
            for (size_t i = 0; i < original_data.size(); i++){
                // std::copy_if(original_data.begin(), original_data.end(), filter_data.begin(), isValidHeight);
                if (isValidHeight(original_data[i])){
                    filter_data.push_back(original_data[i]);
                }
            }
        }

        void WriteSortData(const std::string& filename){
            std::ofstream fout(filename);
            if (!fout.is_open()){
                std::cerr << "Ошибка! Не удалось создать файл " << filename << "\n";
            }
            // fout << "t,H\n";

            for (const auto& alt : filter_data){
                fout << alt.first << "," << alt.second << "\n";
            }

            fout.close();
            std::cout << "Данные сохранены в файл: " << filename << std::endl;
        }

            void generateGnuplotScript(const std::string& script_filename) {
    std::ofstream script(script_filename);
    if (!script.is_open()) {
        std::cerr << "Ошибка: не удалось создать скрипт " << script_filename << std::endl;
        return;
    }

    // Правильный синтаксис для Gnuplot!
    script << "# Gnuplot script for altitude comparison\n";
    script << "set terminal pngcairo enhanced font 'Arial,10' size 1200,500\n";
    script << "set output 'altitude_comparison.png'\n";
    script << "set grid\n";
    script << "set key outside right\n";
    script << "set xlabel 'Время, с'\n";
    script << "set ylabel 'Высота, м'\n";
    
    // Первый график (слева)
    script << "set multiplot layout 1,2 title 'Сравнение исходных и отфильтрованных данных'\n";
    
    // График 1: Исходные данные
    script << "set title 'Исходные данные'\n";
    script << "plot 'data.txt' using 1:2 with linespoints title 'H(t)'";
    
    // График 2: Отфильтрованные данные
    script << "set title 'Отфильтрованные данные (900 < H < 1100)'\n";
    script << "plot 'filter_data.csv' using 1:2 with linespoints title 'H_{filtered}(t)'";
    
    script << "unset multiplot\n";
    script << "reset\n"; // Важно: сбросить настройки после multiplot

    script.close();
    std::cout << "✅ Скрипт для Gnuplot успешно сохранён: " << script_filename << std::endl;
    std::cout << "   Выполните команду: gnuplot " << script_filename << std::endl;
}
};

int main(){
    AltitudeFilter filter;
    filter.LoadData("data.txt");
    filter.SortData();
    filter.WriteSortData("filter_data.csv");
    filter.generateGnuplotScript("result_plot.gp");
}