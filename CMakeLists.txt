CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(libavencoding)

SET(BUILD_SHARED_LIBS ON)
SET(CMAKE_BUILD_TYPE DEBUG)

IF(CMAKE_COMPILER_IS_GNUCXX)
	SET(CMAKE_CXX_FLAGS_DEBUG  "-g3")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

SET(CMAKE_CXX_FLAGS "-DTIXML_USE_TICPP")
SET(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined -fPIC")

ADD_LIBRARY(avencoding 
		src/DeviceInterface.cpp)
			
SET(install_headers
		include/DeviceException.h
		include/DeviceInterface.h)
			

			
TARGET_LINK_LIBRARIES (avencoding cpputil)

LINK_DIRECTORIES (${libavencoding_BINARY_DIR})

INCLUDE_DIRECTORIES (${libavencoding_SOURCE_DIR}/include)


INSTALL (TARGETS avencoding LIBRARY DESTINATION lib)

# INSTALL (TARGETS avencoding ARCHIVE DESTINATION lib)

INSTALL (FILES ${install_headers} DESTINATION include/libavencoding)