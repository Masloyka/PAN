#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <memory>
#include <cstdio>

const double MS21_MASS = 70000.0;          // Масса самолета, кг
const double MS21_WING_AREA = 113.0;       // Площадь крыла, м²
const double MS21_NOMINAL_THRUST = 2 * 137200.0; // Суммарная тяга, Н
const double MAX_THRUST_PERCENT = 0.9;     // Реалистичный процент тяги
const double INITIAL_ALTITUDE = 400.0;      // Начальная высота, м
const double FINAL_ALTITUDE = 6500.0;       // Конечная высота, м
const double INITIAL_VELOCITY = 310.0 / 3.6; // Начальная скорость, м/с (340 км/ч)
const double FINAL_VELOCITY = 550.0 / 3.6;  // Конечная скорость, м/с (670 км/ч)
const double GRAVITY = 9.81;               // Ускорение свободного падения, м/с²
const double R_AIR = 287.05;               // Газовая постоянная воздуха, Дж/(кг·К)
const double PI = 3.14159;
class CSVWriter {
private:
    std::ofstream file;

public:
    CSVWriter(const std::string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename);
        }
    }

    ~CSVWriter() {
        if (file.is_open()) file.close();
    }

    void writeRow(const std::vector<double>& row) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << std::setprecision(6) << row[i];
            if (i < row.size() - 1) file << ",";
        }
        file << "\n";
    }

    void writeHeader(const std::vector<std::string>& headers) {
        for (size_t i = 0; i < headers.size(); ++i) {
            file << headers[i];
            if (i < headers.size() - 1) file << ",";
        }
        file << "\n";
    }
};

class TableInterpolator {
private:
    std::vector<double> altitudes;
    std::vector<double> temperatures;
    std::vector<double> pressures;
    std::vector<double> densities;
    std::vector<double> sound_speeds;

    void initializeTableData() {
        altitudes = {0, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
        temperatures = {288.15, 284.9, 281.651, 275.154, 268.659, 262.166, 255.676,
                       249.187, 242.7, 236.215, 229.733, 223.252};
        pressures = {1.01325e5, 9.54613e4, 8.98763e4, 7.95014e4, 7.01212e4, 6.16604e4,
                    5.40483e4, 4.72176e4, 4.11051e4, 3.56516e4, 3.08007e4, 2.64999e4};
        densities = {1.22500, 1.16727, 1.11166, 1.00655, 0.909254, 0.819347, 0.736429,
                    0.660111, 0.590018, 0.526783, 0.467063, 0.413510};
        sound_speeds = {340.294, 338.37, 336.435, 332.532, 328.584, 324.589, 320.545,
                       316.452, 312.306, 308.105, 303.848, 299.532};
    }

public:
    TableInterpolator() {
        initializeTableData();
    }   

    double get_eq_value(double current_altitude, const std::vector<double>& altitude, const std::vector<double>& parametrs) const {
        if (current_altitude <= altitude[0]) return parametrs[0];
        if(current_altitude >= altitude.back()) return parametrs.back();

        for (size_t i = 0; i < altitude.size()-1; i++){
            if (current_altitude >= altitude[i] && current_altitude <= altitude[i+1]){
                double d_value = (parametrs[i+1] - parametrs[i])/(altitude[i+1] - altitude[i]) * current_altitude;
                return parametrs[i+1] + d_value;
            }
        }
        return 0.1;
    }

    double getTemperature(double current_altitude) const { return get_eq_value(current_altitude, altitudes, temperatures); }
    double getPressure(double current_altitude) const { return get_eq_value(current_altitude, altitudes, pressures); }
    double getDensity(double current_altitude) const { return get_eq_value(current_altitude, altitudes, densities); }
    double getSoundSpeed(double current_altitude) const { return get_eq_value(current_altitude, altitudes, sound_speeds); }
    double getMach(double V, double current_altitude) const { return V / getSoundSpeed(current_altitude); }
};

class TrajectoryPoint {
public:
    double time;        // Время, с
    double x;           // Горизонтальная координата, м
    double y;           // Высота, м
    double V;           // Скорость, м/с
    double Vx;          // Горизонтальная скорость, м/с
    double Vy;          // Вертикальная скорость, м/с
    double theta;       // Угол наклона траектории, рад
    double alpha;       // Угол атаки, рад
    double fuel;        // Итоговое количество потраченного топлива, кг
    double mass;        // Масса, кг
    double acceleration;// Ускорение, м/с²
    double mach;        // Число Маха

    TrajectoryPoint(double t = 0, double X = 0, double Y = 0, double vel = 0,
                   double V_X = 0, double V_Y = 0, double thet = 0, double alp = 0,
                   double f = 0, double m = MS21_MASS, double acc = 0, double mch = 0)
        : time(t), x(X), y(Y), V(vel), Vx(V_X), Vy(V_Y), theta(thet), alpha(alp),
          fuel(f), mass(m), acceleration(acc), mach(mch) {}

    void print() const {
        std::cout << "Текущая точка\n";
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "t=" << time << "с, H=" << y << "м, V=" << V*3.6 << "км/ч, ";
        std::cout << "Vy=" << Vy << "м/с, θ=" << theta*180/PI << "°";
        std::cout << ", масса=" << mass << "кг" << std::endl;
    }
};

class Trajectory {
private:
    std::vector<TrajectoryPoint> points;

public:
    Trajectory() {}

    void addPoint(const TrajectoryPoint& point) { 
        points.push_back(point); 
    }
    const std::vector<TrajectoryPoint>& getPoints() const {
         return points; 
    }
    double getTotalTime() const { 
        return points.empty() ? 0 : points.back().time; 
    }
    double getTotalFuel() const { 
        return points.empty() ? 0 : points.back().fuel; 
    }

    void saveToCSV(const std::string& filename) {
        CSVWriter csv(filename);
        csv.writeHeader({"time_s", "altitude_m", "velocity_ms", "velocity_kmh",
                        "vertical_velocity_ms", "theta_deg", "alpha_deg",
                        "fuel_kg", "mass_kg", "acceleration_ms2", "mach_number"});

        for (const auto& point : points) {
            std::vector<double> row_data = {
                point.time, point.y, point.V, point.V * 3.6,
                point.Vy, point.theta * 180/PI, point.alpha * 180/PI,
                point.fuel, point.mass, point.acceleration, point.mach
            };
            csv.writeRow(row_data);
        }

        std::cout << "Траектория сохранена в файл: " << filename << std::endl;
    }

    void plotTrajectory() const {
        FILE* gp = _popen("\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\" -persist", "w");
        if (!gp) {
            std::cerr << "Ошибка" << std::endl;
            return;
        }

        fprintf(gp, "set terminal wxt size 1200,800 font 'Arial,12'\n");
        fprintf(gp, "set multiplot layout 2,2 title 'Параметры полета МС-21'\n");

        // Высота от времени
        fprintf(gp, "set title 'Высота от времени'\n");
        fprintf(gp, "set xlabel 'Время, с'\n");
        fprintf(gp, "set ylabel 'Высота, м'\n");
        fprintf(gp, "set grid\n");
        fprintf(gp, "plot '-' with lines lw 2 lc 'blue' title 'Высота'\n");
        for (const auto& point : points) {
            fprintf(gp, "%f %f\n", point.time, point.y);
        }
        fprintf(gp, "e\n");
        // Скорость от времени
        fprintf(gp, "set title 'Скорость от времени'\n");
        fprintf(gp, "set xlabel 'Время, с'\n");
        fprintf(gp, "set ylabel 'Скорость, км/ч'\n");
        fprintf(gp, "set grid\n");
        fprintf(gp, "plot '-' with lines lw 2 lc 'red' title 'Скорость'\n");
        for (const auto& point : points) {
            fprintf(gp, "%f %f\n", point.time, point.V * 3.6);
        }
        fprintf(gp, "e\n");
        fprintf(gp, "unset multiplot\n");
        fflush(gp);
        std::cout << "Закройте окно Gnuplot чтобы продолжить" << std::endl;
        std::cin.get();
        _pclose(gp);
    }
};

class Aircraft {
private:
    double wing_area;
    double initial_mass;
    TableInterpolator env;

public:
    double mass;
    double thrust;      // Тяга, Н
    double fuel_flow;   // Расход топлива, кг/с
    double Cx0;         // Коэффициент сопротивления при нулевой подъемной силе
    double K;           // Коэффициент индуктивного сопротивления
    double Cy_max;      // Максимальный коэффициент подъемной силы

    Aircraft(double m = MS21_MASS, double wing = MS21_WING_AREA)
        : wing_area(wing), initial_mass(m), env(), mass(m) {

        thrust = MS21_NOMINAL_THRUST * MAX_THRUST_PERCENT;
        fuel_flow = 0.69; // кг/с - при крейсерском движении
        Cx0 = 0.0275;
        K = 0.05;
        Cy_max = 1.1;
    }

    // Коэффициент подъемной силы в зависимости от угла атаки
    double getLiftCoefficient(double alpha) const {
        // Упрощенная линейная зависимость до сваливания
        double Cl_alpha = 5.0; // Производная по углу атаки
        return std::min(Cl_alpha * alpha, Cy_max);
    }

    // Коэффициент сопротивления в зависимости от коэффициента подъемной силы
    double getDragCoefficient(double Cl) const {
        // Параболическая поляра
        return Cx0 + K * Cl * Cl;
    }

    // Подъемная сила
    double computeLiftForce(double V, double H, double alpha) const {
        double rho = env.getDensity(H);
        double q = 0.5 * rho * V * V;
        double Cl = getLiftCoefficient(alpha);
        return Cl * wing_area * q;
    }

    // Сила сопротивления
    double computeDragForce(double V, double H, double alpha) const {
        double rho = env.getDensity(H);
        double q = 0.5 * rho * V * V;
        double Cl = getLiftCoefficient(alpha);
        double Cd = getDragCoefficient(Cl);
        return Cd * wing_area * q;
    }

    TrajectoryPoint updateState(const TrajectoryPoint& current, double dt, double alpha_control) {
        TrajectoryPoint next = current;

        // Ограничение угла атаки 0.26 рад ~ 15 градусов, информация взята из Открытых источников
        // -0.1 рад ~ -5 градусов, информация из открытых источников
        alpha_control = std::max(-0.1, std::min(0.26, alpha_control));

        
        double lift = computeLiftForce(current.V, current.y, alpha_control);
        double drag = computeDragForce(current.V, current.y, alpha_control);

        double Fx = thrust - drag - mass * GRAVITY * sin(current.theta);
        double Fy = lift - mass * GRAVITY * cos(current.theta);

        
        double ax = Fx / mass;
        double ay = Fy / mass;
        // Выполняем пересчет параметров самолета
        next.V = current.V + ax * dt;
        next.V = std::max(100.0, next.V); 

        if (next.V > 0) {
            // угол наклона траектории это арктангенс горизонтального ускорения к вертикальному ускорению
            next.theta = atan2(ay, ax + GRAVITY * sin(current.theta)); 
        }

        next.theta = std::max(-0.3, std::min(0.3, next.theta));
        next.Vx = next.V * cos(next.theta);
        next.Vy = next.V * sin(next.theta);
        next.x = current.x + next.Vx * dt;
        next.y = current.y + next.Vy * dt;

        // Предотвращение удара о землю, путем задания минимально возможной высоты и маскимально возможной вертикальной скорости
        if (next.y < 0) {
            next.y = 10.0;
            next.Vy = std::max(0.0, next.Vy);
        }

        next.alpha = alpha_control;
        next.mach = env.getMach(next.V, next.y);
        next.acceleration = ax;
        double dfuel = fuel_flow * dt;
        next.fuel = current.fuel + dfuel;
        next.mass = current.mass - dfuel;

        // Изменяем тягу, в следствии изменения массы ЛА
        thrust = MS21_NOMINAL_THRUST * MAX_THRUST_PERCENT * (next.mass / initial_mass);

        next.time = current.time + dt;

        return next;
    }

    double getInitialMass() const { return initial_mass; }
};


class DynamicProgrammingSolver {
public:
    DynamicProgrammingSolver() {}

    Trajectory computeOptimalTrajectory(Aircraft& ac, double time_max = 600.0) {
        Trajectory trajectory;
        double dt = 1.0; 

        TrajectoryPoint start;
        start.time = 0;
        start.x = 0;
        start.y = INITIAL_ALTITUDE;
        start.V = INITIAL_VELOCITY;
        start.Vx = INITIAL_VELOCITY;
        start.Vy = 5.0; // Начальная вертикальная скорость 5 м/с
        start.theta = 0.05; // Начальный угол 3 градуса
        start.alpha = 0.03;
        start.fuel = 0;
        start.mass = ac.getInitialMass();
        start.acceleration = 0;

        TableInterpolator env;
        start.mach = env.getMach(start.V, start.y);

        TrajectoryPoint current = start;
        trajectory.addPoint(current);

        std::cout << "Целевая высота: " << FINAL_ALTITUDE << "м" << std::endl;
        std::cout << "Целевая скорость: " << FINAL_VELOCITY*3.6 << "км/ч" << std::endl;
        std::cout << "Время моделирования: " << time_max << "с" << std::endl << std::endl;

        int step = 0;
        bool target_reached = false;

        while (current.time < time_max && !target_reached) {
            step++;
            double alpha_control;
            double height_ratio = current.y / FINAL_ALTITUDE;

            if (height_ratio < 0.3) {
                alpha_control = 0.06; // Набор высоты
            } else if (height_ratio < 0.7) {
                alpha_control = 0.04; // Крейсерский набор
            } else {
                alpha_control = 0.02; // Вывод на высоту
            }

            if (current.V < FINAL_VELOCITY * 0.9) {
                alpha_control -= 0.01;
            }

            current = ac.updateState(current, dt, alpha_control);
            trajectory.addPoint(current);
            // Добавим вывод промежуточного состояния моделирования полета МС-21
            if (step % 10 == 0) {
                std::cout << "t=" << current.time << "с: ";
                std::cout << "H=" << current.y << "м, ";
                std::cout << "V=" << current.V*3.6 << "км/ч, ";
                std::cout << "Vy=" << current.Vy << "м/с, ";
                std::cout << "θ=" << current.theta*180/PI << "°" << std::endl;
            }

            // Проверка достижения заданной высоты
            if (current.y >= FINAL_ALTITUDE) {
                target_reached = true;
                std::cout << std::endl << "ЦЕЛЕВАЯ ВЫСОТА ДОСТИГНУТА!" << std::endl;
            }

           if (current.y > 20000 || current.V > 1000) {
                std::cout << "✗ Прервано: значения не соответствуют реальности." << std::endl;
                break;
            }
        }
        std::cout << "Высота: " << current.y << " м (" << (current.y/FINAL_ALTITUDE*100) << "% от цели)" << std::endl;
        std::cout << "Скорость: " << current.V*3.6 << " км/ч" << std::endl;
        std::cout << "Время: " << current.time << " с" << std::endl;
        std::cout << "Расход топлива: " << current.fuel << " кг" << std::endl;
        std::cout << "Число Маха: " << current.mach << std::endl;
        return trajectory;
    }
};

int main() {

    try {
        Aircraft ms21;
        DynamicProgrammingSolver solver;
        Trajectory trajectory = solver.computeOptimalTrajectory(ms21, 600.0);
        trajectory.saveToCSV("ms21_trajectory_realistic.csv");
        trajectory.plotTrajectory();
    } catch (const std::exception& e) {
        std::cerr << "ОШИБКА: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
