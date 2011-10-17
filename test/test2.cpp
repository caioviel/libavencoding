/*
 * test2.cpp
 *
 *  Last Change: Oct 6, 2010
 *       Author: Caio César Viel
 *        Email: caio_viel@comp.ufscar.br
 *
 * This program transcodes the content of the shared buffer into a video using the codec h264 and
 * a transcodes a audio from the file audio.mp3 using the codec aac. The coded video and
 * audio are used to generate a MpegTS, that is streamed using the UDP protocol addressed
 * to the localhost on port 5004.
 */

#include <streaming/X11Terminal.h>
#include <streaming/AVInputFile.h>
#include <streaming/AVSource.h>
#include <streaming/AVEncoder.h>
#include <streaming/Streaming.h>
#include <streaming/UDPMpegTS.h>

using namespace ::br::ufscar::lince::streaming;

int main() {
	AVSource* device = new X11Terminal(1280, 1024, 25);
	AVSource* file = new AVInputFile("audio.mp3", "mp3");

	AVEncoder* encoderVid = new AVEncoder(device);
	encoderVid->setVideoCodec(H264);
	encoderVid->setVideoPreset("ultrafast");
	encoderVid->setPropertyValue("crf", "22");

	AVEncoder* encoderAud = new AVEncoder(file);
	encoderAud->setAudioCodec(AAC);

	Streaming* streammer = new UDPMpegTS("127.0.0.1", 1234);
	streammer->addStream(encoderVid);
	//streammer->addStream(encoderAud);
	streammer->start();

	streammer->waitFinishing();

	return 0;
}
