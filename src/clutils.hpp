/*
 * clutils.hpp
 *
 *  Created on: Jan 2, 2018
 *      Author: fidgetsinner
 */

#ifndef CLUTILS_HPP_
#define CLUTILS_HPP_

#include <iostream>
#include <vector>

#include "cl.hpp"

cl::Platform get_platform(int32_t i, bool display) {
  /* Returns platform specified by the index i on a platform.
   * If display is true, then all of the platforms are listed
   */
  std::vector<cl::Platform> all_platforms;
  cl::Platform::get(&all_platforms);
  if (all_platforms.size() == 0) {
    std::cout << "No platforms found. Check OpenCL installation!\n";
    exit(1);
  }

  if (display) {
    for (uint32_t j = 0; j < all_platforms.size(); j++) {
      std::cout << "Platform " << j << ": "
                << all_platforms[j].getInfo<CL_PLATFORM_NAME>() << std::endl;
    }
  }

  return (all_platforms[i]);
}

cl::Device get_device(cl::Platform platform, int32_t i, bool display) {
  /* Returns the deviced specified by the index i on platform.
   * If display is true, then all of the platforms are listed.
   */
  std::vector<cl::Device> all_devices;
  platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
  if (all_devices.size() == 0) {
    std::cout << "No devices found. Check OpenCL installation!\n";
    exit(1);
  }

  if (display) {
    for (uint32_t j = 0; j < all_devices.size(); j++) {
      std::cout << "Device " << j << ": "
                << all_devices[j].getInfo<CL_DEVICE_NAME>() << std::endl;
    }
  }
  return (all_devices[i]);
}

cl::Context get_context(cl::Device device) {
  std::vector<cl::Device> device_vector = {device};
  return (cl::Context(device_vector));
}

cl::Program build_program(std::string program_source, cl::Context context,
                          cl::Device device) {
  cl::Program::Sources sources;
  sources.push_back({program_source.c_str(), program_source.length()});

  cl::Program program(context, sources);

  std::vector<cl::Device> cld;
  cld.push_back(device);
  if (program.build(cld) != CL_SUCCESS) {
    std::cout << " Error building: "
              << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << "\n";
    exit(1);
  }
  return (program);
}

#endif /* CLUTILS_HPP_ */
