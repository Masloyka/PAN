# Gnuplot script for altitude comparison
set terminal pngcairo enhanced font 'Arial,10' size 1200,500
set output 'altitude_comparison.png'
set grid
set key outside right
set xlabel 'Время, с'
set ylabel 'Высота, м'
set multiplot layout 1,2 title 'Сравнение исходных и отфильтрованных данных'
set title 'Исходные данные'
plot 'data.txt' using 1:2 with linespoints title 'H(t)'set title 'Отфильтрованные данные (900 < H < 1100)'
plot 'filter_data.csv' using 1:2 with linespoints title 'H_{filtered}(t)'unset multiplot
reset
