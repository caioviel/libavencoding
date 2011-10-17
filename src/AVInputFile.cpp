/*
 * AVInputFile.cpp
 *
 *  Last Change: Oct 6, 2010
 *       Author: Caio César Viel
 *        Email: caio_viel@comp.ufscar.br
 */

#include <libffmpeg/libffmpeg.h>
#include "../include/AVInputFile.h"

namespace br{
namespace ufscar{
namespace lince{
namespace streaming{

AVInputFile::AVInputFile(string filename,
		string format) : AVSource(format) {

	this->filename = filename;
}

string AVInputFile::getFilename() {
	return filename;
}

void AVInputFile::configure(void *ffrapper_) {
	/*if (configured) {
		return;
	}*/
	configured = true;

	FFMpeg_setFormat( (char*) getFormat().c_str());
	FFMpeg_setInputFile( (char*) getFilename().c_str());
}

AVInputFile::~AVInputFile() {
	// TODO Auto-generated destructor stub
}

}
}
}
}