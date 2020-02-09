RUN COMMAND (Ubuntu 18.04):

g++ -std=c++11 mainX.cpp -larmadillo -o out

DEPENDENCIES:

c++ : armadillo
http://arma.sourceforge.net/

python: numpy, matplotlib, networkx
https://networkx.github.io/

Pay attention to: 

1) before running the program modify the file:
MME/DataVisualization/netvis.cpp
updating the variable 'visualization_path' to fit with your directories system.

2) whet you save random networks their labels will allways start from 0 this will allow you to correctly visualize the net

E COLI PATH, DATA SOURCE ( main1 )

http://www.weizmann.ac.il/mcb/UriAlon/e-coli-transcription-network


C ELEGANS PATH, DATA SOURCE ( main2 )

https://snap.stanford.edu/data/C-elegans-frontal.html


ECOLI NET 2
https://www.inetbio.org/ecolinet/downloadnetwork.php
