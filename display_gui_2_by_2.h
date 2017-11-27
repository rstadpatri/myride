#include "std_lib_facilities_4.h"
#include "myride_class_functions.h"
#include <sstream>     // for string streams
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"

#ifndef DISPLAY_FUNCTIONS
#define DISPLAY_FUNCTIONS

namespace disp_lib {
	using namespace funct_lib;
	using namespace Graph_lib;
	using namespace std;

	struct Disp_2 : Graph_lib::Window {

		//constructor
		Disp_2(Point xy, int w, int h, const string& title, const vector<Driver>& m);
		Disp_2(Point xy, int w, int h, const string& title, const vector<Customer>& m);
		Disp_2(Point xy, int w, int h, const string& title, const vector<Place>& m);

		//destructor
		~Disp_2() {
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
			case 'p':
				next_members_p();
			}
		}

		void previous_pressed() {
			switch (type) {
			case 'd':
				previous_members_d();
				break;
			case 'c':
				previous_members_c();
			case 'p':
				previous_members_p();
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

	Disp_2::Disp_2(Point xy, int w, int h, const string& title, const vector<Driver>& m) :
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
			Point(x_max() - 100, 0),
			100, 40,
			"Quit",
			cb_quit
		),

		format(
			Point(x_max() / 2 - 10, 20),
			"Format: 2x2"
		),

		member1_info(Point(x_max() / 4, y_max() / 3), 100, 100, "Item 1"),
		member2_info(Point(x_max() / 4 * 3, y_max() / 3), 100, 100, "Item 2"),
		member3_info(Point(x_max() / 4, y_max() / 3 * 2), 100, 100, "Item 3"),
		member4_info(Point(x_max() / 4 * 3, y_max() / 3 * 2), 100, 100, "Item 4")

	{//constructor body
	 // get all images for members
		type = 'd';
		int x_coord, y_coord;
		string image_name;
		for (int i = 0; i < d_members.size(); ++i) {
			if (i % 4 == 0) {
				x_coord = x_max() / 4;
				y_coord = y_max() / 3 - 100;
			}
			if (i % 4 == 1) {
				x_coord = x_max() / 4 * 3;
				y_coord = y_max() / 3 - 100;
			}
			if (i % 4 == 2) {
				x_coord = x_max() / 4;
				y_coord = y_max() / 3 * 2 - 100;
			}
			if (i % 4 == 3) {
				x_coord = x_max() / 4 * 3;
				y_coord = y_max() / 3 * 2 - 100;
			}
			image_name = d_members[i].get_photo();
			stringstream ss;
			ss << image_name << ".jpg";
			ss >> image_name;
			Image* memb_im = new Image(Point(x_coord, y_coord), image_name);
			memb_im->resize(100, 100);
			member_images.push_back(memb_im);
		}

		attach_all_d();

		attach(quit_button);
		attach(next_button);
		if (d_members.size() <= 4)
			next_button.hide(); // no more items to display
		attach(format);
		attach(previous_button);
		previous_button.hide(); // going to start with first elements, therefore no previous
	}

	Disp_2::Disp_2(Point xy, int w, int h, const string& title, const vector<Customer>& m) :
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
			Point(x_max() - 100, 0),
			100, 40,
			"Quit",
			cb_quit
		),

		format(
			Point(x_max() / 2 - 10, 20),
			"Format: 2x2"
		),

		member1_info(Point(x_max() / 4, y_max() / 3), 100, 100, "Item 1"),
		member2_info(Point(x_max() / 4 * 3, y_max() / 3), 100, 100, "Item 2"),
		member3_info(Point(x_max() / 4, y_max() / 3 * 2), 100, 100, "Item 3"),
		member4_info(Point(x_max() / 4 * 3, y_max() / 3 * 2), 100, 100, "Item 4")

	{//constructor body
	 // get all images for members
		type = 'c';
		int x_coord, y_coord;
		string image_name;
		for (int i = 0; i < c_members.size(); ++i) {
			if (i % 4 == 0) {
				x_coord = x_max() / 4;
				y_coord = y_max() / 3 - 100;
			}
			if (i % 4 == 1) {
				x_coord = x_max() / 4 * 3;
				y_coord = y_max() / 3 - 100;
			}
			if (i % 4 == 2) {
				x_coord = x_max() / 4;
				y_coord = y_max() / 3 * 2 - 100;
			}
			if (i % 4 == 3) {
				x_coord = x_max() / 4 * 3;
				y_coord = y_max() / 3 * 2 - 100;
			}
			image_name = c_members[i].get_photo();
			stringstream ss;
			ss << image_name << ".jpg";
			ss >> image_name;
			Image* memb_im = new Image(Point(x_coord, y_coord), image_name);
			memb_im->resize(100, 100);
			member_images.push_back(memb_im);
		}

		attach_all_c();

		attach(quit_button);
		attach(next_button);
		if (c_members.size() <= 4)
			next_button.hide(); // no more items to display
		attach(format);
		attach(previous_button);
		previous_button.hide(); // going to start with first elements, therefore no previous
	}

	Disp_2::Disp_2(Point xy, int w, int h, const string& title, const vector<Place>& m) :
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
			Point(x_max() - 100, 0),
			100, 40,
			"Quit",
			cb_quit
		),

		format(
			Point(x_max() / 2 - 10, 20),
			"Format: 2x2"
		),

		member1_info(Point(x_max() / 4, y_max() / 3), 100, 100, "Item 1"),
		member2_info(Point(x_max() / 4 * 3, y_max() / 3), 100, 100, "Item 2"),
		member3_info(Point(x_max() / 4, y_max() / 3 * 2), 100, 100, "Item 3"),
		member4_info(Point(x_max() / 4 * 3, y_max() / 3 * 2), 100, 100, "Item 4")

	{//constructor body
	 // get all images for members
		type = 'p';
		int x_coord, y_coord;
		string image_name;
		for (int i = 0; i < p_members.size(); ++i) {
			if (i % 4 == 0) {
				x_coord = x_max() / 4;
				y_coord = y_max() / 3 - 100;
			}
			if (i % 4 == 1) {
				x_coord = x_max() / 4 * 3;
				y_coord = y_max() / 3 - 100;
			}
			if (i % 4 == 2) {
				x_coord = x_max() / 4;
				y_coord = y_max() / 3 * 2 - 100;
			}
			if (i % 4 == 3) {
				x_coord = x_max() / 4 * 3;
				y_coord = y_max() / 3 * 2 - 100;
			}
			image_name = p_members[i].get_photo();
			stringstream ss;
			ss << image_name << ".jpg";
			ss >> image_name;
			Image* memb_im = new Image(Point(x_coord, y_coord), image_name);
			memb_im->resize(100, 100);
			member_images.push_back(memb_im);
		}

		attach_all_p();

		attach(quit_button);
		attach(next_button);
		if (p_members.size() <= 4)
			next_button.hide(); // no more items to display
		attach(format);
		attach(previous_button);
		previous_button.hide(); // going to start with first elements, therefore no previous
	}



	//callback functions for buttons
	void Disp_2::cb_quit(Address, Address pw) {
		reference_to<Disp_2>(pw).quit();
	}

	void Disp_2::quit() {
		hide();
	}

	void Disp_2::cb_previous(Address, Address pw) {
		reference_to<Disp_2>(pw).previous_pressed();
	}

	void Disp_2::detach_all_d() {
		if (d_members.size() >= screen_num * 4 + 1) {
			detach(member1_info);
			detach(*member_images[screen_num * 4]);
		}
		if (d_members.size() >= screen_num * 4 + 2) {
			detach(member2_info);
			detach(*member_images[screen_num * 4 + 1]);
		}
		if (d_members.size() >= screen_num * 4 + 3) {
			detach(member3_info);
			detach(*member_images[screen_num * 4 + 2]);
		}
		if (d_members.size() >= screen_num * 4 + 4) {
			detach(member4_info);
			detach(*member_images[screen_num * 4 + 3]);
		}
	}

	void Disp_2::detach_all_c() {
		if (c_members.size() >= screen_num * 4 + 1) {
			detach(member1_info);
			detach(*member_images[screen_num * 4]);
		}
		if (c_members.size() >= screen_num * 4 + 2) {
			detach(member2_info);
			detach(*member_images[screen_num * 4 + 1]);
		}
		if (c_members.size() >= screen_num * 4 + 3) {
			detach(member3_info);
			detach(*member_images[screen_num * 4 + 2]);
		}
		if (c_members.size() >= screen_num * 4 + 4) {
			detach(member4_info);
			detach(*member_images[screen_num * 4 + 3]);
		}
	}

	void Disp_2::detach_all_p() {
		if (p_members.size() >= screen_num * 4 + 1) {
			detach(member1_info);
			detach(*member_images[screen_num * 4]);
		}
		if (p_members.size() >= screen_num * 4 + 2) {
			detach(member2_info);
			detach(*member_images[screen_num * 4 + 1]);
		}
		if (p_members.size() >= screen_num * 4 + 3) {
			detach(member3_info);
			detach(*member_images[screen_num * 4 + 2]);
		}
		if (p_members.size() >= screen_num * 4 + 4) {
			detach(member4_info);
			detach(*member_images[screen_num * 4 + 3]);
		}
	}

	void Disp_2::attach_all_d() {
		if (d_members.size() >= screen_num * 4 + 1) {
			attach(member1_info);
			member1_info.put(d_members[screen_num * 4].display());
			attach(*member_images[screen_num * 4]);


		}
		if (d_members.size() >= screen_num * 4 + 2) {
			attach(member2_info);
			member2_info.put(d_members[screen_num * 4 + 1].display());
			attach(*member_images[screen_num * 4 + 1]);
		}
		if (d_members.size() >= screen_num * 4 + 3) {
			attach(member3_info);
			member3_info.put(d_members[screen_num * 4 + 2].display());
			attach(*member_images[screen_num * 4 + 2]);
		}
		if (d_members.size() >= screen_num * 4 + 4) {
			attach(member4_info);
			member4_info.put(d_members[screen_num * 4 + 3].display());
			attach(*member_images[screen_num * 4 + 3]);
		}
	}

	void Disp_2::attach_all_c() {
		if (c_members.size() >= screen_num * 4 + 1) {
			attach(member1_info);
			member1_info.put(c_members[screen_num * 4].display());
			attach(*member_images[screen_num * 4]);


		}
		if (c_members.size() >= screen_num * 4 + 2) {
			attach(member2_info);
			member2_info.put(c_members[screen_num * 4 + 1].display());
			attach(*member_images[screen_num * 4 + 1]);
		}
		if (c_members.size() >= screen_num * 4 + 3) {
			attach(member3_info);
			member3_info.put(c_members[screen_num * 4 + 2].display());
			attach(*member_images[screen_num * 4 + 2]);
		}
		if (c_members.size() >= screen_num * 4 + 4) {
			attach(member4_info);
			member4_info.put(c_members[screen_num * 4 + 3].display());
			attach(*member_images[screen_num * 4 + 3]);
		}
	}

	void Disp_2::attach_all_p() {
		if (p_members.size() >= screen_num * 4 + 1) {
			attach(member1_info);
			member1_info.put(p_members[screen_num * 4].display());
			attach(*member_images[screen_num * 4]);


		}
		if (p_members.size() >= screen_num * 4 + 2) {
			attach(member2_info);
			member2_info.put(p_members[screen_num * 4 + 1].display());
			attach(*member_images[screen_num * 4 + 1]);
		}
		if (p_members.size() >= screen_num * 4 + 3) {
			attach(member3_info);
			member3_info.put(p_members[screen_num * 4 + 2].display());
			attach(*member_images[screen_num * 4 + 2]);
		}
		if (p_members.size() >= screen_num * 4 + 4) {
			attach(member4_info);
			member4_info.put(p_members[screen_num * 4 + 3].display());
			attach(*member_images[screen_num * 4 + 3]);
		}
	}

	void Disp_2::next_members_d() {
		// 4 items per screen (0-3), (4-7), (8-11), ...
		// Screen:          0      1      2     ...

		// Clean up the screen in case there are not enough objects to display
		detach_all_d();

		screen_num++;

		attach_all_d();

		// Will always have a previous after a next
		previous_button.show();

		if (d_members.size() <= 4 * (screen_num + 1))
			next_button.hide();
	}

	void Disp_2::next_members_c() {
		// 4 items per screen (0-3), (4-7), (8-11), ...
		// Screen:          0      1      2     ...

		// Clean up the screen in case there are not enough objects to display
		detach_all_c();

		screen_num++;

		attach_all_c();

		// Will always have a previous after a next
		previous_button.show();

		if (c_members.size() <= 4 * (screen_num + 1))
			next_button.hide();
	}

	void Disp_2::next_members_p() {
		// 4 items per screen (0-3), (4-7), (8-11), ...
		// Screen:          0      1      2     ...

		// Clean up the screen in case there are not enough objects to display
		detach_all_p();

		screen_num++;

		attach_all_p();

		// Will always have a previous after a next
		previous_button.show();

		if (p_members.size() <= 4 * (screen_num + 1))
			next_button.hide();
	}

	void Disp_2::cb_next(Address, Address pw) {
		reference_to<Disp_2>(pw).next_pressed();
	}

	void Disp_2::previous_members_d() {
		// Clean up screen
		detach_all_d();

		screen_num--;

		attach_all_d();

		// Will always be a next after a previous
		next_button.show();

		if (screen_num == 0)
			previous_button.hide();
	}

	void Disp_2::previous_members_c() {
		// Clean up screen
		detach_all_c();

		screen_num--;

		attach_all_c();

		// Will always be a next after a previous
		next_button.show();

		if (screen_num == 0)
			previous_button.hide();
	}

	void Disp_2::previous_members_p() {
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