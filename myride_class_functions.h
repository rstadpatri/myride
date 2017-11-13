
#include "std_lib_facilities_4.h"

#ifndef LOGIC_FUNCTIONS
#define LOGIC_FUNCTIONS

namespace funct_lib {

	vector<Place> places;
	vector<Customer> customers;
	vector<Driver> drivers;

	double to_radian(double degree);  //Conversion from degrees to radians

	double distance_between(double x1d, double y1d, double x2d, double y2d);
		// Formula for calculating distance between waypoints


	class Member;

	class Place;

	class Customer;

	class Driver;

	vector<Place> places;
	vector<Customer> customers;
	vector<Driver> drivers;

	bool operator==(Driver a, Driver b);

	void add_place();

	double find_distance(Place x, Place y);  //Essentially a more user friendly distance_between function, takes Place_info as an input.

	//void initialize_places();

	void add_funds(double addend);

	void add_customer();

	template<class C> void remove(vector<C>& list, string name);  //GUI will need to provide call with different types of classes

	void add_driver();

	vector<Place> ride_ordest();

	Driver find_driver(vector<Place> ordest);

	vector<Driver> find_driver_within(string tag, double radius);

	void request_ride();

	string import_data();

	void export_data(string filename);
}
#endif