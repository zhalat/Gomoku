#include "Heuristics/TreeLogger.h"
#include <fstream>
#include <stdio.h>

bool TreeLogger::IsRecordExist( const char* filePath ) const
{
    std::ifstream file( filePath );
    return file.good();
}

void TreeLogger::NewRecord( const char* filePath )
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

void TreeLogger::AddEntryToRecord( const IBoard::PositionXY& move )
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

void TreeLogger::AddEntryToRecord( const uint32_t row, const uint32_t column, const ISearchTree::ScoreForMove& score )
{
    if( IsRecordExist( LOG_MINMAX_TREE_RECORD_FILE_NAME ) )
    {
        std::fstream file;
        file.open( LOG_MINMAX_TREE_RECORD_FILE_NAME, std::ios::app );

        // format: position/move/score
        file << row << "_" << column << " " << "(" << score.m_move.m_x << "," << score.m_move.m_y << ")" << " " << "[" << score.m_score << "]" <<endl;
        file.close();
    }
    else
    {
        std::string fileError =  std::string( "Record doesn't exist: ");
        throw fileError;
    }
}

void TreeLogger::AddEntryToRecord( const uint32_t row, const uint32_t column, const ThreatTracker& threatTracker )
{
    if( IsRecordExist( LOG_MINMAX_BOARD_RECORD_FILE_NAME ) )
    {
        std::fstream file;
        file.open( LOG_MINMAX_BOARD_RECORD_FILE_NAME, std::ios::app );

        file << threatTracker <<endl;
        file.close();
    }
    else
    {
        std::string fileError =  std::string( "Record doesn't exist: ");
        throw fileError;
    }
}

void TreeLogger::AddEntryToRecord( const uint32_t row, const uint32_t column, const IBoard& board )
{
    if( IsRecordExist( LOG_MINMAX_BOARD_RECORD_FILE_NAME ) )
    {
        std::fstream file;
        file.open( LOG_MINMAX_BOARD_RECORD_FILE_NAME, std::ios::app );

        // format: position/move/score
        file << row << "_" << column <<endl;
        file << board <<endl;
        file.close();
    }
    else
    {
        std::string fileError =  std::string( "Record doesn't exist: ");
        throw fileError;
    }
}

void TreeLogger::FirstPlayer( const char* filePath, const bool isCpuStart )
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

void TreeLogger::ClearRecord( const char* filePath )
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

void TreeLogger::RemoveRecord( const char* filePath )
{
    if( remove( filePath ) !=0 )
    {
        std::string fileError =  std::string( "File doesn't exist: ") + std::string( filePath );
        throw fileError;
    }
}
