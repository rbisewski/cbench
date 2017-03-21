# cbench - Multi-threaded software renderer and benchmark, written in C

cbench is a tiny software rendering program that uses OpenMP to
parallelize a rendered scene.

Originally this was utilized as a multi-thread CPU benchmark for my own
servers and systems, ideally headless or at least independent of Xorg or
other graphical and GUI based systems.

The code itself is based off of a fork of the famous 99 line C++ smallpt
software renderer created by Kevin Beason in 2008.

Perhaps one day additional rendering features could be added, but for now
it is a nifty C version of the original path tracing application.


# Requirements

Specifically, the following package is required:

* gcc 4.5 or later

Recommend examining the Makefile for more details if you are unable to get
cbench to properly compile.


# Installation

Run make and copy cbench to the relevant bin directory on your OS.


# Running cbench

cbench <samples>

Where "samples" refers to the number of paths to render.

An example usage case would be... 

cbench 7000

This will attempt to path trace 7000 samples so this could take a long
time on slower computers, however, anything new should not take more than
about 10 minutes.

Afterwards the user will see a "image.ppm" file present, which contains
the rendered image. Consider openning it in the GIMP to ensure the
benchmark performed normally (e.g. no distortions).

# Authors

The code in this program was based on ideas of Kevin Beason's 99
line C++ program. For more information, consider contacting him at:

* Website -> www.kevinbeason.com/smallpt

* Email -> kevin.beason@gmail.com

This was forked and adapted to the C language by Robert Bisewski at Ibis
Cybernetics. For more information, contact:

* Website -> www.ibiscybernetics.com

* Email -> contact@ibiscybernetics.com
