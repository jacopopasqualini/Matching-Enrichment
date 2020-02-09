#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>

#include "datastream.h"

using namespace std; 

//-----------------------------------------------------------------------------------------------
// CONSTRUCTORS
//-----------------------------------------------------------------------------------------------

DataStream::DataStream( int ne, int nf){

raw_data = new string[(ne+1)*nf];

for(int i = 0; i < ne; i++){
   for(int j=0; j< nf; j++)
      { 
       raw_data[i*nf + j] = "";
      }
}

number_of_entries = ne;
number_of_features = nf;

}

//-----------------------------------------------------------------------------------------------
// DESTRUCTOR 
//-----------------------------------------------------------------------------------------------

DataStream::~DataStream(){
delete[] raw_data;
}

//-----------------------------------------------------------------------------------------------
// SETTER 
//-----------------------------------------------------------------------------------------------

void DataStream::insert_data(string input, int i, int j){

// i = id entry, j = id feature
raw_data[ i*number_of_features + j] = input;
return;
}

//-----------------------------------------------------------------------------------------------
// GETTER 
//-----------------------------------------------------------------------------------------------

string DataStream::get_value(int n, int f){

string entry = raw_data[ n*number_of_features + f ];

return entry;

}

int DataStream::get_number_of_entries(){

int ne = number_of_entries;
return ne;
}

int DataStream::get_number_of_features(){

int nf = number_of_features;
return nf;
}


//-----------------------------------------------------------------------------------------------
// PRINTER 
//-----------------------------------------------------------------------------------------------

void DataStream::print_number_of_features(){

cout << number_of_features;
return;}

void DataStream::print(){

cout << "\n ------------------ ******* ------------------ ";
cout << "\n  ----------------- DATASET ------------------ ";
cout << "\n ------------------ ******* ------------------ \n \n";

for(int i=0; i< number_of_entries; i++) {
   cout <<" "<< i + 1 << ") ";
   for(int j=0; j<number_of_features; j++){
      cout << raw_data[i*number_of_features + j] << " ";}
      cout << "\n";}

cout << "\n ------------------ ******* ------------------ \n";
cout <<   " ------------------ ******* ------------------ \n \n";

return;
}


//-----------------------------------------------------------------------------------------------
// WRITER 
//-----------------------------------------------------------------------------------------------

void DataStream::write_down_data( string filename ){

if(filename == " "){
   cout << "Output file has not been generated \n";
   return;
}

ofstream outfile;
outfile.open ( filename );

// myfile << "Writing this to a file.\n" << "AHAHAHHA DIO BESTIAAAAA";
for(int i=0; i< number_of_entries; i++) {

   for(int j=0; j<number_of_features; j++){
      outfile << raw_data[i*number_of_features + j] << " ";}
      outfile << "\n";}


outfile.close();
return;
}















