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
	Button menu_button;
	Button quit_button;

	//function members
	void hide_menu() {
		first_menu.hide();
		menu_button.show();
	}

	void add_pressed() {
		//add menu here
		hide_menu();
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
		menu_button.hide();
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
};

User_window::User_window(Point xy, int w, int h, const string& title) :
	//initialization
	Window(xy, w, h, title),

	quit_button(
		Point(x_max() - 70, 0),
		70, 20,
		"Quit",
		cb_quit),

	first_menu(
		Point(x_max() - 70, 30),
		70, 20,
		Menu::vertical,
		"My Ride"),

	menu_button(
		Point(x_max() - 80, 30),
		80, 20,
		"My Ride",
		cb_menu)
{
	//constructor body

	attach(quit_button);

	first_menu.attach(new Button(Point(0, 0), 0, 0, "add", cb_add));
	first_menu.attach(new Button(Point(0, 0), 0, 0, "remove", cb_remove));
	first_menu.attach(new Button(Point(0, 0), 0, 0, "request", cb_request));
	first_menu.attach(new Button(Point(0, 0), 0, 0, "display", cb_display));
	attach(first_menu);
	first_menu.hide();

	attach(menu_button);
}

//callback functions for buttons
void User_window::cb_quit(Address, Address pw) {
	reference_to<User_window>(pw).quit();
}
void User_window::quit() {
	hide();
}

void User_window::cb_add(Address, Address pw) {
	//code for add menu
}

void User_window::cb_remove(Address, Address pw) {
	//code for add menu
}

void User_window::cb_request(Address, Address pw) {
	//code for add menu
}

void User_window::cb_display(Address, Address pw) {
	//code for add menu
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
