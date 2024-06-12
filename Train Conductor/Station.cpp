/* Meghana Chamarty
 * Station.cpp
 * CPSC 223
 * 4/4/2023
 * Implementation of the Station class
 * Don't forget to remove //TODO when you submit!
 * 
 */

#include "Station.h"

// Constructor
Station::Station(){
	name = "NoName";
    access = false;
}

// Parameterized Constructor
Station::Station(string input_name, bool input_access){
    name = input_name; 
    access = input_access; 
}

// Function: checks if two stations are equal
// Input: station
// Returns: boolean
// Does: Returns true if the station given as a parameter is identical to the object whose
//       function is being invoked. Else, returns false
bool Station::isEqual(Station s){
    if (name == s.getName() && access == s.getAccess()) {
        return true; 
    }
    else {
        return false; 
    }
}

// Function: prints station name followed by A or U based on access
// Input: reference to ostream object
// Returns: void
// Does: prints a) the string containing the station name and b) an A or U to indicate
//       whether access options are available (A = available, U = unavailable). 
void Station::print(ostream &outfile) {
    if (getAccess() == true){
        outfile << name << " A";
    }
    else{
        outfile << name << " U"; 
    }
}
