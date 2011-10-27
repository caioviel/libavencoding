/*
 * screenshotTest.cpp
 *
 *  Last Change: Oct 27, 2011
 *       Author: Caio César Viel
 *        Email: caio_viel@dc.ufscar.br
 *
 * This program take shots of the x11 (screen) and generate a images files called screenshotX.jpg
 * It uses the image codec MJPEG.
 */

#include "../include/X11Terminal.h"
#include "../include/ImageShotter.h"
using namespace ::br::ufscar::lince::avenconding;

#include <libcpputil/Functions.h>
using namespace ::cpputil;

#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	AVSource* x11terminal = new X11Terminal(1280, 1024, 24);
	ImageShotter* shotter = new ImageShotter(x11terminal);

	shotter->setImageSize(800, 600);
	shotter->takeShot("screenshot1.jpg");
	shotter->waitFinishing();

	shotter->takeShot("screenshot2.jpg");
	while (!shotter->isFinished()) {
		usleep(50000);
	}

	bool continueLoop;
	int index = 3;
	do {
		string resp;

		continueLoop = false;
		string resposta;
		shotter->takeShot("screenshot" +
				Functions::numberToString(index++) + ".jpg");
		shotter->waitFinishing();
		cout << "Continue take screenshots? (Y/N)";
		cin >> resp;
		if (resp == "y" || resp == "Y") {
			continueLoop = true;
		}
	} while(continueLoop);

	return 0;
}
