cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(project)

add_compile_options(-fPIC)
add_compile_options(-fcf-protection=none)



set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Geant4 overwrites flags :-(
set(M_CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS}")
set(M_CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG}")
set(M_CMAKE_CXX_FLAGS_MINSIZEREL     "${CMAKE_CXX_FLAGS_MINSIZEREL}")
set(M_CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE}")
set(M_CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
set(M_CMAKE_EXE_LINKER_FLAGS         "${CMAKE_EXE_LINKER_FLAGS}")

message("--> Searching source files....")
file(GLOB SOURCE_FILES src/*.cpp *.c
        src/simulation/*.cc)
message("Found: ${SOURCE_FILES}")

message("--> Searching header files....")
file(GLOB HEADER_FILES src/*.h *.hpp
        src/simulation/*.hh)
message("Found: ${HEADER_FILES}")

message("--> Searching UI files....")
set(CMAKE_AUTOUIC_SEARCH_PATHS uis/)
file(GLOB UI_FILES uis/*.ui)
message("Found: ${UI_FILES}")

# Qt5 --------------------------------------------------------
find_package(Qt5 COMPONENTS Core Widgets Gui Xml OpenGL REQUIRED)
find_package(Qt5Core REQUIRED NO_DEFAULT_PATH)
find_package(Qt5Widgets REQUIRED NO_DEFAULT_PATH)
find_package(Qt5Gui REQUIRED NO_DEFAULT_PATH)

message("--> Printing QT5 Modules")
message("Qt5               : " ${Qt5_DIR})
message("Qt5Core           : " ${Qt5Core_DIR})
message("Qt5Widgets        : " ${Qt5Widgets_DIR})
message("Qt5Gui            : " ${Qt5Gui_DIR})
message("Qt5OpenGL         : " ${Qt5OpenGL_DIR})

message("--> Printing Qt5 Libraries")
get_target_property(QtCore_location Qt5::Core LOCATION)
message("Qt5::Core Lib    : ${QtCore_location}")
get_target_property(QtWidgets_location Qt5::Widgets LOCATION)
message("Qt5::Widgets Lib : ${QtWidgets_location}")
get_target_property(QtGui_location Qt5::Gui LOCATION)
message("Qt5::Gui Lib     : ${QtGui_location}")

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
# Qt5 ---------------------------------------------------------

# Geant4 -----------------------------------------------------
find_package(Geant4 REQUIRED)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# add_compile_options(-march=native -Ofast)
add_compile_options(-ggdb3)

file(GLOB Geant4Sources ${PROJECT_SOURCE_DIR}/src/GDML/*.cc)
file(GLOB Geant4Headers ${PROJECT_SOURCE_DIR}/src/GDML/*.hh)

qt5_wrap_cpp(Geant4Wrap ${Geant4Headers})

# Geant4 -----------------------------------------------------

# OpenCASCADE -------------------------------------------------------------------
option(USE_OCE "Use OpenCASCADE Community Edition " OFF)

if (USE_OCE)
    # OPENCASCADE COMMUNITY EDITION
    set(OCE_DIR /usr/lib/x86_64-linux-gnu/oce-0.17)
    find_package(OCE REQUIRED)
    include_directories(${OCE_INCLUDE_DIRS})
    SET(OpenCASCADE_LIBRARIES
            TKernel;TKMath
            TKG2d;TKG3d;TKGeomBase;TKBRep
            TKGeomAlgo;TKTopAlgo;TKPrim;TKBO;TKShHealing;TKBool;TKHLR;TKFillet;TKOffset;TKFeat;TKMesh;TKXMesh
            TKService;TKV3d;TKOpenGl;TKMeshVS
            TKCDF;TKLCAF;TKCAF;TKBinL;TKXmlL;TKBin;TKXml;TKTObj;TKBinTObj;TKXmlTObj #;TKVCAF #TKStdL;TKStd;
            TKXSBase;TKSTEPBase;TKSTEPAttr;TKSTEP209;TKSTEP;TKIGES;TKXCAF;TKXDEIGES;TKXDESTEP;TKSTL;TKVRML;TKXmlXCAF;TKBinXCAF; #TKRWMesh
            #TKDraw;TKTopTest;TKViewerTest;TKXSDRAW;TKDCAF;TKXDEDRAW;TKTObjDRAW;TKQADraw;
            -lGL -lGLU #-lglut
            TKernel TKMath TKSTL TKSTEP TKV3d TKOpenGl
            )
else()
    ### OpenCASCADE Official Edition
    add_definitions(-DOCCT)
    if(WIN32)
        find_path(OpenCASCADE_DIR OpenCASCADEConfig.cmake
                C:\\Dev\\OpenCASCADE\\OpenCASCADEv740\\cmake)
    else()
        find_path(OpenCASCADE_DIR OpenCASCADEConfig.cmake
                /opt/Dev/OpenCASCADE/lib/cmake/opencascade/
                /opt/opencascade-7.4.0/lib/cmake/opencascade/)
    endif()
    find_package(OpenCASCADE REQUIRED)
    find_package(OpenCASCADE COMPONENTS FoundationClasses REQUIRED)
    find_package(OpenCASCADE COMPONENTS ModelingData REQUIRED)
    find_package(OpenCASCADE COMPONENTS DataExchange REQUIRED)
    include_directories(${OpenCASCADE_INCLUDE_DIR})
endif()
# OpenCASCADE -------------------------------------------------------------------

add_executable(${PROJECT_NAME}
        ${SOURCE_FILES}
        ${HEADER_FILES}
        ${UI_FILES}
        ${Geant4Sources}
        ${Geant4Headers}
        ${Geant4Wrap})

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt5::Widgets Qt5::Core Qt5::Gui
        ${OpenCASCADE_LIBRARIES}
        ${Geant4_LIBRARIES} )


# Geant4 overwrites flags, so we add back our own
set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} ${M_CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG          "${CMAKE_CXX_FLAGS_DEBUG} ${M_CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "${CMAKE_CXX_FLAGS_MINSIZEREL} ${M_CMAKE_CXX_FLAGS_MINSIZEREL}")
set(CMAKE_CXX_FLAGS_RELEASE        "${CMAKE_CXX_FLAGS_RELEASE} ${M_CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${M_CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
set(CMAKE_EXE_LINKER_FLAGS         "${CMAKE_EXE_LINKER_FLAGS} ${M_CMAKE_EXE_LINKER_FLAGS}")

