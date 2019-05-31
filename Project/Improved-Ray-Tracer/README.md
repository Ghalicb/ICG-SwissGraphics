Ray Tracer
==========

We are using a couple of C++11 features, so please ensure that you use an up-to-date compiler (GCC 4.7 or higher, Visual Studio 2012). [CMake](www.cmake.org) is used for setting up build environments.


Building under Linux/macOS
--------------------------

Inside the exercise's top-level directory, execute the following commands:

    mkdir build
    cd build
    cmake ..
    make

The last command -- i.e. `make` -- compiles the application. Rerun it whenever you have added/changed code in order to recompile.

To build a pretty documentation use:

    make doc

and open the `index.html` in the html folder with your favourite browser. To build the documentation, you must install Doxygen.

Running the Ray Tracer
----------------------

The program expects two command line arguments: an input scene (`*.sce`) and an output image (`*.png`). To render the scene with the three spheres, while inside the `build` directory, type:

    ./raytrace ../scenes/spheres/spheres.sce output.png

