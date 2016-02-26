#Dependencies


Ubuntu 14.04 or higher

For building Graphytti from source code on Ubuntu, the following dependencies must be pre-installed-

* Qt libraries from Qt 5.5.1 or higher
* Compiler:-g++ 4.9.2 or higher

#####Build Steps:-

Make sure that your current directory is Graphytti,then run the below commands 

`qmake Graphytti.pro -r -spec linux-g++ `

Then choose the target_directory where the build is to be located 

`make in  target_directory`

#####Clean Steps:-

`make clean in target_directory`

#Attributions:-

The following tools and libraries have been utilised and we thank their respective authors 

##Qt
Qt  is a cross-platform application framework that is widely used for developing application software that can be run on various software and hardware platforms with little or no change in the underlying codebase, while still being a native application with the capabilities and speed thereof.
This framework has been used under the LGPL v3 license.

##QCustomPlot
QCustomPlot is a Qt C++ widget for plotting and data visualization.
This plotting library focuses on making good looking, publication quality 2D plots, graphs 
and charts, as well as offering high performance for realtime visualization applications.
The library has been used in this project under the GPL v3 license.





 
