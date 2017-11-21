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

		//destructor
		~Disp_2() {
			for (int i = 0; i < member_images.size(); ++i) {
				delete member_images[i];
			}
		}

	private:
		//members
		vector<Driver> members;
		int screen_num;

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
			next_members();
		}

		void previous_pressed() {
			previous_members();
		}

		void detach_all();

		void attach_all();

		void next_members();

		void previous_members();

		void quit();

		//callback functions
		static void cb_next(Address, Address);
		static void cb_previous(Address, Address);
		static void cb_quit(Address, Address);
	};

	Disp_2::Disp_2(Point xy, int w, int h, const string& title, const vector<Driver>& m) :
		//initialization
		Window(xy, w, h, title),

		members(m),

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
			"Format: 2x2"
		),

		member1_info(Point(x_max() / 4, y_max() / 3), 100, 100, "Item 1"),
		member2_info(Point(x_max() / 4 * 3, y_max() / 3), 100, 100, "Item 2"),
		member3_info(Point(x_max() / 4, y_max() / 3 * 2), 100, 100, "Item 3"),
		member4_info(Point(x_max() / 4 * 3, y_max() / 3 * 2), 100, 100, "Item 4")

	{//constructor body
	 // get all images for members
		int x_coord, y_coord;
		string image_name;
		for (int i = 0; i < members.size(); ++i) {
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
			image_name = members[i].get_photo();
			stringstream ss;
			ss << image_name << ".jpg";
			ss >> image_name;
			Image* memb_im = new Image(Point(x_coord, y_coord), image_name);
			memb_im->resize(100, 100);
			member_images.push_back(memb_im);
		}

		attach_all();

		attach(quit_button);
		attach(next_button);
		if (members.size() <= 4)
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

	void Disp_2::detach_all() {
		if (members.size() >= screen_num * 4 + 1) {
			detach(member1_info);
			detach(*member_images[screen_num * 4]);
		}
		if (members.size() >= screen_num * 4 + 2) {
			detach(member2_info);
			detach(*member_images[screen_num * 4 + 1]);
		}
		if (members.size() >= screen_num * 4 + 3) {
			detach(member3_info);
			detach(*member_images[screen_num * 4 + 2]);
		}
		if (members.size() >= screen_num * 4 + 4) {
			detach(member4_info);
			detach(*member_images[screen_num * 4 + 3]);
		}
	}

	void Disp_2::attach_all() {
		if (members.size() >= screen_num * 4 + 1) {
			attach(member1_info);
			member1_info.put(members[screen_num * 4].display());
			attach(*member_images[screen_num * 4]);


		}
		if (members.size() >= screen_num * 4 + 2) {
			attach(member2_info);
			member2_info.put(members[screen_num * 4 + 1].display());
			attach(*member_images[screen_num * 4 + 1]);
		}
		if (members.size() >= screen_num * 4 + 3) {
			attach(member3_info);
			member3_info.put(members[screen_num * 4 + 2].display());
			attach(*member_images[screen_num * 4 + 2]);
		}
		if (members.size() >= screen_num * 4 + 4) {
			attach(member4_info);
			member4_info.put(members[screen_num * 4 + 3].display());
			attach(*member_images[screen_num * 4 + 3]);
		}
	}

	void Disp_2::next_members() {
		// 4 items per screen (0-3), (4-7), (8-11), ...
		// Screen:          0      1      2     ...

		// Clean up the screen in case there are not enough objects to display
		detach_all();

		screen_num++;

		attach_all();

		// Will always have a previous after a next
		previous_button.show();

		if (members.size() <= 4 * (screen_num + 1))
			next_button.hide();
	}

	void Disp_2::cb_next(Address, Address pw) {
		reference_to<Disp_2>(pw).next_pressed();
	}

	void Disp_2::previous_members() {
		// Clean up screen
		detach_all();

		screen_num--;

		attach_all();

		// Will always be a next after a previous
		next_button.show();

		if (screen_num == 0)
			previous_button.hide();
	}
}
#endif