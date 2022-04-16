/////////////////////////////////////////////////////////////////////////////////////////
/// @file Logger.cpp
///
/// Logs the game progress.
///
/// @par Full Description.
/// Logs the game progress in the txt file.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 23-Apr-2017 Initial revision.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2017 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

// SYSTEM INCLUDES
#include <Logger.hpp>   // Logger declaration.
#include <fstream>		// For file stream operating.
#include <stdio.h>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES

// FORWARD REFERENCES
// <none>

const char* Logger::LOG_GAME_RECORD_FILE_NAME = "GameRecord.txt";
const char* Logger::LOG_MINMAX_TREE_RECORD_FILE_NAME = "MinMaxTreeRecord.txt";
const char* Logger::LOG_MINMAX_BOARD_RECORD_FILE_NAME = "MinMaxBoardRecord.txt";
const char* Logger::LOG_SEPARATOR = "--";

/// Checks if file exists.
bool Logger::IsRecordExist( const char* filePath ) const
{
    std::ifstream file( filePath );
    return file.good();
}

/// Create a new file.
void Logger::NewRecord( const char* filePath )
{
	try{
		std::ofstream file;
		file.open ( filePath );
		file<< LOG_SEPARATOR <<endl;
		file.close();
	}
	catch(...)
	{
		assert( false );
	}
}

/// Logs human - cpu move.
void Logger::AddEntryToRecord( const Board::PositionXY move )
{
	if( IsRecordExist( LOG_GAME_RECORD_FILE_NAME ) )
	{
		std::fstream file;
		file.open( LOG_GAME_RECORD_FILE_NAME, std::ios::app );
		file << "( " << move.m_x << ", " << move.m_y<< " )"<<std::endl;
		file.close();
	}
	else
	{
		std::string fileError =  std::string( "Record doesn't exist: ");
		throw fileError;
	}
}

/// Logs score being associated with row/column indexing.
void Logger::AddEntryToRecord( const uint32_t row, const uint32_t column, const SearchTreeAlgorithmIf::ScoreForMove& rScore )
{
	if( IsRecordExist( LOG_MINMAX_TREE_RECORD_FILE_NAME ) )
	{
		std::fstream file;
		file.open( LOG_MINMAX_TREE_RECORD_FILE_NAME, std::ios::app );

		// format: position/move/score
		file << row << "_" << column << " " << "(" << rScore.m_move.m_x << "," << rScore.m_move.m_y << ")" << " " << "[" << rScore.m_score << "]" <<endl;
		file.close();
	}
	else
	{
		std::string fileError =  std::string( "Record doesn't exist: ");
		throw fileError;
	}
}

/// Logs board score being associated with row/column indexing.
void Logger::AddEntryToRecord( const uint32_t row, const uint32_t column, const BoardScore& rBoardScore )
{
	if( IsRecordExist( LOG_MINMAX_BOARD_RECORD_FILE_NAME ) )
	{
		std::fstream file;
		file.open( LOG_MINMAX_BOARD_RECORD_FILE_NAME, std::ios::app );

		file << rBoardScore <<endl;
		file.close();
	}
	else
	{
		std::string fileError =  std::string( "Record doesn't exist: ");
		throw fileError;
	}
}

/// Logs board being associated with row/column indexing.
void Logger::AddEntryToRecord( const uint32_t row, const uint32_t column, const Board& rBoard )
{
	if( IsRecordExist( LOG_MINMAX_BOARD_RECORD_FILE_NAME ) )
	{
		std::fstream file;
		file.open( LOG_MINMAX_BOARD_RECORD_FILE_NAME, std::ios::app );

		// format: position/move/score
		file << row << "_" << column <<endl;
		file << rBoard <<endl;
		file.close();
	}
	else
	{
		std::string fileError =  std::string( "Record doesn't exist: ");
		throw fileError;
	}
}

/// Logs info who starts the game.
void Logger::FirstPlayer( const char* filePath, const bool isCpuStart )
{
	if( IsRecordExist( filePath ) )
	{
		std::fstream file;
		file.open( filePath, std::ios::app );

		if( isCpuStart )
		{
			file << "CPU starts game."<<std::endl;
		}
		else
		{
			file << "HUMAN starts game."<<std::endl;
		}

		file.close();
	}
	else
	{
		std::string fileError =  std::string( "Record doesn't exist: ");
		throw fileError;
	}
}

/// Clear a record.
void Logger::ClearRecord( const char* filePath )
{
	if( IsRecordExist( filePath ) )
	{
		std::ofstream file;
		file.open( filePath, std::ofstream::out | std::ofstream::trunc);
		file.close();
	}
	else
	{
		std::string fileError =  std::string( "Record doesn't exist: ");
		throw fileError;
	}
}

/// Remove a record.
void Logger::RemoveRecord( const char* filePath )
{
	if( remove( filePath ) !=0 )
	{
		std::string fileError =  std::string( "File doesn't exist: ") + std::string( filePath );
		throw fileError;
	}
}

/***************************************************************************
 *   Copyright (C) 2018 by Zbigniew Halat                                  *
 *   zby.halat@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 ***************************************************************************/
