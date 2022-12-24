cmake_minimum_required(VERSION 3.16)
project(ui)

file(GLOB_RECURSE SOURCES "*.ui" "*.cpp" "*.c" "*.qrc")
file(GLOB_RECURSE RESOURCES "*.qrc")
set(RCC_RESOURCES ${RESOURCES} PARENT_SCOPE)

set(EXTERNAL_LINKINK_LIBRARIES)
# Try to find Qt6 in case if it is not there give a try to find Qt5
find_package(Qt6 CONFIG COMPONENTS Core Widgets)
if (NOT Qt6_FOUND)
    # As we expect to find at least Qt5 that is why it is REQUIRED
    find_package(Qt5 CONFIG REQUIRED COMPONENTS Core Widgets)
    set(QT_VERSION_MAJOR 5)
else()
    set(QT_VERSION_MAJOR 6)
endif()
list(APPEND EXTERNAL_LINKINK_LIBRARIES Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)


add_library(ui ${SOURCES})
target_link_libraries(ui ${RCC_SOURCES} ${EXTERNAL_LINKINK_LIBRARIES})
