# Gnuplot скрипт для визуализации траектории
set terminal png size 800,600
set output 'trajectory_plot.png'
set grid
set xlabel 'Время (с)'
set ylabel 'Параметр'
set title 'Оптимальная траектория'
set key outside right top
plot 'trajectory.csv' using 1:2 with lines title 'Скорость (м/с)', \
     'trajectory.csv' using 1:3 with lines title 'Высота (м)', \
     'trajectory.csv' using 1:4 with lines title 'Расстояние (м)', \
     'trajectory.csv' using 1:5 with lines title 'Расход топлива (кг)'
