#include "CppUTest/TestHarness.h"
#include "CppUTest/SimpleString.h"
#include "CppUTest/PlatformSpecificFunctions.h"
#include "CppUTest/TestMemoryAllocator.h"
#include "CppUTest/MemoryLeakDetector.h"
//-------------------------------
#include "SingleList.hpp"
#include "SingleListIterator.hpp"

#define NUMELEM(x) (sizeof(x) / sizeof(x[0]))

TEST_GROUP(SingleListTest)
{
    void setup() { m_pSingleList = new SingleList<uint32_t>; }

    void teardown() { delete m_pSingleList; }

   public:
    SingleList<uint32_t>* m_pSingleList;
};

TEST(SingleListTest, IsEmptyTest)
{
    const uint32_t data = 10;

    CHECK(m_pSingleList->IsEmpty());
    m_pSingleList->AddToTail(data);
    CHECK(!m_pSingleList->IsEmpty());
    m_pSingleList->RemoveFromTail();
    CHECK(m_pSingleList->IsEmpty());
}

TEST(SingleListTest, AddToTailTest)
{
    const uint32_t data[] = {10, 20, 30};
    bool isCompared       = false;

    m_pSingleList->AddToTail(data[0]);
    m_pSingleList->AddToTail(data[1]);
    m_pSingleList->AddToTail(data[2]);

    IteratorIf<uint32_t>* pIteratorIf = m_pSingleList->GetIterator();

    for(uint32_t i = 0; pIteratorIf->HasNext(); ++i)
    {
        CHECK(data[i] == pIteratorIf->GetNext());
        CHECK(i == (pIteratorIf->GetIndex() - 1));
        isCompared = true;
    }

    CHECK(isCompared);
}

TEST(SingleListTest, AddToHeadTest)
{
    const uint32_t data[] = {10, 20, 30, 40};
    bool isCompared       = false;

    m_pSingleList->AddToHead(data[0]);
    m_pSingleList->AddToHead(data[1]);
    m_pSingleList->AddToHead(data[2]);
    m_pSingleList->AddToHead(data[3]);

    IteratorIf<uint32_t>* pIteratorIf = m_pSingleList->GetIterator();

    for(uint32_t i = (NUMELEM(data) - 1); pIteratorIf->HasNext(); --i)
    {
        CHECK(data[i] == pIteratorIf->GetNext());
        isCompared = true;
    }

    CHECK(isCompared);
}

TEST(SingleListTest, RemoveFromTailTest)
{
    const uint32_t data[]             = {10, 20, 30, 40, 50, 60};
    const uint32_t dataSize           = NUMELEM(data);
    const uint32_t indexOfLastElement = NUMELEM(data) - 1;
    uint32_t removedElementCntr       = 0;
    uint32_t i                        = 0;
    IteratorIf<uint32_t>* pIteratorIf = m_pSingleList->GetIterator();

    m_pSingleList->AddToTail(data[0]);
    m_pSingleList->AddToTail(data[1]);
    m_pSingleList->AddToTail(data[2]);
    m_pSingleList->AddToTail(data[3]);
    m_pSingleList->AddToTail(data[4]);
    m_pSingleList->AddToTail(data[5]);

    for(; removedElementCntr < dataSize;)
    {
        // Remove element form the tail.
        CHECK(data[indexOfLastElement - removedElementCntr] == m_pSingleList->RemoveFromTail());
        ++removedElementCntr;

        // Check that the rest are untouched.
        for(i = 0; pIteratorIf->HasNext(); ++i)
        {
            CHECK(data[i] == pIteratorIf->GetNext());
        }
        const uint32_t remainedElementInList = dataSize - removedElementCntr;
        CHECK(i == remainedElementInList);

        pIteratorIf->SetToBase();
    }

    CHECK(m_pSingleList->IsEmpty());
}

TEST(SingleListTest, RemoveFromHeadTest)
{
    const uint32_t data[]             = {10, 20, 30, 40, 50, 60};
    const uint32_t dataReversed[]     = {60, 50, 40, 30, 20, 10};
    const uint32_t dataSize           = NUMELEM(data);
    const uint32_t indexOfLastElement = NUMELEM(data) - 1;
    uint32_t removedElementCntr       = 0;
    uint32_t j                        = 0;
    IteratorIf<uint32_t>* pIteratorIf = m_pSingleList->GetIterator();

    m_pSingleList->AddToHead(data[0]);
    m_pSingleList->AddToHead(data[1]);
    m_pSingleList->AddToHead(data[2]);
    m_pSingleList->AddToHead(data[3]);
    m_pSingleList->AddToHead(data[4]);
    m_pSingleList->AddToHead(data[5]);

    for(uint32_t i = 0; i < dataSize; ++i)
    {
        // Remove element form the head.
        CHECK(dataReversed[i] == m_pSingleList->RemoveFromHead());
        removedElementCntr++;
        const uint32_t remainedElementInList = dataSize - removedElementCntr;

        // Check that the rest are untouched.
        for(j = 0; pIteratorIf->HasNext(); ++j)
        {
            CHECK(dataReversed[j + removedElementCntr] == pIteratorIf->GetNext());
        }

        CHECK(j == remainedElementInList);

        pIteratorIf->SetToBase();
    }

    CHECK(m_pSingleList->IsEmpty());
}

TEST(SingleListTest, IsPresentTest)
{
    const uint32_t data[] = {10, 20, 30, 40};
    m_pSingleList->AddToTail(data[0]);
    m_pSingleList->AddToTail(data[1]);
    m_pSingleList->AddToTail(data[2]);

    CHECK(true == m_pSingleList->IsPresent(data[0]));
    CHECK(true == m_pSingleList->IsPresent(data[1]));
    CHECK(true == m_pSingleList->IsPresent(data[2]));
    CHECK(false == m_pSingleList->IsPresent(data[3]));
}

TEST(SingleListTest, RemoveNodeTest)
{
    const uint32_t data[] = {10, 20, 30, 40};
    m_pSingleList->AddToTail(data[0]);

    CHECK(data[0] == m_pSingleList->RemoveNode(data[0]));
    CHECK(false == m_pSingleList->IsPresent(data[0]));

    m_pSingleList->AddToTail(data[0]);
    m_pSingleList->AddToTail(data[1]);
    m_pSingleList->AddToTail(data[2]);

    CHECK(data[2] == m_pSingleList->RemoveNode(data[2]));
    CHECK(false == m_pSingleList->IsPresent(data[2]));
}

TEST(SingleListTest, SizeTest)
{
    const uint32_t data[] = {10, 20, 30, 40};

    // List is empty.
    CHECK(0 == m_pSingleList->Size());

    for(uint32_t i = 0; i < NUMELEM(data); ++i)
    {
        m_pSingleList->AddToTail(data[i]);

        const uint32_t expectedElementsInList = i + 1;
        CHECK(expectedElementsInList == m_pSingleList->Size());
    }
}
