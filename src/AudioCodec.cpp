/**
 * File: AudioCodec.cpp
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

#include "AudioCodec.h"
#include <libcpputil/SimpleException.h>
#include <libcpputil/Functions.h>

namespace br {
namespace ufscar {
namespace lince {
namespace avencoding {

AudioCodec::AudioCodec() {
	this->type = types[0];
	this->str = strTypes[0];
}

AudioCodec::AudioCodec(AudioCodec::Type type) {
	this->type = type;
	this->str = typeToString(type);
}

AudioCodec::AudioCodec(const AudioCodec& obj) {
	this->type = obj.type;
	this->str = obj.str;
}

AudioCodec::AudioCodec(const std::string& str) {
	for (int i = 0; i <7; i++) {
		if (str == strTypes[i]) {
			this->type = types[i];
			this->str = strTypes[i];
			return;
		}
	}
	throw cpputil::SimpleException(
			"Trying to convert a invalid string: " + str,
			"br::ufscar::lince::avencoding::AudioCodec",
			"AudioCodec(const string&)");
}

AudioCodec& AudioCodec::operator=(const AudioCodec& obj) {
	if (this->type != obj.type) {
		this->type = obj.type;
		this->str = obj.str;
	}
	return *this;
}

AudioCodec& AudioCodec::operator=(AudioCodec::Type type) {
	if (this->type != type) {
		this->type = type;
		this->str = typeToString(type);
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, const AudioCodec& obj) {	out << obj.toString();
	return out;
}

bool AudioCodec::operator==(const AudioCodec& obj) const {
	return (this->type == obj.type);
}

bool AudioCodec::operator==(AudioCodec::Type type) const {
	return (this->type == type);
}

bool AudioCodec::operator!=(const AudioCodec& obj) const {
	return (this->type != obj.type);
}

bool AudioCodec::operator!=(AudioCodec::Type type) const {
	return (this->type != type);
}

std::string AudioCodec::toString() const {
	return str;
}

AudioCodec::Type AudioCodec::getType() const {
	return type;
}

char* AudioCodec::typeToString(AudioCodec::Type type) {
	for (int i = 0; i < 9; i++) {
		if (type == types[i]) {
			return strTypes[i];
		}
	}
	throw cpputil::SimpleException(
			"Trying to convert a invalid AudioCodec::Type",
			"br::ufscar::lince::avencoding::AudioCodec",
			"typeToString(AudioCodec::Type)");
}

AudioCodec::Type AudioCodec::stringToType(const std::string& str) {
	std::string aux = cpputil::Functions::toUpperCase(str);
	for (int i = 0; i < 9; i++) {
		if (aux == strTypes[i]) {
			return types[i];
		}
	}
	throw cpputil::SimpleException(
			"Trying to convert a invalid string: " + str,
			"br::ufscar::lince::avencoding::AudioCodec",
			"stringToType(const string&)");
}

char** AudioCodec::initializeStrTypes() {
	char** aux = new char*[9];
	aux[0] = (char*) "NONE";
	aux[1] = (char*) "VORBIS";
	aux[2] = (char*) "PCM16";
	aux[3] = (char*) "PCM32";
	aux[4] = (char*) "AAC";
	aux[5] = (char*) "AC3";
	aux[6] = (char*) "MP3";
	aux[7] = (char*) "COPY";
	aux[8] = (char*) "FLAC";
	return aux;
}

char** AudioCodec::strTypes = AudioCodec::initializeStrTypes();

AudioCodec::Type* AudioCodec::initializeTypes() {
	AudioCodec::Type* aux = new AudioCodec::Type[9];
	aux[0] = NONE;
	aux[1] = VORBIS;
	aux[2] = PCM16;
	aux[3] = PCM32;
	aux[4] = AAC;
	aux[5] = AC3;
	aux[6] = MP3;
	aux[7] = COPY;
	aux[8] = FLAC;
	return aux;
}

AudioCodec::Type* AudioCodec::types = AudioCodec::initializeTypes();

} /* namespace br */
} /* namespace ufscar */
} /* namespace lince */
} /* namespace avencoding */
