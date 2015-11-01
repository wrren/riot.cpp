cmake_minimum_required( VERSION 3.2 )
project( riot_api )

# Reconfigure Output Directories
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib )
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/lib )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_CURRENT_SOURCE_DIR}/lib )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

# Set Include Paths
include_directories( 	${CMAKE_CURRENT_SOURCE_DIR}/include
			${CMAKE_CURRENT_SOURCE_DIR}/deps/curl/include
			${CMAKE_CURRENT_SOURCE_DIR}/deps/rapidjson/include )

# Link cURL Statically
add_definitions( -DCURL_STATICLIB )
link_directories( ${CMAKE_CURRENT_SOURCE_DIR}/deps/curl/lib )

# Setup Source Sets
set( riot_api_sources 		include/riot/riot.h 		src/riot/riot.cpp )

set( riot_api_core_sources 	include/riot/core/core.h 	
				include/riot/core/url.h 	src/riot/core/url.cpp
				include/riot/core/json.h 	src/riot/core/json.cpp )

set( riot_api_dto_sources 	include/riot/dto/summoner.h 	src/riot/dto/summoner.cpp 
				include/riot/dto/team.h 	src/riot/dto/team.cpp 
				include/riot/dto/match.h 	src/riot/dto/match.cpp )

# Visual Studio Source Groups
source_group( "riot" 		FILES 	${riot_api_sources} )
source_group( "riot\\core" 	FILES 	${riot_api_core_sources} )
source_group( "riot\\dto" 	FILES 	${riot_api_dto_sources} )

# Generate Library
add_library( riot_api STATIC 	${riot_api_sources} 
				${riot_api_core_sources} 
				${riot_api_dto_sources} )

# Enable C++11 Support
set_property( TARGET riot_api PROPERTY CXX_STANDARD 11 )