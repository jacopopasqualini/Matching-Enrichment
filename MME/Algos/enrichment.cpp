#include<bits/stdc++.h> 
#include <stdlib.h>     /* srand, rand */
#include <typeinfo>
#include <armadillo>
#include <math.h>       /* sqrt */

//#include "bipg.h"
#include "bipg.cpp"

using namespace std; 
using namespace arma;

//-------------------------------------------------------------------------------------------------
// EXPERIMENT WITH ER ENSEMBLE

void enrichment_experiment( int ensemble_size, int n_nodes, int number_of_links, 
                            int maximum_match_size, 
                            int real_self_loops, double real_avg_deg) // double real_out_deg, double realt_ind_deg )
{ 

if(ensemble_size == 0){ cout << "\n 0 experiemnts performed \n"; return; }

// 
// INITIALIZATIONS

double p = (1 - ( (double)n_nodes*n_nodes - (double)number_of_links )/((double)n_nodes*n_nodes));

double nn = (double)n_nodes;
double es = (double)ensemble_size;

double random_controllability = 0.0;

int*   samples                = new int[ensemble_size];
double average_match_size     = 0.0;
double standard_deviation     = 0.0;
int    s                      = 0; // match size initialized to zero


int* ER_self_loop   = new int[ensemble_size];
double sl_mean      = 0.0;
double sl_sigm      = 0.0;
double d_sl         = 0.0; // dummy variable


double* ER_deg_list = new double[ensemble_size]; // ER_deg_list
double  ER_avg_deg  = 0.0; // ER_avg_deg
double  ER_sigm_deg = 0.0; // ER_sigm_deg
double  d           = 0.0; // d


// 
// ALGORITHM

for(int i=0; i<ensemble_size; i++){
 
    arma_rng::set_seed_random();

    sp_mat ER_ME = sprandu(n_nodes,n_nodes,p);
    BipGraph ER_BG(n_nodes,n_nodes);

    sp_mat::const_iterator it     = ER_ME.begin();
    sp_mat::const_iterator it_end = ER_ME.end();

	for(; it != it_end; ++it){ ER_BG.addEdge( it.row() ,it.col() ); } 

	   set<int> matched_nodes = ER_BG.hopcroftKarp();
	   s = matched_nodes.size();

	   samples[i] = s;  
	   average_match_size+= s;

     Network ER_NET( ER_ME );
     it = ER_ME.begin();

  for(; it != it_end; ++it){ ER_NET.add_link( it.row() ,it.col(), 1); }

     d_sl = ER_NET.self_loop_number();
     ER_self_loop[i] = d_sl;
     sl_mean += d_sl;

     
     d = ER_NET.average_deg();
     ER_deg_list[i] = d;
     ER_avg_deg += d; 
}

// 
// STATISTICS

average_match_size = average_match_size/es;

// standard deviations
for(int i=0; i<ensemble_size; i++){

  standard_deviation += pow(average_match_size - samples[i], 2);
  sl_sigm  +=           pow(sl_mean - ER_self_loop[i], 2);
  ER_sigm_deg +=        pow(ER_avg_deg - ER_deg_list[i], 2);
  
}

// 
// PRINT RESULTS
cout << "\n                                                --- RESULTS  \n \n \n";


random_controllability = 1 - (nn - average_match_size)/nn;
cout << "                 Controllability in random ER networks  : " << random_controllability << "\n";

standard_deviation = sqrt(standard_deviation/es);
double enrichment = (maximum_match_size - average_match_size)/standard_deviation;
cout << "                 Enrichment of maximum matching pattern : " << enrichment << "\n";

sl_mean = sl_mean/es;
sl_sigm = sqrt(sl_sigm/es); 
double sl_enrichment = abs(real_self_loops - sl_mean); //sl_sigm;
cout << "                 Deviation of self-loop motif           : " << sl_enrichment << "\n";


ER_sigm_deg = sqrt(ER_sigm_deg/es); 
ER_avg_deg = ER_avg_deg/es;
double deg_enrichment = abs(real_avg_deg - ER_avg_deg); //ER_sigm_deg;
cout << "                 Deviation in average degree            : " << deg_enrichment << "\n";


delete[] samples;
delete[] ER_self_loop;
delete[] ER_deg_list;

return; 
} 

//-------------------------------------------------------------------------------------------------
// MATCHED NODES DETECTION

set<int> matched_nodes( Network* net) // poi sarà una lista dei nodi unmatched
{ 
int n_nodes = net->get_number_of_nodes();

sp_mat ADJ = net->get_adjagency();

BipGraph g(n_nodes,n_nodes);

sp_mat::const_iterator it     = ADJ.begin();
sp_mat::const_iterator it_end = ADJ.end();

for(; it != it_end; ++it){
   g.addEdge( it.row() ,it.col() ); // shift for unmatched nodes detection
   }


set<int> matched_nodes = g.hopcroftKarp();

return matched_nodes; 
} 



















