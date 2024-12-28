/*
main.cpp
Author: Janine Obiri <jo21aap@herts.ac.uk>
Created: 20/11/2024
Updated: 20/12/2024
*/ 


 #include "bike.h"
 #include "system_helper_functions.h"


int main(int argc, char* argv[]) 
{

    std::vector<Pushbike> push_bikes; 
    std::vector<Electricbike> electric_bikes;
    electric_bikes = initialise_bikes_electric();
    push_bikes = initialise_bikes_push();


    std::string filename; //getting the file name from cmd line arguments
    for(int i = 1; i < argc; ++i){
        filename = filename + argv[i];
    };

    std::ifstream file(filename);
    std::string date; 
    getline(file,date,'\n'); //Getting the first line which holds the date to use for filename

    
    while(!file.eof()) 
    {

        process_day(file,push_bikes,electric_bikes,date);
        reset_stock(push_bikes,electric_bikes);
    }
    file.close();

    return 0;
};
