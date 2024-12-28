#ifndef _SYSTEM_HELPER_FUNCTIONS_H 
#define _SYSTEM_HELPER_FUNCTIONS_H
 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "bike.h"

 /*
system_helper_functions.h
Author: Janine Obiri <jo21aap@herts.ac.uk>
Created: 3/12/2024
Updated: 22/12/2024
*/ 

/**
 * Function to convert a vector in the shape of {hour,minute}
 * into a numerical value to represent charge where 
 * 1 hour is the equivalent of 1 unit of charge
 * If the time of rental is larger than the time returned 
 * the function should return 0 as this system has no use for
 * a negative time value
 * @param time_taken vector representing starting time
 * @param time_returned vector representing ending time
 * @return double representing units of charge
 */
double convert_hour_to_charge(std::vector<int>& time_taken, 
                        std::vector<int>& time_returned);

/**
 * Function to split up a string into a vector 
 * @param string to be split 
 * @param splitter representing separation character
 * @return vector of strings that have been split
 */
std::vector<std::string> splitstr(std::string& str,char &splitter);

/**
 * Function to split up a string which is a date in the form of 
 * XX/XX/XXXX and return it without the '/' character
 * @param date string representing a date 
 * @return A string representing a date
 */
std::string split_date(std::string& date);

/**
 * Function which puts together all indices of a vector
 * to make a string
 * @param strings vector containing separated strings
 * @return string composed of all strings from the vector
 */
std::string fromvectortostr(std::vector<std::string>& strings); 

/**
 * Function which initialises a vector of ten Electricbike objects
 * @return vector of Electricbike objects
 */
std::vector<Electricbike> initialise_bikes_electric();

/**
 * Function which initialises a vector of thirty Pushbike 
 * objects 
 * @return vector of Pushbike objects
 */
std::vector<Pushbike> initialise_bikes_push();

/**
 * Function to receive and process a line from a file 
 * @param file open ifstream file
 * @return vector of strings
 */
std::vector<std::string> get_line_from_file(std::ifstream& file);

/**
 * Assuming all dates in file will be in the form of XX/XX/XXXX or XX/XX/XX means the 
 * length will be ten characters or eight characters. This function uses that logic to check if a line relates to a rental
 * or holds a date.
 * @param line from file to be checked
 * @return boolean value indicating if line is a date
 */
bool is_line_date(std::string& line);

/**
 * Function to compare two times in the shape of {hour,minute}
 * @param time1 a vector in the shape of {hour,minute}
 * @param time2 a vector in the shape of {hour,minute}
 * @return boolean to confirm if time1 is bigger than 
 * time2
 */
bool compare_time(std::vector<int>& time1, std::vector<int>& time2); 

/**
 * Function to find the first available push bike in a vector of 
 * Pushbike objects
 * @param bikes vector of Pushbike objects
 * @return index of first available bike
 */
int find_available_bike_push(std::vector<Pushbike>& bikes);

/**
 * Function to find the first available electric bike in a 
 * @param bikes vector of Electricbike objects 
 * @param vector of Electricbike objects
 */
int find_available_bike_electric(std::vector<Electricbike>& bikes);

/**
 * Function to check if push bikes have been returned 
 * @param bike pushbike object to be checked
 * @param time_taken vector in the shape of {hour,minute} 
 * representing the most recent rental time
 */
void check_if_bike_available_push(Pushbike& bike, 
                                    std::vector<int>& time_taken);

/**
 * Function to check if electric bikes have been returned
 * @param bike electricbike object to be checked
 * @param time_taken vector in the shape of {hour,minute}
 * representing the most recent rental time
 */ 
void check_if_bike_available_electric(Electricbike& bike, 
                                    std::vector<int>& time_taken);

/**
 * Function to convert a string to a vector in the shape of 
 * {hour,minute}
 * @param data time in the form of a string
 * @return vector in the shape of {hour,minute}
 */
std::vector<int> string_to_time(std::string& data);

/**
 * Function which processes a day from a file
 * @param file open ifstream file
 * @param push_bikes vector of Pushbike objects
 * @param electric_bikes vector of Electricbike objects
 * @param date string representing date of the day
 */
void process_day(std::ifstream& file,std::vector<Pushbike>& push_bikes, 
                        std::vector<Electricbike>& electric_bikes,
                        std::string& date);

/**
 * Function that resets all bikes, designed to be used at the end 
 * of a day 
 * @param push_bikes vector of Pushbike objects
 * @param electric_bikes vector of Electricbike objects
 */
void reset_stock(std::vector<Pushbike>& push_bikes, 
                        std::vector<Electricbike>& electric_bikes);


#endif