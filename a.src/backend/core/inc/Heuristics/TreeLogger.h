#pragma once

#include "Interfaces/IBoard.h"
#include "Interfaces/ISearchTree.h"
#include "ThreatTracker.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: TreeLogger
///
/// Logs the game progress.
///
/// @par Full Description.
/// Logs the game progress in the txt file for debuging purposes
///////////////////////////////////////////////////////////////////////////////////////////
class TreeLogger final
{
public:
    static constexpr char* LOG_GAME_RECORD_FILE_NAME = "GameRecord.txt";
    static constexpr char* LOG_MINMAX_TREE_RECORD_FILE_NAME = "MinMaxTreeRecord.txt";
    static constexpr char* LOG_MINMAX_BOARD_RECORD_FILE_NAME = "MinMaxBoardRecord.txt";
    static constexpr char* LOG_SEPARATOR= "--";

    TreeLogger() = default;
    ~TreeLogger() = default;

    bool IsRecordExist( const char* filePath ) const;
    void NewRecord( const char* filePath );
    void AddEntryToRecord( const IBoard::PositionXY& move );
    void AddEntryToRecord( const uint32_t row, const uint32_t column, const ISearchTree::ScoreForMove& score );
    void AddEntryToRecord( const uint32_t row, const uint32_t column, const ThreatTracker& threatTracker );
    void AddEntryToRecord( const uint32_t row, const uint32_t column, const IBoard& board );
    void FirstPlayer( const char* filePath, const bool isCpuStart );
    void ClearRecord( const char* filePath );
    void RemoveRecord( const char* filePath );

private:


};
