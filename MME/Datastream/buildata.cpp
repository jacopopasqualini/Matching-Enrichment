#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>

#include <armadillo>

#include "datastream.h"

using namespace std; 
using namespace arma;

// const string directory = "/home/jacopo/Desktop/SCBIO/TFNet/Data/";

const string directory = "";

//-----------------------------------------------------------------------------------------------
// NUMBER OF ENTRIES FROM FILE
//-----------------------------------------------------------------------------------------------

int file_entries_counter( string filename ){

ifstream data_reader;
data_reader.open( directory+filename);

string line = "";
int ne = 0;

if( data_reader.is_open() ){
	while( !data_reader.eof() ){

	getline(data_reader,line);		// prendo la stringa
	istringstream iss(line);	// la rompo nelle sue componenti-parole
	
	string s;			// swap-like variable

	/*while(iss >> s){
	nf++ }*/
	ne++;
	}
}
else{ 
	cout << " CAN NOT OPEN THE FILE \n"; 
	ne = 0;
	return ne;
}

ne = ne - 1; 

cout << " 		Number of entries            : " << ne << "\n";

data_reader.close();

return ne; // RETURN NUMBER OF ENTRIES
}

//-----------------------------------------------------------------------------------------------
// NUMBER OF FEATURES FROM FILE
//-----------------------------------------------------------------------------------------------

int file_features_counter( string filename ){

ifstream data_reader;
data_reader.open( directory+filename);

string line = "";
int nf = 0;

if( data_reader.is_open() ){
	
	getline(data_reader,line);		// prendo la stringa
	istringstream iss(line);	// la rompo nelle sue componenti-parole
	
	string s;			// swap-like variable

	while(iss >> s){ nf++; }
}
else {cout << " CAN NOT OPEN THE FILE \n";}

cout << " 		Number of features           : " << nf << "\n";

data_reader.close();

return nf; // RETURN NUMBER OF FEATURES
}

//-----------------------------------------------------------------------------------------------
// DATASTREAM BUILDER
//-----------------------------------------------------------------------------------------------

DataStream datastream_building(string filename, int ne, int nf){ 

DataStream dataset(ne, nf);

ifstream data_reader;
data_reader.open( directory+filename );

int i =0;
string line = " "; 
string s = "";

if( data_reader.is_open() ){
	while( !data_reader.eof() ) 			// vai avanti fino alla fine del file
	{  getline(data_reader,line);			// prendo la stringa
	   istringstream iss(line);		// la rompo nelle sue componenti-parole

	   for(int j=0; j< nf; j++)	// riempi la tabella dopo aver scomposto
	      {   s = "";
	          iss >> s;
	          dataset.insert_data(s,i,j); }
	 i++; }
}
else
  cout << " CAN NOT OPEN THE FILE \n";

data_reader.close();
cout << " \n --- DATASET BUILT --- \n";

return dataset;
}

//-----------------------------------------------------------------------------------------------
// DATA CREATION FROM ADJAGENCY
DataStream ER_datastream_building( sp_mat ADJ ){


DataStream ER_data( ADJ.n_nonzero, 2);

sp_mat::const_iterator it     = ADJ.begin();
sp_mat::const_iterator it_end = ADJ.end();

int l = 0;

for(; it != it_end; ++it){
	ER_data.insert_data( to_string(it.row()) ,l ,0 );
	ER_data.insert_data( to_string(it.col()) ,l ,1 );
	l++;
} 

return ER_data;
}

//-----------------------------------------------------------------------------------------------
// OUTPUT DATA

DataStream matched_nodes_data( set<int> minimum_drive_nodes, int n_nodes ){

DataStream output_data(n_nodes,2);

for(int i=0; i<n_nodes; i++){
   
        output_data.insert_data(to_string(i),i,0);

	if(minimum_drive_nodes.count(i))
		output_data.insert_data("1",i,1); // matched nodes
	else
		output_data.insert_data("-1",i,1); // unmatched nodes
}

return output_data;
}

DataStream translate_vocab_to_data( map<string, int> direct_index_names ){

	int n_nodes = direct_index_names.size();

	DataStream names_sheet(n_nodes,2);

	for(auto d : direct_index_names){
		names_sheet.insert_data( to_string(d.second), d.second, 0 );
		names_sheet.insert_data( d.first,  d.second, 1 );
	}

return names_sheet;
}

DataStream numeric_formatting(DataStream* data, map<string, int> direct_index_names){

	int number_of_links = data->get_number_of_entries();

	DataStream nf(number_of_links,2);

	string k = "";
	string l = "";

	for(int j=0; j < number_of_links; j++ ){

		k = data->get_value(j,0);
		l = data->get_value(j,1);
		cout << k << " " << l << " - ";
		nf.insert_data(to_string(direct_index_names[k]), j, 0);
		nf.insert_data(to_string(direct_index_names[l]), j, 1);
	}

	return nf;
}