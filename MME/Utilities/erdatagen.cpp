#include <iostream> 
#include <iomanip>
#include <string>
#include <armadillo>

using namespace std;
using namespace arma;

void ER_data_generator( int number_of_nodes, int number_of_links, string directory){

double p = (1 - ( (double)number_of_nodes*number_of_nodes - (double)number_of_links )/((double)number_of_nodes*number_of_nodes));

sp_mat ER_ADJ = sprandu(number_of_nodes,number_of_nodes,p);

sp_mat::const_iterator it     = ER_ADJ.begin();
sp_mat::const_iterator it_end = ER_ADJ.end();
for(; it != it_end; ++it){ ER_ADJ( it.row() ,it.col() ) = 1; } 

Network  ER_TF_Regulation( ER_ADJ );
Network* ER_TFR = & ER_TF_Regulation;

set<int> ER_matched_nodes = matched_nodes( ER_TFR );

cout << " If you want to save ER net write its filename, otherwise write 'exit' \n";
string er_sheet;
cin >> er_sheet;

if(er_sheet == "exit")
 return;

DataStream ER_data = ER_datastream_building( ER_ADJ );
ER_data.write_down_data(directory+er_sheet);

cout << "Write ER network unmatched nodes filename: \n";
string erm_sheet;
cin>> erm_sheet;

DataStream ER_match_out_data = matched_nodes_data( ER_matched_nodes, number_of_nodes);
ER_match_out_data.write_down_data(directory+erm_sheet);

return;
}
