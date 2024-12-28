#include "bike.h" 
#include "system_helper_functions.h"
#include <iostream>

/*
bike.h
Author: Janine Obiri <jo21aap@herts.ac.uk>
Created: 20/11/2024
Updated: 19/12/2024
*/


Bike::Bike(int& id,int& price)
{
  this->id = id;
  this->price = price;
}


bool Bike::rent_bike(std::vector<int>& time_taken, std::vector<int>& time_returned)
{
  if(this->status == "taken") 
  {
    return false;
  } 
  if(compare_time(time_taken,time_returned) == true) {
    return false;
  }
  this->set_timetaken(time_taken);
  this->set_timereturned(time_returned);
  this->change_status();
  return true;
}



Pushbike::Pushbike(int &id,int &price) : Bike(id,price)
{
  Bike(id,price);
}



Electricbike::Electricbike(int &id,int &price) : Bike(id,price)
{
  Bike(id,price);
}

std::string Bike::to_string() const
{
    std::string info; 
    std::vector<int> time1 = this->get_timetaken(), 
                            time2 = this->get_timereturned();
    info = std::to_string(this->get_id()) + "\n"  
    + this->check_status() + "\n" 
    + std::to_string(time1[0]) + "." + std::to_string(time1[1]) + "\n"
    + std::to_string(time2[0]) + "." + std::to_string(time2[1]) + "\n"
    + std::to_string(this->get_price()) + "\n";

    return info;
}

int Bike::get_id() const
{
    return this->id;
}

std::vector<int> Bike::get_timetaken() const
{
    return this->time_taken;
}

std::vector<int> Bike::get_timereturned() const
{
    return this->time_returned;
}

int Bike::get_price() const
{
    return this->price;
}

void Bike::set_timetaken(std::vector<int>& time_taken) 
{
    this->time_taken = time_taken;

}

void Bike::set_timereturned(std::vector<int>& time_returned)
{
    this->time_returned = time_returned;
}

void Bike::change_status()
{
    if (this->status == "available")
    {
        this->status ="taken";
    } else if (this->status == "taken")
    {
      this->status = "available";
    };
}


void Bike::shelf_bike()
{
  this->status = "unavailable";
}

void Bike::unshelf_bike()
{
  this->status = "available";
}

void Bike::reset_bike(std::vector<int>& time_taken, std::vector<int>& time_returned)
{
    this->set_timetaken(time_taken);
    this->set_timereturned(time_returned);
}



std::string Bike::check_status() const
{
    return this->status;
}


void Pushbike::reset_bike(std::vector<int>& time_taken, 
                        std::vector<int>& time_returned)
{
    if(this->check_status() == "taken")
    {
      this->change_status();
    }    
    this->set_timetaken(time_taken);
    this->set_timereturned(time_returned);
}

  
void Electricbike::reset_bike(std::vector<int>& time_taken, std::vector<int>& time_returned)
{
    this->set_timetaken(time_taken);
    this->set_timereturned(time_returned);
    this->refill_battery();
    this->unshelf_bike();
}

void Electricbike::refill_battery()
{
  this->charge = 5;
}

void Electricbike::update_battery(double& charge)
{
  this->charge = this->charge - charge; 
  if(this->charge <=0) 
  {
    this->shelf_bike();
  }
}

double Electricbike::get_charge() const
{
    return this->charge;
}
