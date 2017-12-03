/*
Nick Esposito, Nick Nelson, & Reuben Tadpatri
Fall Semester 2017 (Nov - Dec)
Solution to Final Project
Based on solution to HW 5
*/

#include "std_lib_facilities_4.h"

#ifndef LOGIC_FUNCTIONS
#define LOGIC_FUNCTIONS
namespace funct_lib {

	double to_radian(double degree);  //Conversion from degrees to radians

	double distance_between(double x1d, double y1d, double x2d, double y2d);
		// Formula for calculating distance between waypoints

	// Each data entry in the myRide system is a member
	// each member has a name and photo
	class Member {
		string name;
		string photo_loc;

	protected:
		// Constructors with and without a provided photo
		Member(string s) : name(s), photo_added(false), photo_loc("default.jpg") {}
		Member(string s, string p) : name(s), photo_loc(p), photo_added(true) {}
		
		// Default constructor
		Member() {}

	public:
		bool photo_added; // whether or not a phot is provided in the data file
		
		// Getter functions
		string get_name() const { return name; };
		string get_photo() const { return photo_loc; }
		
		// Setter function
		void add_photo(string s) {
			photo_loc = s;
		}

		// Virtual function to be used by derived members
		virtual string display() {
			return "Virtual function error";
		}

		// Write out whether or not a photo name was provided
		string export_photo() {
			string to_print = " ";
			if (photo_added) {
				to_print += "1 " + photo_loc;
			}
			else
				to_print += "0";
			return to_print;
		}
	};

	// First derived class of Member
	class Place : public Member {
		// Places have coordinates and tags
		double lat;
		double lon;
		vector<string> tags;

	public:
		// Cosntructors
		Place(string n, double lat, double lon)
			: Member(n), lat(lat), lon(lon) {}

		Place(string n, double lat, double lon, vector<string> tags)
			: Member(n), lat(lat), lon(lon) {
			for (unsigned int i = 0; i < tags.size(); ++i) {
				add_tag(tags[i]);
			}
		}

		Place(string n, double lat, double lon, string photo_loc)
			: Member(n, photo_loc), lat(lat), lon(lon) {}

		Place(string n, double lat, double lon, vector<string> tags, string photo_loc)
			: Member(n, photo_loc), lat(lat), lon(lon) {
			for (unsigned int i = 0; i < tags.size(); ++i) {
				add_tag(tags[i]);
			}
			}

		// Default constructor
		Place() {}

		// Getter functions
		double get_latitude() const { return lat; }
		double get_longitude() const { return lon; }
		int get_tags_length() const { return tags.size(); }

		vector<string> get_tags() const { return tags; }

		// Setter function
		void add_tag(string s) {
			tags.push_back(s);
		}

		// Overwritten virtual function for displaying all info
		// associated with a Place object
		string display() {
			string for_display;
			for_display = get_name() + "\n";
			for (unsigned int i = 0; i < tags.size(); ++i) {
				for_display = for_display + tags[i] + " ";
			}
			for_display = for_display + "\n" + to_string(lat) + "\n" + to_string(lon) + "\n";
			return for_display;
		}

		string display_tags() {
			string for_display;
			for (unsigned int i = 0; i < tags.size(); ++i) {
				for_display = for_display + tags[i] + " ";
			}
			return for_display;
		}
	};

	// Second derived class of Member
	class Customer : public Member {
	private:
		// All customers have balances
		double balance;

	public:
		// Constructors
		Customer(string n) : Member(n), balance(0) {}
		Customer(string n, double bal) : Member(n), balance(bal) {};
		Customer(string n, double bal, string photo_loc) : Member(n, photo_loc), balance(bal) {};

		// Getter function
		double get_balance() const { return balance; }
		void make_payment(double amount) {
			balance = balance - amount;
		}

		// Setter function
		void add_funds(double amount) {
			balance = balance + amount;
		}

		// Overwritten virtual function for displaying all info
		// associated with a Customer object
		string display() {
			string for_display;
			for_display = get_name() + "\n"
				+ to_string(get_balance()) + "\n";
			return for_display;
		}
	};

	// Third derived class of Member
	class Driver : public Member {
		// All drivers have locations and balances
		Place loc;
		double balance;

	public:
		// Constructors
		Driver() {};
		Driver(string name, Place loc) : Member(name), loc(loc), balance(0) {};
		Driver(string name, Place loc, double balance) : Member(name), loc(loc), balance(balance) {};
		Driver(string name, Place loc, double balance, string photo_loc)
			: Member(name, photo_loc), loc(loc), balance(balance) {};

		// Getter functions
		double get_balance() const { return balance; }
		Place get_place() const { return loc; }
		
		// Setter functions
		void add_funds(double amount) {
			balance = balance + amount;
		}
		void change_place(Place p) {
			loc = p;
		}

		// Overwritten virtual function for displaying all info
		// associated with a Driver object
		string display() {
			string for_display;
			for_display = get_name() + "\n" + to_string(balance) + "\n" + loc.get_name()
				+ "\n" + to_string(loc.get_latitude()) + "\n" + to_string(loc.get_longitude()) + "\n";
			return for_display;
		}
	};

	// Getter functions for passing all objects of a certain type to other functions in the project
	vector<Place>& get_places();
	vector<Customer>& get_customers();
	vector<Driver>& get_drivers();

	// For comparing drivers
	bool operator==(Driver a, Driver b);

	// Adding a new place to the running list of places
	void add_place(string name, double lat, double lon, vector<string> tags, string photo_loc);

	double find_distance(Place x, Place y);  //Essentially a more user friendly distance_between function, takes Place_info as an input.

	void add_funds(double addend);

	// Adding a new customer to the running list of customers
	void add_customer(string name, double balance, string photo_loc);

	// Take a member out of the list
	void remove_member(char c, string name);

	// Adding a new driver to the running list of drivers
	void add_driver(string name, double balance, Place loc, string photo_loc);

	vector<Place> ride_ordest(string location, int nametag, string destination_tag);

	// Return all customers with a negative balance
	vector<Customer> find_neg_customer();

	// Return all places with a given tag
	vector<Place> find_places_tags(string tag);

	// Return index of the driver closest to a place
	int find_driver(vector<Place> ordest);

	// Return drivers within a given radius of a place with a given tag
	vector<Driver> find_driver_within(string tag, double radius);

	string request_ride(string customer_name, string location, int nametag, string destination_tag);

	// Read in preexisting members from a data file
	void import_data();

	// Update the data file with any new or removed members
	void export_data();
}
#endif