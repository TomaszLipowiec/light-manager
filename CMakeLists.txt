cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(LightManagerApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_PREFIX_PATH "/home/tomasz/Qt/6.5.3/gcc_64/lib/cmake")

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Qml Quick Network)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.5)
    qt_standard_project_setup()
endif()

qt_add_executable(LightManagerApp src/main.cpp
    src/manager.h src/manager.cpp
    src/lightclient.h src/lightclient.cpp
)

qt_add_resources(LightManagerApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

target_link_libraries(LightManagerApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Network
)

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS LightManagerApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
