/*
 * AVOutoutFile.h
 *
 *  Last Change: Oct 6, 2010
 *       Author: Caio César Viel
 *        Email: caio_viel@comp.ufscar.br
 */

#ifndef AVOUTPUTFILE_H_
#define AVOUTPUTFILE_H_

#include <libffmpeg/libffmpeg.h>

#include <cpputil/Thread.h>
#include <cpputil/InitializationException.h>
using namespace cpputil;

#include <vector>
using namespace std;

#include "Transcoder.h"

namespace br {
namespace ufscar {
namespace lince {
namespace streaming {

/**
 * This class is used to generate a audio/video output file as result of a transcoding process.
 * It implements the abstract class Transcoder.
 */
class AVOutputFile: public Transcoder, public Thread {
public:
	/**
	 * Construtor
	 * @param filename the name of the file that will be generated.
	 * @param format the format of the fila that will be generated.
	 */
	AVOutputFile(string filename, string format="", bool fileOverwrite=false);

	/**
	 * Virtual Destructor
	 */
	virtual ~AVOutputFile();

	/**
	 * Return the name of the file that will be generate.
	 * @param the name of the file.
	 */
	string getFilename();

	/**
	 * Abort the transcoding process.
	 * @throw InitializationException if the process hasn't begun.
	 */
	void stop();

	/**
	 * Start the transcoding and streaming process.
	 * This method should be called after the streaming and transcoding process was defined.
	 * It creates a new theard that will process with the process.
	 * @throw InitializationException if no stream was add.
	 * @throw OptionException when parameters informed are wrong or invalids.
	 * @throw TranscodingException when errors occurs during the transcoding processes.
	 * @see addStream
	 */
	virtual void start();

	/**
	 * This method is used to add a new audio-video stream
	 * to the network stream that will be generated.
	 * @param stream the audio-video stream.
	 */
	void addStream(AVEncoder* stream);

	/**
	 * This method returns true if the transcoding process is finished.
	 * It can be used to create a non-block program, that will not sleep until the coding
	 * is finished.
	 * @return True if the transcoding process is finished; false otherwise.
	 */
	virtual bool isFinished();

	/**
	 * This method waits until the transcoding process is finished.
	 * It can be used to create a block program, that will sleep until the coding is finished.
	 * @throw InitializationException when the transcoding process hasn't begun.
	 */
	virtual void waitFinishing();

protected:
	bool finished;
	bool started;

private:
	void run();
	vector<AVSource*>* sources;
	vector<AVEncoder*>* encoders;
	string filename;
	string format;

	bool fileOverwrite;
};

}
}
}
}

#endif /* AVOUTPUTFILE_H_ */