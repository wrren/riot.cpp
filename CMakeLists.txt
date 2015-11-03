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
set( riot_api_sources 		include/riot/riot.h 				src/riot/riot.cpp )

set( riot_api_core_sources 	include/riot/core/core.h 			src/riot/core/core.cpp
				include/riot/core/url.h 			src/riot/core/url.cpp
				include/riot/core/json.h 			src/riot/core/json.cpp )

set( riot_api_dto_sources 	include/riot/dto/dto.h 	
				include/riot/dto/dto_decoder.h
				include/riot/dto/dto_vector.h 	
				include/riot/dto/dto_map.h
				include/riot/dto/dto_base.h 			src/riot/dto/dto_base.cpp
				include/riot/dto/dto_complex.h 			src/riot/dto/dto_complex.cpp
				include/riot/dto/dto_retriever.h 		src/riot/dto/dto_retriever.cpp )

set( riot_api_lol_sources	include/riot/lol/summoner.h 			src/riot/lol/summoner.cpp 
				include/riot/lol/team.h 			src/riot/lol/team.cpp 
				include/riot/lol/match.h 			src/riot/lol/match.cpp )

set( riot_api_lol_match_sources	include/riot/lol/match/participant.h 		src/riot/lol/match/participant.cpp
				include/riot/lol/match/participant_identity.h 	src/riot/lol/match/participant_identity.cpp
				include/riot/lol/match/participant_stats.h 	src/riot/lol/match/participant_stats.cpp
				include/riot/lol/match/player.h 		src/riot/lol/match/player.cpp
				include/riot/lol/match/team.h 			src/riot/lol/match/team.cpp )

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

# Enable C++11 Support
set_property( TARGET riot_api PROPERTY CXX_STANDARD 11 )