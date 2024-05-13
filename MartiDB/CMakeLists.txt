set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)

set(HEADERS 
	inc/martidb.h
	inc/database.h
	inc/extensions/database_ext.h
)

add_library(martidb 
	${HEADERS}
	src/database.cpp
	src/martidb.cpp
)

set_target_properties(martidb PROPERTIES PUBLIC_HEADER "${HEADERS}")

target_include_directories(martidb 
	PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
	$<INSTALL_INTERFACE:inc>
)

target_compile_features(martidb PRIVATE cxx_std_17)

install(TARGETS martidb 
    EXPORT martidb
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}  
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/martidb
)

install(EXPORT martidb 
	NAMESPACE martidb::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/martidb
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET martidb PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
