#ifndef VideoCodec_H_
#define VideoCodec_H_

#include <string>
#include <iostream>

namespace br {
namespace ufscar {
namespace lince {
namespace avencoding {

class VideoCodec{
public:
	enum Type {
		NONE,
		THEORA,
		H264,
		MPEG2,
		MPEG1,
		VP8,
		COPY,
	};

public:
	//Default constructor will use the first element of the enumeration for initializations
	VideoCodec();
	VideoCodec(VideoCodec::Type type);
	VideoCodec(const VideoCodec& obj);
	VideoCodec(const std::string& str);

	VideoCodec& operator=(const VideoCodec& obj);
	VideoCodec& operator=(VideoCodec::Type type);

	bool operator==(const VideoCodec& obj) const;
	bool operator==(VideoCodec::Type type) const;

	bool operator!=(const VideoCodec& obj) const;
	bool operator!=(VideoCodec::Type type) const;

	friend std::ostream& operator<<(std::ostream &out,
			const VideoCodec& obj);

	std::string toString() const;
	VideoCodec::Type getType() const;

private:
	VideoCodec::Type type;
	char* str;

	static char** initializeStrTypes();
	static char** strTypes;
	static VideoCodec::Type* initializeTypes();
	static VideoCodec::Type* types;

	static char* typeToString(VideoCodec::Type);
	static VideoCodec::Type stringToType(const std::string& str);

};

} /* namespace br */
} /* namespace ufscar */
} /* namespace lince */
} /* namespace avencoding */

#endif /* VideoCodec_H_ */