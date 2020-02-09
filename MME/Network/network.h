#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>

#include <armadillo>

using namespace std;
using namespace arma;

#ifndef Network_h
#define Network_h
  
class Network 
{ 
public: 

    Network( int number_of_nodes );
    Network( sp_mat m );

    //Network( string mode, int number_of_nodes, int number_of_links );
    
   ~Network();

    void    add_link( int row, int column, double weight);

    double get_link( int row, int column);
    int    get_number_of_nodes();
    int    get_number_of_links();

    sp_mat get_adjagency();
    
    int    in_degree( int n );
    int    out_degree( int n);
    double average_deg();
    
    double self_loop_number();

    void   print();
    
private:

    sp_mat adjagency;
    int n_nodes;
    int n_links;
};

#endif
