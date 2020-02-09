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
#include "erdatagen.cpp"

using namespace std;
using namespace arma;

int main(){

cout <<   " \n \n ************************************************************************************************** \n \n";
cout << " \n         MAXIMUM MATCHING PATTERN ANALYSIS IN REAL NETWORKS, WITH AN ENRICHMENT EXPERIEMNT          \n";

cout << "\n \n \n				*** D A T A - U P L O A D - A N D - O B J E C T S - C R E A T I O N ***			 \n \n \n";

auto start_time = chrono::steady_clock::now();

// ------------------------------------------------------------------------------------------------------------------------------------------
// ALON VOCABULARY DATA
cout << "\n						--- VOCABULARY EXTRACTION \n \n \n";

cout << "Insert file name and location in format ../path/filename.txt \n";
string filename;
cin >> filename; 
cout << "\n";

// string filename1 = "vocabalon.txt";

int n_entries  = file_entries_counter( filename );
int n_features = file_features_counter( filename );

if(n_entries == 0 || n_features == 0 ){
	cout << "ERROR in file upload \n";
	return 0;
}

DataStream  names = datastream_building(filename, n_entries, n_features);
DataStream* names_data = &names;

map<string, int> direct_index_names = direct_dict( names_data );
map<int, string> inverse_index = inverse_dict( direct_index_names );



// ------------------------------------------------------------------------------------------------------------------------------------------
// REWRITE DATA IN THE APPROPRIATE FORMAT
cout << "\n						--- VOCABULARY WRITING \n \n \n";

cout << " Vocab reformatting : \n";
cout << "Insert file name and location in format ../path/filename.txt \n";
string filename1;
cin >> filename1; 
cout << "\n";

DataStream output_names_sheet = translate_vocab_to_data(direct_index_names);

output_names_sheet.write_down_data(filename1);

cout << " Numeric reformatting : \n";
cout << "Insert file name and location in format ../path/filename.txt \n";
string filename2;
cin >> filename2; 
cout << "\n";

DataStream nd = numeric_formatting( names_data, direct_index_names);// converti il foglio di ecoli con i nomi a quello con i numeri

nd.write_down_data(filename2);


// ------------------------------------------------------------------------------------------------------------------------------------------
// ALON ECOLI NETWORK
cout << "\n						--- NETWORKS BUILDING  \n \n \n";

int number_of_nodes = node_count( direct_index_names );
int number_of_links = names_data->get_number_of_entries();


cout << " 		Number of nodes             : " << number_of_nodes << "\n";
cout << " 		Number of links             : " << number_of_links << "\n";

Network TF_Regulation = network_building( number_of_nodes, number_of_links, names_data, direct_index_names );
Network* TFR = & TF_Regulation;


cout << "\n \n \n				*** D A T A - A N A L Y S I S - A N D - P R O C E S S I N G ***			 \n \n \n";

//riguarda come sono definite in network.cpp perchè sono lentissime, è come se il programma si bloccasse

double real_self_loops = TF_Regulation.self_loop_number();
double real_out_deg    = TF_Regulation.average_out_deg();
double real_in_deg     = TF_Regulation.average_in_deg();

cout << " \n";
cout << "  		Self loops                  : " << real_self_loops << "\n";
cout << " 		Average out degree          : " << real_out_deg << "\n";
cout << " 		Average in degree           : " << real_in_deg << "\n";



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

cout << "Insert file name and location in format ../path/filename.txt \n";
string filename3;
cin >> filename3; 
cout << "\n";

DataStream out_data = matched_nodes_data( nodes_to_control, number_of_nodes);
out_data.write_down_data(filename3);



// ------------------------------------------------------------------------------------------------------------------------------------------
// MATCHING ALGORITHM ON ER NETWORK
cout << "\n						--- ENRICHMENT EXPERIMENT  \n \n \n";

int number_of_samples;
cout << "How many random samples do you want to generate? \n";
cin >> number_of_samples;

enrichment_experiment(number_of_samples, number_of_nodes, number_of_links, 
					  maximum_match_size,
					  real_self_loops, real_out_deg, real_in_deg);



// ------------------------------------------------------------------------------------------------------------------------------------------
// ER MATCHING DATA GENEARTOR

cout << "\n						--- WRITING DOWN AN ER RANDOM NETWORK  \n \n \n";

ER_data_generator( number_of_nodes, number_of_links);


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
