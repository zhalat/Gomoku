#pragma once

#include <gtest/gtest_prod.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <list>

#include "Score.h"
#include "Interfaces/ISpotter.h"
#include "DataContainers/PriorityQueue.h"

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
    void updateScore(const IBoard::PositionXY xy, bool isEnemy, const uint32_t multiplier);
    const std::list<ThreatFinder::ThreatLocation> & getThreatList(const ThreatFinder::KindOfThreats threatKind) const;
    uint32_t getScore() const { return m_score; }
    IBoard::Player getPlayer() const { return m_player; }
    void setPlayer(const IBoard::Player player) { m_player = player; }
    void setBoard(const IBoard& board){ m_board = &board;}
    void mementoEnable();
    void mementoDisable(){m_isMementoEnabled=false;};
    void mementoClear(){m_memento.clearAll();};
    bool mementoRevert(uint32_t n);
    void resetInstance();

    virtual ~ThreatTracker()=default;
    ThreatTracker(const IBoard::Player player,ISpotter& spotter)
    : m_player{player}
    , m_spotter{spotter}
    {}

    ThreatTracker(const ThreatTracker& ref)
    : m_player{ref.m_player}
    , m_spotter{ref.m_spotter}
    , m_threatsOnBoard{ref.m_threatsOnBoard}
    , m_score{ref.m_score}
    , m_board{ref.m_board}
    , m_hashCntr{0}
    , m_isMementoEnabled{false}
    {
        mementoClear();
    }

    ThreatTracker(ThreatTracker&& ref)
    : m_player{ref.m_player}
    , m_spotter{ref.m_spotter}
    , m_threatsOnBoard{std::move(ref.m_threatsOnBoard)}
    , m_score(ref.m_score)
    , m_board(ref.m_board)
    , m_hashCntr{0}
    , m_isMementoEnabled{false}
    {
        ref.m_board = nullptr;
        mementoClear();
    }

    ThreatTracker& operator=(const ThreatTracker& ref)
    {
        if(*this != ref)
        {
            m_player= ref.m_player;
            m_spotter = ref.m_spotter;
            m_threatsOnBoard = ref.m_threatsOnBoard;
            m_score=ref.m_score;
            m_board=ref.m_board;
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
    static constexpr uint32_t k_MAX_MEMENTO = 10;
    uint32_t removeThreats(const IBoard::PositionXY xy);
    bool addThreats(const ThreatFinder::ThreatLocation & treatLocation, const uint32_t kindOfThreat, const uint32_t multiplier = ThreatFinder::ThreatLocation::k_DEFAULT_MULTIPLIER);
    bool isPartOfThreat(const ThreatFinder::ThreatLocation & rThreatLocation, const IBoard::PositionXY xy) const;
    void getThreatElementDismissal(const ThreatFinder::ThreatLocation & threatLocation, const IBoard::Player player,
                                   IBoard::PositionXY threatElements[k_MAX_THREAT_PARTS]) const;
    void getThreatElementPromotion(const ThreatFinder::ThreatLocation & rThreatLocation,
                                   IBoard::PositionXY & threatElement, const bool isTheFist) const;
    void storeMemento();

    IBoard::Player m_player;
    ISpotter& m_spotter;
    ThreatsOnBoard m_threatsOnBoard{};
    uint32_t m_score{0};
    const IBoard * m_board{nullptr};
    unsigned int m_hashCntr{0};

    //simple memento. Any relevant state of the class is kept in a queue. The newest version of the class has higher m_hashCntr
    struct Memento
    {
        ThreatsOnBoard m_threatsOnBoard;
        uint32_t m_score;
        unsigned int m_hashCntr;

        bool operator<(const Memento& other) const
        {
            return this->m_hashCntr < other.m_hashCntr;
        }

        bool operator>(const Memento& other) const
        {
            return this->m_hashCntr > other.m_hashCntr;
        }
    };

    bool m_isMementoEnabled{false};
    PriorityQueue<Memento, std::vector<Memento>> m_memento{k_MAX_MEMENTO};

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
        return _stream;
    }

    FRIEND_TEST(ThreatTrackerTest, AddThreatsTest1);
    FRIEND_TEST(ThreatTrackerTest, RemoveThreatsRemoveAllTest1);
    FRIEND_TEST(ThreatTrackerTest, RemoveThreatsRemoveAllTest2);
    FRIEND_TEST(ThreatTrackerTest, RemoveThreatsRemoveAllTest3);
    FRIEND_TEST(ThreatTrackerTest, RemoveThreatsPartiallyRemoveTest);
    FRIEND_TEST(ThreatTrackerTest, GetNumberOfRecognizedThreatTest);
    FRIEND_TEST(ThreatTrackerTest, GetExGapsTest1);
    FRIEND_TEST(ThreatTrackerTest, GetGapsUniqueTest1);
    FRIEND_TEST(ThreatTrackerTest, GetGapsNonUniqueTest1);
};

