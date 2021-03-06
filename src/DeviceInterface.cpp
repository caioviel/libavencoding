/**
 * File: DeviceInterface.cpp
 * Created by: Caio César Viel
 * Contact: caioviel@gmail.com
 * Last Modification: 02-16-2012
 *
 * Copyright (c) 2012 LINCE-UFSCar
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <cstdlib>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>

#include "DeviceInterface.h"
using namespace std;
using namespace cpputil::logger;

#define CLASS_NAME  "br::ufscar::lince::avencoding::DeviceInterface"

//TODO: Verify parameters of the constructor

#define SHMKEY 7101
#define SHMINFOKEY 4687
#define SEMKEY 1246

#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
#else
  union semun {
    int val;                    /* valor para SETVAL */
     struct semid_ds *buf;       /* buffer para IPC_STAT, IPC_SET */
     unsigned short int *array;  /* vetor para GETALL, SETALL */
     struct seminfo *__buf;      /* buffer para IPC_INFO */
  };
#endif

namespace br{
namespace ufscar{
namespace lince{
namespace avencoding{

#ifndef SHM_DEVICE_INFO
#define SHM_DEVICE_INFO
typedef struct {
	int height;
	int width;
	int bitsPerPixel;
	int fps;
	int shmkey;
	int semkey;
} DeviceInfo;
#endif //SHM_DEVICE_INFO


DeviceInterface* DeviceInterface::_instance = NULL;



DeviceInterface::DeviceInterface() : Loggable(CLASS_NAME) {

	trace("begin constructor");
	unmounted = true;
}

DeviceInterface::~DeviceInterface() {
	trace("begin destructor");
}

void DeviceInterface::lock() {
	struct sembuf ssbuf;

	ssbuf.sem_num=0;
	ssbuf.sem_op=-1;
	ssbuf.sem_flg=1;	// flag == 1 indica acesso bloqueante
	semop(semid,&ssbuf,1);

}
void DeviceInterface::unlock() {
	struct sembuf ssbuf;

	ssbuf.sem_num=0;
	ssbuf.sem_op=1;
	ssbuf.sem_flg=1;	// flag == 1 indica acesso bloqueante
	semop(semid,&ssbuf,1);
}

DeviceInterface* DeviceInterface::getInstance() {
	if (_instance == NULL) {
		_instance = new DeviceInterface();
	}
	return _instance;
}

void DeviceInterface::initDeviceInfo() {
	trace("begin initDeviceInfo()");

	union semun sem_un;
	DeviceInfo* info;


	int shmid = shmget(SHMINFOKEY, sizeof(DeviceInfo) ,0777|IPC_CREAT);
	if (shmid < 0) {
		throw cpputil::InitializationException(
				"Couldn't retrive information of the device",
				CLASS_NAME,
				"initDeviceInfo()");
		return;
	}
	/* Associa a variavel local com o buffer compartilhado */
	info = (DeviceInfo*) shmat(shmid,0,0);

	info->width = width;
	info->height = height;
	info->fps = fps;
	info->bitsPerPixel = bitsPerPixel;
}

void DeviceInterface::mount(int width, int height, int bitsPerPixel, int fps) {
	trace ("begin mount(int, int, int, int");

	if (unmounted) {
		unmounted = false;
		this->width = width;
		this->height = height;
		this->bitsPerPixel = bitsPerPixel;
		this->fps = fps;
		this->shmsize = width*height*(bitsPerPixel/8);
	} else {
		throw DeviceException(
				"Shared Memory buffer has been already created.",
				CLASS_NAME,
				"mount(int, int, int, int");
	}

	initDeviceInfo();

	union semun sem_un;

	shmid = shmget(SHMKEY, shmsize ,0777|IPC_CREAT);
	if (shmid < 0) {
		throw DeviceException(
				"Can Not create the Shared Memory buffer",
				CLASS_NAME,
				"mount(int, int, int, int");
	}

	semid = semget(SEMKEY,1,0744|IPC_CREAT);
	if(semid < 0) {
		throw DeviceException(
				"Can Not create the Semaphore",
				CLASS_NAME,
				"mount(int, int, int, int");
	}

	/* Associa a variavel local com o buffer compartilhado */
	shmdata = (unsigned char *) shmat(shmid,0,0);

   	if(shmdata == NULL){
		throw DeviceException(
				"Can Not allocate Shared Memory buffer",
				CLASS_NAME,
				"mount(int, int, int, int");
   	}

	/* inicializa o semaforo*/
	sem_un.val = 1;
	semctl(semid,0,SETVAL,sem_un);
}

void DeviceInterface::release() {
	trace("begin release()");

	union semun sem_un;
	struct shmid_ds shmds;

	semctl(semid,0,IPC_RMID,sem_un);
	shmdt((char *) shmdata);
    shmctl(shmid,IPC_RMID,&shmds);

}

static unsigned char reverse(unsigned char x) {
 unsigned char h = 0;
 int i = 0;

 for(h = i = 0; i < 8; i++) {
  h = (h << 1) + (x & 1);
  x >>= 1;
 }

 return h;
}

void DeviceInterface::putBuffer1(unsigned char* buffer) {
	trace("begin putBuffer1(unsigned char*)");

	lock();
	for (int i=0; i < height*width*4; i++) {
		shmdata[i] = buffer[i];
	}
	unlock();
}

void DeviceInterface::putBuffer2(unsigned char* buffer) {
	trace("begin putBuffer2(unsigned char*)");

	lock();
	for (int linha = 0; linha < height; linha++) {
		for (int coluna = 0; coluna < width; coluna++) {
			int origem = linha*height*4 + coluna*4;
			int destino = (height-1-linha)*height*4 + coluna*4;
			shmdata[destino] = buffer[origem+2];
			shmdata[destino+1] = buffer[origem+1];
			shmdata[destino+2] = buffer[origem];
			shmdata[destino+3] = buffer[origem+3];
		}
	}
	unlock();
}

void DeviceInterface::putBuffer3(unsigned char* buffer) {
	trace("begin putBuffer3(unsigned char*)");

	lock();
	for (int i = 0; i < height*width; i++) {
		int origem = i*4;
		shmdata[origem] = buffer[origem+2];
		shmdata[origem+1] = buffer[origem+1];
		shmdata[origem+2] = buffer[origem];
		//shmdata[origem+3] = buffer[origem+3];
	}
	unlock();
}

void DeviceInterface::putBuffer4(unsigned char* buffer) {
	trace("begin putBuffer4(unsigned char*)");

	lock();
	for (int i=0; i < height*width; i++) {
		int origem = i*3;
		shmdata[origem] = buffer[origem+2];
		shmdata[origem+1] = buffer[origem+1];
		shmdata[origem+2] = buffer[origem];
		//shmdata[origem+3] = buffer[origem+1];
	}
	/*int uncount = height*width*3 -1;
	for (int i=0; i < height*width*3; i++) {
		shmdata[i] = buffer[i];
	}*/
	unlock();
}

int DeviceInterface::getWidth() {
	return this->width;
}

int DeviceInterface::getHeight() {
	return this->height;
}

int DeviceInterface::getFPS() {
	return this->fps;
}

int DeviceInterface::getBitsPerPixel() {
	return this->bitsPerPixel;
}

}
}
}
}
