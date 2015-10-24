project(madLib)
CMAKE_MINIMUM_REQUIRED ( VERSION 2.8.11 )

SET ( CMAKE_AUTOMOC ON )
SET ( CMAKE_INCLUDE_CURRENT_DIR ON )

FILE ( GLOB_RECURSE madLib_SOURCES *.cpp )
FILE ( GLOB_RECURSE madLib_HEADERS *.h )

INCLUDE_DIRECTORIES ( textDocs/ )
ADD_SUBDIRECTORY ( textDocs )

include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

SET ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" )

#FILE ( READ textDocs/simple.txt simple )
#SET(simple.txt ${simple})
#MESSAGE(STATUS "${simple.txt}")

add_executable( ${PROJECT_NAME} ${madLib_SOURCES} ${madLib_HEADERS})

FILE ( COPY textDocs/ DESTINATION textDocs)


