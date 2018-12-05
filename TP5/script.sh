#!/bin/bash

make -f Makefile

./plotter $$

gnuplot <<- EOF
        set terminal canvas
	set output "/tmp/$$.html"
	set style data histogram
	set boxwidth 0.5
	set style fill solid
	set style histogram cluster gap 1
	set title 'Access frequency'
	set xlabel 'hours'
	set xrange [0:24]
	set yrange [0:*]
	set ylabel 'accesses'
	plot "< sort /tmp/data$$.txt" using 2:xtic(1) with boxes
EOF

firefox -new-window "/tmp/$$.html"

make clean

rm /tmp/data$$.txt 

