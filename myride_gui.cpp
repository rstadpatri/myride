#include <iostream>    // for i/o
#include <sstream>     // for string streams
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"
#include "std_lib_facilities_4.h"
#include "myride_class_functions.h"
#include "display_gui_2_by_2.h"

using namespace Graph_lib;
using namespace std;
using namespace funct_lib;
using namespace disp_lib;

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
	Button request_name;
	Button request_tag;
	Out_box request_info;
	Button request_submit;
	Out_box request_summary;
	Button request_okay;
	Button display_customers_all;
	Button display_customers_neg;
	Button display_drivers_all;
	Button display_drivers_rad;
	In_box display_drivers_tag;
	In_box display_drivers_radius;
	Button display_places_all;
	Button display_places_withtag;
	In_box display_places_tag;
	Menu display_size_menu;

	char add_indicator;
	char remove_indicator;
	int nametag_indicator;
	int disp_size;

	//function members
	void hide_menu() {
		first_menu.hide();
	}

	void show_menu() {
		first_menu.show();
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
		add_submit.hide();

		string name = add_name.get_string();
		string photo_loc = add_photo_loc.get_string();
		double balance;
		stringstream convert;
		Place loc;
		string place_name;
		vector<string> tags;
		string hold;
		vector<Place>& places = get_places();

		switch (add_indicator) {
		case 'c':
			convert << add_balance.get_string();
			convert >> balance;
			add_customer(name, balance, photo_loc);
			break;
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
			break;
		case'p':
			double lat;
			double lon;

			convert << add_lat.get_string();
			convert >> lat;
			convert.clear();
			convert << add_lon.get_string();
			convert >> lon;
			convert.clear();
			convert << add_tags.get_string();
			while (!(convert.eof())) {
				convert >> hold;
				tags.push_back(hold);
			}
			add_place(name, lat, lon, tags, photo_loc);
			break;
		}

		show_menu();
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

		remove_indicator = 'c';
	}

	void remove_driver_pressed() {
		remove_name.show();
		remove_submit.show();
		remove_customer.show();
		remove_driver.hide();
		remove_place.show();

		remove_indicator = 'd';
	}

	void remove_place_pressed() {
		remove_name.show();
		remove_submit.show();
		remove_customer.show();
		remove_driver.show();
		remove_place.hide();

		remove_indicator = 'p';
	}

	void remove_submit_pressed() {
		remove_name.hide();
		remove_submit.hide();
		remove_customer.hide();
		remove_driver.hide();
		remove_place.hide();
		show_menu();

		string name = remove_name.get_string();

		remove_member(remove_indicator, name);
	}

	void request_pressed() {
		nametag_indicator = 1;
		request_placeA_name.show();
		request_placeB_name.show();
		request_customer_name.show();
		request_tag.show();

		vector<Place>& places = get_places();
		string place_list;
		for (int i = 0; i < places.size(); ++i) {
			place_list += places[i].get_name() + " : "
				+ places[i].display_tags() + "\n";
		}
		request_info.put(place_list);
		request_info.show();
		request_submit.show();

		hide_menu();
	}

	void request_name_pressed() {
		request_name.hide();
		request_tag.show();
		nametag_indicator = 1;
	}

	void request_tag_pressed() {
		request_tag.hide();
		request_name.show();
		nametag_indicator = 2;
	}

	void request_submit_pressed() {
		request_placeA_name.hide();
		request_placeB_name.hide();
		request_customer_name.hide();
		request_tag.hide();
		request_name.hide();
		request_info.hide();
		request_submit.hide();

		string loc_name = request_placeA_name.get_string();
		string customer_name = request_customer_name.get_string();
		string dest_name = request_placeB_name.get_string();

		string summary = request_ride(customer_name, loc_name, nametag_indicator, dest_name);

		request_summary.show();
		request_summary.put(summary);
		request_okay.show();
	}

	void request_okay_pressed() {
		request_summary.hide();
		request_okay.hide();
		show_menu();
	}

	void display_pressed() {
		display_size_menu.show();
		display_customers_all.show();
		display_customers_neg.show();
		display_drivers_all.show();
		display_drivers_tag.show();
		display_drivers_rad.show();
		display_drivers_radius.show();
		display_places_all.show();
		display_places_withtag.show();
		display_places_tag.show();
		hide_menu();
	}

	int display_customers_all_pressed() {
		display_customers_all.hide();
		display_customers_neg.hide();
		display_drivers_all.hide();
		display_drivers_tag.hide();
		display_drivers_rad.hide();
		display_drivers_radius.hide();
		display_places_all.hide();
		display_places_withtag.hide();
		display_places_tag.hide();
		display_size_menu.hide();
		show_menu();

		switch (disp_size) {
		default:
			Disp_2 customer_disp(Point(x_max() - 600, y_max() - 600), 600, 600, 
				"All Customers", get_customers());
			return gui_main();
		}
		//opens display GUI (separate window)
		//implement logic
	}

	int display_customers_neg_pressed() {
		display_customers_all.hide();
		display_customers_neg.hide();
		display_drivers_all.hide();
		display_drivers_tag.hide();
		display_drivers_rad.hide();
		display_drivers_radius.hide();
		display_places_all.hide();
		display_places_withtag.hide();
		display_places_tag.hide();
		display_size_menu.hide();
		show_menu();

		switch (disp_size) {
		default:
			Disp_2 cust_neg(Point(x_max() - 600, y_max() - 600), 600, 600, 
				"Negative Customers", find_neg_customer());
			return gui_main();
		}
		//opens display GUI (separate window)
		//implement logic
	}

	int display_drivers_all_pressed() {
		display_customers_all.hide();
		display_customers_neg.hide();
		display_drivers_all.hide();
		display_drivers_tag.hide();
		display_drivers_rad.hide();
		display_drivers_radius.hide();
		display_places_all.hide();
		display_places_withtag.hide();
		display_places_tag.hide();
		display_size_menu.hide();
		show_menu();

		switch (disp_size) {
		default:
			Disp_2 driv_disp(Point(x_max() - 600, y_max() - 600), 600, 600, 
				"All Customers", get_drivers());
			return gui_main();
		}

		//opens display GUI (separate window)
		//implement logic
	}

	int display_drivers_rad_pressed() {  //NEEDS LOGIC
		display_customers_all.hide();
		display_customers_neg.hide();
		display_drivers_all.hide();
		display_drivers_tag.hide();
		display_drivers_rad.hide();
		display_drivers_radius.hide();
		display_places_all.hide();
		display_places_withtag.hide();
		display_places_tag.hide();
		display_size_menu.hide();
		show_menu();
		stringstream ss;
		double radius;
		ss << display_drivers_radius.get_string();
		ss >> radius;
		string tag = display_drivers_tag.get_string();
		vector<Driver> drivs = find_driver_within(tag, radius);

		switch (disp_size) {
		default:
			Disp_2 rad_driv_disp(Point(x_max() - 600, y_max() - 600), 600, 600, "Drivers", drivs);
			return gui_main();
		}
		//opens display GUI (separate window)
		//implement logic
	}

	int display_places_all_pressed() {
		display_customers_all.hide();
		display_customers_neg.hide();
		display_drivers_all.hide();
		display_drivers_tag.hide();
		display_drivers_rad.hide();
		display_drivers_radius.hide();
		display_places_all.hide();
		display_places_withtag.hide();
		display_places_tag.hide();
		display_size_menu.hide();
		show_menu();
		//opens display GUI (separate window)
		//implement logic

		switch (disp_size) {
		default:
			Disp_2 all_place(Point(x_max() - 600, y_max() - 600), 600, 600,
				"Places", get_places());
			return gui_main();
		}
	}

	int display_places_withtag_pressed() {
		display_customers_all.hide();
		display_customers_neg.hide();
		display_drivers_all.hide();
		display_drivers_tag.hide();
		display_drivers_rad.hide();
		display_drivers_radius.hide();
		display_places_all.hide();
		display_places_withtag.hide();
		display_places_tag.hide();
		display_size_menu.hide();
		show_menu();

		string tag = display_places_tag.get_string();

		switch (disp_size) {
		default:
			Disp_2 tag_places(Point(x_max() - 600, y_max() - 600), 600, 600,
				"Places with tags", find_places_tags(tag));
			return gui_main();
		}
		//opens display GUI (separate window)
		//implement logic
	}

	int display_2_pressed() {
		disp_size = 2;
	};

	void display_3_pressed() {
		disp_size = 3;
	};

	void display_4_pressed() {
		disp_size = 4;
	};

	void menu_pressed() {
		first_menu.show();
	}

	void quit() {
		export_data();
		hide();
	}

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
	static void cb_request_submit(Address, Address);
	static void cb_request_okay(Address, Address);
	static void cb_display_customers_all(Address, Address);
	static void cb_display_customers_neg(Address, Address);
	static void cb_display_drivers_all(Address, Address);
	static void cb_display_drivers_rad(Address, Address);
	static void cb_display_places_all(Address, Address);
	static void cb_display_places_withtag(Address, Address);
	static void cb_2(Address, Address);
	static void cb_3(Address, Address);
	static void cb_4(Address, Address);
	static void cb_request_name(Address, Address);
	static void cb_request_tag(Address, Address);

};

User_window::User_window(Point xy, int w, int h, const string& title) :
	//initialization
	Window(xy, w, h, title),

	quit_button(
		Point(x_max() / 2 - 50, y_max() - 40),
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
		Point(x_max() - 100, y_max() - 40),
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
		Point(x_max() - 100, y_max() - 40),
		100, 40,
		"Submit",
		cb_remove_submit),

	remove_name(
		Point(x_max() / 2 - 50, 100),
		100, 20,
		"Name:"),

	request_placeA_name(
		Point(x_max() / 2 - 100, 70),
		200, 20,
		"Place A:"),

	request_customer_name(
		Point(x_max() / 2 - 100, 40),
		200, 20,
		"Customer Name:"),

	request_placeB_name(
		Point(x_max() / 2 - 100, 100),
		200, 20,
		"Place B:"),

	request_name(
		Point(10, 70),
		100, 40,
		"Use name",
		cb_request_name
	),

	request_tag(
		Point(10, 70),
		100, 40,
		"Use tag",
		cb_request_tag
	),

	request_info(
		Point(x_max() - (x_max() - 100), 130),
		x_max() - 200, y_max() - 230,
		"Places  \nand  \ntags: "),

	request_submit(
		Point(x_max() / 2 + 130, 40),
		100, 80,
		"Submit",
		cb_request_submit),

	request_okay(
		Point(x_max() - 100, y_max() - 40),
		100, 40,
		"Okay",
		cb_request_okay),

	request_summary(
		Point(x_max() - (x_max() - 20), 100),
		x_max() - 40, 300,
		""),


	display_size_menu(
		Point(x_max() / 2 - 50, y_max() / 6),
		100, 40,
		Menu::vertical,
		"Select size"),

	display_customers_all(
		Point(50, 350),
		120, 40,
		"All Customers",
		cb_display_customers_all),

	display_customers_neg(
		Point(50, 400),
		120, 40,
		"Neg Balance",
		cb_display_customers_neg),

	display_drivers_all(
		Point(250, 350),
		120, 40,
		"All Drivers",
		cb_display_drivers_all),

	display_drivers_tag(
		Point(250, 400),
		100, 20,
		"Tag: "
	),

	display_drivers_radius(
		Point(250, 430),
		100, 20,
		"Radius: "
	),

	display_drivers_rad(
		Point(250, 460),
		100, 40,
		"Within Radius",
		cb_display_drivers_rad),

	display_places_all(
		Point(450, 350),
		120, 40,
		"All Places",
		cb_display_places_all
	),

	display_places_tag(
		Point(450, 400),
		100, 20,
		"Tag: "
	),

	display_places_withtag(
		Point(450, 430),
		120, 40,
		"With Tag",
		cb_display_places_withtag
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
	attach(request_info);
	attach(request_submit);
	attach(request_okay);
	attach(request_summary);
	attach(request_name);
	attach(request_tag);
	attach(display_customers_all);
	attach(display_customers_neg);
	attach(display_drivers_all);
	attach(display_drivers_rad);
	attach(display_drivers_tag);
	attach(display_drivers_radius);
	attach(display_places_all);
	attach(display_places_tag);
	attach(display_places_withtag);


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
	request_name.hide();
	request_tag.hide();
	request_info.hide();
	request_submit.hide();
	request_summary.hide();
	request_okay.hide();
	display_customers_all.hide();
	display_customers_neg.hide();
	display_drivers_all.hide();
	display_drivers_rad.hide();
	display_drivers_radius.hide();
	display_drivers_tag.hide();
	display_places_all.hide();
	display_places_tag.hide();
	display_places_withtag.hide();

	display_size_menu.attach(new Button(Point(0, 0), 0, 0, "2 x 2", cb_2));
	display_size_menu.attach(new Button(Point(0, 0), 0, 0, "3 x 3", cb_3));
	display_size_menu.attach(new Button(Point(0, 0), 0, 0, "4 x 4", cb_4));
	attach(display_size_menu);
	display_size_menu.hide();

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

void User_window::cb_request_name(Address, Address pw) {
	reference_to<User_window>(pw).request_name_pressed();
}

void User_window::cb_request_tag(Address, Address pw) {
	reference_to<User_window>(pw).request_tag_pressed();
}

void User_window::cb_request_submit(Address, Address pw) {
	reference_to<User_window>(pw).request_submit_pressed();
}

void User_window::cb_request_okay(Address, Address pw) {
	reference_to<User_window>(pw).request_okay_pressed();
}

void User_window::cb_display(Address, Address pw) {
	reference_to<User_window>(pw).display_pressed();
}

void User_window::cb_display_customers_all(Address, Address pw) {
	reference_to<User_window>(pw).display_customers_all_pressed();
}

void User_window::cb_display_customers_neg(Address, Address pw) {
	reference_to<User_window>(pw).display_customers_neg_pressed();
}

void User_window::cb_display_drivers_all(Address, Address pw) {
	reference_to<User_window>(pw).display_drivers_all_pressed();
}

void User_window::cb_display_drivers_rad(Address, Address pw) {
	reference_to<User_window>(pw).display_drivers_rad_pressed();
}

void User_window::cb_display_places_all(Address, Address pw) {
	reference_to<User_window>(pw).display_places_all_pressed();
}

void User_window::cb_display_places_withtag(Address, Address pw) {
	reference_to<User_window>(pw).display_places_withtag_pressed();
}

void User_window::cb_2(Address, Address pw) {
	reference_to<User_window>(pw).display_2_pressed();
}

void User_window::cb_3(Address, Address pw) {
	reference_to<User_window>(pw).display_3_pressed();
}

void User_window::cb_4(Address, Address pw) {
	reference_to<User_window>(pw).display_4_pressed();
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