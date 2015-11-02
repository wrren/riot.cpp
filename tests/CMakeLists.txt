cmake_minimum_required( VERSION 3.2 )
project( tests )

set( BUILD_SHARED_LIBS OFF )

if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
  set( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage" )
  set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage" )
endif()

link_directories( 	${CMAKE_CURRENT_SOURCE_DIR}/../lib
			${CMAKE_CURRENT_SOURCE_DIR}/../deps/curl/lib )

include_directories( 	${CMAKE_CURRENT_SOURCE_DIR}
			${CMAKE_CURRENT_SOURCE_DIR}/../include
			${CMAKE_CURRENT_SOURCE_DIR}/../deps/curl/include
			${CMAKE_CURRENT_SOURCE_DIR}/../deps/catch/include
                      	${CMAKE_CURRENT_SOURCE_DIR}/../deps/rapidjson/include)

add_executable(		unit
 			unit_url.cpp )

add_executable( 	integration
			int_key.cpp
			int_team.cpp
			int_summoner.cpp )

target_link_libraries( unit riot_api )
target_link_libraries( integration riot_api )

if( WIN32 )
  target_link_libraries( unit ws2_32 libcurl )
  target_link_libraries( integration ws2_32 libcurl )
else()
  target_link_libraries( unit pthread curl )
  target_link_libraries( integration pthread curl )
endif()

set_property( TARGET unit PROPERTY CXX_STANDARD 11 )
set_property( TARGET integration PROPERTY CXX_STANDARD 11 )