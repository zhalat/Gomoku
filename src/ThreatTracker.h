#pragma once

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <list>

#include "Score.h"
#include "Interfaces/ISpotter.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: ThreatTracker
///
/// Keeps threats for board.
///
/// @par Full Description.
/// Keeps threats for board.
///////////////////////////////////////////////////////////////////////////////////////////
class ThreatTracker
{
   public:
    struct ThreatsOnBoard
    {
        uint32_t m_numberOfThreats[Score::MAX_KIND_OF_THREATS];
        std::list<ThreatFinder::ThreatLocation> m_recognizedThreats[Score::MAX_KIND_OF_THREATS];
    };

    uint32_t getNumberOf(ThreatFinder::KindOfThreats threatKind) const;
    void getGapsNonUnique(std::vector<IBoard::PositionXY>& gaps, const ThreatFinder::KindOfThreats threatKind) const;
    void getGapsUnique(std::vector<IBoard::PositionXY>& gaps, const ThreatFinder::KindOfThreats threatKind) const;
    void getGapsDuplicated(std::vector<IBoard::PositionXY>& gaps,const ThreatFinder::KindOfThreats threatKind) const;
    void getExGaps(std::vector<IBoard::PositionXY> & exGaps, const ThreatFinder::KindOfThreats threatKind) const;
    uint32_t getCommonFieldNumber(const ThreatFinder::KindOfThreats threatKindA, const ThreatFinder::KindOfThreats threatKindB) const;
    uint32_t removeThreats(const IBoard::PositionXY xy);
    bool addThreats(const ThreatFinder::ThreatLocation & treatLocation, const uint32_t kindOfThreat, const uint32_t multiplier = ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    void updateScore(const IBoard::PositionXY xy, bool isEnemy, const uint32_t multiplier);
    const std::list<ThreatFinder::ThreatLocation> & getThreatList(const ThreatFinder::KindOfThreats threatKind) const;
    uint32_t getScore() const { return m_score; }
    IBoard::Player getPlayer() const { return m_player; }
    void setPlayer(const IBoard::Player player) { m_player = player; }
    void setBoard(const IBoard& board){ m_board = &board;}
    void resetInstance();

    virtual ~ThreatTracker()=default;
    ThreatTracker(const IBoard::Player player,ISpotter& spotter)
            : m_player{player}
            , m_spotter{spotter}
    {}

    ThreatTracker(const ThreatTracker& ref)
    : m_player{ref.m_player}
    , m_spotter(ref.m_spotter)
    , m_threatsOnBoard(ref.m_threatsOnBoard)
    , m_score(ref.m_score)
    {}

    ThreatTracker& operator=(const ThreatTracker& ref)
    {
        if(*this != ref)
        {
            m_player= ref.m_player;
            m_spotter = ref.m_spotter;
            m_threatsOnBoard = ref.m_threatsOnBoard;
            m_score=ref.m_score;
        }

        return *this;
    }

    bool operator==(const ThreatTracker & scoreTracker) const
    {
        const bool isEqual = (this->m_score == scoreTracker.m_score);
        return isEqual;
    }
    bool operator!=(const ThreatTracker & scoreTracker) const
    {
        const bool isNotEqual = !(*this == scoreTracker);
        return isNotEqual;
    }
    bool operator<(const ThreatTracker & scoreTracker) const
    {
        const bool isGrather = (this->m_score < scoreTracker.m_score);
        return isGrather;
    }
    bool operator>(const ThreatTracker & scoreTracker) const
    {
        const bool isLower = (this->m_score > scoreTracker.m_score);
        return isLower;
    }

   private:
    static constexpr uint32_t k_MAX_THREAT_PARTS = 3;
    bool isPartOfThreat(const ThreatFinder::ThreatLocation & rThreatLocation, const IBoard::PositionXY xy) const;
    void getThreatElementDismissal(const ThreatFinder::ThreatLocation & threatLocation, const IBoard::Player player,
                                   IBoard::PositionXY threatElements[k_MAX_THREAT_PARTS]) const;
    void getThreatElementPromotion(const ThreatFinder::ThreatLocation & rThreatLocation,
                                   IBoard::PositionXY & threatElement, const bool isTheFist) const;

    IBoard::Player m_player;
    ISpotter& m_spotter;
    ThreatsOnBoard m_threatsOnBoard{};
    uint32_t m_score{0};
    const IBoard * m_board{nullptr};

    /// Print board.
    friend std::ostream & operator<<(std::ostream & _stream, const ThreatTracker & ref)
    {
        _stream << "Recognized threats:" << endl;

        for(uint32_t i = 0; i < Score::MAX_KIND_OF_THREATS; ++i)
        {
            // Print threat number.
            _stream << i << ": " << ref.m_threatsOnBoard.m_numberOfThreats[i] << " ";

            std::list<ThreatFinder::ThreatLocation>::const_iterator citer =
                    ref.m_threatsOnBoard.m_recognizedThreats[i].begin();

            for(; citer != ref.m_threatsOnBoard.m_recognizedThreats[i].end(); ++citer)
            {
                // Print the recognized group in format: [(beg_x,beg_y),(end_x,end_y) ]
                _stream << "["
                        << "(" << citer->m_threatDetails.m_beginningThreat.m_x << ","
                        << citer->m_threatDetails.m_beginningThreat.m_y << ")"
                        << ",";
                _stream << "(" << citer->m_threatDetails.m_endThreat.m_x << ","
                        << citer->m_threatDetails.m_endThreat.m_y << ")"
                        << "] ";
            }

            _stream << endl;
        }
    }
};

