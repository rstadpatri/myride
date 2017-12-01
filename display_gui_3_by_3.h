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

	struct Disp_3 : Graph_lib::Window {

		//constructor
		Disp_3(Point xy, int w, int h, const string& title, const vector<Driver>& m);
		Disp_3(Point xy, int w, int h, const string& title, const vector<Customer>& m);
		Disp_3(Point xy, int w, int h, const string& title, const vector<Place>& m);

		//destructor
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

		void next_pressed() {
			switch (type) {
			case 'd':
				next_members_d();
				break;
			case 'c':
				next_members_c();
				break;
			case 'p':
				next_members_p();
				break;
			}
		}

		void previous_pressed() {
			switch (type) {
			case 'd':
				previous_members_d();
				break;
			case 'c':
				previous_members_c();
				break;
			case 'p':
				previous_members_p();
				break;
			}
		}

		void detach_all_d();

		void detach_all_c();

		void detach_all_p();

		void attach_all_d();

		void attach_all_c();

		void attach_all_p();

		void next_members_d();

		void next_members_c();

		void next_members_p();

		void previous_members_d();

		void previous_members_c();

		void previous_members_p();

		void quit();

		//callback functions
		static void cb_next(Address, Address);
		static void cb_previous(Address, Address);
		static void cb_quit(Address, Address);
	};

	Disp_3::Disp_3(Point xy, int w, int h, const string& title, const vector<Driver>& m) :
		//initialization
		Window(xy, w, h, title),

		d_members(m),

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
		int x_coord, y_coord;
		string image_name;
		for (int i = 0; i < d_members.size(); ++i) {
			switch (i % 9) {
			case 0:
				x_coord = x_max() / 5 + x_max() / 20;
				y_coord = y_max() / 5 * 2 - 50;
				break;
			case 1:
				x_coord = x_max() / 5 * 2 + x_max() / 20;
				y_coord = y_max() / 5 * 2 - 50;
				break;
			case 2:
				x_coord = x_max() / 5 * 3 + x_max() / 20;
				y_coord = y_max() / 5 * 2 - 50;
				break;
			case 3:
				x_coord = x_max() / 5 + x_max() / 20;
				y_coord = y_max() / 5 * 3 - 35;
				break;
			case 4:
				x_coord = x_max() / 5 * 2 + x_max() / 20;
				y_coord = y_max() / 5 * 3 - 35;
				break;
			case 5:
				x_coord = x_max() / 5 * 3 + x_max() / 20;
				y_coord = y_max() / 5 * 3 - 35;
				break;
			case 6:
				x_coord = x_max() / 5 + x_max() / 20;
				y_coord = y_max() / 5 * 4 - 20;
				break;
			case 7:
				x_coord = x_max() / 5 * 2 + x_max() / 20;
				y_coord = y_max() / 5 * 4 - 20;
				break;
			case 8:
				x_coord = x_max() / 5 * 3 + x_max() / 20;
				y_coord = y_max() / 5 * 4 - 20;
				break;
			}
			image_name = d_members[i].get_photo();
			stringstream ss;
			ss << image_name << ".jpg";
			ss >> image_name;
			Image* memb_im = new Image(Point(x_coord - x_max() / 20, y_coord - y_max() / 10), image_name);
			memb_im->resize(x_max() / 10, y_max() / 10);
			member_images.push_back(memb_im);
		}

		attach_all_d();

		attach(quit_button);
		attach(next_button);
		if (d_members.size() <= 9)
			next_button.hide(); // no more items to display
		attach(format);
		attach(previous_button);
		previous_button.hide(); // going to start with first elements, therefore no previous
	}

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
		hide();
	}

	void Disp_3::cb_previous(Address, Address pw) {
		reference_to<Disp_3>(pw).previous_pressed();
	}

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

	void Disp_3::cb_next(Address, Address pw) {
		reference_to<Disp_3>(pw).next_pressed();
	}

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