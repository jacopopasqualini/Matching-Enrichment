// RUN INSTRUCTIONS:
// cd Desktop/SCBIO/oop
// g++ -std=c++11 alon.cpp -larmadillo -o out

#include <iostream> 
#include <iomanip>
#include <string>
#include <chrono>
#include <armadillo>

// objects
#include "Datastream/datastream.cpp"
#include "Network/network.cpp"

// algorithms and utilities
#include "Network/netbuild.cpp"
#include "Datastream/buildata.cpp"
#include "Algos/enrichment.cpp"
#include "DataVisualization/netvis.cpp"
#include "Utilities/erdatagen.cpp"

using namespace std;
using namespace arma;

int main(){

cout <<   " \n \n ************************************************************************************************** \n \n";
cout << " \n         MAXIMUM MATCHING PATTERN ANALYSIS IN REAL NETWORKS, WITH AN ENRICHMENT EXPERIEMNT          \n";

cout << "\n \n \n				*** D A T A - U P L O A D - A N D - O B J E C T S - C R E A T I O N ***			 \n \n \n";

auto start_time = chrono::steady_clock::now();

cout << " Insert data directory path: \n";
string directory;
cin >> directory;

// ------------------------------------------------------------------------------------------------------------------------------------------
// ALON VOCABULARY DATA
cout << "\n						--- VOCABULARY EXTRACTION \n \n \n";

cout << "Insert file name: \n";
string filename1;
cin >> filename1; 
cout << "\n";
cout << directory + filename1 << "\n";
int n_e1 = file_entries_counter( directory + filename1 );
int n_f1 = file_features_counter( directory + filename1 );

if(n_e1 == 0 || n_f1 == 0 ){
	cout << "ERROR in file upload \n";
	return 0;
}

DataStream  names = datastream_building(directory + filename1, n_e1, n_f1);
DataStream* names_data = &names;

map<string, int> direct_index_names = direct_dict( names_data );



// ------------------------------------------------------------------------------------------------------------------------------------------
// ALON ECOLI DATA
cout << "\n						--- DATA EXTRACTION \n \n \n";

cout << "Insert file name: \n";
string filename2;
cin >> filename2;
cout << "\n";

int n_entries  = file_entries_counter( directory + filename2 );
int n_features = file_features_counter( directory + filename2 );

if(n_entries == 0 || n_features == 0 ){
	cout << "ERROR in file upload \n";
	return 0;
}

DataStream  ecnet = datastream_building(directory + filename2, n_entries, n_features);
DataStream* ecnet_data = &ecnet;



// ------------------------------------------------------------------------------------------------------------------------------------------
// ALON ECOLI NETWORK
cout << "\n						--- NETWORKS BUILDING  \n \n \n";

int number_of_nodes = node_count( direct_index_names );
int number_of_links = ecnet_data->get_number_of_entries();


cout << " 		Number of nodes             : " << number_of_nodes << "\n";
cout << " 		Number of links             : " << number_of_links << "\n";

Network TF_Regulation = raw_network_building(number_of_nodes, number_of_links, ecnet_data);
Network* TFR = & TF_Regulation;


cout << "\n \n \n				*** D A T A - A N A L Y S I S - A N D - P R O C E S S I N G ***			 \n \n \n";

double real_self_loops = TF_Regulation.self_loop_number();
double real_avg_deg    = TF_Regulation.average_deg();


cout << " \n";
cout << "  		Self loops                  : " << real_self_loops << "\n";
cout << " 		Average degree              : " << real_avg_deg << "\n";



// ------------------------------------------------------------------------------------------------------------------------------------------
// MATCHING ALGORITHM ON REAL DATASET

cout << "\n						--- MAXIMUM MATCHING ALGORITHM  \n \n \n";
set<int> nodes_to_control = matched_nodes( TFR );

int maximum_match_size = nodes_to_control.size();
cout << " 		Number of matched nodes     : " << maximum_match_size << "\n";

long double unmatch_percentage = (double)(number_of_nodes - maximum_match_size)/ ((double)number_of_nodes);
cout << " 		Unmatched nodes percentage in real network : " << unmatch_percentage << "\n";

long double controllability = 1 - unmatch_percentage;
cout << " 		Real network controllability : " << controllability << "\n";



// ------------------------------------------------------------------------------------------------------------------------------------------
// DATA OUTSTREAM
cout << "\n						--- DATA OUTSTREAM \n \n \n";

cout << "Insert file name: \n";
string filename3;
cin >> filename3; 
cout << "\n";

DataStream out_data = matched_nodes_data( nodes_to_control, number_of_nodes);
out_data.write_down_data(directory + filename3);



// ------------------------------------------------------------------------------------------------------------------------------------------
// MATCHING ALGORITHM ON ER NETWORK
cout << "\n						--- ENRICHMENT EXPERIMENT  \n \n \n";

int number_of_samples;
cout << "How many random samples do you want to generate? \n";
cin >> number_of_samples;

enrichment_experiment(number_of_samples, number_of_nodes, number_of_links, 
					  maximum_match_size,
					  real_self_loops, real_avg_deg);



// ------------------------------------------------------------------------------------------------------------------------------------------
// ER MATCHING DATA GENEARTOR

cout << "\n						--- WRITING DOWN AN ER RANDOM NETWORK  \n \n \n";

ER_data_generator( number_of_nodes, number_of_links, directory);



// ------------------------------------------------------------------------------------------------------------------------------------------
// PYTHON VISUALIZATION

network_matching_visualization();



// ------------------------------------------------------------------------------------------------------------------------------------------
// RUNTIME
auto end_time = chrono::steady_clock::now();
auto diff = end_time - start_time;

cout << "\n	RUNTIME: "
          << chrono::duration_cast<chrono::milliseconds>(diff).count()
          << " ms \n";

cout << " \n \n ************************************************************************************************** \n \n";

return 0;
}
