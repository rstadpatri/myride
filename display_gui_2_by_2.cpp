#include <iostream>    // for i/o
#include <sstream>     // for string streams
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"
#include "std_lib_facilities_4.h"
#include "myride_class_functions.h"

using namespace funct_lib;
using namespace Graph_lib;
using namespace std;

struct Disp_2 : Graph_lib::Window {

	//constructor
	Disp_2(Point xy, int w, int h, const string& title, const vector<Member>& m);

	//destructor
	~Disp_2() {
		for (int i = 0; i < member_images.size(); ++i) {
			delete member_images[i];
		}
	}

private:
	//members
	vector<Member> members;
	int screen_num;

	//widgets:
	Text format;

	//member images and info
	vector<Image*> member_images;
	Text member1_info;
	Text member2_info;
	Text member3_info;
	Text member4_info;

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

	void next_members();

	void previous_members();

	void quit();

	//callback functions
	static void cb_next(Address, Address);
	static void cb_previous(Address, Address);
	static void cb_quit(Address, Address);
};

Disp_2::Disp_2(Point xy, int w, int h, const string& title, const vector<Member>& m) :
	//initialization
	Window(xy, w, h, title),

	members(m),

	screen_num(0),

	next_button(
		Point(x_max() - 70, y_max()),
		70, 20,
		"Next",
		cb_next
	),

	previous_button(
		Point(0, y_max()),
		70, 20,
		"Previous",
		cb_previous
	),

	quit_button(
		Point(x_max() - 70, 0),
		70, 20,
		"Quit",
		cb_quit
	),

	format(
		Point(x_max() / 2 - 70, 10),
		"Format: 2x2"
	),

	member1_info(Text(Point(x_max() / 4, y_max() / 3), "Item 1")),
	member2_info(Text(Point(x_max() / 4 * 3, y_max() / 3), "Item 2")),
	member3_info(Text(Point(x_max() / 4, y_max() / 3 * 2), "Item 3")),
	member4_info(Text(Point(x_max() / 4 * 3, y_max() / 3 * 2), "Item 4"))

{//constructor body
 // get images & info for members if there are enough members
	int x_coord, y_coord;
	string image_name;
	for (int i = 0; i < members.size(); ++i) {
		if (4 % i == 1) {
			x_coord = x_max() / 4;
			y_coord = y_max() / 3 - 100;
		}
		else if (4 % i == 2) {
			x_coord = x_max() / 4 * 3;
			y_coord = y_max() / 3 - 100;
		}
		else if (4 % i == 3) {
			x_coord = x_max() / 4;
			y_coord = y_max() / 3 * 2 - 100;
		}
		else {
			x_coord = x_max() / 4 * 3;
			y_coord = y_max() / 3 * 2 - 100;
		}
		image_name = members[i].get_photo();
		Image* memb_im = new Image(Point(x_coord, y_coord), image_name);
		member_images.push_back(memb_im);
	}

	if (members.size() >= 1) {
		member1_info.set_label(members[0].display());
		attach(member1_info);
		attach(*member_images[0]);
	}
	else if (members.size() >= 2) {
		member2_info.set_label(members[1].display());
		attach(member2_info);
		attach(*member_images[1]);
	}
	else if (members.size() >= 3) {
		member3_info.set_label(members[2].display());
		attach(member3_info);
		attach(*member_images[2]);
	}
	else if (members.size() >= 4) {
		member4_info.set_label(members[3].display());
		attach(member4_info);
		attach(*member_images[3]);
	}

	attach(quit_button);
	attach(next_button);
	if (members.size() > 4)
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
	detach(member1_info);
	detach(*member_images[screen_num * 4]);
	detach(member2_info);
	detach(*member_images[screen_num * 4 + 1]);
	detach(member3_info);
	detach(*member_images[screen_num * 4 + 2]);
	detach(member4_info);
	detach(*member_images[screen_num * 4 + 3]);
}

void Disp_2::next_members() {
	// 4 items per screen (0-3), (4-7), (8-11), ...
	// Screen:          0      1      2     ...

	// Clean up the screen in case there are not enough objects to display
	detach_all();

	screen_num++;

	// get images & info for members if there are enough members
	if (members.size() >= screen_num * 4 + 1) {
		member1_info.set_label(members[screen_num * 4].display());
		attach(member1_info);
		attach(*member_images[screen_num * 4]);
	}
	else if (members.size() >= screen_num * 4 + 2) {
		member2_info.set_label(members[screen_num * 4 + 1].display());
		attach(member2_info);
		attach(*member_images[screen_num * 4 + 1]);
	}
	else if (members.size() >= screen_num * 4 + 3) {
		member3_info.set_label(members[screen_num * 4 + 2].display());
		attach(member3_info);
		attach(*member_images[screen_num * 4 + 2]);
	}
	else if (members.size() >= screen_num * 4 + 4) {
		member4_info.set_label(members[screen_num * 4 + 3].display());
		attach(member4_info);
		attach(*member_images[screen_num * 4 + 3]);
	}

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

	// Will attach all four items because previous was able to be called
	member1_info.set_label(members[screen_num * 4].display());
	attach(member1_info);
	attach(*member_images[screen_num * 4]);

	member2_info.set_label(members[screen_num * 4 + 1].display());
	attach(member2_info);
	attach(*member_images[screen_num * 4 + 1]);

	member3_info.set_label(members[screen_num * 4 + 2].display());
	attach(member3_info);
	attach(*member_images[screen_num * 4 + 2]);

	member4_info.set_label(members[screen_num * 4 + 3].display());
	attach(member4_info);
	attach(*member_images[screen_num * 4 + 3]);

	next_button.show();

	if (screen_num == 0)
		previous_button.hide();
}

// REMOVE THIS AFTER TESTING!
int main() {
	try {
		import_data();
		vector<Member> data = get_drivers();
		Disp_2 win(Point(1000, 100), 1000, 1000, "Display - 2x2", data);
		return gui_main();
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
}
