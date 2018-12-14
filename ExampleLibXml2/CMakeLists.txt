PROJECT (ExampleLibXml2)
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

FIND_PACKAGE( LibXml2 )
include_directories(${LIBXML2_INCLUDE_DIR})

link_directories(${CMAKE_INSTALL_PREFIX}/../lib)

MESSAGE( STATUS "Include directory ${CMAKE_CURRENT_SOURCE_DIR}/../share/" )

#    ADD_DEFINITIONS(-Wall)
#    ADD_DEFINITIONS(-std=c++0x)

add_executable(
	${PROJECT_NAME}
        main.cpp
	ExampleLibXml2.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} xml2)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ../bin
        LIBRARY DESTINATION ../lib
        ARCHIVE DESTINATION ../lib
)

