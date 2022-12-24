cmake_minimum_required(VERSION 3.16)
option(AL_LOGGING "Build with logging enabled" OFF)
option(AL_ASSERTIONS "Build with logging enabled" OFF)
option(AL_DEBUG "Debug build" OFF)
option(AL_TESTS "Tests build" OFF)

project(power_point)

#set(CMAKE_PREFIX_PATH "/home/varduhi/Qt/6.4.1/gcc_64/lib/cmake;/home/varduhi/Qt/6.4.1/gcc_64/lib/cmake/Qt6")

#set(CMAKE_PREFIX_PATH "/home/varduhi/Qt/6.4.1/gcc_64/lib/Qt6/cmake")
set(CMAKE_PREFIX_PATH "/home/varduhi/Qt/5.15.2/gcc_64/lib/cmake/Qt5")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES x86_64)
endif()

set(EXTERNAL_LINKINK_LIBRARIES)
# Try to find Qt6 in case if it is not there give a try to find Qt5
find_package(Qt6 CONFIG COMPONENTS Gui Core Widgets)
if (NOT Qt6_FOUND)
    # As we expect to find at least Qt5 that is why it is REQUIRED
    find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Widgets)
    set(QT_VERSION_MAJOR 5)
else()
    set(QT_VERSION_MAJOR 6)
endif()

list(APPEND EXTERNAL_LINKINK_LIBRARIES Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-volatile")

if (${AL_LOGGING})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAL_LOGGING")
endif(${AL_LOGGING})

if (${AL_TESTS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAL_TESTS")
endif(${AL_TESTS})

if (${AL_ASSERTIONS})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAL_ASSERTIONS")
endif(${AL_ASSERTIONS})

if (${AL_DEBUG})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -DAL_DEBUG")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g")
    set(CMAKE_BUILD_TYPE Debug)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -O3")
    set(CMAKE_BUILD_TYPE Release)
endif (${AL_DEBUG})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   set(CMAKE_CXX_VISIBILITY_PRESET hidden)
endif()

string(TOLOWER ${CMAKE_SYSTEM_NAME} AL_SYSTEM)

set(DEFAULT_PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(./)
include_directories(cli)
include_directories(common)
include_directories(commands)
include_directories(ui)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/cli)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/common)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/commands)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/ui)

add_subdirectory(cli)
add_subdirectory(common)
add_subdirectory(commands)
add_subdirectory(ui)

if(${AL_TESTS})
    # add_subdirectory(tests)
    add_executable(tests tests/main.cpp)
    target_link_libraries(tests PUBLIC cli common commands ui ${EXTERNAL_LINKINK_LIBRARIES} )
else()
    #TODO ADD sources for final executable
    add_executable(power_point main.cpp ${RCC_RESOURCES})
    target_link_libraries(power_point PUBLIC cli common commands ui ${EXTERNAL_LINKINK_LIBRARIES})
endif()

