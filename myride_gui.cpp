#include <iostream>    // for i/o
#include <sstream>     // for string streams
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"
#include "std_lib_facilities_4.h"
#include "myride_class_functions.h"

using namespace Graph_lib;
using namespace std;
using namespace funct_lib;

struct User_window : Graph_lib::Window {

	//constructor
	User_window(Point xy,
		int w,
		int h,
		const string& title);

private:
	//widgets:
	Menu first_menu;
	Button quit_button;
	Button add_customer_button;
	Button add_driver_button;
	Button add_place_button;
	Button add_submit;
	In_box add_name;
	In_box add_balance;
	In_box add_driver_place;
	In_box add_lat;
	In_box add_lon;
	In_box add_tags;
	In_box add_photo_loc;
	Out_box add_type;
	Button remove_customer;
	Button remove_driver;
	Button remove_place;
	Button remove_submit;
	In_box remove_name;
	In_box request_placeA_name;
	In_box request_customer_name;
	In_box request_placeB_name;
	//Out_box request_info;

	char add_indicator;


	//function members
	void hide_menu() {
		first_menu.hide();
	}

	void add_pressed() {
		//add menu here
		hide_menu();
		add_customer_button.show();
		add_driver_button.show();
		add_place_button.show();
	}

	void add_customer_pressed() {
		add_indicator = 'c';

		add_customer_button.hide();
		add_driver_button.show();
		add_place_button.show();
		add_name.show();
		add_balance.show();
		add_driver_place.hide();
		add_lat.hide();
		add_lon.hide();
		add_tags.hide();
		add_photo_loc.show();
		add_submit.show();
	}

	void add_driver_pressed() {
		add_indicator = 'd';

		add_customer_button.show();
		add_driver_button.hide();
		add_place_button.show();
		add_name.show();
		add_balance.show();
		add_driver_place.show();
		add_lat.hide();
		add_lon.hide();
		add_tags.hide();
		add_photo_loc.show();
		add_submit.show();
	}

	void add_place_pressed() {
		add_indicator = 'p';

		add_customer_button.show();
		add_driver_button.show();
		add_place_button.hide();
		add_name.show();
		add_balance.hide();
		add_driver_place.hide();
		add_lat.show();
		add_lon.show();
		add_tags.show();
		add_photo_loc.show();
		add_submit.show();
	}

	void add_submit_pressed() {
		add_customer_button.hide();
		add_driver_button.hide();
		add_place_button.hide();
		add_name.hide();
		add_balance.hide();
		add_driver_place.hide();
		add_lat.hide();
		add_lon.hide();
		add_tags.hide();
		add_photo_loc.hide();

		string name = add_name.get_string();
		string photo_loc = add_photo_loc.get_string();
		double balance;
		stringstream convert;
		Place loc;
		string place_name;
		vector<string> tags;
		string hold;
		vector<Place> places = get_places();

		switch (add_indicator) {
		case 'c':
			convert << add_balance.get_string();
			convert >> balance;
			add_customer(name, balance, photo_loc);

		case 'd':
			convert << add_balance.get_string();
			convert >> balance;
			place_name = add_driver_place.get_string();
			for (unsigned int i = 0; i < places.size(); ++i) {
				if (places[i].get_name() == place_name) {
					loc = places[i];
					i = places.size();
				}
			}
			add_driver(name, balance, loc, photo_loc);

		case'p':
			double lat;
			double lon;

			convert << add_lat.get_string();
			convert >> lat;
			convert << add_lon.get_string();
			convert >> lon;
			convert.str(add_tags.get_string());
			while (!(convert.eof())) {
				convert >> hold;
				tags.push_back(hold);
			}
			add_place(name, lat, lon, tags, photo_loc);
		}
	}

	void remove_pressed() {
		hide_menu();
		remove_customer.show();
		remove_driver.show();
		remove_place.show();
	}

	void remove_customer_pressed() {
		remove_name.show();
		remove_submit.show();
		remove_customer.hide();
		remove_driver.show();
		remove_place.show();
	}

	void remove_driver_pressed() {
		remove_name.show();
		remove_submit.show();
		remove_customer.show();
		remove_driver.hide();
		remove_place.show();
	}

	void remove_place_pressed() {
		remove_name.show();
		remove_submit.show();
		remove_customer.show();
		remove_driver.show();
		remove_place.hide();
	}

	void remove_submit_pressed() {
		remove_name.show();
		remove_submit.show();
		remove_customer.show();
		remove_driver.show();
		remove_place.show();
	}

	void request_pressed() {
		request_placeA_name.show();
		request_placeB_name.show();
		request_customer_name.show();
		hide_menu();
	}

	void display_presed() {
		//add menu here
		hide_menu();
	}

	void menu_pressed() {
		first_menu.show();
	}

	void quit() {
		export_data();
		hide();
	};

	//callback functions
	static void cb_add(Address, Address);
	static void cb_remove(Address, Address);
	static void cb_request(Address, Address);
	static void cb_display(Address, Address);
	static void cb_menu(Address, Address);
	static void cb_quit(Address, Address);
	static void cb_add_customer(Address, Address);
	static void cb_add_driver(Address, Address);
	static void cb_add_place(Address, Address);
	static void cb_add_submit(Address, Address);
	static void cb_remove_customer(Address, Address);
	static void cb_remove_driver(Address, Address);
	static void cb_remove_place(Address, Address);
	static void cb_remove_submit(Address, Address);
};

User_window::User_window(Point xy, int w, int h, const string& title) :
	//initialization
	Window(xy, w, h, title),

	quit_button(
		Point(x_max() / 2 - 50, 5 * y_max() / 6 - 20),
		100, 40,
		"Quit",
		cb_quit),

	first_menu(
		Point(x_max() / 2 - 50, y_max() / 6),
		100, 40,
		Menu::vertical,
		"My Ride"),

	add_customer_button(
		Point(x_max() / 4 - 50, 50),
		100, 40,
		"Customer",
		cb_add_customer),

	add_driver_button(
		Point(2 * x_max() / 4 - 50, 50),
		100, 40,
		"Driver",
		cb_add_driver),

	add_place_button(
		Point(3 * x_max() / 4 - 50, 50),
		100, 40,
		"Place",
		cb_add_place),

	add_submit(
		Point(x_max() - 100, y_max() - 80),
		100, 40,
		"Submit",
		cb_add_submit),

	add_name(
		Point(x_max() / 2 - 50, 100),
		100, 20,
		"Name:"),

	add_balance(
		Point(x_max() / 2 - 50, 130),
		100, 20,
		"Balance:"),

	add_driver_place(
		Point(x_max() / 2 - 50, 160),
		100, 20,
		"Place:"),

	add_lat(
		Point(x_max() / 2 - 50, 190),
		100, 20,
		"Latitude:"),

	add_lon(
		Point(x_max() / 2 - 50, 220),
		100, 20,
		"Longitude:"),

	add_tags(
		Point(x_max() / 2 - 50, 250),
		200, 20,
		"Tags:"),

	add_photo_loc(
		Point(x_max() / 2 - 50, 280),
		100, 20,
		"Photo filename:"),

	add_type(
		Point(x_max() - 100, y_max() - 100),
		100, 20,
		"Selected Type:"),

	remove_customer(
		Point(x_max() / 4 - 50, 50),
		100, 40,
		"Customer",
		cb_remove_customer),

	remove_driver(
		Point(2 * x_max() / 4 - 50, 50),
		100, 40,
		"Driver",
		cb_remove_driver),

	remove_place(
		Point(3 * x_max() / 4 - 50, 50),
		100, 40,
		"Place",
		cb_remove_place),

	remove_submit(
		Point(x_max() - 100, y_max() - 80),
		100, 40,
		"Submit",
		cb_remove_submit),

	remove_name(
		Point(x_max() / 2 - 50, 100),
		100, 20,
		"Name:"),

	request_placeA_name(
		Point(x_max() / 2 - 50, 120),
		100, 20,
		"Place A:"
	),

	request_customer_name(
		Point(x_max() / 2 - 50, 100),
		100, 20,
		"Customer Name:"
	),

	request_placeB_name(
		Point(x_max() / 2 - 50, 140),
		100, 20,
		"Place B:"
	)

{
	//constructor body

	attach(quit_button);
	attach(add_customer_button);
	attach(add_driver_button);
	attach(add_place_button);
	attach(add_submit);
	attach(add_name);
	attach(add_balance);
	attach(add_driver_place);
	attach(add_lat);
	attach(add_lon);
	attach(add_tags);
	attach(add_photo_loc);
	attach(add_type);
	attach(remove_customer);
	attach(remove_driver);
	attach(remove_place);
	attach(remove_submit);
	attach(remove_name);
	attach(request_placeA_name);
	attach(request_placeB_name);
	attach(request_customer_name);


	add_customer_button.hide();
	add_driver_button.hide();
	add_place_button.hide();
	add_submit.hide();
	add_name.hide();
	add_balance.hide();
	add_driver_place.hide();
	add_lat.hide();
	add_lon.hide();
	add_tags.hide();
	add_photo_loc.hide();
	add_type.hide();
	remove_customer.hide();
	remove_driver.hide();
	remove_place.hide();
	remove_submit.hide();
	remove_name.hide();
	request_placeA_name.hide();
	request_placeB_name.hide();
	request_customer_name.hide();

	first_menu.attach(new Button(Point(0, 0), 0, 0, "add", cb_add));
	first_menu.attach(new Button(Point(0, 0), 0, 0, "remove", cb_remove));
	first_menu.attach(new Button(Point(0, 0), 0, 0, "request", cb_request));
	first_menu.attach(new Button(Point(0, 0), 0, 0, "display", cb_display));
	attach(first_menu);

}

//callback functions for buttons
void User_window::cb_quit(Address, Address pw) {
	reference_to<User_window>(pw).quit();
}

void User_window::cb_add(Address, Address pw) {
	reference_to<User_window>(pw).add_pressed();
}

void User_window::cb_add_customer(Address, Address pw) {
	reference_to<User_window>(pw).add_customer_pressed();
}

void User_window::cb_add_driver(Address, Address pw) {
	reference_to<User_window>(pw).add_driver_pressed();
}

void User_window::cb_add_place(Address, Address pw) {
	reference_to<User_window>(pw).add_place_pressed();
}

void User_window::cb_add_submit(Address, Address pw) {
	reference_to<User_window>(pw).add_submit_pressed();
}

void User_window::cb_remove(Address, Address pw) {
	reference_to<User_window>(pw).remove_pressed();
}

void User_window::cb_remove_customer(Address, Address pw) {
	reference_to<User_window>(pw).remove_customer_pressed();
}

void User_window::cb_remove_driver(Address, Address pw) {
	reference_to<User_window>(pw).remove_driver_pressed();
}

void User_window::cb_remove_place(Address, Address pw) {
	reference_to<User_window>(pw).remove_place_pressed();
}

void User_window::cb_remove_submit(Address, Address pw) {
	reference_to<User_window>(pw).remove_submit_pressed();
}

void User_window::cb_request(Address, Address pw) {
	reference_to<User_window>(pw).request_pressed();
}

void User_window::cb_display(Address, Address pw) {
	//reference to display pressed
}

void User_window::cb_menu(Address, Address pw) {
	reference_to<User_window>(pw).menu_pressed();
}

int main() {
	try {
		import_data();
		User_window win(Point(100, 100), 600, 600, "My Ride");
		return gui_main();
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
}
