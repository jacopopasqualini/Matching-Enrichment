#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

#ifndef DataStream_h
#define DataStream_h
  
class DataStream 
{ 
public: 

    DataStream( int ne, int nf );
   ~DataStream();
 
    void    insert_data(string input, int i, int j);

    string  get_value(int n, int f);
    int     get_number_of_entries();
    int     get_number_of_features();

    void    print_number_of_entries();
    void    print_number_of_features();
    void    print();

    void    write_down_data( string filename );

private:

   int number_of_entries;
   int number_of_features;
   string* raw_data;

};

#endif
