#include <iostream>

#include "clutils.hpp"
#include "utils.hpp"

#include "camera.hpp"

camera ::camera(float x, float y, float z, int x_size, int y_size) {
  location = cl_float4{x, y, z, 0};
  quat_identity(rotation);

  // openCL initialization
  println("~~~~~~~begin camera initialization~~~~~~~");
  println("Starting OpenCL");
  default_platform = get_platform(0, true);
  default_device = get_device(default_platform, 0, true);
  context = get_context(default_device);
  queue = cl::CommandQueue(context, default_device);

  std::string file_name = "raycast.cl";
  // std::string file_loc = executable_path();
  // println("Attempting to read the kernel file at: " + file_loc + file_name);
  std::string raycast_3d_simple = read_file(file_name);
  kernel = cl::Kernel(build_program(raycast_3d_simple, context, default_device),
                      "raycast");

  println("Kernel built sucessfully");

  set_size(x_size, y_size);

  get_next_frame();
}

void camera ::free_array_memory() {
  loc_array_mutex.lock();
  col_array_mutex.lock();
  vec_array_mutex.lock();
  delete[](loc_array);
  loc_array = NULL;
  delete[](vec_array);
  vec_array = NULL;
  delete[](col_array);
  col_array = NULL;
  loc_array_mutex.unlock();
  col_array_mutex.unlock();
  vec_array_mutex.unlock();
}

void camera ::set_array_size(uint32_t size) {
  loc_array_mutex.lock();
  col_array_mutex.lock();
  vec_array_mutex.lock();

  // create new resized arrays
  loc_array = new cl_float4[size];
  vec_array = new cl_float4[size];
  col_array = new uint32_t[size];
  loc_array_size = sizeof(*loc_array) * size;
  vec_array_size = sizeof(*vec_array) * size;
  col_array_size = sizeof(*col_array) * size;

  loc_array_mutex.unlock();
  col_array_mutex.unlock();
  vec_array_mutex.unlock();
}

void camera ::reset_buffers() {

  loc_array_mutex.lock();
  col_array_mutex.lock();
  vec_array_mutex.lock();
  // create buffers
  buffer_loc_array = cl::Buffer(context, CL_MEM_READ_WRITE, loc_array_size);
  buffer_vec_array = cl::Buffer(context, CL_MEM_READ_WRITE, vec_array_size);
  buffer_col_array = cl::Buffer(context, CL_MEM_READ_WRITE, col_array_size);
  loc_array_mutex.unlock();
  col_array_mutex.unlock();
  vec_array_mutex.unlock();

  // set kernel args
  kernel.setArg(0, buffer_loc_array);
  kernel.setArg(1, buffer_vec_array);
  kernel.setArg(2, buffer_col_array);
}

void camera ::set_size(uint32_t xsize, uint32_t ysize) {
  x_size = xsize;
  y_size = ysize;
  ray_num = xsize * ysize;

  set_array_size(ray_num);

  reset_buffers();

  set_location(location);
  set_rotation(rotation);
}

uint32_t camera ::get_x_size() { return (x_size); }
uint32_t camera ::get_y_size() { return (y_size); }

// gets new frame by executing kernel
void camera ::get_next_frame() {
  col_array_mutex.lock();
  loc_array_mutex.lock();
  vec_array_mutex.lock();

  memset(col_array, 0, col_array_size);

  queue.finish();

  // read result C from the device to array C
  queue.enqueueReadBuffer(buffer_col_array, CL_TRUE, 0, col_array_size,
                          col_array);

  queue.enqueueWriteBuffer(buffer_loc_array, CL_TRUE, 0, loc_array_size,
                           loc_array);
  queue.enqueueWriteBuffer(buffer_vec_array, CL_TRUE, 0, vec_array_size,
                           vec_array);
  queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(ray_num),
                             cl::NullRange, NULL, &event);

  col_array_mutex.unlock();
  loc_array_mutex.unlock();
  vec_array_mutex.unlock();
}

void camera ::update_frame_buffer() {
  col_array_mutex.lock();
  if (frame_buffer_size != col_array_size) {
    frame_buffer_size = col_array_size;
    delete[] frame_buffer;
    frame_buffer = new uint32_t[col_array_size];
  }

  memcpy(frame_buffer, col_array, col_array_size);
  col_array_mutex.unlock();
}

uint32_t *camera ::get_frame_buffer() {
  update_frame_buffer();
  return (frame_buffer);
}
// free resources
camera ::~camera() { free_array_memory(); }

void camera ::mover(float x, float y, float z) {
  vec3 v = {x, y, z};

  quat_mul_vec3(v, rotation, v);

  move(v[0], v[1], v[2]);
}

void camera ::move(float x, float y, float z) {
  set_location(location.x + x, location.y + y, location.z + z);
}

void camera ::set_location(float x, float y, float z) {
  set_location(cl_float4{x, y, z, 0});
}

void camera ::set_location(cl_float4 location) {
  this->location = location;
  loc_array_mutex.lock();
  for (uint32_t y = 0; y < y_size; y++) {
    for (uint32_t x = 0; x < x_size; x++) {
      loc_array[x_size * y + x] = location;
    }
  }
  loc_array_mutex.unlock();
}

float camera::x() { return (location.x); }
float camera::y() { return (location.y); }
float camera::z() { return (location.z); }

void camera ::rotate(quat rot) {
  // rotate the current quaternion and set this rotation
  quat result;
  quat_mul(result, rotation, rot);
  set_rotation(result);
}

void camera ::set_rotation(quat rot) {
  // set the rotation to the normalized version
  quat_norm(rotation, rot);

  vec_array_mutex.lock();
  for (uint32_t y = 0; y < y_size; y++) {
    for (uint32_t x = 0; x < x_size; x++) {
      float Py = 2 * ((float)y / (float)y_size - 0.5f);
      float Px = 2 * ((float)x / (float)x_size - 0.5f);
      vec3 v{Px, Py, 1.0f};
      quat_mul_vec3(v, rotation, v);
      vec3_norm(v, v);
      vec3_scale(v, v, 0.3);
      vec_array[x_size * y + x] = cl_float4{v[0], v[1], v[2]};
    }
  }
  vec_array_mutex.unlock();
}
