#ifndef _BIKE_H
#define _BIKE_H
#include <string>
#include <vector>

/*
bike.h
Author: Janine Obiri <jo21aap@herts.ac.uk>
Created: 20/11/2024
Updated: 22/12/2024
*/

/**
 * Base class for rental bike object
 * Time vectors should only have 2 indices for the hour and then minute
 */

class Bike {
  private:
  int id;
  std::vector<int> time_taken;
  std::vector<int> time_returned;
  std::string status="available";
  int price;

  public:

  /**
   * Class constructor 
   * @param id int representing id number of bike
   * @param price int representing valuation of bike
   */
  Bike(int& id, int& price);

  /**
   * Virtual destructor 
   */
  virtual ~Bike() = default;

  /**
   * Copy constructor
   * @param other 
   */
  Bike(const Bike& other) = default;

  /**
   * Move constructor
   * @param other
   */
  Bike(Bike&& other) = default; 

  /**
   * Copy assignment operator
   * @param other
   * @return Bike object
   */
  Bike& operator=(const Bike& other) = default; 

  /**
   * Move assignment operator
   * @param other
   * @return Bike object
   */
  Bike& operator=(Bike&& other) = default;

  /**
   * Function which returns members of a class object
   * @return string with details of instance
   */
  std::string to_string() const;

  /**
   * Function which returns id of bike instance
   * @return int id number
   */
  int get_id() const;

  /**
   * Function which returns a vector in the shape of {hour,minute} representing
   * the time the bike was taken for rental 
   * @return vector<int> time bike was rented
   */
  std::vector<int> get_timetaken() const;

  /**
   * Function which returns a vector in the shape of {hour,minute} representing
   * the time the bike was returned from a rental
   * @return vector<int> time bike was returned
   */
  std::vector<int> get_timereturned() const;

  /**
   * Function which returns the price valuation of the bike instance 
   * @return int price of bike
   */
  int get_price() const;

  /**
   * Function which returns the current status of the bike instance
   * @return string representing bike status
   */
  std::string check_status() const;

  /**
   * Function which sets the time taken out for rental 
   * of the current bike instance
   * @param time vector in the shape of {hour,minute} representing
   * time
   */
  void set_timetaken(std::vector<int>& time);

  /**
   * Function which sets the time the rental should end 
   * for the current bike instance
   * @param tme vector in the shape of {hour,minute} representing
   * time
   */
  void set_timereturned(std::vector<int>& time);

  /**
   * Function which changes the status of the current 
   * bike instance
   */
  void change_status();

  /**
   * Function which permanently retires a bike (should be 
   * used only by electric bikes once charge is <=0) 
   * until it has been reset
   */
  void shelf_bike();

  /**
   * Function which resets a bike's status,time members,
   * and charge (only for electric bikes)
   * @param time_taken vector in shape of {hour,minute} 
   * representing time taken
   * @param time_returned vector in shape of {hour,minute} 
   * representing time returned
   */
  virtual void reset_bike(std::vector<int>& time_taken, 
                        std::vector<int>& time_returned);
  
  /**
   * Function to rent a bike 
   * Changes bike status and time members
   * @param time_taken vector in the shape of {hour,minute} representing 
   * time the bike was rented out 
   * @param time_returned vector in the shape of {hour,minute} representing
   * time the bike will be returned 
   * @return boolean to signify if function was successful
   */
  bool rent_bike(std::vector<int>& time_taken, 
                      std::vector<int>& time_returned);



  void unshelf_bike();


  
  

}; 

/**
 * Derived class representing pushbike objects
 */
class Pushbike: public Bike {
  public:
    /**
   * Class constructor
   * @param id int representing id of the bike
   * @param price int representing price of the bike
   */
      Pushbike(int& id, int &price);

  /** Resets bike state to available status
   * @param time_taken vector representing time in the 
   * shape {hour,minute}
   * @param time_returned vector representing time in the
   * shape {hour,minute}
   */
      void reset_bike(std::vector<int>& time_taken, 
                        std::vector<int>& time_returned);


};

/**
 * Derived class representing Electric bike objects
 */
class Electricbike: public Bike 
{
  private: 
     double charge = 5;

  public:
    /**
     * Class constructor 
     * @param id int representing id of the bike
     * @param price int representing the price of the bike
     */
      Electricbike(int &id, int &price);

      /**
       * Resets bike state to available and refills battery 
       * @param time_taken vector representing time in the 
       * shape {hour,minute}
       * @param time_taken vector representing time in the shape
       * {hour,minute}
       */
      void reset_bike(std::vector<int>& time_taken, 
                        std::vector<int>& time_returned);

      /**
       * Changes charge value to 5
       */
      void refill_battery();

      /**
       * Modify battery value using charge value passed as 
       * parameter 
       * @param charge charge units to be deducted
       */
      void update_battery(double& charge);

      /**
       * Returns charge value 
       * @return charge
       */
      double get_charge() const;
};


#endif
