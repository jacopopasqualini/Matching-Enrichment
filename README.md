Matching-Enrichment

This is a personal project. It creates directed graphs from real data [1], [2] and finds their maximum matching with Hopcroft–Karp algorithm [3]. Once that matched/ unmatched nodes are found they are labelled according to their status. The interest in finding unmatched nodes in complex networks comes from an application of structural control theory to complex networks [4]. Unmatched nodes percentage in E. Coli transcription factors network is reproduced, according to [5]. An enrichment experiment is included, in order to estimate matched nodes subset cardinality deviation from a null model, an Erdos-Renyi network. The maximum matching pattern is strongly enriched in real networks (~34 standard deviations). A python visualization tool is integrated in the c++ code, allowing an easier interpretation of results. Some instructions for software usage can be found in the README file.

DEPENDENCIES:

c++ : armadillo, http://arma.sourceforge.net/

python: numpy, matplotlib, networkx https://networkx.github.io/

REFERENCES:

[1] http://www.weizmann.ac.il/mcb/UriAlon/e-coli-transcription-network 
[2] https://snap.stanford.edu/data/C-elegans-frontal.html
[3] https://www.geeksforgeeks.org/hopcroft-karp-algorithm-for-maximum-matching-set-2-implementation/ 
[4] https://arxiv.org/pdf/1508.05384.pdf 
[5] https://arxiv.org/pdf/1703.00876.pdf
