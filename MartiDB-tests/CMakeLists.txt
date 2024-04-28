# Include directories
include_directories("./inc")
include_directories("../MartiDB/inc")

# Create a list of source files
set(SOURCES_DIR "./src")
file(GLOB_RECURSE SOURCE_FILES "${SOURCES_DIR}/*.cpp")

# Create a list of header files
set(INCLUDES_DIR "./inc")
file(GLOB_RECURSE HEADER_FILES "${INCLUDES_DIR}/*.h")

# Fetch Catch2 from its GitHub repository
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later s
)
FetchContent_MakeAvailable(Catch2)

# Add the executable target for tests
add_executable(MartiDB-tests ${SOURCE_FILES} ${HEADER_FILES})

# Link Catch2 with the tests target
target_link_libraries(MartiDB-tests PRIVATE Catch2::Catch2WithMain)

# Set C++ standard if supported by the CMake version
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MartiDB-tests PROPERTY CXX_STANDARD 20)
endif()