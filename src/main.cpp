#include <iostream>
#include <pthread.h>
#include <thread>

#include "utils.hpp"
#include "camera.hpp"
#include "linmath.h"
#include "x_window.hpp"

#define SCALE 1

#define DEFAULT_FRAME_XSIZE 500
#define DEFAULT_FRAME_YSIZE 500 //Even so, still 10,000 rays to consider

#define FRAME_REQUEST_TIME 0.01 //Half a second to reduce the lag
#define SCREEN_REFRESH_TIME 0.01 //Ok if higher, this is on our cpu


static bool running = true;

void output_to_window(x_window* win, camera* cam)
{
	while(running)
	{
		uint32_t height = cam->get_y_size();
		uint32_t width = cam->get_x_size();

		uint32_t* col_array = cam->get_frame_buffer();

		sleep_seconds(SCREEN_REFRESH_TIME);
		for(uint32_t y = 0; y < height; y++)
		{
			for(uint32_t x = 0; x < width; x++)
			{
				win->set_color(col_array[width*y + x]);
				win->fill_rect(x*SCALE,y*SCALE,SCALE,SCALE);
			}
		}
	}
}

void get_user_input(x_window* win, camera* cam)
{
	while(running)
	{

		sleep_seconds(SCREEN_REFRESH_TIME);
		win->get_user_input();

		//Die if q pressed
		if(win->is_key_pressed(XK_q))
		{
			running = false;
		}

		uint32_t camera_x_size = win->get_x_size()/SCALE;
		uint32_t camera_y_size = win->get_y_size()/SCALE;

		if(camera_x_size != cam->get_x_size() || camera_y_size != cam->get_y_size())
		{
			cam->set_size(camera_x_size, camera_y_size);
		}

		float mo = 0.05;
		float ro = 0.05;

		if(win->is_key_pressed(XK_a))
			cam->mover(-mo,0,0);
		if(win->is_key_pressed(XK_d))
			cam->mover(mo,0,0);
		if(win->is_key_pressed(XK_w))
			cam->mover(0,0,mo);
		if(win->is_key_pressed(XK_s))
			cam->mover(0,0,-mo);


		vec3 horizontal_axis = {1.0f, 0.0f, 0.0f};
		vec3 vertical_axis = {0.0f, 1.0f, 0.0f};
		vec3 frontback_axis = { 0.0f, 0.0f, 1.0f };

		if(win->is_key_pressed(XK_Left))
		{
			quat q;
			quat_rotate(q,-ro,vertical_axis);
			cam->rotate(q);
		}
		if(win->is_key_pressed(XK_Right))
		{
			quat q;
			quat_rotate(q,ro,vertical_axis);
			cam->rotate(q);
		}
		if(win->is_key_pressed(XK_Up))
		{
			quat q;
			quat_rotate(q,ro,horizontal_axis);
			cam->rotate(q);
		}
		if(win->is_key_pressed(XK_Down))
		{
			quat q;
			quat_rotate(q,-ro,horizontal_axis);
			cam->rotate(q);
		}
		if (win->is_key_pressed(XK_Page_Down)) {
			quat q;
			quat_rotate(q, ro, frontback_axis);
			cam->rotate(q);
		}
		if (win->is_key_pressed(XK_Page_Up)) {
			quat q;
			quat_rotate(q, -ro, frontback_axis);
			cam->rotate(q);
		}


	}
}

void get_frames(camera* cam)
{
	while(running)
	{
		sleep_seconds(FRAME_REQUEST_TIME);
		cam->get_next_frame();
	}
}

int main()
{
	//println(std::string("began excution sucessfully at: ") + executable_path());

	println("starting initialization procedures");
	camera cam(0,0,-10,DEFAULT_FRAME_XSIZE/SCALE,DEFAULT_FRAME_YSIZE/SCALE);

	x_window win(DEFAULT_FRAME_XSIZE,DEFAULT_FRAME_YSIZE);
	println("starting threads");
	std::thread frame_thread(get_frames,&cam);
	std::thread input_thread(get_user_input,&win,&cam);
	std::thread screen_thread(output_to_window,&win,&cam);

	println("All threads started sucessfully");
	println("Initialization complete");

	frame_thread.join();
	input_thread.join();
	screen_thread.join();

	return(0);
}
