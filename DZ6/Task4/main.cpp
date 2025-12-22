#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>

using namespace std;

class Navigator {
public:
    vector<double> t;
    vector<double> x;
    vector<double> y;

    // Метод: загрузка данных из CSV файла
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Не удалось открыть файл: " + filename);
        }

        string line;
        getline(file, line); // Пропускаем заголовок

        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() != 3) continue;

            try {
                double time = stod(tokens[0]);
                double pos_x = stod(tokens[1]);
                double pos_y = stod(tokens[2]);

                t.push_back(time);
                x.push_back(pos_x);
                y.push_back(pos_y);
            } catch (...) {
                cerr << "Ошибка парсинга строки: " << line << endl;
            }
        }

        file.close();
        cout << "Загружено " << t.size() << " точек.\n";
    }

    // Метод: вычисление скоростей по осям
    vector<double> computeVelocityX() const {
        vector<double> vx;
        if (t.size() < 2) return vx;

        for (size_t i = 1; i < t.size(); ++i) {
            double dt = t[i] - t[i-1];
            if (dt == 0) {
                vx.push_back(0.0);
            } else {
                double dx = x[i] - x[i-1];
                vx.push_back(dx / dt);
            }
        }
        return vx;
    }

    vector<double> computeVelocityY() const {
        vector<double> vy;
        if (t.size() < 2) return vy;

        for (size_t i = 1; i < t.size(); ++i) {
            double dt = t[i] - t[i-1];
            if (dt == 0) {
                vy.push_back(0.0);
            } else {
                double dy = y[i] - y[i-1];
                vy.push_back(dy / dt);
            }
        }
        return vy;
    }

    // Метод: вычисление полного модуля скорости
    vector<double> computeTotalVelocity() const {
        vector<double> vx = computeVelocityX();
        vector<double> vy = computeVelocityY();
        vector<double> v;

        size_t n = min(vx.size(), vy.size());
        for (size_t i = 0; i < n; ++i) {
            v.push_back(sqrt(vx[i] * vx[i] + vy[i] * vy[i]));
        }

        return v;
    }

    // Метод: сохранение в файл t,v
    void saveVelocityToFile(const string& filename) const {
        vector<double> v = computeTotalVelocity();

        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Не удалось создать файл: " + filename);
        }

        file << "t,v\n";
        for (size_t i = 0; i < v.size(); ++i) {
            file << t[i+1] << "," << v[i] << "\n"; // v[i] соответствует интервалу [t[i], t[i+1]]
        }

        file.close();
        cout << "Скорости сохранены в файл: " << filename << endl;
    }

    // Метод: построение графика через GNUPlot
    void plotVelocity(const string& outputFilename = "velocity.csv") {
        // Сначала сохраним данные
        saveVelocityToFile(outputFilename);

        // Команда для GNUPlot
        string gnuplotCmd = R"(
set terminal png size 800,600
set output 'velocity_plot.png'
set xlabel 'Время t'
set ylabel 'Скорость v'
set title 'График скорости v(t)'
set grid
plot ')" + outputFilename + R"(' using 1:2 with linespoints lw 2 title 'v(t)'
)";

        // Запись команды в временный файл
        ofstream script("plot.gp");
        script << gnuplotCmd;
        script.close();

        // Запуск GNUPlot
        int result = system("gnuplot plot.gp");
        if (result == 0) {
            cout << "График сохранён как velocity_plot.png\n";
        } else {
            cerr << "Ошибка при вызове GNUPlot. Убедитесь, что он установлен.\n";
        }
    }
};

// Пример использования
int main() {
    try {
        Navigator nav;
        nav.loadFromFile("navigation.csv");

        // Сохраняем файл t,v
        nav.saveVelocityToFile("velocity.csv");

        // Строим график
        nav.plotVelocity();

    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}