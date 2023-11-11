#pragma once
#include <assert.h>
#include <unordered_map>
#include "Interfaces/IBoard.h"
#include "GomokuBoard.h"

#define NUMELEM(x) (sizeof(x) / sizeof(x[0]))
#define CLR_BIT(p, n) ((p) &= ~((1) << (n)))

class ThreatFinder
{
   public:
    static constexpr uint32_t k_MAX_ALLOWED_EXCEPTION = 2;

    /// Kind of threats. Stronger first.
    enum KindOfThreats : uint8_t
    {
        THREAT_WINNER    = 0,
        THREAT_4_CASE_A  = 1,
        THREAT_4_CASE_AA = 2,
        THREAT_4_CASE_B  = 3,
        THREAT_4_CASE_C  = 4,
        THREAT_3_CASE_A  = 5,
        THREAT_3_CASE_AA = 6,
        THREAT_3_CASE_B  = 7,
        THREAT_3_CASE_C  = 8,
        THREAT_2_CASE_A  = 9,
        THREAT_2_CASE_AA = 10,
        THREAT_2_CASE_B  = 11,
        THREAT_2_CASE_C  = 12,

        THREAT_NONE  // Must be the last.
    };

    /// Define a 4-way direction.
    enum Trend : uint8_t
    {
        VERTICAL   = 0,
        HORIZONTAL = 1,
        RISING     = 2,
        FALLING    = 3,

        TREND_NONE  // Must be the last.
    };

    /// List elements each threat is consisted from.
    enum ThreatAnatnomy : uint8_t
    {
        MY_PAWN    = 0,
        ENEMY_PAWN = 1,
        GAP        = 2,
        ASTERIX    = 3
    };

    /// Straight and reverse conversion trend to direction.
    static const std::unordered_map<Trend, IBoard::Direction> Trend2DirectionStraight;
    static const std::unordered_map<Trend, IBoard::Direction> Trend2DirectionReverse;

    /// Keeps flags about symmetric pattern. Does matter only for symmetric patterns like 2A.
    struct FoundFlags
    {
        bool m_isNormalFound;     // ..x.x.*
        bool m_isSymmetricFound;  // *.x.x..
        bool m_isSearchingForSymmetric;

        void clearAll()
        {
            m_isNormalFound           = false;
            m_isSymmetricFound        = false;
            m_isSearchingForSymmetric = false;
        }
    };

    /// Keeps threat content down details. Needed to find out threat location.
    struct ThreatDownDetails
    {
        uint32_t m_hexCode;
        uint32_t m_pointOfView;
        FoundFlags m_foundFlags;
        IBoard::Player m_playerPerspective;

        ThreatDownDetails()
        {
            clearAll();
        }

        void clearAll()
        {
            m_hexCode           = 0;
            m_pointOfView       = 0;
            m_foundFlags        = {0};
            m_playerPerspective = IBoard::PLAYER_NONE;
        }
    };

    /// Keeps threat content up details. Needed to find out threat location.
    struct ThreatUpDetails
    {
        static constexpr uint32_t k_MAX_MY_PAWNS    = 5;
        static constexpr uint32_t k_MAX_ENEMY_PAWNS = 2;
        static constexpr uint32_t k_MAX_EMPTY_SPACES =
            10;  // index [0-4] for normal; [5-9] symmetric. Duplication allowed! So must be filter while getting.
        static constexpr uint32_t k_MAX_EXTEND_SPACES = 2;
        static constexpr uint32_t k_MAX_ASTERIXES     = 2;

        IBoard::Player m_whos;
        IBoard::PositionXY m_myPawns[k_MAX_MY_PAWNS];
        IBoard::PositionXY m_enemyPawns[k_MAX_ENEMY_PAWNS];
        IBoard::PositionXY m_gaps[k_MAX_EMPTY_SPACES];
        IBoard::PositionXY m_extGaps[k_MAX_EXTEND_SPACES];
        IBoard::PositionXY m_asterixes[k_MAX_ASTERIXES];
        IBoard::PositionXY m_beginningThreat;
        IBoard::PositionXY m_endThreat;

        ThreatUpDetails() { clearAll(); }

        void clearAll()
        {
            // Tell who's threat.
            m_whos = IBoard::Player::PLAYER_NONE;
            for(uint32_t i = 0; i < k_MAX_MY_PAWNS; ++i)
                m_myPawns[i] = ThreatLocation::k_XY_OUT_OF_BOARD;
            for(uint32_t i = 0; i < k_MAX_ENEMY_PAWNS; ++i)
                m_enemyPawns[i] = ThreatLocation::k_XY_OUT_OF_BOARD;
            for(uint32_t i = 0; i < k_MAX_EMPTY_SPACES; ++i)
                m_gaps[i] = ThreatLocation::k_XY_OUT_OF_BOARD;
            for(uint32_t i = 0; i < k_MAX_EXTEND_SPACES; ++i)
                m_extGaps[i] = ThreatLocation::k_XY_OUT_OF_BOARD;
            for(uint32_t i = 0; i < k_MAX_ASTERIXES; ++i)
                m_asterixes[i] = ThreatLocation::k_XY_OUT_OF_BOARD;

            m_beginningThreat = ThreatLocation::k_XY_OUT_OF_BOARD;
            m_endThreat       = ThreatLocation::k_XY_OUT_OF_BOARD;
        }
    };

    /// Keeps threat location on a board.
    struct ThreatLocation
    {
        static constexpr IBoard::PositionXY k_XY_OUT_OF_BOARD = IBoard::PositionXY(IBoard::PositionXY::k_INVALID_FIELD, IBoard::PositionXY::k_INVALID_FIELD);
        static constexpr IBoard::PositionXY k_XY_BEGIN_OF_BOARD = IBoard::PositionXY(0, 0);
        static const uint32_t k_DEFAULT_MULTIPLIER = 1;

        Trend m_trend;
        uint32_t m_multiplier;
        ThreatUpDetails m_threatDetails;

        ThreatLocation()
        {
            clearAll();
        }

        void clearAll()
        {
            m_trend      = TREND_NONE;
            m_multiplier = ThreatLocation::k_DEFAULT_MULTIPLIER;
            m_threatDetails.clearAll();
        }
    };

    /// Threat pattern container.
    struct ThreatPattern
    {
        uint32_t m_threatPattern;
        uint8_t m_pointOfView;
    };

    void setBoard(const IBoard * pBoard) { m_board = pBoard; }
    const IBoard & getBoard() const{ return *m_board;}
    virtual bool findThreatPattern(const IBoard::PositionXY & initialPosition,
                                   const Trend trend,
                                   const IBoard::Player playerPerspective) final;
    void getThreatFields(ThreatLocation & rThreatLocation) const;

    ThreatFinder(const uint32_t patternLenght, const uint32_t * pPointsView, const uint32_t pointsViewSize,
                 const std::unordered_map<ThreatFinder::ThreatAnatnomy, int> atomNumber) :
            m_board(nullptr),
            m_patternLenght(patternLenght),
            m_pointsView(pPointsView),
            m_pointsViewSize(pointsViewSize),
            m_threatLocation(),
            m_isThreatPatternFound(false)
    {}
    ThreatFinder(const ThreatFinder &&) = delete;
    ThreatFinder(const ThreatFinder &) = delete;
    ThreatFinder & operator=(const ThreatFinder &) = delete;
    ThreatFinder & operator=(const ThreatFinder &&) = delete;
    virtual ~ThreatFinder()
    {
        m_board         = nullptr;
        m_pointsView          = nullptr;
        m_isThreatPatternFound = false;
    }

   protected:
    virtual bool checkThreat(const uint32_t pretendThreat, const uint32_t pointOfView,
                             const IBoard::Player playerPerspective) const = 0;
    virtual void getThreatUpDetails(const IBoard::PositionXY initialPosition, const Trend trend,
                                    ThreatUpDetails & rThreatUpDetails) const = 0;
    virtual bool isSearchForSimmetrics() const = 0;
    virtual void prepareSelfForNewSearch() = 0;
    uint8_t standarizePov(const uint8_t hexCode, const uint8_t pointOfView, const uint8_t length) const;
    void getPieces(const uint8_t normHexCode, const IBoard::PositionXY initialPositionNorm,
                   const IBoard::Direction direction, IBoard::PositionXY pBuffer[], const uint32_t bufferSize) const;
    bool makeStepOnTrend(const bool isReversion, IBoard::PositionXY & currentXYPosition, const Trend trend) const;

   private:
    const IBoard * m_board;
    const uint32_t m_patternLenght;
    const uint32_t * m_pointsView;
    const uint32_t m_pointsViewSize;
    ThreatLocation m_threatLocation;
    bool m_isThreatPatternFound;

};
