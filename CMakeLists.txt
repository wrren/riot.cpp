cmake_minimum_required( VERSION 3.2 )
project( riot_api )
include( ExternalProject )
find_package( Git REQUIRED )

set( CURL_FLAGS -DBUILD_CURL_EXE=OFF -DBUILD_CURL_TESTS=OFF -DCURL_STATICLIB=ON )

if( WIN32 )
	set( BUILD_SHARED_LIBS OFF )

	if( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX )
		set( CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage" )
		set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage" )
	endif()

	ExternalProject_Add(
		curl
		URL http://curl.haxx.se/download/curl-7.45.0.tar.gz
		PREFIX ${CMAKE_SOURCE_DIR}/deps/curl
		PATCH_COMMAND ${CURL_PATCH_COMMAND}
		CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/deps/curl ${CURL_FLAGS}
	)
endif()

ExternalProject_Add(
	catch
	PREFIX ${CMAKE_SOURCE_DIR}/deps/catch
	GIT_REPOSITORY https://github.com/philsquared/Catch.git
	TIMEOUT 10
	UPDATE_COMMAND ${GIT_EXECUTABLE} pull
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/deps/catch/src/catch/include ${CMAKE_SOURCE_DIR}/deps/catch/include
	LOG_DOWNLOAD ON
)

ExternalProject_Add(
	rapidjson
	PREFIX ${CMAKE_SOURCE_DIR}/deps/rapidjson
	GIT_REPOSITORY https://github.com/miloyip/rapidjson.git
	TIMEOUT 10
	UPDATE_COMMAND ${GIT_EXECUTABLE} pull
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/deps/rapidjson/src/rapidjson/include ${CMAKE_SOURCE_DIR}/deps/rapidjson/include
	LOG_DOWNLOAD ON
)

# Reconfigure Output Directories
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib )
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/lib )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

# Set Include Paths
include_directories( 	${CMAKE_SOURCE_DIR}/include
			${CMAKE_SOURCE_DIR}/deps/curl/include
			${CMAKE_SOURCE_DIR}/deps/catch/include
			${CMAKE_SOURCE_DIR}/deps/rapidjson/include )

# Setup Source Sets
set( riot_api_sources 		include/riot/riot.h 				src/riot/riot.cpp )

set( riot_api_core_sources 	include/riot/core/core.h 			src/riot/core/core.cpp
				include/riot/core/http.h 			src/riot/core/http.cpp
				include/riot/core/url.h 			src/riot/core/url.cpp
				include/riot/core/json.h 			src/riot/core/json.cpp )

set( riot_api_dto_sources 	include/riot/dto/dto.h 	
				include/riot/dto/dto_decoder.h
				include/riot/dto/dto_vector.h 	
				include/riot/dto/dto_map.h
				include/riot/dto/dto_exception.h 		src/riot/dto/dto_exception.cpp 
				include/riot/dto/dto_base.h 			src/riot/dto/dto_base.cpp
				include/riot/dto/dto_complex.h 			src/riot/dto/dto_complex.cpp
				include/riot/dto/dto_retriever.h 		src/riot/dto/dto_retriever.cpp )

set( riot_api_lol_sources	include/riot/lol/summoner.h 			src/riot/lol/summoner.cpp 
				include/riot/lol/team.h 			src/riot/lol/team.cpp 
				include/riot/lol/match.h 			src/riot/lol/match.cpp
				include/riot/lol/game.h 			src/riot/lol/game.cpp )

set( riot_api_lol_match_sources	include/riot/lol/match/participant.h 		src/riot/lol/match/participant.cpp
				include/riot/lol/match/participant_identity.h 	src/riot/lol/match/participant_identity.cpp
				include/riot/lol/match/participant_stats.h 	src/riot/lol/match/participant_stats.cpp
				include/riot/lol/match/player.h 		src/riot/lol/match/player.cpp
				include/riot/lol/match/team.h 			src/riot/lol/match/team.cpp )

set(	riot_unit_test_sources
	tests/unit_url.cpp 
	tests/unit_http.cpp )

set( 	riot_integration_test_sources
	tests/int_key.cpp
	tests/int_team.cpp
	tests/int_match.cpp
	tests/int_summoner.cpp )

# Visual Studio Source Groups
source_group( "riot" 			FILES 	${riot_api_sources} )
source_group( "riot\\core" 		FILES 	${riot_api_core_sources} )
source_group( "riot\\dto" 		FILES 	${riot_api_dto_sources} )
source_group( "riot\\lol" 		FILES 	${riot_api_lol_sources} )
source_group( "riot\\lol\\match" 	FILES 	${riot_api_lol_match_sources} )

# Generate Library
add_library( riot_api STATIC 	${riot_api_sources} 
				${riot_api_core_sources} 
				${riot_api_dto_sources}
				${riot_api_lol_sources}
				${riot_api_lol_match_sources} )

if( WIN32 )
	# Link cURL Statically
	

else()
	target_link_libraries( riot_api curl )
endif()



add_executable(	riot_api_unit ${riot_unit_test_sources} )
add_executable( riot_api_integration ${riot_integration_test_sources} )

target_link_libraries( riot_api_unit riot_api )
target_link_libraries( riot_api_integration riot_api )

if( WIN32 )
	add_definitions( -DCURL_STATICLIB )
	target_link_libraries( riot_api_unit 		${CMAKE_CURRENT_SOURCE_DIR}/deps/curl/lib/libcurl.lib ws2_32 )
  	target_link_libraries( riot_api_integration 	${CMAKE_CURRENT_SOURCE_DIR}/deps/curl/lib/libcurl.lib ws2_32 )
	target_link_libraries( riot_api 		${CMAKE_SOURCE_DIR}/deps/curl/lib/libcurl.lib ws2_32 )
else()
  	target_link_libraries( riot_api_unit pthread curl )
  	target_link_libraries( riot_api_integration pthread curl )
endif()

enable_testing()
add_test( unit riot_api_unit )
add_test( integration riot_api_integration )

# Enable C++11 Support
set_property( TARGET riot_api 			PROPERTY CXX_STANDARD 11 )
set_property( TARGET riot_api_unit 		PROPERTY CXX_STANDARD 11 )
set_property( TARGET riot_api_integration 	PROPERTY CXX_STANDARD 11 )