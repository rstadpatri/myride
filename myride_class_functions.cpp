//Nick Nelson - UIN: 425005869 - hw5 - 10/2/17
//This program functions like Uber. It stores customers and drivers and allows customers to request rides.
//It now allows for the input of a file to import data.
//I have commented in where I would check for errors if I had more time to give to this problem.

#include "std_lib_facilities_4.h"

constexpr double R = 3963.1676;  //Radius of Earth
constexpr double pi = 3.14159;
string filename = "Data File";

double to_radian(double degree) {  //Conversion from degrees to radians
	double radian = degree*pi / 180;
	return radian;
}

double distance_between(double x1d, double y1d, double x2d, double y2d) {  // Formula for calculating distance between waypoints
	double x1 = to_radian(x1d);
	double y1 = to_radian(y1d);
	double x2 = to_radian(x2d);
	double y2 = to_radian(y2d);

	double distance = acos(sin(x1)*sin(x2) + cos(x1)*cos(x2)*cos(y1 - y2))*R;
	return distance;
}

class Member {
	string name;
	string photo_loc;

protected:
	Member(string s) : name(s) {};
	Member() {};

public:
	string get_name() const { return name; };
	string get_photo() const { return photo_loc; }
	void add_photo(string s) {
		photo_loc = s;
	}
};

class Place : public Member {
	double lat;
	double lon;
	vector<string> tags;

public:
	Place(string n, double lat, double lon)
		: Member(n), lat(lat), lon(lon) {}

	Place() {}

	double get_latitude() const { return lat; }
	double get_longitude() const { return lon; }
	int get_tags_length() const { return tags.size(); }

	vector<string> get_tags() const { return tags; }

	void add_tag(string s) {
		tags.push_back(s);
	}

	void print() {};  // Define for GUI
};

class Customer : public Member {
private: 
	double balance;

public:
	Customer(string n) : Member(n), balance(0) {}
	Customer(string n, double bal) : Member(n), balance(bal) {};

	double get_balance() const { return balance; }
	void make_payment(double amount) {
		balance = balance - amount;
	}
	void add_funds(double amount) {
		balance = balance + amount;
	}

	void print() {}; //Needs written with GUI. Virtual function?
};

class Driver : public Member {
	Place loc;
	double balance;

public:
	Driver() {};
	Driver(string name, Place loc) : Member(name), loc(loc), balance(0) {};
	Driver(string name, Place loc, double balance) : Member(name), loc(loc), balance(balance) {};

	double get_balance() const { return balance; }
	Place get_place() const { return loc; }
	void add_funds(double amount) { 
		balance = balance + amount; 
	}
	void change_place(Place p) {
		loc = p;
	}
	void print() {} //Needs defined for the GUI
};

vector<Place> places;
vector<Customer> customers;
vector<Driver> drivers;

bool operator==(Driver a, Driver b) {
	if (a.get_name() == b.get_name()) {
		return true;
	}
	else
		return false;
}

ostream& operator<<(ostream& ost, Place p) {
	ost << p.get_name();
	return ost;
}

void add_place() {
	//Takes in user input and creates a new Place_info object
	//Unincluded error checking: I did not check to make sure that latitude and longitude were in the appropriate range.

	//I HAVE COMMENTED OUT ALL COUT'S -> REWRITE FOR THE GUI

	string extra_input;  //For places where cin cuts off a string, I store what's leftover in this variable using the getline function

	//cout << "Now enter the latitude of an arbitrary point: \n";
	//double input_lat;
	//cin >> input_lat;
	//cout << "\nEnter the corresponding longitude: \n";
	//double input_long;
	//cin >> input_long;

	//cout << "\nWhat is the name of this location? \n";
	//string input_name;
	//cin >> input_name;
	//getline(cin, extra_input);
	//input_name += extra_input;

	//cout << "\nWhat is the address?\n";
	//string input_address;
	//string input_address2;
	//cin >> input_address;  //Cin cuts off line at first whitespace
	//getline(cin, extra_input);
	//input_address += extra_input;

	//cout << "\nGive the location two tags...\nTag 1:";
	//string input_tag1;
	//cin >> input_tag1;
	//cout << "\nTag 2:";
	//string input_tag2;
	//cin >> input_tag2;

	//Constructor with info taken in with GUI
	//Place arbitrary_loc{ input_name, input_lat, input_long };  

	//arbitrary_loc.add_tag(input_tag1);
	//arbitrary_loc.add_tag(input_tag2);

	//places.push_back(arbitrary_loc);
}

double find_distance(Place x, Place y) {  //Essentially a more user friendly distance_between function, takes Place_info as an input.
	double distance = distance_between(x.get_latitude(), x.get_longitude(), y.get_latitude(), y.get_longitude());
	return distance;
}

//void initialize_places() {  //Creates a list of landmarks to begin program
//	Geo_loc brightloc{ "Bright Building", 30.6190, -96.3389 };
//	Place_info bright{ "Bright_Building", "College_Station", brightloc };
//	bright.tags.push_back("computer_science");
//	bright.tags.push_back("aerospace");
//
//	Geo_loc airportloc{ "Easterwood Airport", 30.5910, -96.3628 };
//	Place_info airport{ "Easterwood_Airport", "College_Station", airportloc };
//	airport.tags.push_back("airport");
//	airport.tags.push_back("transit");
//
//	Geo_loc bwwloc{ "Buffalo Wild Wings", 30.6358, -96.3246 };
//	Place_info bww{ "Buffalo_Wild_Wings", "College_Station", bwwloc };
//	bww.tags.push_back("dining");
//	bww.tags.push_back("sports");
//
//	Geo_loc ucloc{ "UCentre", 30.6254, -96.3461 };
//	Place_info uc{ "UCentre", "College_Station", ucloc };
//	uc.tags.push_back("housing");
//	uc.tags.push_back("pool");
//
//	Geo_loc lbloc{ "Lake Bryan", 30.7085, -96.4677 };
//	Place_info lb{ "Lake_Bryan", "Bryan", lbloc};
//	lb.tags.push_back("lake");
//	lb.tags.push_back("camping");
//
//	Geo_loc walloc{ "Walmart", 30.5974, -96.3005 };
//	Place_info wal{ "Walmart", "College_Station", walloc };
//	wal.tags.push_back("shopping");
//	wal.tags.push_back("produce");
//
//	Place_info v[6] = { bright, airport, bww, uc, lb, wal };  //Use array to place data into a single vector as requested by homework.
//	for (int i = 0; i < 6; ++i) { places.push_back(v[i]); }; // I didn't want to write "pushback" and "print" 7 times each so I quickly checked the textbook on using arrays.
//
//	Driver jim{ "Jim", places[0].loc, 10 };  //Adds a couple of drivers to the program for starting purposes (leftover from HW3)
//	drivers.push_back(jim);
//	Driver greg{ "Greg", places[0].loc, 10 };
//	drivers.push_back(greg);
//	Customer terry{ "Terry" };
//	customers.push_back(terry);
//}

void add_funds(double addend) {  
	//Adds funds (only works for customer accounts)
	string customer_name;
	//cout << "Whose account would you like to credit: ";  NEED GUI SUPPORT HERE
	//cin >> customer_name;
	for (unsigned int i = 0; i < customers.size(); ++i) {
		if (customers[i].get_name() == customer_name) {
			customers[i].add_funds(addend);
		}
	}
}

void add_customer() {
	string name;

	//cout << "Input the customer's name: "; NEED GUI SUPPORT HERE
	//cin >> name;
	//string extra_input;
	//getline(cin, extra_input);
	//name += extra_input;

	Customer new_customer{ name  };
	customers.push_back(new_customer);

}

template<class C> void remove(vector<C>& list, string name) {  //GUI will need to provide call with different types of classes
	for (unsigned int i = 0; i < list.size(); ++i) {
		if (list[i].get_name() == name) {
			list.erase(list.begin() + i);
		}
	}
}

void add_driver() {  
	//Did not error check for proper input types when using cin. Also did not check for in-range latitude and longitude.
	//Adds a driver to the program; includes name, driver number, and current coordinates


	string name;	//NEED GUI SUPPORT HERE
	Place loc;
	double balance = 0;									// MAKE THIS A DECLARATION
	//
	//cout << "Input the driver's name: ";
	//cin >> name;
	//cout << "Input driver's current latitude: ";
	//cin >> lat;
	//cout << "Input driver's current longitude: ";
	//cin >> lon;
	//cout << "Input driver's starting balance: ";
	//cin >> balance;

	Driver new_driver{ name, loc, balance };
	drivers.push_back(new_driver);
}

vector<Place> ride_ordest() {  
	//Returns Place vector with ride origin and destination
	string extra_input;

	vector<Place> ordest;
	//cout << "\n\nWhere are you?\n\n";		//NEED GUI SUPPORT

	//for (unsigned int i = 0; i < places.size(); ++i) {  Lists places to choose from.
	//	cout << places[i].name << "\n";
	//}
	//cout << "Other\n\nEnter name: ";

	string location;
	string tag;
	//cin >> location;
	//getline(cin, extra_input);
	//location += extra_input;
	if (location == "Other") { //Did not error check for improper input. User must enter one of the options verbatim
		add_place();
		ordest.push_back(places.back()); 
	}  

	else {
		for (unsigned int i = 0; i < places.size(); ++i) {
			if (location == places[i].get_name()) { 
				ordest.push_back(places[i]); 
			}
		}
	}

	//NEED GUI SUPPORT
	//cout << "\nWhere are you going? Would you like to enter a location name or tag?\n\n1 - name\n2 - tag\n";
	int nametag = 1;
	//cin >> nametag;
	switch (nametag) {  //Switch case for entering either a tag or a name of a location
	case 1:
		for (unsigned int i = 0; i < places.size(); ++i) {  //Gives options to choose from
			cout << places[i].get_name() << "\n";
		}
		cout << "Other\n\n";
		cin >> location;
		getline(cin, extra_input);
		location += extra_input;
		if (location == "Other") { 
			add_place();
			ordest.push_back(places.back()); 
		}
		else {
			for (unsigned int i = 0; i < places.size(); ++i) {
				if (location == places[i].get_name()) { 
					ordest.push_back(places[i]); 
				}
			}
		}
		break;
	case 2:
		for (unsigned int i = 0; i < places.size(); ++i) {
			places[i].print();
		}
		//cin >> tag;
		//getline(cin, extra_input);
		//tag += extra_input;
		for (unsigned int i = 0; i < places.size(); ++i) {
			vector<string> tags = places[i].get_tags();
			if ((tag == tags[0]) || (tag == tags[1])) {
				 ordest.push_back(places[i]); 
			}
		}
		break;
	default:
		break;
	}
	return ordest;
}

vector<Customer> find_neg_customer() {
	vector<Customer> negative_customers;
	for (unsigned int i = 0; i < customers.size(); ++i) {
		if (customers[i].get_balance() < 0) {
			negative_customers.push_back(customers[i]);
		}
	}
	return negative_customers;
}

Driver find_driver(vector<Place> ordest) {	//Returns the driver closest to the origin of the route
	vector<double> ranges;
	double short_distance = 100000; //No two places on earth are 100000 miles apart
	double distance;
	Driver designated_driver;  //Initialize with first driver

	for (unsigned int i = 0; i < drivers.size(); ++i) {
		Place driver_loc = drivers[i].get_place();
		distance = distance_between(ordest[0].get_latitude(), ordest[0].get_longitude(), driver_loc.get_latitude(), driver_loc.get_longitude());
		if (distance < short_distance) {
			designated_driver = drivers[i]; 
			short_distance = distance;
		}
	}
	return designated_driver;
}

vector<Driver> find_driver_within(string tag, double radius) {
	vector<Driver> eligible_drivers;
	vector<Place> possible_places;
	for (unsigned int i = 0; i < places.size(); ++i) {		//Finds all places with tag
		vector<string> tags = places[i].get_tags();
		for (unsigned int j = 0; i < tags.size(); ++j) {
			if (tags[j] == tag){
				possible_places.push_back(places[i]);
				i = places.size();
			}
		}
	}
	for (unsigned int i = 0; i < possible_places.size(); ++i) {   //Finds all drivers within the radius of all places with tag
		for (unsigned int j = 0; j < drivers.size(); ++j) {
			if (find_distance(possible_places[i], drivers[j].get_place()) <= radius) {
				eligible_drivers.push_back(drivers[j]);
			}
		}
	}
	for (unsigned int i = 0; i + 1 < eligible_drivers.size(); ++i) {	//Eliminates duplicates
		for (unsigned int j = i + 1; j < eligible_drivers.size(); ++j) {
			if (eligible_drivers[i] == eligible_drivers[j]) {			//Overload this operator
				eligible_drivers.erase(eligible_drivers.begin() + j);
				--j;
			}
		}
	}
	return eligible_drivers;
}

void request_ride() {
	//Finds driver, finds distance, credits driver account, changes driver's location, debits customer account, prints summary

	string customer_name;
	cout << "Enter your name: ";
	cin >> customer_name;

	vector<Place> ordest = ride_ordest();  // Returns vector with origin and destination
	Driver designated_driver = find_driver(ordest); //Returns driver with closest driver

	double distance = find_distance(ordest[0], ordest[1]);  //Returns distance between PLACE A and PLACE B
	designated_driver.add_funds(distance*.5);  //Credits the driver's balance
	designated_driver.change_place(ordest[1]); //Changes driver's location

	Customer designated_customer = customers[0]; //Initialization of customer requesting ride
	for (unsigned int i = 0; i < customers.size(); ++i) {
		if (customers[i].get_name() == customer_name) {
			customers[i].make_payment(distance);
			designated_customer = customers[i];
		}
	}

	return;

	//Summary of transaction -- NEED GUI SUPPORT
	//cout << "\n" << drivers[designated_driver].name << " has driven " << designated_customer.name << " from " << ordest[0].name << " to "
	//	<< ordest[1].name << ".\n" << drivers[designated_driver].name << "'s account has been credited with $" << fixed << setprecision(2) << distance / 2
	//	<< ".\nAnd " << designated_customer.name << "'s account has been charged $" << distance << ".\n";  //Summary of transaction
}

string import_data() {
	//Imports data from a file. Function returns string of filename for future overwriting.

	//NEED GUI SUPPORT
	//cout << "Please enter input filename: ";
	string filename;
	//cin >> filename;
	try {
		ifstream ist{ filename };
		if (!ist) error("Can't open data file ", filename);
		for (unsigned int i = 0; i < 3; ++i) {
			int total;
			ist >> total;
			string name;
			double balance;
			switch (i) {
			case 0:   //Import places
				for (int j = 0; j < total; ++j) {
					int number_tags;
					double lat;
					double lon;
					string tag;
					ist >> name >> lat >> lon >> number_tags;
					Place new_place{ name, lat, lon };
					for (int i = 0; i < number_tags; ++i) {
						ist >> tag;
						new_place.add_tag(tag);
					}
					places.push_back(new_place);
				}
				break;
			case 1:   //Import drivers
				for (int j = 0; j < total; ++j) {
					Place loc;
					string loc_name;
					ist >> name >> balance >> loc_name;  //Overload this operator
					for (unsigned int i = 0; i < places.size(); ++i) {
						if (places[i].get_name() == loc_name) {
							loc = places[i];
							i = places.size();
						}
					}
					Driver new_driver{ name, loc, balance };
					drivers.push_back(new_driver);
				}
				break;
			case 2:   //Import customers
				for (int j = 0; j < total; ++j) {
					ist >> name >> balance;
					Customer new_customer{ name, balance };
					customers.push_back(new_customer);
				}
				break;
			}
		}
		return filename;
	}
	catch (runtime_error e) {
		cerr << e.what();
		cout << "\n";
		keep_window_open("x");
		return "null";
	}
	
}

void export_data(string filename) {
	//Simply writes all information back out to file in the proper format.
	//If improper filename was given, info is written to file name "null"
	try {
		ofstream ost{ filename };
		if (!ost) error("Can't open output file ", filename);
		ost << places.size() << "\n";
		for (unsigned int i = 0; i < places.size(); ++i) {
			ost << places[i].get_name() << " " << places[i].get_latitude() << " " <<
				places[i].get_longitude() << " " << places[i].get_tags_length();
			vector<string> tags = places[i].get_tags();

			for (int j = 0; j < places[i].get_tags_length(); ++j) {
				ost << " " << tags[j];
			}
			ost << "\n";
		}

		ost << drivers.size() << "\n";
		for (unsigned int i = 0; i < drivers.size(); ++i) {
			ost << drivers[i].get_name() << " " << drivers[i].get_balance() << " " 
				<< drivers[i].get_place() << "\n";
		}

		ost << customers.size() << "\n";
		for (unsigned int i = 0; i < customers.size(); ++i) {
			ost << customers[i].get_name() << " " << customers[i].get_balance() << "\n";
		}
	}
	catch (runtime_error e) {
		cerr << e.what();
		keep_window_open("x");
	}
}

//int main() {
////	string filename = initializing_file();  //For HW5; calls function that imports data from input file
////
////	
////	// NEED GUI SUPPORT --> Main Menu screen
////	//int select = 1;
////	//cout << "What would you like to do?\n";
////	//while (select != 0) {
////	//	cout << "\n1 - add customer\n2 - add driver\n3 - add place\n4 - add default places, drivers, and customers\n5 - add funds\n6 - request ride\n" 
////	//		<< "7 - view customer info\n8 - view driver info\n9 - view places\n0 - quit program\n";
////	//	cin >> select;
////	//	switch (select) {
////	//	case 1:
////	//		add_customer(customers);
////	//		break;
////	//	case 2:
////	//		add_driver(drivers);
////	//		break;
////	//	case 3:
////	//		add_place(places);
////	//		break;
////	//	case 4:
////	//		initialize_places(places, drivers, customers);
////	//		break;
////	//	case 5:
////	//		double funds;
////	//		cout << "How much funds would you like to add?\n";
////	//		cin >> funds;
////	//		customers = add_funds(funds, customers);
////	//		break;
////	//	case 6:
////	//		request_ride(customers, places, drivers);
////	//		break;
////	//	case 7:
////	//		for (unsigned int i = 0; i < customers.size(); ++i) { 
////	//			customers[i].print(); 
////	//		}
////	//		break;
////	//	case 8:
////	//		for (unsigned int i = 0; i < drivers.size(); ++i) { 
////	//			drivers[i].print(); 
////	//		}
////	//		break;
////	//	case 9:
////	//		for (unsigned int i = 0; i < places.size(); ++i) {
////	//			places[i].print();
////	//		}
////	//		break;
////	//	case 0:
////	//		write_to_file(filename, places, customers, drivers);
////	//		return 0;
////	//	default:
////	//		cout << "Enter a valid selection.\n";
////	//		break;
////	//	}
////	//}
//	return 0;
//}