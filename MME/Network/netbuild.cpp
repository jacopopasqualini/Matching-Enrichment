#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iomanip>
#include <random>

#include "network.h"

using namespace std;

// ----------------------------------------------
// DIRECT INDEX

map<string, int> direct_dict( DataStream* dataset ){

int data_size  = dataset->get_number_of_entries() -1;
int n_features = dataset->get_number_of_features();

map<string, int> direct_index;

int l = 0;
string p = "";

// FEATURES SELECTION
int low_span=0; int up_span=0;

cout << " \n 		Choose file features to vocabularize "
     << " \n		- TRUE : default vocabularization "
     << " \n		- FALSE: custom vocabularization \n";
bool s;
cin >> s;

if(s==true)
  { low_span = 0;
    up_span  = n_features - 1;}
else
  { cout <<" 		Insert the first feature : ";
    cin >> low_span;
    cout <<" 		Insert the last feature  : ";
    cin >>  up_span;
    up_span = up_span + 1; }

// FEATURES DICTIONARIZATION
for(int i=0; i <= data_size; i++){
   for(int j= low_span; j< up_span; j++){

      //cout << "extracting from feature :" << j << "\n";

      p="";
      p = dataset->get_value(i,j);
      if( !direct_index.count(p) ) {
         direct_index[ p ] = l;
         l++; }
      else
         continue;
   }
}

return direct_index;
}

// ----------------------------------------------
// INVERSE INDEX

map<int, string> inverse_dict( map<string,int> direct ){

map<int, string> inverse;

for(auto d : direct)
{
 int id = d.second;
 string name = d.first;
 inverse[ id ] = name;
}

return inverse;
}

// ----------------------------------------------
// NUMBER OF NODES

int node_count( map<string,int> direct_index ){
int non = 0;

for(auto it = direct_index.cbegin(); it != direct_index.cend(); ++it)
{ non++; }

return non;
}

// ----------------------------------------------
// EXPERIMENTAL NETWORK BUILDER

Network network_building( int number_of_nodes, int number_of_links, DataStream* dataset, map<string, int> direct_index ){

Network net( number_of_nodes );

string source = ""; string target = ""; string w = "";

int k=0; int l=0; double weight = 0.0;

for(int i=0; i< number_of_links; i++) {

	source = dataset->get_value(i,0); // riga
	k      = direct_index[ source ];

	target = dataset->get_value(i,1); // colonna
	l      = direct_index[ target ];

	w      = dataset->get_value(i,2); // peso
	weight = atof(w.c_str());

  net.add_link(k,l,1.0);

}
cout << "\n --- REAL NETWORK BUILT --- \n";
return net;
}

// ----------------------------------------------
// NETWORK BUILDER FOR ALON DATASET

Network raw_network_building( int number_of_nodes, int number_of_links, DataStream* dataset){

int shift = 0;
int start = 0;
cout << "Names stast from node 0 or 1? \n";
cin>>start;

if(start == 1) // alon case
	{shift = 1;}


Network net( number_of_nodes );

string source = ""; string target = ""; string w = "";

int k=0; int l=0; double weight = 0.0;

for(int i=0; i< number_of_links; i++) {

	source = dataset->get_value(i,0); // riga
	k      = atof(source.c_str())-shift; // -1 shift due to dataset file

	target = dataset->get_value(i,1); // colonna
	l      = atof(target.c_str())-shift;

	w      = dataset->get_value(i,2); // peso
	weight = atof(w.c_str());

	if(weight!=0)
          { net.add_link(k,l,1.0); } // unweighted
	else
	  continue;
    
}

cout << "\n --- REAL NETWORK BUILT --- \n";

return net;
}



































