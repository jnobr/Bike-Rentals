#define CATCH_CONFIG_MAIN 
#include "catch.hpp" 
#include "system_helper_functions.h"
#include "bike.h"


/*
bike_tests.cpp
Author: Janine Obiri <jo21aap@herts.ac.uk>
Created: 03/12/2024
Updated: 20/12/2024
*/

//All test cases present are designed to be run together for integration testing 
//purposes. If tags are specified in the command line certain tests may fail due to
//prerequisite action not being run

std::vector<int> time1 = {10,02}, time2 = {20,51} , time3 = {3,2};
int id1 = 100, id2 = 2, id3 = 40;
int price_electric = 3, price_push = 1;
Pushbike bike1(id1,price_push);
Pushbike bike2(id2,price_push);
Pushbike bike3(id3,price_push);
Electricbike bike4(id2,price_electric);
Electricbike bike5(id1,price_electric);
Electricbike bike6(id3,price_electric);

TEST_CASE("Test bike getters","[Pushbike]") 
{
    REQUIRE(bike1.get_price()==price_push);
    REQUIRE(bike1.get_id() == id1);
    REQUIRE(bike4.get_price() == price_electric);
    REQUIRE(bike4.get_id()==id2);

}

TEST_CASE("Check time members in pushbike classes update","[Pushbike]")
{
    bike1.set_timetaken(time1);
    REQUIRE(bike1.get_timetaken() == time1);
    bike1.set_timereturned(time2);
    REQUIRE(bike1.get_timereturned() == time2);

    bike2.set_timetaken(time2);
    REQUIRE(bike2.get_timetaken() == time2);
    bike2.set_timereturned(time2);
    REQUIRE(bike2.get_timereturned()== time2);

    bike3.set_timetaken(time1);
    REQUIRE(bike3.get_timetaken() == time1);
    bike3.set_timereturned(time3);
    REQUIRE(bike3.get_timereturned() == time3);
}

TEST_CASE("Check time members in electricbike classes update","[Electricbike]")
{
    bike4.set_timetaken(time1);
    REQUIRE(bike4.get_timetaken() == time1);
    bike4.set_timereturned(time2);
    REQUIRE(bike4.get_timereturned() == time2);

    bike5.set_timetaken(time2);
    REQUIRE(bike5.get_timetaken() == time2);
    bike5.set_timereturned(time2);
    REQUIRE(bike5.get_timereturned()== time2);

    bike6.set_timetaken(time1);
    REQUIRE(bike6.get_timetaken() == time1);
    bike6.set_timereturned(time3);
    REQUIRE(bike6.get_timereturned() == time3);
}

TEST_CASE("check compare_time works","[compare_time]") 
{

    REQUIRE(compare_time(time1,time1) == true);
    REQUIRE(compare_time(time2,time1) == true);
    REQUIRE(compare_time(time3,time1) == false);


}

TEST_CASE("Check bike.to_string() method works","[Bike]")
{
    std::string bike1_details = "100\navailable\n10.2\n20.51\n1\n";
    std::string bike4_details = "2\navailable\n10.2\n20.51\n3\n";
    REQUIRE_THAT(bike1.to_string(),Catch::Matches(bike1_details)); 
    REQUIRE_THAT(bike4.to_string(),Catch::Matches(bike4_details));
}



TEST_CASE("Check that bike status changes", "[change_status]")
{
    
    bike1.change_status(); //this status should be available -> taken
    bike3.change_status(); //this status should be available -> taken
    bike4.change_status(); //this status should be available -> taken


    REQUIRE(bike1.check_status() == "taken");
    REQUIRE(bike2.check_status() == "available"); //bike2 wasn't flipped
    REQUIRE(bike4.check_status() == "taken");

}

TEST_CASE("Check that bikes are being shelved","[shelf_bike]")
{
    bike5.shelf_bike(); //this should be available -> unavailable
    REQUIRE(bike5.check_status() == "unavailable");

}

TEST_CASE ("Checking for free push bikes", "[check_if_bike_available_push]") 
{
    std::vector<int> test_time = {7,35};
    check_if_bike_available_push(bike1,test_time);
    check_if_bike_available_push(bike2,test_time);
    check_if_bike_available_push(bike3,test_time);
    REQUIRE(bike1.check_status() == "taken");
    REQUIRE(bike2.check_status() == "available"); //bike2 was never switched in the above test case
    REQUIRE(bike3.check_status() == "available");
} 

TEST_CASE ("Check that electric bikes reset", "[reset_bike]") 
{
    bike5.reset_bike(time2,time2);
    REQUIRE(bike5.check_status() == "available");
    REQUIRE(bike5.get_charge() == 5);
}


TEST_CASE("Checking for free electric bikes", "[check_if_bike_available_electric]")
{
    std::vector<int> test_time = {7,35};
    check_if_bike_available_electric(bike4,test_time);
    check_if_bike_available_electric(bike5,test_time);
    check_if_bike_available_electric(bike6,test_time); 
    REQUIRE(bike4.check_status() == "taken");
    REQUIRE(bike5.check_status() == "available");
    REQUIRE(bike6.check_status() == "taken");

}

TEST_CASE("Check to see if rent function works","[rent_bike]")
{
    //bike 1 violates 1 rental requirement (taken status)
    //bike 3 violates no requirements
    //bike 4 violates 1 rental requirement (taken status)
    //bike 5 violates 1 rental requirement (rental time > return time)

    REQUIRE(bike1.rent_bike(time1,time2) == false);
    REQUIRE(bike3.rent_bike(time3,time1) == true);
    REQUIRE(bike4.rent_bike(time2,time3) == false);
    REQUIRE(bike5.rent_bike(time2,time1) == false);
}

TEST_CASE("Check that push bikes are reset","[reset_bike]")
{
    //all three bikes should behave the same way
    std::vector<int> empty_time = {0,0};
    bike1.reset_bike(empty_time,empty_time);
    bike2.reset_bike(empty_time,empty_time);
    bike3.reset_bike(empty_time,empty_time);

    REQUIRE_THAT(bike1.get_timetaken(), Catch::Equals(empty_time));
    REQUIRE_THAT(bike2.get_timereturned(), Catch::Equals(empty_time));
    REQUIRE(bike3.check_status() == "available");
}

TEST_CASE("Converting time value to charge value", "[convert_hour_to_charge]")
{
    REQUIRE(convert_hour_to_charge(time1,time3) == 0);
    REQUIRE(convert_hour_to_charge(time1,time2) == 12.98);
    REQUIRE(convert_hour_to_charge(time3,time2) == 21.38);

}

TEST_CASE("Checking string splits","[splitstr]")
{
    std::string test_string = "electric bike:xx.xx:xx.xx", test_string_2 = "", 
    test_string_3 = "09/10/2024";
    char splitter_1 = ':', splitter_2 = ' ', splitter_3 = '/';
    std::vector<std::string> result_1 = splitstr(test_string,splitter_1), 
    result_2 = splitstr(test_string_2,splitter_2), 
    result_3 = splitstr(test_string_3,splitter_3),
    response_1 = {"electric bike"," xx.xx"," xx.xx"},
    response_2 = {""},
    response_3 = {"09"," 10"," 2024"};

    REQUIRE_THAT(result_1, Catch::Equals(response_1));
    REQUIRE_THAT(result_2, Catch::Equals(response_2));
    REQUIRE_THAT(result_3, Catch::Equals(response_3));
}

TEST_CASE("Split date and return a string","[split_date]")
{
    std::string date_1 = "01/01/2002", date_2 = "01/01/02", date_3 = "10023002";
    REQUIRE_THAT(split_date(date_1),Catch::Equals("01 01 2002"));
    REQUIRE_THAT(split_date(date_2),Catch::Equals("01 01 02"));
    REQUIRE_THAT(split_date(date_3),Catch::Equals(date_3));
}

TEST_CASE("Check to see if date is properly identified", "[is_line_date]") 
{
    std::string date = "02/11/2024", notdate = "LALALA", bike_request = "electric bike:2.20:8.30";
    CHECK(is_line_date(date));
    CHECK(is_line_date(notdate) == false);
    CHECK(is_line_date(bike_request) == false);
}

TEST_CASE("Convert vectors to string","[fromvectortostr]")
{
    std::vector<std::string> test_vector = {"a","b","c"};
    REQUIRE_THAT(fromvectortostr(test_vector),Catch::Equals("abc"));

}

std::vector<Electricbike> elec_bikes = initialise_bikes_electric();
std::vector<Pushbike> push_bikes = initialise_bikes_push();

TEST_CASE("Checking ten electric bikes are being initialised","[initialise_bikes]")
{

    REQUIRE(elec_bikes.size() == 10);
}

TEST_CASE("Checking thirty push bikes are being initialised","[initialise_bikes]")
{

    REQUIRE(push_bikes.size() == 30);
}



TEST_CASE("Checking to see if correct index is returned for pushbike list","[find_free_bike]")
{
    push_bikes[0].rent_bike(time1,time2);
    push_bikes[2].rent_bike(time1,time2);
    push_bikes[29].rent_bike(time1,time2);
    REQUIRE(find_available_bike_push(push_bikes) == 1);
    for(int id = 0; id < 30; ++id) 
    {
        push_bikes[id].rent_bike(time1,time2);
    }
    REQUIRE(find_available_bike_push(push_bikes) == -1);
}

TEST_CASE("Checking to see if correct index is returned for electric bike list","[find_free_bike]")
{
    elec_bikes[1].rent_bike(time1,time2);
    elec_bikes[3].rent_bike(time1,time2);
    elec_bikes[9].rent_bike(time1,time2);
    REQUIRE(find_available_bike_electric(elec_bikes) == 0);

    for(int id = 0; id < 10; ++id) 
    {
        elec_bikes[id].rent_bike(time1,time2);
    }
    REQUIRE(find_available_bike_electric(elec_bikes) == -1);
}

TEST_CASE("String is converting to time vector","[string_to_time]")
{
    std::string test_time_1 = "10.02", test_time_2 = "04.05",
    test_time_3 = "00.00";
    std::vector<int> result_1 = {10,2}, result_2 = {4,5}, 
    result_3 = {0,0};

    REQUIRE_THAT(string_to_time(test_time_1), Catch::Equals(result_1));
    REQUIRE_THAT(string_to_time(test_time_2), Catch::Equals(result_2));
    REQUIRE_THAT(string_to_time(test_time_3), Catch::Equals(result_3));
}


TEST_CASE("Checking line retrieval from file","[get_line_from_file]")
{
    //Using the test file rental_requests
    std::ifstream file("rental_requests");
    std::vector<std::string> result_1 = {"01/11/2024"}, 
    result_2 = {"push bike"," 06.08"," 08.50"};
    std::vector<std::string> line_1 = get_line_from_file(file);
    std::vector<std::string> line_2 = get_line_from_file(file);

    REQUIRE_THAT(line_1, Catch::Equals(result_1));
    REQUIRE_THAT(line_2, Catch::Equals(result_2));
    file.close();

}


TEST_CASE("Bike stock is resetting","[reset_stock]")
{
    reset_stock(push_bikes,elec_bikes);
    REQUIRE(push_bikes[0].check_status() == "available");
    REQUIRE(elec_bikes[5].check_status() == "available");
}
