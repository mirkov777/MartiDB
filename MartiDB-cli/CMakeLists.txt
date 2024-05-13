cmake_minimum_required(VERSION 3.12)

# Add the executable target for cli
add_executable(martidb-cli
	src/main.cpp
)

# Include headers
include_directories("./inc")

# Include martidb sources
include_directories(${martidb_SOURCE_DIR})

# Link Catch2 with the cli target
target_link_libraries(martidb-cli PRIVATE Catch2::Catch2WithMain)

# Link martidb with the cli target
target_link_libraries(martidb-cli PRIVATE martidb)

target_compile_features(martidb-cli PRIVATE cxx_std_17)