#!/bin/bash
set -e
make -f Makefile

echo $$
./plotter $$

gnuplot -e "set title \"Access frequency\""
gnuplot -e "set xdata time"
gnuplot -e "set format x '%H:%M'"
gnuplot -e "set xlabel \"hours\""
gnuplot -e "set ylabel \"accesses\""
gnuplot -e "set grid"
echo "/tmp/data$$.txt"
gnuplot -e "plot \"/tmp/data$$.txt\""
