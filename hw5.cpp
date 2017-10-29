//Nick Nelson - UIN: 425005869 - hw5 - 10/2/17
//This program functions like Uber. It stores customers and drivers and allows customers to request rides.
//It now allows for the input of a file to import data.
//I have commented in where I would check for errors if I had more time to give to this problem.

#include "../../std_lib_facilities_4.h"

constexpr double R = 3963.1676;  //Radius of Earth
constexpr double pi = 3.14159;

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

class Geo_loc {   //Simply carries latitude, longitude, and calculated distance
	string geoname;
public:
	double lat;
	double lon;
	Geo_loc(string geoname, double lat, double lon) :geoname(geoname), lat(lat), lon(lon) {}
	Geo_loc(double lat, double lon) :geoname(""), lat(lat), lon(lon) {}
};

class Place_info {
public:
	string name;
	string address;
	Geo_loc loc;
	vector<string> tags;

	Place_info(string name, string address, Geo_loc loc)  //2 Constructors
		:name(name), address(address), loc(loc) {}
	Place_info(string name) :name(name), address(""), loc(0, 0) {}

	void print() {  //Print function within class for easy use by all objects of this type
		cout << name << "\n" << address << "\nLat: " << loc.lat << "\nLon: " << loc.lon << "\nTags:";
		for (unsigned int i = 0; i < tags.size(); ++i)
			cout << " " << tags[i];
		cout << "\n\n";
	}

	void print_tags() {
		for (unsigned int i = 0; i < tags.size(); ++i)
			cout << tags[i] << "\n";
	}
	string get_name() { return name; }   //Get functions, as requested in homework
	string get_address() { return address; }
	double get_lat() { return loc.lat; }
	double get_lon() { return loc.lon; }
	vector<string> get_tags() { return tags; }

};

class customer {
public:
	string name;
	double balance;
	customer(string name) : name(name), balance(0) {}
	void print() {
		cout << "\nName: " << name << "\nBalance: " << balance << "\n";
	}
};

class driver {
public:
	string name;
	Geo_loc loc;
	double balance;
	driver(string name) :name(name), loc(0, 0), balance(0) {};
	driver(string name, Geo_loc loc) :name(name), loc(loc), balance(0) {};
	driver(string name, Geo_loc loc, double balance) :name(name), loc(loc), balance(balance) {};

	void print() {
		cout << "\nName: " << name << "\nBalance: " << balance << "\nCoordinates: " <<
			loc.lat << ", " << loc.lon << "\n";
	}
};

void add_place(vector<Place_info>& places) {
	//Takes in user input and creates a new Place_info object
	//Unincluded error checking: I did not check to make sure that latitude and longitude were in the appropriate range.
	string extra_input;  //For places where cin cuts off a string, I store what's leftover in this variable using the getline function

	cout << "Now enter the latitude of an arbitrary point: \n";
	double input_lat;
	cin >> input_lat;
	cout << "\nEnter the corresponding longitude: \n";
	double input_long;
	cin >> input_long;

	cout << "\nWhat is the name of this location? \n";
	string input_name;
	cin >> input_name;
	getline(cin, extra_input);
	input_name += extra_input;

	cout << "\nWhat is the address?\n";
	string input_address;
	string input_address2;
	cin >> input_address;  //Cin cuts off line at first whitespace
	getline(cin, extra_input);
	input_address += extra_input;

	cout << "\nGive the location two tags...\nTag 1:";
	string input_tag1;
	cin >> input_tag1;
	cout << "\nTag 2:";
	string input_tag2;
	cin >> input_tag2;

	Geo_loc arbloc{ input_name, input_lat, input_long };
	Place_info arb{ input_name, input_address, arbloc};
	arb.tags.push_back(input_tag1);
	arb.tags.push_back(input_tag2);

	places.push_back(arb);
}

double find_distance(Place_info x, Place_info y) {  //Essentially a more user friendly distance_between function, takes Place_info as an input.
	double distance = distance_between(x.loc.lat, x.loc.lon, y.loc.lat, y.loc.lon);
	return distance;
}

void initialize_places(vector<Place_info>& places, vector<driver>& drivers, vector<customer>& customers) {  //Creates a list of landmarks to begin program
	Geo_loc brightloc{ "Bright Building", 30.6190, -96.3389 };
	Place_info bright{ "Bright_Building", "College_Station", brightloc };
	bright.tags.push_back("computer_science");
	bright.tags.push_back("aerospace");

	Geo_loc airportloc{ "Easterwood Airport", 30.5910, -96.3628 };
	Place_info airport{ "Easterwood_Airport", "College_Station", airportloc };
	airport.tags.push_back("airport");
	airport.tags.push_back("transit");

	Geo_loc bwwloc{ "Buffalo Wild Wings", 30.6358, -96.3246 };
	Place_info bww{ "Buffalo_Wild_Wings", "College_Station", bwwloc };
	bww.tags.push_back("dining");
	bww.tags.push_back("sports");

	Geo_loc ucloc{ "UCentre", 30.6254, -96.3461 };
	Place_info uc{ "UCentre", "College_Station", ucloc };
	uc.tags.push_back("housing");
	uc.tags.push_back("pool");

	Geo_loc lbloc{ "Lake Bryan", 30.7085, -96.4677 };
	Place_info lb{ "Lake_Bryan", "Bryan", lbloc};
	lb.tags.push_back("lake");
	lb.tags.push_back("camping");

	Geo_loc walloc{ "Walmart", 30.5974, -96.3005 };
	Place_info wal{ "Walmart", "College_Station", walloc };
	wal.tags.push_back("shopping");
	wal.tags.push_back("produce");

	Place_info v[6] = { bright, airport, bww, uc, lb, wal };  //Use array to place data into a single vector as requested by homework.
	for (int i = 0; i < 6; ++i) { places.push_back(v[i]); }; // I didn't want to write "pushback" and "print" 7 times each so I quickly checked the textbook on using arrays.

	driver jim{ "Jim", places[0].loc, 10 };  //Adds a couple of drivers to the program for starting purposes (leftover from HW3)
	drivers.push_back(jim);
	driver greg{ "Greg", places[0].loc, 10 };
	drivers.push_back(greg);
	customer terry{ "Terry" };
	customers.push_back(terry);
}

vector<customer> add_funds(double addend, vector<customer> customers) {  
	//Adds funds (only works for customer accounts)
	string customer_name;
	cout << "Whose account would you like to credit: ";
	cin >> customer_name;
	for (unsigned int i = 0; i < customers.size(); ++i) {
		if (customers[i].name == customer_name) {
			customers[i].balance += addend;
		}
	}
	return customers;
}

void add_customer(vector<customer>& customers) {
	string name;

	cout << "Input the customer's name: ";
	cin >> name;
	string extra_input;
	getline(cin, extra_input);
	name += extra_input;

	customer new_customer{ name  };
	customers.push_back(new_customer);
}

void add_driver(vector<driver>& drivers) {  
	//Did not error check for proper input types when using cin. Also did not check for in-range latitude and longitude.
	//Adds a driver to the program; includes name, driver number, and current coordinates
	string name;
	double lat;
	double lon;
	double balance;
	
	cout << "Input the driver's name: ";
	cin >> name;
	cout << "Input driver's current latitude: ";
	cin >> lat;
	cout << "Input driver's current longitude: ";
	cin >> lon;
	cout << "Input driver's starting balance: ";
	cin >> balance;

	Geo_loc loc = { "driver", lat, lon };

	driver new_driver{ name, loc, balance };
	drivers.push_back(new_driver);
}

vector<Place_info> ride_ordest(vector<Place_info>& places) {  
	//Returns Place_info vector with ride origin and destination
	string extra_input;

	vector<Place_info> ordest;
	cout << "\n\nWhere are you?\n\n";
	for (unsigned int i = 0; i < places.size(); ++i) {  //Lists places to choose from.
		cout << places[i].name << "\n";
	}
	cout << "Other\n\nEnter name: ";

	string location;
	string tag;
	cin >> location;
	getline(cin, extra_input);
	location += extra_input;
	if (location == "Other") { //Did not error check for improper input. User must enter one of the options verbatim
		add_place(places);
		ordest.push_back(places.back()); 
	}  
	else {
		for (unsigned int i = 0; i < places.size(); ++i) {
			if (location == places[i].name) { 
				ordest.push_back(places[i]); 
			}
		}
	}

	cout << "\nWhere are you going? Would you like to enter a location name or tag?\n\n1 - name\n2 - tag\n";
	int nametag;
	cin >> nametag;
	switch (nametag) {  //Switch case for entering either a tag or a name of a location
	case 1:
		for (unsigned int i = 0; i < places.size(); ++i) {  //Gives options to choose from
			cout << places[i].name << "\n";
		}
		cout << "Other\n\n";
		cin >> location;
		getline(cin, extra_input);
		location += extra_input;
		if (location == "Other") { 
			add_place(places);
			ordest.push_back(places.back()); 
		}
		else {
			for (unsigned int i = 0; i < places.size(); ++i) {
				if (location == places[i].name) { 
					ordest.push_back(places[i]); 
				}
			}
		}
		break;
	case 2:
		for (unsigned int i = 0; i < places.size(); ++i) {
			places[i].print_tags();
		}
		cin >> tag;
		getline(cin, extra_input);
		tag += extra_input;
		for (unsigned int i = 0; i < places.size(); ++i) {
			if ((tag == places[i].tags[0]) || (tag == places[i].tags[1])) {
				 ordest.push_back(places[i]); 
			}
		}
		break;
	default:
		break;
	}
	return ordest;
}

int find_driver(vector<Place_info> ordest, vector<driver>& drivers) {	//Returns the driver closest to the origin of the route
	vector<double> ranges;
	double short_distance = 100000; //No two places on earth are 100000 miles apart
	double distance;
	int designated_driver = 0;  //Initialize with first driver

	for (unsigned int i = 0; i < drivers.size(); ++i) {
		distance = distance_between(ordest[0].loc.lat, ordest[0].loc.lon, drivers[i].loc.lat, drivers[i].loc.lon);
		if (distance < short_distance) {
			designated_driver = i; short_distance = distance;
		}
	}
	return designated_driver;
}

void request_ride(vector<customer>& customers, vector<Place_info>& places, vector<driver>& drivers) {
	//Finds driver, finds distance, credits driver account, changes driver's location, debits customer account, prints summary

	string customer_name;
	cout << "Enter your name: ";
	cin >> customer_name;

	vector<Place_info> ordest = ride_ordest(places);  // Returns vector with origin and destination
	int designated_driver = find_driver(ordest, drivers); //Returns driver with closest driver

	double distance = find_distance(ordest[0], ordest[1]);  //Returns distance between PLACE A and PLACE B
	drivers[designated_driver].balance += distance*.5;  //Credits the driver's balance
	drivers[designated_driver].loc = ordest[1].loc; //Changes driver's location

	customer designated_customer = customers[0]; //Initialization of customer requesting ride
	for (unsigned int i = 0; i < customers.size(); ++i) {
		if (customers[i].name == customer_name) {
			customers[i].balance -= distance;
			designated_customer = customers[i];
		}
	}
	cout << "\n" << drivers[designated_driver].name << " has driven " << designated_customer.name << " from " << ordest[0].name << " to "
		<< ordest[1].name << ".\n" << drivers[designated_driver].name << "'s account has been credited with $" << fixed << setprecision(2) << distance / 2
		<< ".\nAnd " << designated_customer.name << "'s account has been charged $" << distance << ".\n";  //Summary of transaction
}

string initializing_file(vector<Place_info>& places, vector<customer>& customers, vector<driver>& drivers) {
	//Imports data from a file. Function returns string of filename for future overwriting.
	cout << "Please enter input filename: ";
	string filename;
	cin >> filename;
	try {
		ifstream ist{ filename };
		if (!ist) error("Can't open input file ", filename);
		for (unsigned int i = 0; i < 3; ++i) {
			int total;
			ist >> total;
			switch (i) {
			case 0:   //Import drivers
				for (int j = 0; j < total; ++j) {
					string driver_name;
					ist >> driver_name;
					driver new_driver{ driver_name };
					ist >> new_driver.balance >> new_driver.loc.lat >> new_driver.loc.lon;
					drivers.push_back(new_driver);
				}
				break;
			case 1:   //Import customers
				for (int j = 0; j < total; ++j) {
					string customer_name;
					ist >> customer_name;
					customer new_customer{ customer_name };
					ist >> new_customer.balance;
					customers.push_back(new_customer);
				}
				break;
			case 2:   //Import places
				for (int j = 0; j < total; ++j) {
					int number_tags;
					string place_name;
					ist >> place_name;
					Place_info new_place{ place_name };
					ist >> new_place.address >> new_place.loc.lat >> new_place.loc.lon >> number_tags;
					for (int i = 0; i < number_tags; ++i) {
						string tag;
						ist >> tag;
						new_place.tags.push_back(tag);
					}
					places.push_back(new_place);
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
		initialize_places(places, drivers, customers);
		return "null";
	}
	
}

void write_to_file(string filename, const vector<Place_info>& places, const vector<customer>& customers, const vector<driver>& drivers) {
	//Simply writes all information back out to file in the proper format.
	//If improper filename was given, info is written to file name "null"
	try {
		ofstream ost{ filename };
		if (!ost) error("Can't open output file ", filename);
		ost << drivers.size() << "\n";
		for (unsigned int i = 0; i < drivers.size(); ++i) {
			ost << drivers[i].name << " " << drivers[i].balance << " " << drivers[i].loc.lat << " " << drivers[i].loc.lon << "\n";
		}

		ost << customers.size() << "\n";
		for (unsigned int i = 0; i < customers.size(); ++i) {
			ost << customers[i].name << " " << customers[i].balance << "\n";
		}

		ost << places.size() << "\n";
		for (unsigned int i = 0; i < places.size(); ++i) {
			ost << places[i].name << " " << places[i].address << " " << places[i].loc.lat << " " <<
				places[i].loc.lon << " " << places[i].tags.size();
			for (unsigned int j = 0; j < places[i].tags.size(); ++j) {
				ost << " " << places[i].tags[j];
			}
			ost << "\n";
		}
	}
	catch (runtime_error e) {
		cerr << e.what();
		keep_window_open("x");
	}
}

int main() {
	vector<Place_info> places;
	vector<customer> customers;
	vector<driver> drivers;
	string filename = initializing_file(places, customers, drivers);  //For HW5; calls function that imports data from input file

	int select = 1;
	cout << "What would you like to do?\n";
	while (select != 0) {
		cout << "\n1 - add customer\n2 - add driver\n3 - add place\n4 - add default places, drivers, and customers\n5 - add funds\n6 - request ride\n" 
			<< "7 - view customer info\n8 - view driver info\n9 - view places\n0 - quit program\n";
		cin >> select;
		switch (select) {
		case 1:
			add_customer(customers);
			break;
		case 2:
			add_driver(drivers);
			break;
		case 3:
			add_place(places);
			break;
		case 4:
			initialize_places(places, drivers, customers);
			break;
		case 5:
			double funds;
			cout << "How much funds would you like to add?\n";
			cin >> funds;
			customers = add_funds(funds, customers);
			break;
		case 6:
			request_ride(customers, places, drivers);
			break;
		case 7:
			for (unsigned int i = 0; i < customers.size(); ++i) { 
				customers[i].print(); 
			}
			break;
		case 8:
			for (unsigned int i = 0; i < drivers.size(); ++i) { 
				drivers[i].print(); 
			}
			break;
		case 9:
			for (unsigned int i = 0; i < places.size(); ++i) {
				places[i].print();
			}
			break;
		case 0:
			write_to_file(filename, places, customers, drivers);
			return 0;
		default:
			cout << "Enter a valid selection.\n";
			break;
		}
	}
}