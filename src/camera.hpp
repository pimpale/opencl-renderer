#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <mutex>
#include <stdint.h>
#include "cl.hpp"
#include "linmath.h"

class camera {
public:
	camera(float x, float y, float z, int x_size, int y_size);

	void set_size(uint32_t x_size, uint32_t y_size);
	uint32_t get_x_size();
	uint32_t get_y_size();

	void mover(float x, float y, float z);
	void move(float x, float y, float z);
	void set_location(float x, float y, float z);
	void set_location(cl_float4 location);
	float x();
	float y();
	float z();
	void rotate(quat rot);
	void set_rotation(quat rot);

	void get_next_frame();
	uint32_t* get_frame_buffer();
	~camera();



private:

	uint32_t* frame_buffer;
	uint64_t frame_buffer_size;
	void update_frame_buffer();

	//the x any y camera size and how many rays
	uint32_t x_size;
	uint32_t y_size;
	uint32_t ray_num;

	//camera position
	cl_float4 location;
	quat rotation;

	//opencl stuff
	cl::Platform default_platform;
	cl::Device default_device;
	cl::Context context;
	cl::CommandQueue queue;


	//size of arrays
	uint64_t loc_array_size;
	uint64_t vec_array_size;
	uint64_t col_array_size;
	//arrays holding the arguments
	cl_float4 *loc_array = NULL;
	cl_float4 *vec_array = NULL;
	uint32_t *col_array  = NULL;
	//prevent them from being modified concurrently
	std::mutex loc_array_mutex;
	std::mutex vec_array_mutex;
	std::mutex col_array_mutex;

	void free_array_memory();

	void set_array_size(uint32_t);

	void reset_buffers();

	//buffers hold the data on the gpu
	//scene opencl buffers
	cl::Buffer buffer_data;
	//ray opencl buffers
	cl::Buffer buffer_loc_array;
	cl::Buffer buffer_vec_array;
	cl::Buffer buffer_col_array;
	//ray kernel
	cl::Kernel kernel;
	cl::Event event = cl::Event(); //lets us check on any events
};

#endif //CAMERA_HPP_
