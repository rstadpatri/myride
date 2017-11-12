#include <iostream>    // for i/o
#include <sstream>     // for string streams
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"
#include "std_lib_facilities_4.h"

using namespace Graph_lib;
using namespace std;

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
	Button add_customer;
	Button add_driver;
	Button add_place;
	Button add_submit;
	In_box add_name;
	In_box add_balance;
	In_box add_driver_place;
	In_box add_lat;
	In_box add_lon;
	In_box add_tags;
	In_box add_photo_loc;
	Out_box add_type;


	//function members
	void hide_menu() {
		first_menu.hide();
	}

	void add_pressed() {
		//add menu here
		hide_menu();
		add_customer.show();
		add_driver.show();
		add_place.show();
	}

	void add_customer_pressed() {
		add_customer.hide();
		add_driver.show();
		add_place.show();
		add_name.show();
		add_balance.show();
		add_driver_place.hide();
		add_lat.hide();
		add_lon.hide();
		add_tags.hide();
		add_photo_loc.show();
	}

	void add_driver_pressed() {
		add_customer.show();
		add_driver.hide();
		add_place.show();
		add_name.show();
		add_balance.show();
		add_driver_place.show();
		add_lat.hide();
		add_lon.hide();
		add_tags.hide();
		add_photo_loc.show();
	}

	void add_place_pressed() {
		add_customer.show();
		add_driver.show();
		add_place.hide();
		add_name.show();
		add_balance.show();
		add_driver_place.show();
		add_lat.hide();
		add_lon.hide();
		add_tags.hide();
		add_photo_loc.show();
	}

	void add_submit_pressed() {
		add_customer.hide();
		add_driver.hide();
		add_place.hide();
		add_name.hide();
		add_balance.hide();
		add_driver_place.hide();
		add_lat.hide();
		add_lon.hide();
		add_tags.hide();
		add_photo_loc.hide();
	}

	void remove_pressed() {
		//remove menu here
		hide_menu();
	}

	void request_pressed() {
		//request menu here
		hide_menu();
	}

	void display_presed() {
		//add menu here
		hide_menu();
	}

	void menu_pressed() {
		first_menu.show();
	}

	void quit();

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
};

User_window::User_window(Point xy, int w, int h, const string& title) :
	//initialization
	Window(xy, w, h, title),

	quit_button(
		Point(x_max()/2 - 50, 5*y_max()/6-20),
		100, 40,
		"Quit",
		cb_quit),

	first_menu(
		Point(x_max()/2 - 50, y_max()/6),
		100, 40,
		Menu::vertical,
		"My Ride"),

	add_customer(
		Point(x_max()/4 - 50, 50),
		100, 40,
		"Customer",
		cb_add_customer),

	add_driver(
		Point(2*x_max()/4 - 50, 50),
		100, 40,
		"Driver",
		cb_add_driver),
	
	add_place(
		Point(3*x_max()/4 - 50, 50),
		100, 40,
		"Place",
		cb_add_place),

	add_submit(
		Point(x_max()-100, y_max()-80),
		100, 40,
		"Submit",
		cb_add_submit),

	add_name(									
		Point(x_max() / 2 - 50, 100),		
		100, 20,
		"Name:"),

	add_balance	(
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
		"Selected Type:")

{
	//constructor body

	attach(quit_button);

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
void User_window::quit() {
	hide();
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
	//code for remove menu
}

void User_window::cb_request(Address, Address pw) {
	//code for request menu
}

void User_window::cb_display(Address, Address pw) {
	//code for display menu
}

void User_window::cb_menu(Address, Address pw) {
	reference_to<User_window>(pw).menu_pressed();
}

int main() {
	try {
		User_window win(Point(100, 100), 600, 600, "My Ride");
		return gui_main();
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
}
