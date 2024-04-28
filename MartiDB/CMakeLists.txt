# CMakeList.txt : CMake project for MartiDB, include source and define
# project specific logic here.
#

# Create a list of source files
set(SOURCES_DIR "./src")
file(GLOB_RECURSE SOURCE_FILES "${SOURCES_DIR}/*.cpp")

# Create a list of header files
set(INCLUDES_DIR "./inc")
file(GLOB_RECURSE HEADER_FILES "${INCLUDES_DIR}/*.h")

add_executable (MartiDB ${SOURCE_FILES} ${HEADER_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MartiDB PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
