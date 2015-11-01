cmake_minimum_required( VERSION 3.2 )
project( deps )
include( ExternalProject )
find_package( Git REQUIRED )

set( CURL_FLAGS -DBUILD_CURL_EXE=OFF -DBUILD_CURL_TESTS=OFF -DCURL_STATICLIB=ON )

if( WIN32 )
	ExternalProject_Add(
		curl
		URL http://curl.haxx.se/download/curl-7.45.0.tar.gz
		PREFIX curl
		PATCH_COMMAND ${CURL_PATCH_COMMAND}
		CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/curl ${CURL_FLAGS}
	)
endif()

ExternalProject_Add(
	catch
	PREFIX catch
	GIT_REPOSITORY https://github.com/philsquared/Catch.git
	TIMEOUT 10
	UPDATE_COMMAND ${GIT_EXECUTABLE} pull
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/catch/src/catch/include ${CMAKE_CURRENT_SOURCE_DIR}/catch/include
	LOG_DOWNLOAD ON
)

ExternalProject_Add(
	rapidjson
	PREFIX rapidjson
	GIT_REPOSITORY https://github.com/miloyip/rapidjson.git
	TIMEOUT 10
	UPDATE_COMMAND ${GIT_EXECUTABLE} pull
	CONFIGURE_COMMAND ""
	BUILD_COMMAND ""
	INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/src/rapidjson/include ${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/include
	LOG_DOWNLOAD ON
)