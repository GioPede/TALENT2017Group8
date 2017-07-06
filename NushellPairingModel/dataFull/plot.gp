#set format x "%.3f"
set format y "%.3f"
set mxtics 5
set mytics 5
set key top right
set grid
set encoding iso_8859_1 
set fit errorvariables
#set terminal pngcairo enhanced font 'Times,20' background "#ffffff" fontscale 1.0 dashed size 1280,720
#set terminal pngcairo enhanced font 'Arial, 20' dashed size 1280,720
set term postscript eps  size 6,4.5 enhanced color "Times-Roman, 25"


set style line 1  linetype 2 linecolor rgb "orange"  linewidth 2.5 pointtype 2 pointinterval 0
set style line 2  linetype 2 linecolor rgb "red"  linewidth 1.2 pointtype 6 pointinterval 0
set style line 3  linetype 2 linecolor rgb "green"  linewidth 1.2 pointtype 2 pointinterval 0
set style line 4  linetype 1 linecolor rgb "blue"  linewidth 1  pointtype 6
set style line 5  linetype 7 linecolor rgb "magenta"  linewidth 0.9 pointtype 2 pointinterval 0


set output 'unbroken.eps'
set xrange [-1:1]
set yrange [0:14]
set xlabel "g"
set ylabel "E"
set title "Pairing Model: FCI (Unbroken Pairs) and NuShellX"
unset key

plot "nush.dat" u ($1):2, "nush.dat" u ($1):3, "nush.dat" u ($1):4, "nush.dat" u ($1):5, "nush.dat" u ($1):6, \
     "nush.dat" u ($1):7, "nush.dat" u ($1):8, "nush.dat" u ($1):9, "nush.dat" u ($1):10, "nush.dat" u ($1):11,\
     "nush.dat" u ($1):12, "nush.dat" u ($1):13, "nush.dat" u ($1):14, "nush.dat" u ($1):15, "nush.dat" u ($1):16, \
     "nush.dat" u ($1):17, "nush.dat" u ($1):18, "nush.dat" u ($1):19, "nush.dat" u ($1):20, "nush.dat" u ($1):21, \
	 "FCI.dat" u ($1):2 ls 2 w lines, "FCI.dat" u ($1):3 w lines, "FCI.dat" u ($1):4 w lines, \
     "FCI.dat" u ($1):5 w lines, "FCI.dat" u ($1):6 w lines, "FCI.dat" u ($1):7 w lines, \

set output 'one_broken.eps'
set xrange [-1:1]
set yrange [0:14]
set xlabel "g"
set ylabel "E"
set title "Pairing Model: NuShellX, 1 Broken Pair"
unset key

plot "nush.dat" u ($1):2, "nush.dat" u ($1):3 w linespoints, "nush.dat" u ($1):4 w linespoints, "nush.dat" u ($1):5, "nush.dat" u ($1):6, \
     "nush.dat" u ($1):7 w linespoints, "nush.dat" u ($1):8, "nush.dat" u ($1):9, "nush.dat" u ($1):10, "nush.dat" u ($1):11,\
     "nush.dat" u ($1):12, "nush.dat" u ($1):13, "nush.dat" u ($1):14, "nush.dat" u ($1):15 w linespoints, "nush.dat" u ($1):16, \
     "nush.dat" u ($1):17, "nush.dat" u ($1):18 w linespoints, "nush.dat" u ($1):19, "nush.dat" u ($1):20 w linespoints, "nush.dat" u ($1):21

set output 'two_broken.eps'
set xrange [-1:1]
set yrange [0:14]
set xlabel "g"
set ylabel "E"
set title "Pairing Model: NuShellX, 2 Broken Pairs"
unset key

plot "nush.dat" u ($1):2, "nush.dat" u ($1):3, "nush.dat" u ($1):4, "nush.dat" u ($1):5, "nush.dat" u ($1):6, \
     "nush.dat" u ($1):7, "nush.dat" u ($1):8, "nush.dat" u ($1):9, "nush.dat" u ($1):10 w linespoints, "nush.dat" u ($1):11,\
     "nush.dat" u ($1):12, "nush.dat" u ($1):13, "nush.dat" u ($1):14, "nush.dat" u ($1):15, "nush.dat" u ($1):16, \
     "nush.dat" u ($1):17, "nush.dat" u ($1):18, "nush.dat" u ($1):19, "nush.dat" u ($1):20, "nush.dat" u ($1):21


