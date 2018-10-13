# opencl-renderer

This project is a volumetric raymarcher coded in C++ and OpenCL. Its goal is to demonstrate the use of raymarching using OpenCL, especially over noneuclidean topologies. This demo renders an infinite number of 3d cubes. It won an award at the Synopsys Championship science fair in Santa Clara.

The source is provided as an Eclipse C/C++ Project, and can simply be imported into eclipse and run.
To build manually, 

```bash
$ cd Debug/
$ make clean all
$ cd ..
$ ./Debug/opencl-renderer
```

It should be run from the project root.
