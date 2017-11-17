
#include "std_lib_facilities_4.h"

#ifndef LOGIC_FUNCTIONS
#define LOGIC_FUNCTIONS
namespace funct_lib {

	double to_radian(double degree);  //Conversion from degrees to radians

	double distance_between(double x1d, double y1d, double x2d, double y2d);
		// Formula for calculating distance between waypoints

	class Member {
		string name;
		string photo_loc;

	protected:
		Member(string s) : name(s), photo_added(false) {/*photo_loc = default_loc*/};
		Member(string s, string p) : name(s), photo_loc(p), photo_added(true) {};
		Member() {};

	public:
		bool photo_added;
		string get_name() const { return name; };
		string get_photo() const { return photo_loc; }
		void add_photo(string s) {
			photo_loc = s;
		}
		virtual string display() {
			return "Virtual function error";
		}
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

	class Place : public Member {
		double lat;
		double lon;
		vector<string> tags;

	public:
		Place(string n, double lat, double lon)
			: Member(n), lat(lat), lon(lon) {}

		Place(string n, double lat, double lon, string photo_loc)
			: Member(n, photo_loc), lat(lat), lon(lon) {}

		Place(string n, double lat, double lon, vector<string> tags, string photo_loc)
			: Member(n, photo_loc), lat(lat), lon(lon) {
			for (unsigned int i = 0; i < tags.size(); ++i) {
				add_tag(tags[i]);
			}
			}

		Place() {}

		double get_latitude() const { return lat; }
		double get_longitude() const { return lon; }
		int get_tags_length() const { return tags.size(); }

		vector<string> get_tags() const { return tags; }

		void add_tag(string s) {
			tags.push_back(s);
		}

		void print() {};  // Define for GUI

		string display() {
			string for_display;
			for_display = get_name() + "\n";
			for (unsigned int i = 0; i < tags.size(); ++i) {
				for_display = for_display + tags[i] + " ";
			}
			for_display = for_display + "\n" + to_string(lat) + "\n" + to_string(lon) + "\n";
			return for_display;
		}
	};

	class Customer : public Member {
	private:
		double balance;

	public:
		Customer(string n) : Member(n), balance(0) {}
		Customer(string n, double bal) : Member(n), balance(bal) {};
		Customer(string n, double bal, string photo_loc) : Member(n, photo_loc), balance(bal) {};

		double get_balance() const { return balance; }
		void make_payment(double amount) {
			balance = balance - amount;
		}
		void add_funds(double amount) {
			balance = balance + amount;
		}

		string display() {
			string for_display;
			for_display = get_name() + "\n"
				+ to_string(get_balance()) + "\n";
			return for_display;
		}
	};

	class Driver : public Member {
		Place loc;
		double balance;

	public:
		Driver() {};
		Driver(string name, Place loc) : Member(name), loc(loc), balance(0) {};
		Driver(string name, Place loc, double balance) : Member(name), loc(loc), balance(balance) {};
		Driver(string name, Place loc, double balance, string photo_loc)
			: Member(name, photo_loc), loc(loc), balance(balance) {};

		double get_balance() const { return balance; }
		Place get_place() const { return loc; }
		void add_funds(double amount) {
			balance = balance + amount;
		}
		void change_place(Place p) {
			loc = p;
		}

		string display() {
			string for_display;
			for_display = get_name() + "\n" + to_string(balance) + "\n" + loc.get_name()
				+ "\n" + to_string(loc.get_latitude()) + "\n" + to_string(loc.get_longitude()) + "\n";
			return for_display;
		}
	};

	vector<Place>& get_places();
	vector<Customer>& get_customers();
	vector<Driver>& get_drivers();

	bool operator==(Driver a, Driver b);

	void add_place(string name, double lat, double lon, vector<string> tags, string photo_loc);

	double find_distance(Place x, Place y);  //Essentially a more user friendly distance_between function, takes Place_info as an input.

	void add_funds(double addend);

	void add_customer(string name, double balance, string photo_loc);

	template<class C> void remove(vector<C>& list, string name);  //GUI will need to provide call with different types of classes

	void add_driver(string name, double balance, Place loc, string photo_loc);

	vector<Place> ride_ordest();

	Driver find_driver(vector<Place> ordest);

	vector<Driver> find_driver_within(string tag, double radius);

	void request_ride();

	void import_data();

	void export_data();
}
#endif