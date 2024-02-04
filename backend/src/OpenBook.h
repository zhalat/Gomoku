#pragma once
#include "Interfaces/IBoard.h"

///////////////////////////////////////////////////////////////////////////////////////////
/// CLASS NAME: OpenBook
///
/// OpenBook interface declaration.
///
/// @par Full Description.
/// Provide third move for white.
///////////////////////////////////////////////////////////////////////////////////////////
class OpenBook
{
   public:
    enum OpenGameType
    {
        DIRECT,
        INDIRECT,
        UNDEFINED
    };

    // Helpful containers to browsing best open game move.
    struct Crawling
    {
        IBoard::Direction m_direction;
        uint32_t m_shift;

        Crawling() : m_direction(IBoard::DIRECTION_NONE), m_shift(0) {}
        Crawling(const IBoard::Direction direction, const uint32_t shift) : m_direction(direction), m_shift(shift) {}

        bool operator==(const Crawling & el)
        {
            bool retVal{ false };

            if(this->m_direction == el.m_direction and this->m_shift == el.m_shift)
            {
                retVal = true;
            }

            return retVal;
        }

        bool operator!=(const Crawling & el) { return !(*this == el); }
    };

    struct CrawlingChain
    {
        char m_spotName;
        Crawling m_crawlingList[3];
    };

    struct Openings
    {
        // constituted by two first movements.
        IBoard::Direction m_mainDirection;
        CrawlingChain * m_crawlingChain;

        Openings(const IBoard::Direction direction, CrawlingChain * const pCrawlingChain) :
            m_mainDirection(direction), m_crawlingChain(pCrawlingChain)
        {}
    };

    static IBoard::PositionXY getBestThirdWhiteMove(const IBoard & board);
    static IBoard::PositionXY getBestSecondBlackMove(const IBoard & rBoard);
    static OpenGameType openGame(const IBoard & rBoard);

   private:
    OpenBook(const OpenBook & ref) = delete;
    OpenBook(const OpenBook && ref) = delete;
    OpenBook & operator=(const OpenBook & ref) = delete;
    OpenBook & operator=(const OpenBook && ref) = delete;
    virtual ~OpenBook()=default;

    // Directions to find direct or indirect kind of opening game.
    static constexpr IBoard::Direction DIRECT_PATH[]   = { IBoard::UP, IBoard::RIGHT, IBoard::DOWN, IBoard::LEFT };
    static constexpr IBoard::Direction INDIRECT_PATH[] = { IBoard::UP_RIGHT, IBoard::DOWN_RIGHT, IBoard::DOWN_LEFT,
                                                          IBoard::UP_LEFT };
    static constexpr auto DIRECT_PATH_SIZE{ std::size(DIRECT_PATH) };
    static constexpr auto INDIRECT_PATH_SIZE{ std::size(INDIRECT_PATH) };

    // Containers for direct open game.
    static const Openings DIRECT_OPEN[];
    static CrawlingChain m_crawlingChainUp[];
    static CrawlingChain m_crawlingChainRight[];
    static CrawlingChain m_crawlingChainDown[];
    static CrawlingChain m_crawlingChainLeft[];

    // Containers for indirect open game.
    static const Openings INDIRECT_OPEN[];
    static CrawlingChain m_crawlingChainUpRight[];
    static CrawlingChain m_crawlingChainDownRight[];
    static CrawlingChain m_crawlingChainDownLeft[];
    static CrawlingChain m_crawlingChainUpLeft[];

    static const uint32_t CRAWLING_DIRECT_SIZE;
    static const uint32_t CRAWLING_INDIRECT_SIZE;
    static const uint32_t DIRECT_OPEN_SIZE;
    static const uint32_t INDIRECT_OPEN_SIZE;
};
