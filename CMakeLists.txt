# face recognition
project(MyCtrl)
cmake_minimum_required(VERSION 2.8)

if(MSVC)
    #set_target_properties(client PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
    ADD_DEFINITIONS(-D_AFXDLL)
    add_definitions(-DUNICODE -D_UNICODE)
    SET(CMAKE_MFC_FLAG 2)
endif()

# add c++11 flags for gcc
if (CMAKE_COMPILER_IS_GNUCXX)
    set(ENABLE_CXX11 "-std=c++11")
    if (GCC_VERSION VERSION_LESS 4.7)
        set(ENABLE_CXX11 "-std=c++0x")
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")
endif()

include_directories(.)
file(GLOB SOURCE *.h* *.c* *.rc)

add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME})
