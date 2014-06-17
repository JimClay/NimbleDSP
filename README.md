SlickDsp
========

## About
SlickDsp is a C++ digital signal processing (DSP) library that aims to be fast, comprehensive, and most importantly- really easy to use.

## Features
* Vector classes for real, complex, floating point, and fixed point data types.
* Filter classes (coming)
* Matlab-style syntax (e.g. "spectrum_dB = log10(abs(fft(data))) * 20;")
* Efficient multi-rate filter functions (decimate, interp, and resample)
* FFT and inverse FFT
* 100% template classes and functions
* Doxygen comments/documentation for all methods and functions.
* Comprehensive unit tests.
* Non-restrictive license (MIT) that allows you to keep your software proprietary if you want.

## Installation
None required!  Well, mostly none.  All of the source code is header files so all you have to do is "include" it in your code and make sure that their directory is in your include path.  The libraries header files are all in the "src" directory.

You will also need a header file from KissFFT.  Download it from [here](https://sourceforge.net/projects/kissfft/) and unzip the package wherever you wish (though if you wish to build and run the unit tests you should put it at the same level as SlickDsp- see the Unit Tests section) and include its top-level directory in your include path.

### Unit Tests
That being said, you may want to get the unit tests up and running.  If so, do the following steps:

* Download the latest copy of KissFFT and unzip it at the same level as SlickDsp (i.e. not inside the SlickDsp directory).
* Download googletest by executing the following at the same level as SlickDsp and KissFFT: "svn checkout http://googletest.googlecode.com/svn/trunk/ googletest-read-only".  If you don't have a Subversion client installed and really don't want to install one you can probably download the source as a zip file [here](https://code.google.com/p/googletest/downloads/list), unzip it and rename the directory to "googletest-read-only", but I haven't tried it.
* Linux platform
    * cd to SlickDsp/build
    * run "cmake .."
    * run "make"
    * If all went well then a SlickDspTests executable was created.  Run it to execute the unit tests.
* Mac platform
    * cd to SlickDsp/build
    * run "cmake .. -G Xcode"
    * Start Xcode and open the SlickDsp/build/SlickDsp.xcodeproj file.
    * Build the project.
    * Prepare to run the unit tests inside of Xcode by switching the scheme from "ALL_BUILD" to "SlickDspTests->My Mac (64 bit)".
    * Run the program.
* Windows platform
    * Run the Cmake Gui.
    * Set the directory to run out of to the SlickDsp directory.
    * Set the directory to put the build files in to SlickDsp/build.
    * Push the "Configure" button.  You will have to have a modern C++ compiler installed, like Visual Studio 2013.  I have done this with VC++ 2013, but not with any others.  It will probably work with any compiler that supports C++11, but I don't guarantee it- especially since Microsoft's standards support has often been spotty.
    * Push the "Generate" button.
    * Start Visual Studio (or whatever compiler you configured Cmake for), go to the build directory and open the SlickDsp.sln file.
    * ##########

## Documentation
To create the code documentation do the following:

* Run the Doxygen GUI.
* Tell it to operate in the SlickDsp directory.
* Open the config file "doxygen.cfg".
* Tell Doxygen to run.  It will put the HTML documentation in the doc directory.

## License
SlickDsp is offered under the MIT license.  KissFFT is available under the BSD license.  Both are very similar.  They basically let you do whatever you want- for the fine print read the license files.

## Author
Jim Clay