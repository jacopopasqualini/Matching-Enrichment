#include <iostream> 
#include <iomanip>
#include <string>

void network_matching_visualization(){

cout << "Insert number of figures that you want to generate \n";
int vt = 0; // visualization times
cin >> vt;

string compiler = "python3 ";

string visualization_path = ".../MME/DataVisualization/";
string filename = "visualization.py";
	
for(int i=0; i<vt; i++){
	string command = compiler + visualization_path + filename;
	system(command.c_str());
}

return;
}
