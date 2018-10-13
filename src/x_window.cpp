#include <iostream>
#include <algorithm>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include "x_window.hpp"
#include "utils.hpp"

x_window :: x_window(uint32_t x_size, uint32_t y_size) {
	println("~~~~~~begin x window initialization~~~~~~");
	this->x_size = x_size;
	this->y_size = y_size;
	println(std::string("Attempting to initialize x window with dimensions: ") + std::to_string(x_size) + std::string("x") + std::to_string(y_size));
	XInitThreads();
	dis=XOpenDisplay((char *)0);
	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,
			x_size, y_size, 0, 0, 0);
	XSetStandardProperties(dis,win,"Now with even more confusing vectors!","4Sight",None,NULL,0,NULL);
	XSelectInput(dis, win,
			StructureNotifyMask|ButtonPressMask|ButtonReleaseMask|PointerMotionMask|KeyPressMask|KeyReleaseMask);
	gc=XCreateGC(dis, win, 0,0);
	XSetBackground(dis,gc,0);
	XSetForeground(dis,gc,0);
	XClearWindow(dis, win);
	XMapRaised(dis, win);
}


x_window :: ~x_window() {
	println("destroying window");
	//free window
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);
}

void x_window :: get_user_input() {
	// get the next event and stuff it into our event variable.
	// Note:  only events we set the mask for are detected!
	while (XPending(dis) > 0)
	{
		XNextEvent(dis, &event);
		switch (event.type) {

		case ConfigureNotify: {
			XConfigureEvent xce = event.xconfigure;
			x_size = xce.width;
			y_size = xce.height;
		}
			break;
		case KeyPress:
		{
			KeySym k = XLookupKeysym(&event.xkey, 0);
			if (std::find(keys_pressed.begin(), keys_pressed.end(), k)
					== keys_pressed.end()) {
				keys_pressed.push_back(k);
			}
		}
			break;
		case KeyRelease:
		{
			KeySym k = XLookupKeysym(&event.xkey, 0);
			keys_pressed.erase(std::remove(keys_pressed.begin(), keys_pressed.end(), k), keys_pressed.end());
		}
		break;
		case ButtonPress: {
			//mouse is down
			mouse_down = true;
		}
			break;
		case ButtonRelease: {
			//mouse is up
			mouse_down = false;
		}
			break;
		case MotionNotify: {
			//set mouses
			mouse_previous_x = mouse_x;
			mouse_previous_y = mouse_y;
			mouse_x = event.xmotion.x;
			mouse_y = event.xmotion.y;
		}
			break;
		default: {

		}

		}
	}
}


uint32_t x_window :: get_mouse_x(){return(mouse_x);}
uint32_t x_window :: get_mouse_y(){return(mouse_y);}
uint32_t x_window :: get_previous_mouse_x(){return (mouse_previous_x);}
uint32_t x_window :: get_previous_mouse_y(){return (mouse_previous_y);}
bool x_window :: get_mouse_down(){return(mouse_down);}
uint32_t x_window :: get_x_size(){return(x_size);}
uint32_t x_window :: get_y_size(){return(y_size);}
std::vector<KeySym> x_window :: get_keys_pressed(){ return(keys_pressed); }
bool x_window :: is_key_pressed(KeySym key_sym){
	return(std::find(keys_pressed.begin(), keys_pressed.end(), key_sym) != keys_pressed.end());
}

void x_window :: redraw()
{

}

void x_window :: set_color(uint32_t color)
{
	XSetForeground(dis, gc, color);
}

void x_window :: draw_point(uint32_t x, uint32_t y)
{
	XDrawPoint(dis, win, gc, x ,y);
}

void x_window :: draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
	XDrawLine(dis, win, gc, x1, y1, x2, y2);
}

void x_window :: draw_string(uint32_t x, uint32_t y, std::string text)
{
	XDrawString(dis, win, gc, x, y, text.c_str(), text.length());
}

void x_window :: fill_rect(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	XFillRectangle(dis,win,gc,x,y,width,height);
}


