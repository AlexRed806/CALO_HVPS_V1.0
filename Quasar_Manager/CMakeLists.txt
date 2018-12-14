PROJECT (Quasar_Manager)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

include_directories(${LIBXML2_INCLUDE_DIR})
if (CMAKE_BUILD_TYPE STREQUAL Debug)
      SET(CMAKE_DEBUG_POSTFIX "d")
endif (CMAKE_BUILD_TYPE STREQUAL Debug)

FIND_PACKAGE( LibXml2 )
include_directories($ENV{MOS_PATH}/../include/MOS_Plugin)

# convert build type to lower case
IF (CMAKE_BUILD_TYPE)
  STRING(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_TOLOWER)
ELSE(CMAKE_BUILD_TYPE)
  # set default configuration to release
  SET(CMAKE_BUILD_TYPE "Release")
  STRING(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_TOLOWER)
ENDIF(CMAKE_BUILD_TYPE)

MESSAGE( STATUS "Creating Makefile of ${CMAKE_INSTALL_PREFIX}" )

	link_directories(${CMAKE_INSTALL_PREFIX}/../lib)
LINK_DIRECTORIES($ENV{MOS_PATH}/../lib)




####################################### JLP  ########################################
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/share/")
INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/../share/")

MESSAGE( STATUS "Include directory ${CMAKE_CURRENT_SOURCE_DIR}/../share/" )

    ADD_DEFINITIONS(-Wall)
    ADD_DEFINITIONS(-std=c++0x)

add_library(
	${PROJECT_NAME}
	SHARED
        Quasar_Manager.cpp
        )
	#pluginsloader.cpp)


TARGET_LINK_LIBRARIES(${PROJECT_NAME}  ConfigQuasar)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ../bin
        LIBRARY DESTINATION ../lib
        ARCHIVE DESTINATION ../lib
)

