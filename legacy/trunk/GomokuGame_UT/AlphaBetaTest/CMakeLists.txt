#########################################​######################################
# @file CMakeLists.txt
#
# @details AlphaBetaTest source project CMake file.
#
# @if REVISION_HISTORY_INCLUDED
# @par Edit History
# @li zhalat 21-Jun-2017 Initial revision of file.
# @endif
#
# @par Copyright (c) 2017 HalSoft
#
# @ingroup:
#
#########################################​######################################

cmake_minimum_required( VERSION 2.6 )

# Define project name
project( AlphaBetaTest )

# Additional CXX flags
set( ${PROJECT_NAME_UPPERCASE}_CXX_FLAGS -mno-align-double )

# Additional test definitions
add_definitions( 
    -DUNIT_TEST
    -DALPHA_BETA_TEST #this define is for unblock test in main().
)

# not sure why this does not work in _CXX_FLAGS seciton
add_definitions( -std=gnu++0x )

# Set type building Debug/Release
SET( CMAKE_BUILD_TYPE Debug )

# Set project root
set( CMAKE_PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR} )

# Set path directories
set( GOMOKUGAME_SRC "${CMAKE_PROJECT_ROOT}/../../GomokuGame_SRC/Sources" )
set( GOMOKUGAME_INC "${CMAKE_PROJECT_ROOT}/../../GomokuGame_SRC/Headers" )
set( UT_GOMOKUGAME_SRC "${CMAKE_PROJECT_ROOT}" )
set( UT_GOMOKUGAME_INC "${CMAKE_PROJECT_ROOT}" )
set( CPPUNIT_INC "${CMAKE_PROJECT_ROOT}/../../../../cppunit_win/cppunit-1.12.1/cppunit-1.12.1/include" )
set( CPPUNIT_LIB "${CMAKE_PROJECT_ROOT}/../../../../cppunit_win/cppunit-1.12.1/UnitCppLibrary/MyCppUnitStaticLibrary/Debug" )
set( STUBS_GLOBAL "${CMAKE_PROJECT_ROOT}/../StubsGlobal" )

# Define Sources
set( ${PROJECT_NAME_UPPERCASE}_SRC
    # Main file
    "${CMAKE_CURRENT_SOURCE_DIR}/../main.cpp"
    # Unit under test
    "${GOMOKUGAME_SRC}/SearchAlgorithms/AlphaBeta.cpp"
    # Unit test
    "${UT_GOMOKUGAME_SRC}/AlphaBetaTest.cpp"
    # Support classes
    "${GOMOKUGAME_SRC}/SearchAlgorithms/MinMax.cpp"
    "${GOMOKUGAME_SRC}/SearchAlgorithms/StateEvaluation.cpp"
    "${GOMOKUGAME_SRC}/DataContainers/Graph.cpp"
	"${GOMOKUGAME_SRC}/DataContainers/GraphIterator.cpp"
	"${GOMOKUGAME_SRC}/GomokuBoard.cpp"
    "${GOMOKUGAME_SRC}/BoardIterator.cpp"
    "${GOMOKUGAME_SRC}/Score.cpp"
	"${GOMOKUGAME_SRC}/BoardScore.cpp"
	"${GOMOKUGAME_SRC}/Spotter.cpp"
	"${GOMOKUGAME_SRC}/Logger.cpp"
    "${GOMOKUGAME_SRC}/Threats/ThreatFinder.cpp"
    "${GOMOKUGAME_SRC}/Threats/ThreatWinner.cpp"
    "${GOMOKUGAME_SRC}/Threats/Threat4CaseA.cpp"
    "${GOMOKUGAME_SRC}/Threats/Threat4CaseAA.cpp"
    "${GOMOKUGAME_SRC}/Threats/Threat4CaseB.cpp"
    "${GOMOKUGAME_SRC}/Threats/Threat4CaseC.cpp"
    "${GOMOKUGAME_SRC}/Threats/Threat3CaseA.cpp"
    "${GOMOKUGAME_SRC}/Threats/Threat3CaseAA.cpp"
    "${GOMOKUGAME_SRC}/Threats/Threat3CaseB.cpp"
    "${GOMOKUGAME_SRC}/Threats/Threat3CaseC.cpp"
    "${GOMOKUGAME_SRC}/Threats/Threat2CaseA.cpp"
	"${GOMOKUGAME_SRC}/Threats/Threat2CaseAA.cpp"
    "${GOMOKUGAME_SRC}/Threats/Threat2CaseB.cpp"
    "${GOMOKUGAME_SRC}/Threats/Threat2CaseC.cpp"
    "${GOMOKUGAME_SRC}/Threats/ThreatsBloodRelation.cpp"
    # Stubs
    #"${CMAKE_CURRENT_SOURCE_DIR}/ScoreStub.cpp"

)

# Define the path to the includes
set( ${PROJECT_NAME_UPPERCASE}_INCLUDE
    "${CPPUNIT_INC}"
    "${GOMOKUGAME_INC}"
	"${GOMOKUGAME_INC}/DataContainers"
    "${GOMOKUGAME_INC}/SearchAlgorithms"
    "${GOMOKUGAME_INC}/Threats"
	"${GOMOKUGAME_INC}/Platform/Windows"
    "${UT_GOMOKUGAME_INC}"
)

include_directories( ${${PROJECT_NAME_UPPERCASE}_INCLUDE} )
add_executable( AlphaBetaTest ${${PROJECT_NAME_UPPERCASE}_SRC} )

#External library:
add_library( libMyCppUnitStaticLibrary STATIC IMPORTED )
set_target_properties( libMyCppUnitStaticLibrary PROPERTIES IMPORTED_LOCATION "${CPPUNIT_LIB}/libMyCppUnitStaticLibrary.a" )
TARGET_LINK_LIBRARIES( AlphaBetaTest libMyCppUnitStaticLibrary )