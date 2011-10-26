#include "../include/DeviceException.h"

namespace br{
namespace ufscar{
namespace lince{
namespace avenconding{


DeviceException::DeviceException(string m) : msg(m) {

}


DeviceException::~DeviceException() throw() {

}

const char* DeviceException::what() const throw() {
	return msg.c_str();
}

}
}
}
}
