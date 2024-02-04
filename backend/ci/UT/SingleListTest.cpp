#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "SingleList.h"
#include "SingleListIterator.h"

#define NUMELEM(x) (sizeof(x) / sizeof(x[0]))

class SingleListTest : public ::testing::Test
{
public:
    void SetUp() { m_singleList = new SingleList<uint32_t>();}
    void TearDown() { delete m_singleList; }
    SingleList<uint32_t>* m_singleList;
};

TEST_F(SingleListTest, IsEmptyTest)
{
    const uint32_t data = 10;
    ASSERT_TRUE(m_singleList->isEmpty());
    m_singleList->addToTail(data);
    ASSERT_TRUE(!m_singleList->isEmpty());
    m_singleList->removeFromTail();
    ASSERT_TRUE(m_singleList->isEmpty());
}

TEST_F(SingleListTest, AddToTailTest)
{
    const uint32_t data[] = {10, 20, 30};
    bool isCompared       = false;

    m_singleList->addToTail(data[0]);
    m_singleList->addToTail(data[1]);
    m_singleList->addToTail(data[2]);

    IIterator<uint32_t>* pIteratorIf = m_singleList->getIterator();

    for(uint32_t i = 0; pIteratorIf->hasNext(); ++i)
    {
        ASSERT_TRUE(data[i] == pIteratorIf->getNext());
        ASSERT_TRUE(i == (pIteratorIf->getIndex() - 1));
        isCompared = true;
    }

    ASSERT_TRUE(isCompared);
}

TEST_F(SingleListTest, AddToHeadTest)
{
    const uint32_t data[] = {10, 20, 30, 40};
    bool isCompared       = false;

    m_singleList->addToHead(data[0]);
    m_singleList->addToHead(data[1]);
    m_singleList->addToHead(data[2]);
    m_singleList->addToHead(data[3]);

    IIterator<uint32_t>* pIteratorIf = m_singleList->getIterator();

    for(uint32_t i = (NUMELEM(data) - 1); pIteratorIf->hasNext(); --i)
    {
        ASSERT_TRUE(data[i] == pIteratorIf->getNext());
        isCompared = true;
    }

    ASSERT_TRUE(isCompared);
}

TEST_F(SingleListTest, RemoveFromTailTest)
{
    const uint32_t data[]             = {10, 20, 30, 40, 50, 60};
    const uint32_t dataSize           = NUMELEM(data);
    const uint32_t indexOfLastElement = NUMELEM(data) - 1;
    uint32_t removedElementCntr       = 0;
    uint32_t i                        = 0;
    IIterator<uint32_t>* pIteratorIf = m_singleList->getIterator();

    m_singleList->addToTail(data[0]);
    m_singleList->addToTail(data[1]);
    m_singleList->addToTail(data[2]);
    m_singleList->addToTail(data[3]);
    m_singleList->addToTail(data[4]);
    m_singleList->addToTail(data[5]);

    for(; removedElementCntr < dataSize;)
    {
        // remove element form the tail.
        ASSERT_TRUE(data[indexOfLastElement - removedElementCntr] == m_singleList->removeFromTail());
        ++removedElementCntr;

        // Check that the rest are untouched.
        for(i = 0; pIteratorIf->hasNext(); ++i)
        {
            ASSERT_TRUE(data[i] == pIteratorIf->getNext());
        }
        const uint32_t remainedElementInList = dataSize - removedElementCntr;
        ASSERT_TRUE(i == remainedElementInList);

        pIteratorIf->backToBegin();
    }

    ASSERT_TRUE(m_singleList->isEmpty());
}

TEST_F(SingleListTest, RemoveFromHeadTest)
{
    const uint32_t data[]             = {10, 20, 30, 40, 50, 60};
    const uint32_t dataReversed[]     = {60, 50, 40, 30, 20, 10};
    const uint32_t dataSize           = NUMELEM(data);
    const uint32_t indexOfLastElement = NUMELEM(data) - 1;
    uint32_t removedElementCntr       = 0;
    uint32_t j                        = 0;
    IIterator<uint32_t>* pIteratorIf = m_singleList->getIterator();

    m_singleList->addToHead(data[0]);
    m_singleList->addToHead(data[1]);
    m_singleList->addToHead(data[2]);
    m_singleList->addToHead(data[3]);
    m_singleList->addToHead(data[4]);
    m_singleList->addToHead(data[5]);

    for(uint32_t i = 0; i < dataSize; ++i)
    {
        // remove element form the head.
        ASSERT_TRUE(dataReversed[i] == m_singleList->removeFromHead());
        removedElementCntr++;
        const uint32_t remainedElementInList = dataSize - removedElementCntr;

        // Check that the rest are untouched.
        for(j = 0; pIteratorIf->hasNext(); ++j)
        {
            ASSERT_TRUE(dataReversed[j + removedElementCntr] == pIteratorIf->getNext());
        }

        ASSERT_TRUE(j == remainedElementInList);

        pIteratorIf->backToBegin();
    }

    ASSERT_TRUE(m_singleList->isEmpty());
}

TEST_F(SingleListTest, IsPresentTest)
{
    const uint32_t data[] = {10, 20, 30, 40};
    m_singleList->addToTail(data[0]);
    m_singleList->addToTail(data[1]);
    m_singleList->addToTail(data[2]);

    ASSERT_TRUE(true == m_singleList->isPresent(data[0]));
    ASSERT_TRUE(true == m_singleList->isPresent(data[1]));
    ASSERT_TRUE(true == m_singleList->isPresent(data[2]));
    ASSERT_TRUE(false == m_singleList->isPresent(data[3]));
}

TEST_F(SingleListTest, RemoveNodeTest)
{
    const uint32_t data[] = {10, 20, 30, 40};
    m_singleList->addToTail(data[0]);

    ASSERT_TRUE(data[0] == m_singleList->removeNode(data[0]));
    ASSERT_TRUE(false == m_singleList->isPresent(data[0]));

    m_singleList->addToTail(data[0]);
    m_singleList->addToTail(data[1]);
    m_singleList->addToTail(data[2]);

    ASSERT_TRUE(data[2] == m_singleList->removeNode(data[2]));
    ASSERT_TRUE(false == m_singleList->isPresent(data[2]));
}

TEST_F(SingleListTest, SizeTest)
{
    const uint32_t data[] = {10, 20, 30, 40};

    ASSERT_TRUE(0 == m_singleList->size());

    for(uint32_t i = 0; i < NUMELEM(data); ++i)
    {
        m_singleList->addToTail(data[i]);

        const uint32_t expectedElementsInList = i + 1;
        ASSERT_TRUE(expectedElementsInList == m_singleList->size());
    }
}
