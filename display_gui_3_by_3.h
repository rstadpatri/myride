/*
Nick Esposito, Nick Nelson, & Reuben Tadpatri
Fall Semester 2017 (Nov - Dec)
Solution to Final Project
Based on samplegui.cpp
*/

#include "std_lib_facilities_4.h"
#include "myride_class_functions.h"
#include <sstream>     // for string streams
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"

#ifndef DISPLAY_FUNCTIONS_3
#define DISPLAY_FUNCTIONS_3

namespace disp_lib {
	using namespace funct_lib;
	using namespace Graph_lib;
	using namespace std;

	// 3x3 display window
	struct Disp_3 : Graph_lib::Window {

		//constructors for Drivers, Customers, Places
		Disp_3(Point xy, int w, int h, const string& title, const vector<Driver>& m);
		Disp_3(Point xy, int w, int h, const string& title, const vector<Customer>& m);
		Disp_3(Point xy, int w, int h, const string& title, const vector<Place>& m);

		//destructor (needed for pointers to images)
		~Disp_3() {
			for (int i = 0; i < member_images.size(); ++i) {
				delete member_images[i];
			}
		}

	private:
		//members
		vector<Driver> d_members;
		vector<Customer> c_members;
		vector<Place> p_members;
		int screen_num;
		char type;

		//widgets:
		Text format;

		//member images and info
		vector<Image*> member_images;
		Out_box member1_info;
		Out_box member2_info;
		Out_box member3_info;
		Out_box member4_info;
		Out_box member5_info;
		Out_box member6_info;
		Out_box member7_info;
		Out_box member8_info;
		Out_box member9_info;

		Button next_button;
		Button previous_button;
		Button quit_button;

		// Display next set of members
		void next_pressed() {
			switch (type) { // function called based on members being displayed
			case 'd': // drivers
				next_members_d();
				break;
			case 'c': // customers
				next_members_c();
				break;
			case 'p': // places
				next_members_p();
				break;
			}
		}

		// Display previous set of members
		void previous_pressed() {
			switch (type) { // function called based on members being displayed
			case 'd': // drivers
				previous_members_d();
				break;
			case 'c': // customers
				previous_members_c();
				break;
			case 'p': // places
				previous_members_p();
				break;
			}
		}

		void detach_all_d(); // Takes all drivers off of the window

		void detach_all_c(); // Takes all customers off of the window

		void detach_all_p(); // Takes all places off of the window

		void attach_all_d(); // Puts all drivers to be displayed on the window

		void attach_all_c(); // Puts all customers to be displayed on the window

		void attach_all_p(); // Puts all places to be displayed on the window

		void next_members_d(); // Display next function for drivers

		void next_members_c(); // Display next function for customers

		void next_members_p(); // Display next function for places

		void previous_members_d(); // Display previous function for drivers

		void previous_members_c(); // Display previous function for customers

		void previous_members_p(); // Display previous function for places

		void quit(); // Close the window

		//callback functions
		static void cb_next(Address, Address);
		static void cb_previous(Address, Address);
		static void cb_quit(Address, Address);
	};

	// ------------------------------ DRIVERS --------------------------------------------------
	// *Note* The definitions for customers and places follow the same structure

	// Constructor definitio (for drivers)
	Disp_3::Disp_3(Point xy, int w, int h, const string& title, const vector<Driver>& m) :
		//initialization
		Window(xy, w, h, title),

		// Pass in list of drivers
		d_members(m),

		// Initialize screen number to 0 for displaying the first 9 members
		screen_num(0),

		// Set location and sizes of widgets
		next_button(
			Point(x_max() - 70, y_max() - 20),
			70, 20,
			"Next",
			cb_next
		),

		previous_button(
			Point(70, y_max() - 20),
			70, 20,
			"Previous",
			cb_previous
		),

		quit_button(
			Point(x_max() - 70, 5),
			70, 20,
			"Quit",
			cb_quit
		),

		format(
			Point(x_max() / 2 - 10, 20),
			"Format: 3x3"
		),

		// Set up the out boxes for displaying driver information
		member1_info(Point(x_max() / 5, y_max() / 5 * 2 - 50), 100, 85, ""),
		member2_info(Point(x_max() / 5 * 2, y_max() / 5 * 2 - 50), 100, 85, ""),
		member3_info(Point(x_max() / 5 * 3, y_max() / 5 * 2 - 50), 100, 85, ""),

		member4_info(Point(x_max() / 5, y_max() / 5 * 3 - 35), 100, 85, ""),
		member5_info(Point(x_max() / 5 * 2, y_max() / 5 * 3 - 35), 100, 85, ""),
		member6_info(Point(x_max() / 5 * 3, y_max() / 5 * 3 - 35), 100, 85, ""),
		
		member7_info(Point(x_max() / 5, y_max() / 5 * 4 - 20), 100, 85, ""),
		member8_info(Point(x_max() / 5 * 2, y_max() / 5 * 4 - 20), 100, 85, ""),
		member9_info(Point(x_max() / 5 * 3, y_max() / 5 * 4 - 20), 100, 85, "")

	{//constructor body
	 // get all images for members
		type = 'd';
		int x_coord, y_coord; // to be used for positioning the images
		string image_name;
		for (int i = 0; i < d_members.size(); ++i) {
			// Switch case for determining placement of drivers
			switch (i % 9) {
			case 0: // row 1, column 1
				x_coord = x_max() / 5 + x_max() / 20;
				y_coord = y_max() / 5 * 2 - 50;
				break;
			case 1: // row 1, column 2
				x_coord = x_max() / 5 * 2 + x_max() / 20;
				y_coord = y_max() / 5 * 2 - 50;
				break;
			case 2: // row 1, column 3
				x_coord = x_max() / 5 * 3 + x_max() / 20;
				y_coord = y_max() / 5 * 2 - 50;
				break;
			case 3: // row 2, column 1
				x_coord = x_max() / 5 + x_max() / 20;
				y_coord = y_max() / 5 * 3 - 35;
				break;
			case 4: // row 2, column 2
				x_coord = x_max() / 5 * 2 + x_max() / 20;
				y_coord = y_max() / 5 * 3 - 35;
				break;
			case 5: // row 2, column 3
				x_coord = x_max() / 5 * 3 + x_max() / 20;
				y_coord = y_max() / 5 * 3 - 35;
				break;
			case 6: // row 3, column 1
				x_coord = x_max() / 5 + x_max() / 20;
				y_coord = y_max() / 5 * 4 - 20;
				break;
			case 7: // row 3, column 2
				x_coord = x_max() / 5 * 2 + x_max() / 20;
				y_coord = y_max() / 5 * 4 - 20;
				break;
			case 8: // row 3, column 3
				x_coord = x_max() / 5 * 3 + x_max() / 20;
				y_coord = y_max() / 5 * 4 - 20;
				break;
			}
			// Extract photo name
			image_name = d_members[i].get_photo();
			// Append ".jpg" to photo name for proper formatting
			stringstream ss;
			ss << image_name << ".jpg";
			ss >> image_name;

			// Create pointer to image
			Image* memb_im = new Image(Point(x_coord - x_max() / 20, y_coord - y_max() / 10), image_name);
			// Resize image to fit in display matrix
			memb_im->resize(x_max() / 10, y_max() / 10);
			// Add pointer to running list
			member_images.push_back(memb_im);
		}

		// Put all drivers to be displayed on the window
		attach_all_d();

		// Always have quit button
		attach(quit_button);

		// Next button only shown if there are more drivers than can be displayed on one screen
		attach(next_button);
		if (d_members.size() <= 9)
			next_button.hide(); // no more items to display
		attach(format);
		attach(previous_button);
		previous_button.hide(); // going to start with first elements, therefore no previous
	}

	// ------------------------------------------ CUSTOMERS ------------------------------------------

	// Constructor definition (for customers)
	Disp_3::Disp_3(Point xy, int w, int h, const string& title, const vector<Customer>& m) :
		//initialization
		Window(xy, w, h, title),

		c_members(m),

		screen_num(0),

		next_button(
			Point(x_max() - 70, y_max() - 20),
			70, 20,
			"Next",
			cb_next
		),

		previous_button(
			Point(70, y_max() - 20),
			70, 20,
			"Previous",
			cb_previous
		),

		quit_button(
			Point(x_max() - 70, 5),
			70, 20,
			"Quit",
			cb_quit
		),

		format(
			Point(x_max() / 2 - 10, 20),
			"Format: 3x3"
		),

		member1_info(Point(x_max() / 5, y_max() / 5 * 2 - 55), 100, 70, ""),
		member2_info(Point(x_max() / 5 * 2, y_max() / 5 * 2 - 55), 100, 70, ""),
		member3_info(Point(x_max() / 5 * 3, y_max() / 5 * 2 - 55), 100, 70, ""),
		
		member4_info(Point(x_max() / 5, y_max() / 5 * 3 - 55), 100, 70, ""),
		member5_info(Point(x_max() / 5 * 2, y_max() / 5 * 3 - 55), 100, 70, ""),
		member6_info(Point(x_max() / 5 * 3, y_max() / 5 * 3 - 55), 100, 70, ""),
		
		member7_info(Point(x_max() / 5, y_max() / 5 * 4 - 55), 100, 70, ""),
		member8_info(Point(x_max() / 5 * 2, y_max() / 5 * 4 - 55), 100, 70, ""),
		member9_info(Point(x_max() / 5 * 3, y_max() / 5 * 4 - 55), 100, 70, "")

	{//constructor body
	 // get all images for members
		type = 'c';
		int x_coord, y_coord;
		string image_name;
		for (int i = 0; i < c_members.size(); ++i) {
			switch (i % 9) {
			case 0:
				x_coord = x_max() / 5;
				y_coord = y_max() / 5 * 2 - 125;
				break;
			case 1:
				x_coord = x_max() / 5 * 2;
				y_coord = y_max() / 5 * 2 - 125;
				break;
			case 2:
				x_coord = x_max() / 5 * 3;
				y_coord = y_max() / 5 * 2 - 125;
				break;
			case 3:
				x_coord = x_max() / 5;
				y_coord = y_max() / 5 * 3 - 125;
				break;
			case 4:
				x_coord = x_max() / 5 * 2;
				y_coord = y_max() / 5 * 3 - 125;
				break;
			case 5:
				x_coord = x_max() / 5 * 3;
				y_coord = y_max() / 5 * 3 - 125;
				break;
			case 6:
				x_coord = x_max() / 5;
				y_coord = y_max() / 5 * 4 - 125;
				break;
			case 7:
				x_coord = x_max() / 5 * 2;
				y_coord = y_max() / 5 * 4 - 125;
				break;
			case 8:
				x_coord = x_max() / 5 * 3;
				y_coord = y_max() / 5 * 4 - 125;
				break;
			}
			image_name = c_members[i].get_photo();
			stringstream ss;
			ss << image_name << ".jpg";
			ss >> image_name;
			Image* memb_im = new Image(Point(x_coord, y_coord), image_name);
			memb_im->resize(x_max() / 10, y_max() / 10);
			member_images.push_back(memb_im);
		}

		attach_all_c();

		attach(quit_button);
		attach(next_button);
		if (c_members.size() <= 9)
			next_button.hide(); // no more items to display
		attach(format);
		attach(previous_button);
		previous_button.hide(); // going to start with first elements, therefore no previous
	}

	// ----------------------------------------- PLACES ----------------------------------------

	Disp_3::Disp_3(Point xy, int w, int h, const string& title, const vector<Place>& m) :
		//initialization
		Window(xy, w, h, title),

		p_members(m),

		screen_num(0),

		next_button(
			Point(x_max() - 70, y_max() - 20),
			70, 20,
			"Next",
			cb_next
		),

		previous_button(
			Point(70, y_max() - 20),
			70, 20,
			"Previous",
			cb_previous
		),

		quit_button(
			Point(x_max() - 70, 5),
			70, 20,
			"Quit",
			cb_quit
		),

		format(
			Point(x_max() / 2 - 10, 20),
			"Format: 3x3"
		),

		member1_info(Point(x_max() / 5, y_max() / 5 * 2 - 55), 100, 70, ""),
		member2_info(Point(x_max() / 5 * 2, y_max() / 5 * 2 - 55), 100, 70, ""),
		member3_info(Point(x_max() / 5 * 3, y_max() / 5 * 2 - 55), 100, 70, ""),
		
		member4_info(Point(x_max() / 5, y_max() / 5 * 3 - 55), 100, 70, ""),
		member5_info(Point(x_max() / 5 * 2, y_max() / 5 * 3 - 55), 100, 70, ""),
		member6_info(Point(x_max() / 5 * 3, y_max() / 5 * 3 - 55), 100, 70, ""),
		
		member7_info(Point(x_max() / 5, y_max() / 5 * 4 - 55), 100, 70, ""),
		member8_info(Point(x_max() / 5 * 2, y_max() / 5 * 4 - 55), 100, 70, ""),
		member9_info(Point(x_max() / 5 * 3, y_max() / 5 * 4 - 55), 100, 70, "")

	{//constructor body
	 // get all images for members
		type = 'p';
		int x_coord, y_coord;
		string image_name;
		for (int i = 0; i < p_members.size(); ++i) {
			switch (i % 9) {
			case 0:
				x_coord = x_max() / 5;
				y_coord = y_max() / 5 * 2 - 125;
				break;
			case 1:
				x_coord = x_max() / 5 * 2;
				y_coord = y_max() / 5 * 2 - 125;
				break;
			case 2:
				x_coord = x_max() / 5 * 3;
				y_coord = y_max() / 5 * 2 - 125;
				break;
			case 3:
				x_coord = x_max() / 5;
				y_coord = y_max() / 5 * 3 - 125;
				break;
			case 4:
				x_coord = x_max() / 5 * 2;
				y_coord = y_max() / 5 * 3 - 125;
				break;
			case 5:
				x_coord = x_max() / 5 * 3;
				y_coord = y_max() / 5 * 3 - 125;
				break;
			case 6:
				x_coord = x_max() / 5;
				y_coord = y_max() / 5 * 4 - 125;
				break;
			case 7:
				x_coord = x_max() / 5 * 2;
				y_coord = y_max() / 5 * 4 - 125;
				break;
			case 8:
				x_coord = x_max() / 5 * 3;
				y_coord = y_max() / 5 * 4 - 125;
				break;
			}
			image_name = p_members[i].get_photo();
			stringstream ss;
			ss << image_name << ".jpg";
			ss >> image_name;
			Image* memb_im = new Image(Point(x_coord, y_coord), image_name);
			memb_im->resize(x_max() / 10, y_max() / 10);
			member_images.push_back(memb_im);
		}

		attach_all_p();

		attach(quit_button);
		attach(next_button);
		if (p_members.size() <= 9)
			next_button.hide(); // no more items to display
		attach(format);
		attach(previous_button);
		previous_button.hide(); // going to start with first elements, therefore no previous
	}

	//callback functions for buttons
	void Disp_3::cb_quit(Address, Address pw) {
		reference_to<Disp_3>(pw).quit();
	}

	void Disp_3::quit() {
		hide(); // close window
	}

	void Disp_3::cb_previous(Address, Address pw) {
		reference_to<Disp_3>(pw).previous_pressed();
	}

	// ------------------- DETACH FUNCTIONS --------------------------
	// Members are only detached if they were attached in the first place
	// This is determined by examining the size of the member list with the
	// screen number

	void Disp_3::detach_all_d() {
		if (d_members.size() >= screen_num * 9 + 1) {
			detach(member1_info);
			detach(*member_images[screen_num * 9]);
		}
		if (d_members.size() >= screen_num * 9 + 2) {
			detach(member2_info);
			detach(*member_images[screen_num * 9 + 1]);
		}
		if (d_members.size() >= screen_num * 9 + 3) {
			detach(member3_info);
			detach(*member_images[screen_num * 9 + 2]);
		}
		if (d_members.size() >= screen_num * 9 + 4) {
			detach(member4_info);
			detach(*member_images[screen_num * 9 + 3]);
		}
		if (d_members.size() >= screen_num * 9 + 5) {
			detach(member5_info);
			detach(*member_images[screen_num * 9 + 4]);
		}
		if (d_members.size() >= screen_num * 9 + 6) {
			detach(member6_info);
			detach(*member_images[screen_num * 9 + 5]);
		}
		if (d_members.size() >= screen_num * 9 + 7) {
			detach(member7_info);
			detach(*member_images[screen_num * 9 + 6]);
		}
		if (d_members.size() >= screen_num * 9 + 8) {
			detach(member8_info);
			detach(*member_images[screen_num * 9 + 7]);
		}
		if (d_members.size() >= screen_num * 9 + 9) {
			detach(member9_info);
			detach(*member_images[screen_num * 9 + 8]);
		}
	}

	void Disp_3::detach_all_c() {
		if (c_members.size() >= screen_num * 9 + 1) {
			detach(member1_info);
			detach(*member_images[screen_num * 9]);
		}
		if (c_members.size() >= screen_num * 9 + 2) {
			detach(member2_info);
			detach(*member_images[screen_num * 9 + 1]);
		}
		if (c_members.size() >= screen_num * 9 + 3) {
			detach(member3_info);
			detach(*member_images[screen_num * 9 + 2]);
		}
		if (c_members.size() >= screen_num * 9 + 4) {
			detach(member4_info);
			detach(*member_images[screen_num * 9 + 3]);
		}
		if (c_members.size() >= screen_num * 9 + 5) {
			detach(member5_info);
			detach(*member_images[screen_num * 9 + 4]);
		}
		if (c_members.size() >= screen_num * 9 + 6) {
			detach(member6_info);
			detach(*member_images[screen_num * 9 + 5]);
		}
		if (c_members.size() >= screen_num * 9 + 7) {
			detach(member7_info);
			detach(*member_images[screen_num * 9 + 6]);
		}
		if (c_members.size() >= screen_num * 9 + 8) {
			detach(member8_info);
			detach(*member_images[screen_num * 9 + 7]);
		}
		if (c_members.size() >= screen_num * 9 + 9) {
			detach(member9_info);
			detach(*member_images[screen_num * 9 + 8]);
		}
	}

	void Disp_3::detach_all_p() {
		if (p_members.size() >= screen_num * 9 + 1) {
			detach(member1_info);
			detach(*member_images[screen_num * 9]);
		}
		if (p_members.size() >= screen_num * 9 + 2) {
			detach(member2_info);
			detach(*member_images[screen_num * 9 + 1]);
		}
		if (p_members.size() >= screen_num * 9 + 3) {
			detach(member3_info);
			detach(*member_images[screen_num * 9 + 2]);
		}
		if (p_members.size() >= screen_num * 9 + 4) {
			detach(member4_info);
			detach(*member_images[screen_num * 9 + 3]);
		}
		if (p_members.size() >= screen_num * 9 + 5) {
			detach(member5_info);
			detach(*member_images[screen_num * 9 + 4]);
		}
		if (p_members.size() >= screen_num * 9 + 6) {
			detach(member6_info);
			detach(*member_images[screen_num * 9 + 5]);
		}
		if (p_members.size() >= screen_num * 9 + 7) {
			detach(member7_info);
			detach(*member_images[screen_num * 9 + 6]);
		}
		if (p_members.size() >= screen_num * 9 + 8) {
			detach(member8_info);
			detach(*member_images[screen_num * 9 + 7]);
		}
		if (p_members.size() >= screen_num * 9 + 9) {
			detach(member9_info);
			detach(*member_images[screen_num * 9 + 8]);
		}
	}

	// ---------------------- ATTACH FUNCTIONS -------------------------------
	// Only attach members if they exist
	// This is determined by examining the size of the member list
	// with the screen number

	void Disp_3::attach_all_d() {
		if (d_members.size() >= screen_num * 9 + 1) {
			attach(member1_info);
			member1_info.put(d_members[screen_num * 9].display());
			attach(*member_images[screen_num * 9]);
		}
		if (d_members.size() >= screen_num * 9 + 2) {
			attach(member2_info);
			member2_info.put(d_members[screen_num * 9 + 1].display());
			attach(*member_images[screen_num * 9 + 1]);
		}
		if (d_members.size() >= screen_num * 9 + 3) {
			attach(member3_info);
			member3_info.put(d_members[screen_num * 9 + 2].display());
			attach(*member_images[screen_num * 9 + 2]);
		}
		if (d_members.size() >= screen_num * 9 + 4) {
			attach(member4_info);
			member4_info.put(d_members[screen_num * 9 + 3].display());
			attach(*member_images[screen_num * 9 + 3]);
		}
		if (d_members.size() >= screen_num * 9 + 5) {
			attach(member5_info);
			member5_info.put(d_members[screen_num * 9 + 4].display());
			attach(*member_images[screen_num * 9 + 4]);
		}
		if (d_members.size() >= screen_num * 9 + 6) {
			attach(member6_info);
			member6_info.put(d_members[screen_num * 9 + 5].display());
			attach(*member_images[screen_num * 9 + 5]);
		}
		if (d_members.size() >= screen_num * 9 + 7) {
			attach(member7_info);
			member7_info.put(d_members[screen_num * 9 + 6].display());
			attach(*member_images[screen_num * 9 + 6]);
		}
		if (d_members.size() >= screen_num * 9 + 8) {
			attach(member8_info);
			member8_info.put(d_members[screen_num * 9 + 7].display());
			attach(*member_images[screen_num * 9 + 7]);
		}
		if (d_members.size() >= screen_num * 9 + 9) {
			attach(member9_info);
			member9_info.put(d_members[screen_num * 9 + 8].display());
			attach(*member_images[screen_num * 9 + 8]);
		}
	}

	void Disp_3::attach_all_c() {
		if (c_members.size() >= screen_num * 9 + 1) {
			attach(member1_info);
			member1_info.put(c_members[screen_num * 9].display());
			attach(*member_images[screen_num * 9]);
		}
		if (c_members.size() >= screen_num * 9 + 2) {
			attach(member2_info);
			member2_info.put(c_members[screen_num * 9 + 1].display());
			attach(*member_images[screen_num * 9 + 1]);
		}
		if (c_members.size() >= screen_num * 9 + 3) {
			attach(member3_info);
			member3_info.put(c_members[screen_num * 9 + 2].display());
			attach(*member_images[screen_num * 9 + 2]);
		}
		if (c_members.size() >= screen_num * 9 + 4) {
			attach(member4_info);
			member4_info.put(c_members[screen_num * 9 + 3].display());
			attach(*member_images[screen_num * 9 + 3]);
		}
		if (c_members.size() >= screen_num * 9 + 5) {
			attach(member5_info);
			member5_info.put(c_members[screen_num * 9 + 4].display());
			attach(*member_images[screen_num * 9 + 4]);
		}
		if (d_members.size() >= screen_num * 9 + 6) {
			attach(member6_info);
			member6_info.put(d_members[screen_num * 9 + 5].display());
			attach(*member_images[screen_num * 9 + 5]);
		}
		if (c_members.size() >= screen_num * 9 + 7) {
			attach(member7_info);
			member7_info.put(c_members[screen_num * 9 + 6].display());
			attach(*member_images[screen_num * 9 + 6]);
		}
		if (c_members.size() >= screen_num * 9 + 8) {
			attach(member8_info);
			member8_info.put(c_members[screen_num * 9 + 7].display());
			attach(*member_images[screen_num * 9 + 7]);
		}
		if (c_members.size() >= screen_num * 9 + 9) {
			attach(member9_info);
			member9_info.put(c_members[screen_num * 9 + 8].display());
			attach(*member_images[screen_num * 9 + 8]);
		}
	}

	void Disp_3::attach_all_p() {
		if (p_members.size() >= screen_num * 9 + 1) {
			attach(member1_info);
			member1_info.put(p_members[screen_num * 9].display());
			attach(*member_images[screen_num * 9]);
		}
		if (p_members.size() >= screen_num * 9 + 2) {
			attach(member2_info);
			member2_info.put(p_members[screen_num * 9 + 1].display());
			attach(*member_images[screen_num * 9 + 1]);
		}
		if (p_members.size() >= screen_num * 9 + 3) {
			attach(member3_info);
			member3_info.put(p_members[screen_num * 9 + 2].display());
			attach(*member_images[screen_num * 9 + 2]);
		}
		if (p_members.size() >= screen_num * 9 + 4) {
			attach(member4_info);
			member4_info.put(p_members[screen_num * 9 + 3].display());
			attach(*member_images[screen_num * 9 + 3]);
		}
		if (p_members.size() >= screen_num * 9 + 5) {
			attach(member5_info);
			member5_info.put(p_members[screen_num * 9 + 4].display());
			attach(*member_images[screen_num * 9 + 4]);
		}
		if (p_members.size() >= screen_num * 9 + 6) {
			attach(member6_info);
			member6_info.put(p_members[screen_num * 9 + 5].display());
			attach(*member_images[screen_num * 9 + 5]);
		}
		if (p_members.size() >= screen_num * 9 + 7) {
			attach(member7_info);
			member7_info.put(p_members[screen_num * 9 + 6].display());
			attach(*member_images[screen_num * 9 + 6]);
		}
		if (p_members.size() >= screen_num * 9 + 8) {
			attach(member8_info);
			member8_info.put(p_members[screen_num * 9 + 7].display());
			attach(*member_images[screen_num * 9 + 7]);
		}
		if (p_members.size() >= screen_num * 9 + 9) {
			attach(member9_info);
			member9_info.put(p_members[screen_num * 9 + 8].display());
			attach(*member_images[screen_num * 9 + 8]);
		}
	}

	// -------------------------------- NEXT FUNCTION ------------------------------

	void Disp_3::next_members_d() {
		// 9 items per screen (0-8), (9-17), (18-26), ...
		// Screen:          0      1      2     ...

		// Clean up the screen in case there are not enough objects to display
		detach_all_d();

		screen_num++;

		attach_all_d();

		// Will always have a previous after a next
		previous_button.show();

		if (d_members.size() <= 9 * (screen_num + 1))
			next_button.hide();
	}

	void Disp_3::next_members_c() {
		// 9 items per screen (0-8), (9-17), (18-26), ...
		// Screen:          0      1      2     ...

		// Clean up the screen in case there are not enough objects to display
		detach_all_c();

		screen_num++;

		attach_all_c();

		// Will always have a previous after a next
		previous_button.show();

		if (c_members.size() <= 9 * (screen_num + 1))
			next_button.hide();
	}

	void Disp_3::next_members_p() {
		// 9 items per screen (0-8), (9-17), (18-26), ...
		// Screen:          0      1      2     ...

		// Clean up the screen in case there are not enough objects to display
		detach_all_p();

		screen_num++;

		attach_all_p();

		// Will always have a previous after a next
		previous_button.show();

		if (p_members.size() <= 9 * (screen_num + 1))
			next_button.hide();
	}

	// Callback associated with next members
	void Disp_3::cb_next(Address, Address pw) {
		reference_to<Disp_3>(pw).next_pressed();
	}

	// ----------------------- PREVIOUS FUNCTIONS ------------------------------

	void Disp_3::previous_members_d() {
		// Clean up screen
		detach_all_d();

		screen_num--;

		attach_all_d();

		// Will always be a next after a previous
		next_button.show();

		if (screen_num == 0)
			previous_button.hide();
	}

	void Disp_3::previous_members_c() {
		// Clean up screen
		detach_all_c();

		screen_num--;

		attach_all_c();

		// Will always be a next after a previous
		next_button.show();

		if (screen_num == 0)
			previous_button.hide();
	}

	void Disp_3::previous_members_p() {
		// Clean up screen
		detach_all_p();

		screen_num--;

		attach_all_p();

		// Will always be a next after a previous
		next_button.show();

		if (screen_num == 0)
			previous_button.hide();
	}
}
#endif