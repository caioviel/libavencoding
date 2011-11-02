/*
 * X11Terminal.cpp
 *
 *  Last Change: Oct 6, 2010
 *       Author: Caio César Viel
 *        Email: caio_viel@comp.ufscar.br
 */

#include "../include/X11Terminal.h"

#include <X11/Xlib.h>

#include <libffmpeg/libffmpeg.h>

#include <libcpputil/Functions.h>
#include <libcpputil/IllegalParameterException.h>
using namespace cpputil;

using namespace cpputil::logger;

#include <iostream>
using namespace std;

namespace br {
namespace ufscar {
namespace lince {
namespace avencoding {

X11Terminal::X11Terminal(int width, int height, int fps) :
		AVSource("x11grab"), Loggable("br::ufscar::lince::avencoding::X11Terminal") {

	trace("begin Constructor");

	this->width = width;
	this->height = height;
	this->fps = fps;
}

X11Terminal::X11Terminal(int fps) :
		AVSource("x11grab"), Loggable("br::ufscar::lince::avencoding::X11Terminal") {

	trace("begin Constructor");
	XWindowAttributes wAttributes;
	Display* display = XOpenDisplay(NULL);
	Screen* screen = XScreenOfDisplay(display, DefaultScreen(display));
	int width = WidthOfScreen(screen);
	int height = HeightOfScreen(screen);
	cout<<"screen size: "<< width <<"x" << height << endl;
	this->width = width;
	this->height = height;
	this->fps = fps;
}

X11Terminal::X11Terminal() : AVSource("x11grab") {
	X11Terminal(25);
}

X11Terminal::~X11Terminal() {
	// TODO Auto-generated destructor stub
}


int X11Terminal::getFps() {
	return fps;
}

void X11Terminal::configure(void *_ffrapper) {
	trace("begin configure(void*)");
	/*if (configured) {
		return;
	}*/
	configured = true;

	if (FFMpeg_setFormat((char*) "x11grab") != FFMpeg_SUCCESS) {
		error("Error trying to set the format.");
		throw IllegalParameterException(
				FFMpeg_getErrorStr(),
				"br::ufscar::lince::avencoding::X11Terminal",
				"configure(void*)");
	}

	if (FFMpeg_setFramerate((char*)
			Functions::numberToString(fps).c_str()) != FFMpeg_SUCCESS) {

		error("Error trying to set the frame rate.");
		throw IllegalParameterException(
				FFMpeg_getErrorStr(),
				"br::ufscar::lince::avencoding::X11Terminal",
				"configure(void*)");


	}
	if (FFMpeg_setFrameSize2(width, height) != FFMpeg_SUCCESS) {
		error("Error trying to set the frame size.");
		throw IllegalParameterException(
				FFMpeg_getErrorStr(),
				"br::ufscar::lince::avencoding::X11Terminal",
				"configure(void*)");

	}

	if (FFMpeg_setInputFile((char*) ":0.0") != FFMpeg_SUCCESS) {
		error("Error trying to set the device 0:0.");
		throw IllegalParameterException(
				FFMpeg_getErrorStr(),
				"br::ufscar::lince::avencoding::X11Terminal",
				"configure(void*)");
	}
}

int X11Terminal::getHeight() {
	return height;
}

int X11Terminal::getWidth() {
	return width;
}

}
}
}
}
