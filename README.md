# opencl-renderer

This project is a volumetric raymarcher coded in C++ and OpenCL. Its goal is to render an arbitrary tetrahedronal mesh. 


Like all C++ programs, it starts at main. 

main.cpp

Main is where the program starts and ends. In this program, main continuously recieves input from the screen, updates the camera, and updates the screen.

x_window.cpp

The x_window class is for drawing and recieving user input events. It  relies on the x windowing protocol, a very basic library for making a window.  After creating the window, we can listen for events on it. Events include button and key presses as well as mouse clicks and window resizes. There is also an option to draw and set color. 

camera.cpp

The camera class is the main part of the program. It handles the actual interfacing with the gpu as well. It processes the user inputted data it gets from x_window and sends the data to be drawn to the x_window. Most importantly, it compiles and runs the kernel.

utils.cpp

This class is filled with helpful methods that are miscellaneous, like finding the time, rotating vectors, or converting color formats.

raycast.cl

Unlike the other files, this one is not in c++. It is written in OpenCL, a language based on C. However, it lacks many features and is heavily stripped down. But, it also can run simultaneously for thousands of calculations. This code is responsible for the actual vector calculations, like tracing out the paths of every ray and reporting back the color. 
