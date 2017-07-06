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


set output 'exercise3.png'
#set xrange [0:200]
#set yrange [-0.2:0.2]
set xlabel "N"
set ylabel "rms(N)-rms(N-1)"
set title "Brix-Kopferman plot"
unset key

datafile = 'output.dat'
stats datafile
plot for [IDX=1:STATS_blocks] datafile index (IDX-1) u 1:2 w lines 

