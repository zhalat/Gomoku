#########################################​######################################
# @file CMakeLists.txt
#
# @details Threat3CaseATest source project CMake file.
#
# @if REVISION_HISTORY_INCLUDED
# @par Edit History
# @li zhalat 12-MAR-2016 Initial revision of file.
# @endif
#
# @par Copyright (c) 2016 HalSoft
#
# @ingroup:
#
#########################################​######################################

cmake_minimum_required( VERSION 2.6 )

# Define project name
project( Threat3CaseATest )

# Additional CXX flags
set( ${PROJECT_NAME_UPPERCASE}_CXX_FLAGS -mno-align-double )

# Additional test definitions
add_definitions( 
    -DUNIT_TEST
    -DTHREAT_3_CASE_A_TEST #this define is for unblock the test in main().
)

# not sure why this not works in _CXX_FLAGS seciton
add_definitions( -std=gnu++11 )

# Set type building Debug/Release
SET( CMAKE_BUILD_TYPE Debug )

# Set project root
set( CMAKE_PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR} )

# Set path directories
set( GOMOKUGAME_SRC "${CMAKE_PROJECT_ROOT}/../../../GomokuGame_SRC/Sources" )
set( GOMOKUGAME_INC "${CMAKE_PROJECT_ROOT}/../../../GomokuGame_SRC/Headers" )
set( UT_GOMOKUGAME_SRC "${CMAKE_PROJECT_ROOT}" )
set( UT_GOMOKUGAME_INC "${CMAKE_PROJECT_ROOT}" )
set( CPPUNIT_INC "${CMAKE_PROJECT_ROOT}/../../../../../cppunit_win/cppunit-1.12.1/cppunit-1.12.1/include" )
set( CPPUNIT_LIB "${CMAKE_PROJECT_ROOT}/../../../../../cppunit_win/cppunit-1.12.1/UnitCppLibrary/MyCppUnitStaticLibrary/Debug" )
set( STUBS_GLOBAL "${CMAKE_PROJECT_ROOT}/../../StubsGlobal" )

# Define Sources
set( ${PROJECT_NAME_UPPERCASE}_SRC
    # Main file
    "${CMAKE_CURRENT_SOURCE_DIR}/../../main.cpp"
    # Unit under test
    "${GOMOKUGAME_SRC}/Threats/Threat3CaseA.cpp"
    # Unit test
    "${UT_GOMOKUGAME_SRC}/Threat3CaseATest.cpp"
    # Support classes
    "${GOMOKUGAME_SRC}/DataContainers/Graph.cpp"
	"${GOMOKUGAME_SRC}/GomokuBoard.cpp"
	"${GOMOKUGAME_SRC}/Threats/ThreatFinder.cpp"
    # Stubs
    "${STUBS_GLOBAL}/StubBoardIterator.cpp"
    "${STUBS_GLOBAL}/StubGraphIterator.cpp"
)

# Define the path to the includes
set( ${PROJECT_NAME_UPPERCASE}_INCLUDE
    "${CPPUNIT_INC}"
    "${GOMOKUGAME_INC}"
	"${GOMOKUGAME_INC}/DataContainers"
    "${GOMOKUGAME_INC}/Threats"
    "${UT_GOMOKUGAME_INC}"
)

include_directories( ${${PROJECT_NAME_UPPERCASE}_INCLUDE} )
add_executable( Threat3CaseATest ${${PROJECT_NAME_UPPERCASE}_SRC} )

#External library:
add_library( libMyCppUnitStaticLibrary STATIC IMPORTED )
set_target_properties( libMyCppUnitStaticLibrary PROPERTIES IMPORTED_LOCATION "${CPPUNIT_LIB}/libMyCppUnitStaticLibrary.a" )
TARGET_LINK_LIBRARIES( Threat3CaseATest libMyCppUnitStaticLibrary )