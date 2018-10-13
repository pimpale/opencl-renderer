#ifndef X_WINDOW_HPP_
#define X_WINDOW_HPP_


#include <vector>
#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "utils.hpp"

class x_window{
public:
	x_window(uint32_t x_size,uint32_t y_size);
	~x_window();

	void redraw();

	void get_user_input();
	uint32_t get_mouse_x();
	uint32_t get_mouse_y();
	uint32_t get_previous_mouse_x();
	uint32_t get_previous_mouse_y();
	bool get_mouse_down();

	uint32_t get_x_size();
	uint32_t get_y_size();

	std::vector<KeySym> get_keys_pressed();
	bool is_key_pressed(KeySym key_sym);
	void set_color(uint32_t color);
	void draw_point(uint32_t x, uint32_t y);
	void draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
	void draw_string(uint32_t x, uint32_t y, std::string text);
	void fill_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

	Display *dis;
	Window win;
	GC gc;
private:

	XEvent event = XEvent();		// the XEvent declaration !!!
	KeySym key = KeySym();		// a dealie-bob to handle KeyPress Events
	std::vector<KeySym> keys_pressed;// pressed keys
	//some other input-related stuff
	bool mouse_down = false;
	uint32_t mouse_x = 0;
	uint32_t mouse_y = 0;
	uint32_t mouse_previous_x = 0;
	uint32_t mouse_previous_y = 0;
	uint32_t x_size;
	uint32_t y_size;

};

#endif
