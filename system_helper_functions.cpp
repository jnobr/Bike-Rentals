#include "system_helper_functions.h"
/*
system_helper_functions.cpp
Author: Janine Obiri <jo21aap@herts.ac.uk>
Created: 3/12/2024
Updated: 19/12/2024
*/ 

double convert_hour_to_charge(std::vector<int> &time_taken, 
                                std::vector<int> &time_returned) 
{
    if(compare_time(time_taken,time_returned) == true) 
    {
        return 0.0;
    }
    int hour = time_returned[0] - time_taken[0];
    int minutes = time_returned[1] - time_taken[1];
    //rounded value of 1/60 to use for converting time to scale of
    //charge values. Where 60 minutes equals 1 unit of charge
    double conversion_value = 0.02;
    if(hour != 0) 
    {
        hour = hour * 60;
    };
    double time = hour + minutes;

    return time*conversion_value;
}

std::vector<std::string> splitstr(std::string &str,char &splitter) {

   std::vector<std::string> splitstrings;
   std::string token;
   if(str.back() != splitter)
   {
   str = str + splitter;
   }
   int len = str.length();
    for(int i = 0; i < len ; ++i) 
    {
        if(str[i] != splitter)
        {
            token = token + str[i];

        }
        else{
            splitstrings.push_back(token);
            token = " ";
        };
       
    };
    return splitstrings;


}
std::string split_date(std::string& date)
{
    char splitter = '/';
    std::vector<std::string> split_string = splitstr(date,splitter);
    return fromvectortostr(split_string);
};


std::string fromvectortostr(std::vector<std::string> &strings) 
{
    std::string returnstr;
    int len = strings.size();
    
    for(int i = 0; i < len; ++i) {
        returnstr = returnstr + strings[i];

    }
    return returnstr;
};

std::vector<Electricbike> initialise_bikes_electric() 
{
    std::vector<Electricbike> bikes_electric;
    int price = 3;
    for(int x = 0,i; x < 10; ++x) 
    {
        i = x + 30;
        bikes_electric.push_back(Electricbike(i,price));
    }

    return bikes_electric;
};

std::vector<Pushbike> initialise_bikes_push() 
{
    int price = 1;
    std::vector<Pushbike> bikes_push;
    for(int i = 0; i < 30;++i) 
    {
        bikes_push.push_back(Pushbike(i,price));
    }


    return bikes_push;
};


std::vector<std::string> get_line_from_file(std::ifstream& file) 
{
    std::string text;
    std::vector<std::string> data; 
    getline(file,text,'\n');
    char splitter = ':';
    std::vector<std::string> splitstring = splitstr(text,splitter);
    if(splitstring.size() > 1) 
    {
    data.push_back(splitstring[0]);
    data.push_back(splitstring[1]);
    data.push_back(splitstring[2]);
    }
    else 
    {
        data.push_back(splitstring[0]);
    }

    return data;
    
};


bool is_line_date(std::string& line) 
{
    return line.length() == 10 || line.length() == 8;

}


bool compare_time(std::vector<int>& time1, std::vector<int>& time2) 
{
    if(time1[0] > time2[0])
    {
        return true;
    }
    else 
    {
        if((time1[0]==time2[0]) && (time1[1]>=time2[1])) 
        {
            return true;
        }

    }
    return false;
}

int find_available_bike_push(std::vector<Pushbike> &bikes) 
{
    const int MAX_LIST_SIZE = 30;
    for(int i = 0; i < MAX_LIST_SIZE; ++i) 
    {
        if(bikes[i].check_status() == "available")
        {
            return i;
        }


    }
    return -1;
}

int find_available_bike_electric(std::vector<Electricbike> &bikes) 
{
    const int MAX_LIST_SIZE = 10;
    for(int i = 0; i < MAX_LIST_SIZE; ++i) 
    {
        if(bikes[i].check_status() == "available")
        {
            return i;
        }


    }
    return -1;
}



void check_if_bike_available_electric(Electricbike &bike, std::vector<int> &current_time) 
{
    //function intended to be used with a bike that has "taken" status
    std::vector<int> time_returned = bike.get_timereturned();
    std::vector<int> time_taken = bike.get_timetaken();
    bool bike_available = compare_time(time_returned,current_time);
    if(!bike_available)
    {
        double charge_lost = convert_hour_to_charge(time_taken,time_returned);
        bike.update_battery(charge_lost);
        std::string status = bike.check_status();
        bike.change_status();
        if(status == bike.check_status() && bike.check_status() != "unavailable")
        {
            //Electric bikes with no charge (unavailable) will not have their 
            //status changed in this function so it is excluded as an error condition
            std::cerr << "Electric bike status did not change " << bike.to_string();
            
        }

    }
}


void check_if_bike_available_push(Pushbike &bike, std::vector<int> &time_taken) 
{
    //function intended to be used with a bike that has "taken" status
    std::vector<int> time_returned = bike.get_timereturned();
    bool bike_available = compare_time(time_returned,time_taken);
    if(!bike_available)
    {
        std::string status = bike.check_status();
        bike.change_status();
        if(status == bike.check_status())
        {
            std::cerr << "Push bike status did not change";
        } 

    };
}

std::vector<int> string_to_time(std::string &data)
{
    char splitter = '.';
    std::vector<std::string> time = splitstr(data,splitter);
    std::vector<int> v_time = {std::stoi(time[0]),std::stoi(time[1])};
    return v_time;
}

void process_day(std::ifstream &file, std::vector<Pushbike> &push_bikes,
                         std::vector<Electricbike> &electric_bikes, std::string &date)
{
    int total_profit_push = 0,total_profit_electric = 0,total_rentals_electric = 0;
    int total_rentals_push = 0,missed_rentals_electric = 0,missed_rentals_push = 0;
    bool end_of_day = false;


    std::string newdate = split_date(date);
    
    while(!end_of_day)
    //for(int i = 0; i < 110; ++i)
    {
    std::vector<std::string> data = get_line_from_file(file);
    if(is_line_date(data[0]) == true || data[0].length() == 0) 
    {
        date = data[0];
        end_of_day = true;   
    }
    else {

    std::string biketype = data[0];
    std::vector<int> time_taken,time_returned;
    time_taken = string_to_time(data[1]);
    time_returned = string_to_time(data[2]);


    for(Pushbike &pushbike: push_bikes) 
    {
        std::string status = pushbike.check_status();
        if(pushbike.check_status() == "taken")
        {   
            check_if_bike_available_push(pushbike,time_taken);
            
        }


    }

    for(Electricbike &electricbike: electric_bikes) 
    {
        std::string status = electricbike.check_status();
        if(electricbike.check_status() == "taken") 
        {
            check_if_bike_available_electric(electricbike,time_taken);

        }
       


    }

    int available_index;
    if(biketype == "push bike") 
    {
        available_index = find_available_bike_push(push_bikes);
        if(available_index >= 0) 
        {

            bool rent_check = push_bikes[available_index].rent_bike(time_taken,
                                                        time_returned);
            if(!rent_check)
            {
                missed_rentals_push+=1;
            }
            else 
            {
                total_profit_push += 1; 
                total_rentals_push +=1;

            }
        }
        else 
        {
            missed_rentals_push += 1;
        }
    }
    if(biketype == "electric bike")
    {
        
        available_index = find_available_bike_electric(electric_bikes);
        if(available_index >=0){

            bool rent_check = electric_bikes[available_index].rent_bike(time_taken,
                                                    time_returned);
            
            if(!rent_check) 
            {
                missed_rentals_electric +=1;
            }
            else 
            {
                total_profit_electric += 3;
                total_rentals_electric += 1;
            }
        } 
        else 
        {
            missed_rentals_electric += 1;
        }
    }

    }

    }
    std::ofstream myfile; //backslash character is escape character and can't be included in filename 
    myfile.open(newdate);

    if(!myfile) 
    {
        std::cerr << "Error reading file";
    } 


    myfile << "Total profit for electric bikes " << total_profit_electric << std::endl; 
    myfile << "Total profit for push bikes " << total_profit_push << std::endl; 
    myfile << "Number of rentals for electric " << total_rentals_electric << std::endl; 
    myfile << "Number of rentals for push " << total_rentals_push << std::endl; 
    myfile << "Number of missed rentals for electric " << missed_rentals_electric << std::endl; 
    myfile << "Number of missed rentals for push " << missed_rentals_push << std::endl;
    myfile.close();

}

void reset_stock(std::vector<Pushbike> &push_bikes, std::vector<Electricbike> &electric_bikes)
{
    std::vector<int> time = {0,0};
    for(Pushbike &pushbike: push_bikes) 
    {
        pushbike.reset_bike(time,time);

    }

    for(Electricbike &electricbike: electric_bikes) 
    {
        electricbike.reset_bike(time,time);

    }

}
