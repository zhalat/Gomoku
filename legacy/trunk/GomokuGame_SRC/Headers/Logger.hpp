/////////////////////////////////////////////////////////////////////////////////////////
/// @file Logger.hpp
///
/// Logs the game progress.
///
/// @par Full Description.
/// Logs the game progress in the txt file.
///
/// @if REVISION_HISTORY_INCLUDED
/// @par Edit History
/// - zhalat 23-Apr-2017 Initial revision.
/// - zhalat 29-Apr-2017 Interface refactoring.
/// @endif
///
/// @ingroup.
///
/// @par non-Copyright (c) 2017 HalSoft
///////////////////////////////////////////////////////////////////////////////////////////

#if !defined ( LOGGER_HPP_ )
#define LOGGER_HPP_

// SYSTEM INCLUDES
// <none>

// C PROJECT INCLUDES
// <none>

// C++ PROJECT INCLUDES
#include "Board.hpp"
#include "BoardScore.hpp"
#include "SearchTreeAlgorithmIf.hpp"

// FORWARD REFERENCES
// <none>

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: TwoPlayersGame
///
/// Logs the game progress.
///
/// @par Full Description.
/// Logs the game progress in the txt file.
///////////////////////////////////////////////////////////////////////////////////////////
class Logger
{
public:
	static const char* LOG_GAME_RECORD_FILE_NAME;
	static const char* LOG_MINMAX_TREE_RECORD_FILE_NAME;
	static const char* LOG_MINMAX_BOARD_RECORD_FILE_NAME;
	static const char* LOG_SEPARATOR;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Logger::IsRecordExist
    //
    /// Checks if file exists.
    ///
    /// @par Full Description.
    /// Checks if file exists.
    ///
    /// @param filePath Path to file.
	///
    /// @return True if file exists, false otherwise.
    ///////////////////////////////////////////////////////////////////////
	bool IsRecordExist( const char* filePath ) const;

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Logger::NewRecord
    //
    /// Create a new file.
    ///
    /// @par Full Description.
    /// Create a new file.
    ///
    /// @param filePath Path to file.
    ///////////////////////////////////////////////////////////////////////
	void NewRecord( const char* filePath );

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Logger::AddEntryToRecord
    //
    /// Logs human - cpu move.
    ///
    /// @par Full Description.
    /// Logs game movies (for analyzing in the future).
    ///
    /// @param move Move to be recorded.
    ///////////////////////////////////////////////////////////////////////
	void AddEntryToRecord( const Board::PositionXY move );

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Logger::AddEntryToRecord
    //
    /// Logs score being associated with row/column indexing
    ///
    /// @par Full Description.
    /// Logs score being associated with row/column indexing
    ///
    /// @param row    Indexing.
    /// @param column Indexing.
    /// @param score  Estimated board game score.
    ///////////////////////////////////////////////////////////////////////
	void AddEntryToRecord( const uint32_t row, const uint32_t column, const SearchTreeAlgorithmIf::ScoreForMove& rScore );

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Logger::AddEntryToRecord
    //
    /// Logs board threat being associated with row/column indexing
    ///
    /// @par Full Description.
    /// Logs board threat being associated with row/column indexing
    ///
    /// @param row    	   Indexing.
    /// @param column 	   Indexing.
    /// @param boardScore  Board state.
    ///////////////////////////////////////////////////////////////////////
	void AddEntryToRecord( const uint32_t row, const uint32_t column, const BoardScore& rBoardScore );

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Logger::AddEntryToRecord
    //
    /// Logs board being associated with row/column indexing.
    ///
    /// @par Full Description.
    /// Logs board being associated  with row/column indexing.
    ///
    /// @param row    	   Indexing.
    /// @param column 	   Indexing.
    /// @param boardScore  Board state.
    ///////////////////////////////////////////////////////////////////////
	void AddEntryToRecord( const uint32_t row, const uint32_t column, const Board& rBoard );

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Logger::FirstPlayer
    //
    /// Logs info who starts the game.
    ///
    /// @par Full Description.
    /// Logs info who starts the game - human or cpu.
    ///
    /// @param filePath Path to file.
    /// @param isCpuStart True if human starts game, false otherwise.
    ///////////////////////////////////////////////////////////////////////
	void FirstPlayer( const char* filePath, const bool isCpuStart );

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Logger::ClearRecord
    //
    /// Clear a record.
    ///
    /// @par Full Description.
    /// Clear a record.
    ///
    /// @param filePath Path to file.
    ///////////////////////////////////////////////////////////////////////
	void ClearRecord( const char* filePath );

    ///////////////////////////////////////////////////////////////////////
    // METHOD NAME: Logger::RemoveRecord
    //
    /// Remove a record.
    ///
    /// @par Full Description.
    /// Clear a record.
    ///
    /// @param filePath Path to file.
    ///////////////////////////////////////////////////////////////////////
	void RemoveRecord( const char* filePath );

private:


};

#endif /* LOGGER_HPP_ */

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