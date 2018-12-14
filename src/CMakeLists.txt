project(SN_CALO_HVPS)
cmake_minimum_required(VERSION 2.8)
SET(CMAKE_DEBUG_POSTFIX "d")

   FIND_PACKAGE( LibXml2 )
include_directories(${LIBXML2_INCLUDE_DIR})
 
MESSAGE( STATUS "" )
MESSAGE( STATUS "==============================================" )
MESSAGE( STATUS "Now configuring serveur_OPCUA CMakeLists.txt" )
MESSAGE( STATUS "==============================================" )

    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../share)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/share)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/share/socket)
    include_directories(${MOS_PATH}/../include/MOS_Plugin)
    include_directories(${MOS_PATH}/include/MOS_Plugin)
    link_directories(${MOS_PATH}/../lib)
    link_directories(${MOS_PATH}/lib)
    link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)


MESSAGE( STATUS "${CMAKE_CURRENT_SOURCE_DIR}/../lib" )
MESSAGE( STATUS "${MOS_PATH}/../lib")
MESSAGE( STATUS "${MOS_PATH}/../lib")


IF (UNIX)
    INCLUDE_DIRECTORIES()
    ADD_DEFINITIONS(-Wall)
    SET(PLATTFORM_LIBS pthread rt dl)
ENDIF (UNIX)


# create library
add_library(
         ${PROJECT_NAME}
        SHARED
        CALO_HVPS.cpp
	quasar_callback.cpp
        )

#TARGET_LINK_LIBRARIES(${PROJECT_NAME} PluginImpl)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} PluginBase Quasar_Manager ConfigQuasar)
set_target_properties( PROPERTIES DEBUG_POSTFIX "d")

# configure output path
INSTALL(TARGETS  ${PROJECT_NAME}
        RUNTIME DESTINATION ../bin
        LIBRARY DESTINATION ../plugins
        ARCHIVE DESTINATION ../lib
)
