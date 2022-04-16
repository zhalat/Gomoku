#########################################​######################################
# @file CMakeLists.txt
#
# @details GomokuGame_UTTests source project CMake file.
#
# @if REVISION_HISTORY_INCLUDED
# @par Edit History
# @li zhalat 27-SEP-2014 Initial revision of file.
# @li zhalat 01-APR-2015 Update for SingleListTest class test.
# @li zhalat 15-FEB-2016 Update for Threat4Test class test.
# @li zhalat 03-MAR-2016 Update for ThreatStraight4Test class test.
# @li zhalat 05-MAR-2016 Renamed classes.
# @li zhalat 06-MAR-2016 Added Threat4CaseCTest.
# @endif
#
# @par Copyright (c) 2016 HalSoft
#
# @ingroup:
#
#########################################​######################################

cmake_minimum_required( VERSION 2.6 )

# Define project name
project( GomokuGame_UTTests )

# Set project root
set( CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} )

# This builds multiple tests
set( GROUP_SOLUTION TRUE )

# Add sub-directories
add_subdirectory( 
	#Threat4CaseATest
    #Threat4CaseBTest
	#Threat4CaseCTest
    GomokuBoardTest
    #SingleListTest
	#SpotterTest
	#OpenBookTest
)
