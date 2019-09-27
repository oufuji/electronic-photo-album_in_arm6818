



sprintf(s,"./mplayer -quiet -slave -input file=/tmp/fifo\
 -geometry 0:150-zoom -x 800 -y 250 1.mp4& ");
system(s);