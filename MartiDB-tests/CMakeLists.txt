cmake_minimum_required(VERSION 3.12)

# Create executable
add_executable(martidb-tests
	src/database-managment-tests.cpp
	src/key-value-tests.cpp
)

# Fetch Catch2 from its GitHub repository
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later s
)
FetchContent_MakeAvailable(Catch2)

# Include headers
include_directories("./inc")

# Include martidb sources
include_directories(${martidb_SOURCE_DIR})

# Link Catch2 with the tests target
target_link_libraries(martidb-tests PRIVATE Catch2::Catch2WithMain)

# Link martidb with the tests target
target_link_libraries(martidb-tests PRIVATE martidb)

target_compile_features(martidb-tests PRIVATE cxx_std_17)