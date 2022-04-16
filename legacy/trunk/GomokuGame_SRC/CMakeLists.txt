#########################################​######################################
# @file CMakeLists.txt
#
# @details Gomoku source project CMake file.
#
# @if REVISION_HISTORY_INCLUDED
# @par Edit History
# @li zhalat 01-JAN-2015 Initial revision of file.
# @li zhalat 03-FEB-2016 Added ThreatFour.cpp file to project.
# @li zhalat 03-MAR-2016 Added ThreatStraightFour.cpp file to project.
# @li zhalat 05-MAR-2016 Renamed classes. 
# @li zhalat 05-MAR-2016 Add Threat4CaseC class.
# @li zhalat 10-MAR-2016 Add Threat3CaseA, Threat3CaseB, Threat3CaseC classes.
# @li zhalat 26-MAR-2016 Add Threat2CaseA, Threat2CaseB, Threat2CaseC classes.
# @li zhalat 26-JUN-2016 Add GomokuGame class.
# @li zhalat 26-DEC-2016 Add OpenBook class.
# @li zhalat 27-APR-2017 Add Logger.
# @li zhalat 16-SEP-2017 Add Threat3CaseAA.cpp and Threat4CaseAA.cpp.
# @li zhalat 28-OCT-2017 Add Threat2CaseAA.cpp and Threat4CaseAA.cpp.
# @endif
#
# @par Copyright (c) 2017 HalSoft
#
# @ingroup:
#
#########################################​######################################

cmake_minimum_required( VERSION 2.6 )

# Define project name
project( Gomoku )

# Additional CXX flags
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall" ) #-Wno-long-long -save-temps" )

# Additional test definitions
add_definitions( 
    #your macros
	#-DDEBBUG_MODE
	#-DLOGGER_MODE
)

# not sure why this not works in _CXX_FLAGS seciton
add_definitions( -std=gnu++0x )

# Set type building Debug/Release
SET( CMAKE_BUILD_TYPE Debug )

# Set project root
set( CMAKE_PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR} )

# Set path directories
set ( PROJ_HEADERS "${CMAKE_PROJECT_ROOT}/Headers" )
set ( PROJ_SOURCES "${CMAKE_PROJECT_ROOT}/Sources" )

# Define Sources
set( ${PROJECT_NAME_UPPERCASE}_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${PROJ_SOURCES}/DataContainers/Graph.cpp"
    "${PROJ_SOURCES}/DataContainers/GraphIterator.cpp"
    "${PROJ_SOURCES}/GomokuBoard.cpp"
    "${PROJ_SOURCES}/BoardIterator.cpp"
    "${PROJ_SOURCES}/Score.cpp"
	"${PROJ_SOURCES}/Spotter.cpp"
	"${PROJ_SOURCES}/BoardScore.cpp"
    "${PROJ_SOURCES}/GomokuGame.cpp"
	"${PROJ_SOURCES}/Logger.cpp"
	"${PROJ_SOURCES}/OpenBook.cpp"
    "${PROJ_SOURCES}/SearchAlgorithms/MinMax.cpp"
    "${PROJ_SOURCES}/SearchAlgorithms/AlphaBeta.cpp"
    "${PROJ_SOURCES}/SearchAlgorithms/StateEvaluation.cpp"
    "${PROJ_SOURCES}/Threats/ThreatFinder.cpp"
    "${PROJ_SOURCES}/Threats/Threat4CaseA.cpp"
	"${PROJ_SOURCES}/Threats/Threat4CaseAA.cpp"
    "${PROJ_SOURCES}/Threats/Threat4CaseB.cpp"
    "${PROJ_SOURCES}/Threats/Threat4CaseC.cpp"
    "${PROJ_SOURCES}/Threats/Threat3CaseA.cpp"
	"${PROJ_SOURCES}/Threats/Threat3CaseAA.cpp"
    "${PROJ_SOURCES}/Threats/Threat3CaseB.cpp"
    "${PROJ_SOURCES}/Threats/Threat3CaseC.cpp"
    "${PROJ_SOURCES}/Threats/Threat2CaseA.cpp"
	"${PROJ_SOURCES}/Threats/Threat2CaseAA.cpp"
    "${PROJ_SOURCES}/Threats/Threat2CaseB.cpp"
    "${PROJ_SOURCES}/Threats/Threat2CaseC.cpp"
    "${PROJ_SOURCES}/Threats/ThreatWinner.cpp"
    "${PROJ_SOURCES}/Threats/ThreatsBloodRelation.cpp"
	#-------platform dependences-----------------
)

# Define the path to the includes
set( ${PROJECT_NAME_UPPERCASE}_INCLUDE
    "${PROJ_HEADERS}"
    "${PROJ_HEADERS}/DataContainers"
	"${PROJ_HEADERS}/SearchAlgorithms"
    "${PROJ_HEADERS}/Threats"
	#-------platform dependences-----------------
	"${PROJ_HEADERS}/Platform/Windows"
)

include_directories(${${PROJECT_NAME_UPPERCASE}_INCLUDE})
add_executable( Gomoku ${${PROJECT_NAME_UPPERCASE}_SRC} )
