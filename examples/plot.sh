gnuplot -p -e "plot \"$1\" using 1:2 with filledcurves, \"$2\" using 1:2 with filledcurves, \"$3\" using 1:2 with filledcurves" 
