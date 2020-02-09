#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>

#include "network.h"

using namespace std; 

//-----------------------------------------------------------------------------------------------
// CONSTRUCTOR 
//-----------------------------------------------------------------------------------------------
Network::Network( int number_of_nodes ){

adjagency.zeros(number_of_nodes,number_of_nodes);
n_nodes = number_of_nodes;
n_links = 0;
}

Network::Network( sp_mat m ){

adjagency = m;
n_nodes = m.n_rows;
n_links  = m.n_nonzero;

}

//-----------------------------------------------------------------------------------------------
// DESTRUCTOR 
//-----------------------------------------------------------------------------------------------
Network::~Network(){
}

//-----------------------------------------------------------------------------------------------
// SETTER 
//-----------------------------------------------------------------------------------------------
void Network::add_link( int row, int column, double weight){

adjagency(row, column) = weight;
n_links++;
return;

}

//-----------------------------------------------------------------------------------------------
// GETTER 
//-----------------------------------------------------------------------------------------------
double Network::get_link( int row, int column ){

return adjagency(row, column);
}

// features getter
int Network::get_number_of_nodes(){

int number_of_nodes = adjagency.n_rows;
return number_of_nodes;
}

int Network::get_number_of_links(){

int number_of_links = adjagency.n_nonzero;
return number_of_links;
}

sp_mat  Network::get_adjagency(){
	sp_mat ad = adjagency;
	return ad;
}

int Network::in_degree( int index ){
	
	int id = 0;

	id = adjagency.col( index ).n_elem;

	return id;
}

int Network::out_degree( int index ){
	
	int od = 0;

	od = adjagency.row( index ).n_elem;

	return od;
}

double Network::average_deg(){ // somma sugli elementi sotto la diagonale
	
	double ad = 0.0; 
	ad = (double)n_links / (double)n_nodes;

	return ad;
}

double Network::self_loop_number(){

	double sl = 0.0;
	sl = trace(adjagency);
	return sl;

}

//-----------------------------------------------------------------------------------------------
// PRINT 
//-----------------------------------------------------------------------------------------------
void Network::print(){

cout << "\n" << adjagency << "\n";
return;
}
