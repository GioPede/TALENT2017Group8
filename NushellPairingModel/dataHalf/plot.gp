#set format x "%.3f"
set format y "%.3f"
set mxtics 5
set mytics 5
set key top right
set grid
set encoding iso_8859_1 
set fit errorvariables
set terminal pngcairo enhanced font 'Times,20' background "#ffffff" fontscale 1.0 dashed size 1280,720
#set terminal pngcairo enhanced font 'Arial, 20' dashed size 1280,720
#set term postscript eps enhanced color "Times-Roman, 32"


set style line 1  linetype 2 linecolor rgb "orange"  linewidth 2.5 pointtype 2 pointinterval 0
set style line 2  linetype 2 linecolor rgb "red"  linewidth 1.2 pointtype 6 pointinterval 0
set style line 3  linetype 2 linecolor rgb "green"  linewidth 1.2 pointtype 2 pointinterval 0
set style line 4  linetype 1 linecolor rgb "blue"  linewidth 1  pointtype 6
set style line 5  linetype 7 linecolor rgb "magenta"  linewidth 0.9 pointtype 2 pointinterval 0


set output 'unbroken.png'
set xrange [-0.5:0.5]
set yrange [0:12]
set xlabel "g"
set ylabel "E"
set title "Pairing Model: FCI (Unbroken Pairs) and NuShellX"
unset key

plot "FCI.dat" u ($1 /2):2 w lines, "FCI.dat" u ($1 /2):3 w lines, "FCI.dat" u ($1 /2):4 w lines, \
     "FCI.dat" u ($1 /2):5 w lines, "FCI.dat" u ($1 /2):6 w lines, "FCI.dat" u ($1 /2):7 w lines, \
     "nush.dat" u ($1 /2):2, "nush.dat" u ($1 /2):3, "nush.dat" u ($1 /2):4, "nush.dat" u ($1 /2):5, "nush.dat" u ($1 /2):6, \
     "nush.dat" u ($1 /2):7, "nush.dat" u ($1 /2):8, "nush.dat" u ($1 /2):9, "nush.dat" u ($1 /2):10, "nush.dat" u ($1 /2):11,\
     "nush.dat" u ($1 /2):12, "nush.dat" u ($1 /2):13, "nush.dat" u ($1 /2):14, "nush.dat" u ($1 /2):15, "nush.dat" u ($1 /2):16, \
     "nush.dat" u ($1 /2):17, "nush.dat" u ($1 /2):18, "nush.dat" u ($1 /2):19, "nush.dat" u ($1 /2):20, "nush.dat" u ($1 /2):21

set output 'one_broken.png'
set xrange [-0.5:0.5]
set yrange [0:12]
set xlabel "g"
set ylabel "E"
set title "Pairing Model: NuShellX, 1 Broken Pair"
unset key

plot "nush.dat" u ($1 /2):2, "nush.dat" u ($1 /2):3 w linespoints, "nush.dat" u ($1 /2):4 w linespoints, "nush.dat" u ($1 /2):5, "nush.dat" u ($1 /2):6, \
     "nush.dat" u ($1 /2):7 w linespoints, "nush.dat" u ($1 /2):8, "nush.dat" u ($1 /2):9, "nush.dat" u ($1 /2):10, "nush.dat" u ($1 /2):11,\
     "nush.dat" u ($1 /2):12, "nush.dat" u ($1 /2):13, "nush.dat" u ($1 /2):14, "nush.dat" u ($1 /2):15 w linespoints, "nush.dat" u ($1 /2):16, \
     "nush.dat" u ($1 /2):17, "nush.dat" u ($1 /2):18 w linespoints, "nush.dat" u ($1 /2):19, "nush.dat" u ($1 /2):20 w linespoints, "nush.dat" u ($1 /2):21

set output 'two_broken.png'
set xrange [-0.5:0.5]
set yrange [0:12]
set xlabel "g"
set ylabel "E"
set title "Pairing Model: NuShellX, 2 Broken Pairs"
unset key

plot "nush.dat" u ($1 /2):2, "nush.dat" u ($1 /2):3, "nush.dat" u ($1 /2):4, "nush.dat" u ($1 /2):5, "nush.dat" u ($1 /2):6, \
     "nush.dat" u ($1 /2):7, "nush.dat" u ($1 /2):8, "nush.dat" u ($1 /2):9, "nush.dat" u ($1 /2):10 w linespoints, "nush.dat" u ($1 /2):11,\
     "nush.dat" u ($1 /2):12, "nush.dat" u ($1 /2):13, "nush.dat" u ($1 /2):14, "nush.dat" u ($1 /2):15, "nush.dat" u ($1 /2):16, \
     "nush.dat" u ($1 /2):17, "nush.dat" u ($1 /2):18, "nush.dat" u ($1 /2):19, "nush.dat" u ($1 /2):20, "nush.dat" u ($1 /2):21


