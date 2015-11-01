cmake_minimum_required( VERSION 3.2 )
project( tests )

set( BUILD_SHARED_LIBS OFF )

if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
  set( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage" )
  set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage" )
endif()

link_directories( 	${CMAKE_CURRENT_SOURCE_DIR}/../lib
			${CMAKE_CURRENT_SOURCE_DIR}/../deps/curl/lib )

include_directories( 	${CMAKE_CURRENT_SOURCE_DIR}/../include
			${CMAKE_CURRENT_SOURCE_DIR}/../deps/curl/include
			${CMAKE_CURRENT_SOURCE_DIR}/../deps/catch/include
                      	${CMAKE_CURRENT_SOURCE_DIR}/../deps/rapidjson/include)

add_executable(		tests
 			test_url.cpp)

target_link_libraries( tests riot_api )

if( WIN32 )
  target_link_libraries( tests ws2_32 libcurl )
else()
  target_link_libraries( tests idn pthread curl )
endif()
