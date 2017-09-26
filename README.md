# UnitConverter
A simple unit converter made in C++.
Allows for the conversion of units of Distance, Speed Weight and Currency.
The currency module needs to aquire currency data from the internet at least once to work.
Currency data uses http://api.fixer.io/latest as a source.

# Requirements:
--------------
Requires QT4, gcc and libcurl to compile.

# Compiling on GNU/Linux:
-----------------------
First, configure a Makefile for your system using qmake (qt4)

"$ qmake UnitConverter.pro"

Then, compile

"$ make"

Run it:

"$ ./UnitConverter"

Running on Windows:
-------------------
I provide a Windows binary in the Windows.zip zip as to avoid having
to compile in windows.

To run the program, extract the Windows.zip, change to the win32 folder and double click on
UnitConverter.exe.
