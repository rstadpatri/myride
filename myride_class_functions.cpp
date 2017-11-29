//Nick Nelson - UIN: 425005869 - hw5 - 10/2/17
//This program functions like Uber. It stores customers and drivers and allows customers to request rides.
//It now allows for the input of a file to import data.
//I have commented in where I would check for errors if I had more time to give to this problem.

#include "std_lib_facilities_4.h"
#include "myride_class_functions.h"

	constexpr double R = 3963.1676;  //Radius of Earth
	constexpr double pi = 3.14159;
	string filename = "Data File";

	namespace funct_lib{

	vector<Place> places;
	vector<Customer> customers;
	vector<Driver> drivers;

	vector<Place>& get_places() {
		return places;
	}

	vector<Customer>& get_customers() {
		return customers;
	}

	vector<Driver>& get_drivers() {
		return drivers;
	}

	double to_radian(double degree) {  //Conversion from degrees to radians
		double radian = degree*pi / 180;
		return radian;
	}

	double distance_between(double x1d, double y1d, double x2d, double y2d) {  
		// Formula for calculating distance between waypoints
		double x1 = to_radian(x1d);
		double y1 = to_radian(y1d);
		double x2 = to_radian(x2d);
		double y2 = to_radian(y2d);

		double distance = acos(sin(x1)*sin(x2) + cos(x1)*cos(x2)*cos(y1 - y2))*R;
		return distance;
	}

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

	void add_place(string name, double lat, double lon, vector<string> tags, string photo_loc) {
		//Takes in user input and creates a new Place_info object
		//Unincluded error checking: I did not check to make sure that latitude and longitude were in the appropriate range.
		
		if (photo_loc == "") {
			Place new_place{ name, lat, lon, tags };
			places.push_back(new_place);
		}
		else {
			Place new_place{ name, lat, lon, tags, photo_loc };
			places.push_back(new_place);
		}

	}

	double find_distance(Place x, Place y) {  
		//Essentially a more user friendly distance_between function, takes Place_info as an input.
		double distance = distance_between(x.get_latitude(), x.get_longitude(), y.get_latitude(), y.get_longitude());
		return distance;
	}

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

	void add_customer(string name, double balance, string photo_loc) {
		if (photo_loc == "") {
			Customer new_customer{ name, balance };
			customers.push_back(new_customer);
		}
		else {
			Customer new_customer{ name, balance, photo_loc };
			customers.push_back(new_customer);
		}
	}

	void remove_member(char c, string name) { 
		switch (c) {
		case 'c':
			for (unsigned int i = 0; i < customers.size(); ++i) {
				if (customers[i].get_name() == name) {
					customers.erase(customers.begin() + i);
					break;
				}
			}
		case 'd':
			for (unsigned int i = 0; i < drivers.size(); ++i) {
				if (drivers[i].get_name() == name) {
					drivers.erase(drivers.begin() + i);
					break;
				}
			}
			break;
		case 'p':
			for (unsigned int i = 0; i < places.size(); ++i) {
				if (places[i].get_name() == name) {
					places.erase(places.begin() + i);
					break;
				}
			}
			break;
		default:
			break;
		}
	}

	void add_driver(string name, double balance, Place loc, string photo_loc) {
		//Adds a driver to the program; includes name, driver number, and current coordinates

		if (photo_loc == "") {
			Driver new_driver{ name, loc, balance };
			drivers.push_back(new_driver);
		}
		else {
			Driver new_driver{ name, loc, balance, photo_loc };
			drivers.push_back(new_driver);
		}
	}

	vector<Place> ride_ordest(string location, int nametag, string destination_tag) {
		// Returns the origin and destination of the ride
		vector<Place> ordest;

		for (unsigned int i = 0; i < places.size(); ++i) {
			if (location == places[i].get_name()) {
				ordest.push_back(places[i]);
				i = places.size();
			}
		}

		switch (nametag) {  //Switch case for entering either a tag or a name of a location
		
		case 1:
			for (unsigned int i = 0; i < places.size(); ++i) {
				if (destination_tag == places[i].get_name()) {
					ordest.push_back(places[i]);
					break;
				}
			}
			break;

		case 2:
			for (unsigned int i = 0; i < places.size(); ++i) {
				vector<string> tags = places[i].get_tags();
				for (unsigned int j = 0; j < tags.size(); ++j) {
					if (destination_tag == tags[j]) {
						ordest.push_back(places[i]);
						break;
					}
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

	int find_driver(vector<Place> ordest) {	//Returns the driver closest to the origin of the route
		vector<double> ranges;
		double short_distance = 100000; //No two places on earth are 100000 miles apart
		double distance;
		int designated_driver;  //Initialize with first driver

		for (unsigned int i = 0; i < drivers.size(); ++i) {
			Place driver_loc = drivers[i].get_place();
			distance = distance_between(ordest[0].get_latitude(), ordest[0].get_longitude(),
				driver_loc.get_latitude(), driver_loc.get_longitude());
			if (distance < short_distance) {
				designated_driver = i;
				short_distance = distance;
			}
		}
		return designated_driver;
	}

	vector<Driver> find_driver_within(string tag, double radius) {
		// Finds all drivers within radius of all locations with tag
		vector<Driver> eligible_drivers;
		vector<Place> possible_places;
		for (unsigned int i = 0; i < places.size(); ++i) {		//Finds all places with tag
			vector<string> tags = places[i].get_tags();
			for (unsigned int j = 0; j < tags.size(); ++j) {
				if (tags[j] == tag) {
					possible_places.push_back(places[i]);
					j = tags.size();
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
		for (unsigned int i = 0; (i + 1) < eligible_drivers.size(); ++i) {	//Eliminates duplicates
			for (unsigned int j = i + 1; j < eligible_drivers.size(); ++j) {
				if (eligible_drivers[i] == eligible_drivers[j]) {			//Overload this operator
					eligible_drivers.erase(eligible_drivers.begin() + j);
					--j;
				}
			}
		}
		return eligible_drivers;
	}

	vector<Place> find_places_tags(string tag) {
		// Finds all places with a certain tag
		vector<Place> tagged_places;
		for (unsigned int i = 0; i < places.size(); ++i) {
			vector<string> tags = places[i].get_tags();
			for (unsigned int j = 0; j < tags.size(); ++j) {
				if (tags[j] == tag) {
					tagged_places.push_back(places[i]);
					j = tags.size();
				}
			}
		}
		return tagged_places;
	}

	string request_ride(string customer_name, string location, int nametag, string destination_tag) {
		//Finds driver, finds distance, credits driver account, changes driver's location, debits customer account, prints summary

		vector<Place> ordest = ride_ordest(location, nametag, destination_tag);  // Returns vector with origin and destination
		int designated_driver = find_driver(ordest); //Returns driver with closest driver

		double distance = find_distance(ordest[0], ordest[1]);  //Returns distance between PLACE A and PLACE B
		drivers[designated_driver].add_funds(distance*.5);  //Credits the driver's balance
		drivers[designated_driver].change_place(ordest[1]); //Changes driver's location

		Customer designated_customer = customers[0]; //Initialization of customer requesting ride
		for (unsigned int i = 0; i < customers.size(); ++i) {
			if (customers[i].get_name() == customer_name) {
				customers[i].make_payment(distance);
				designated_customer = customers[i];
			}
		}

		//Summary of transaction

		stringstream sm;
		string dist;
		sm << fixed << setprecision(2);
		sm << distance;
		sm >> dist;
		sm.clear();

		string halfdist;
		sm << distance / 2;
		sm >> halfdist;

		string summary = "\n" + drivers[designated_driver].get_name() + " has driven " 
			+ designated_customer.get_name() + " from " + ordest[0].get_name() + " to "
			+ ordest[1].get_name() + ".\n" + drivers[designated_driver].get_name() 
			+ "'s account has been credited with $" + halfdist + ".\nAnd " 
			+ designated_customer.get_name() + "'s account has been charged $" 
			+ dist + ".\n";

		return summary;
	}

	void import_data() {
		//Imports data from the master file. 

		try {
			ifstream ist{ "Data File" };
			if (!ist) error("Can't open data file ", filename);
			for (unsigned int i = 0; i < 3; ++i) {
				int total;
				ist >> total;
				string name;
				double balance;
				int photo_loaded;
				string photo_loc;

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
						ist >> photo_loaded;
						if (photo_loaded != 0) {
							ist >> photo_loc;
							new_place.add_photo(photo_loc);
						}
						places.push_back(new_place);
					}
					break;
				case 1:   //Import drivers
					for (int j = 0; j < total; ++j) {
						Place loc;
						string loc_name;
						ist >> name >> balance >> loc_name >> photo_loaded;  //Overload this operator
						for (unsigned int i = 0; i < places.size(); ++i) {
							if (places[i].get_name() == loc_name) {
								loc = places[i];
								i = places.size();
							}
						}
						if (photo_loaded == 0) {
							Driver new_driver{ name, loc, balance };
							drivers.push_back(new_driver);
						}
						else {
							ist >> photo_loc;
							Driver new_driver{ name, loc, balance, photo_loc };
							drivers.push_back(new_driver);
						}
					}
					break;
				case 2:   //Import customers
					for (int j = 0; j < total; ++j) {
						ist >> name >> balance >> photo_loaded;
						if (photo_loaded == 0) {
							Customer new_customer{ name, balance };
							customers.push_back(new_customer);
						}
						else {
							ist >> photo_loc;
							Customer new_customer{ name, balance, photo_loc };
							customers.push_back(new_customer);
						}
					}
					break;
				}
			}
			return;
		}
		catch (runtime_error e) {
			cerr << e.what();
			cout << "\n";
			keep_window_open("x");
			return;
		}
	}

	void export_data() {
		//Simply writes all information back out to file in the proper format.

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
				ost << places[i].export_photo() << "\n";
			}

			ost << drivers.size() << "\n";
			for (unsigned int i = 0; i < drivers.size(); ++i) {
				ost << drivers[i].get_name() << " " << drivers[i].get_balance() << " "
					<< drivers[i].get_place() << " " << drivers[i].export_photo() << "\n";
			}

			ost << customers.size() << "\n";
			for (unsigned int i = 0; i < customers.size(); ++i) {
				ost << customers[i].get_name() << " " << customers[i].get_balance() << " " 
					<< customers[i].export_photo() << "\n";
			}
		}
		catch (runtime_error e) {
			cerr << e.what();
			keep_window_open("x");
		}
	}
	}