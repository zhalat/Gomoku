#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "VectorLight.h"

class VectorLightTest : public ::testing::Test
{
public:
    static constexpr uint32_t k_VECTOR_TEST_SIZE {25};

    void SetUp() { m_pVectorLight = new VectorLight<k_VECTOR_TEST_SIZE>(0xFFFFFFFF); }
    void TearDown() { delete m_pVectorLight; }
    VectorLight<k_VECTOR_TEST_SIZE>* m_pVectorLight;
};

TEST_F(VectorLightTest, InsertTest)
{
    uint32_t data[k_VECTOR_TEST_SIZE] = {0};

    for(uint32_t i = 0; i < k_VECTOR_TEST_SIZE; ++i)
    {
        data[i] = i;
        m_pVectorLight->insert(data[i]);
    }

    IIterator<uint32_t>* pIterator = m_pVectorLight->getIterator();

    uint32_t index = 0;
    for(pIterator->backToBegin(); pIterator->hasNext(); ++index)
    {
        ASSERT_EQ(data[index] , pIterator->getNext());
    }
}

TEST_F(VectorLightTest, HasNextTest)
{
    IIterator<uint32_t>* iter1 = m_pVectorLight->getIterator();
    ASSERT_FALSE( iter1->hasNext());

    uint32_t data[k_VECTOR_TEST_SIZE] = {0};

    for(uint32_t i = 0; i < k_VECTOR_TEST_SIZE; ++i)
    {
        data[i] = i;
        m_pVectorLight->insert(data[i]);
    }

    IIterator<uint32_t>* iter2 = m_pVectorLight->getIterator();

    uint32_t index = 0;
    for(iter2->backToBegin(); iter2->hasNext(); ++index)
    {
        if(k_VECTOR_TEST_SIZE == index)
        {
            ASSERT_TRUE(iter2->hasNext());
        }
        else
        {
            ASSERT_TRUE(iter2->hasNext());
            iter2->getNext();
        }
    }
}
TEST_F(VectorLightTest, IsPresentTest)
{
    const uint32_t dat1 = 0x4;
    const uint32_t dat2 = 0x6;
    const uint32_t dat3 = 0x7;
    const uint32_t dat4 = 0x5;

    // Add some data into collection:
    m_pVectorLight->insert(dat1);
    m_pVectorLight->insert(dat2);
    m_pVectorLight->insert(dat3);

    // Check if all data that have been added exist in collection:
    ASSERT_TRUE(m_pVectorLight->isPresent(dat1));
    ASSERT_TRUE(m_pVectorLight->isPresent(dat2));
    ASSERT_TRUE(m_pVectorLight->isPresent(dat3));

    // Check if data that has not been added, doesn't exist in collection.
    ASSERT_TRUE(!m_pVectorLight->isPresent(dat4));

    // Add it now, and check it,
    m_pVectorLight->insert(dat4);
    ASSERT_TRUE(m_pVectorLight->isPresent(dat4));
}

TEST_F(VectorLightTest, RemoveTest1)
{
    const uint32_t data[] = {0x4, 0x6, 0x7, 0x5};

    // Add some data into collection:
    m_pVectorLight->insert(data[0]);
    m_pVectorLight->insert(data[1]);
    m_pVectorLight->insert(data[2]);

    IIterator<uint32_t>* pIterator = m_pVectorLight->getIterator();

    uint32_t index = 0;
    for(pIterator->backToBegin(); pIterator->hasNext(); ++index)
    {
        ASSERT_TRUE(data[index] == pIterator->getNext());
    }

    // Try to remove not existing data.
    ASSERT_TRUE(false == m_pVectorLight->remove(data[3]));

    // Try to remove existing data.
    const uint32_t removedData = data[1];
    ASSERT_TRUE(true == m_pVectorLight->remove(removedData));

    // Go thru all elements. Removed element shall be not avaliable.
    for(pIterator->backToBegin(); pIterator->hasNext();)
    {
        const uint32_t currentData = pIterator->getNext();
        ASSERT_TRUE(removedData != currentData);
    }
}

TEST_F(VectorLightTest, RemoveTest2)
{
    const uint32_t data[] = {0x8, 0x1, 0x6, 0x3, 0x4, 0x5, 0x2, 0x7, 0x0};

    for(uint32_t i = 0; i < (sizeof(data) / sizeof(data[0])); ++i)
    {
        m_pVectorLight->insert(data[i]);
    }

    // Data to remove:
    const uint32_t removeData1 = data[0];
    const uint32_t removeData2 = data[3];
    const uint32_t removeData3 = data[7];
    const uint32_t removeData4 = data[8];
    ASSERT_TRUE(true == m_pVectorLight->remove(removeData1));
    ASSERT_TRUE(true == m_pVectorLight->remove(removeData2));
    ASSERT_TRUE(true == m_pVectorLight->remove(removeData3));
    ASSERT_TRUE(true == m_pVectorLight->remove(removeData4));

    const uint32_t dataAfterRemove[] = {0x1, 0x6, 0x4, 0x5, 0x2};

    // Go thru all elements. Removed element shall not be avaliable.
    IIterator<uint32_t>* pIterator = m_pVectorLight->getIterator();
    uint32_t index                  = 0;
    for(pIterator->backToBegin(); pIterator->hasNext(); ++index)
    {
        const uint32_t currentData = pIterator->getNext();
        ASSERT_TRUE(dataAfterRemove[index] == currentData);
    }
}

TEST_F(VectorLightTest, IsSpaceTest)
{
    // An empty collection.
    ASSERT_TRUE(true == m_pVectorLight->isSpace());

    for(uint32_t i = 0; i < (k_VECTOR_TEST_SIZE - 1); ++i)
    {
        m_pVectorLight->insert(i);
        ASSERT_TRUE(true == m_pVectorLight->isSpace());
    }

    // Now collection has only one space.
    ASSERT_TRUE(true == m_pVectorLight->isSpace());

    // Even releasing data from collection vacant space does not change. Still one.
    const uint32_t dataToRemove = 0x01;
    m_pVectorLight->remove(dataToRemove);
    ASSERT_TRUE(true == m_pVectorLight->isSpace());

    // Add again data that has been removed.
    m_pVectorLight->insert(dataToRemove);
    ASSERT_TRUE(false == m_pVectorLight->isSpace());
}

TEST_F(VectorLightTest, GetNumberOfElementsTest)
{
    // An empty collection.
    ASSERT_TRUE(0 == m_pVectorLight->getNumberOfElements());

    // Consecutively insert data and check number of element in collection.
    for(uint32_t i = 0; i < k_VECTOR_TEST_SIZE; ++i)
    {
        m_pVectorLight->insert(i);

        const uint32_t elementsInCollection = i + 1;
        ASSERT_TRUE(elementsInCollection == m_pVectorLight->getNumberOfElements());
    }

    // Consecutively remove data and check number of element in collection.
    const uint32_t initialElements = m_pVectorLight->getNumberOfElements();

    for(uint32_t i = 0, remainedElements = initialElements; i < k_VECTOR_TEST_SIZE; ++i, --remainedElements)
    {
        ASSERT_TRUE(remainedElements == m_pVectorLight->getNumberOfElements());
        m_pVectorLight->remove(i);
    }

    // Here all elements have been removed.
    ASSERT_TRUE(0 == m_pVectorLight->getNumberOfElements());
}

TEST_F(VectorLightTest, ClearTest)
{
    const uint32_t dat1 = 0x4;
    const uint32_t dat2 = 0x6;
    const uint32_t dat3 = 0x7;

    // Add some data into collection:
    m_pVectorLight->insert(dat1);
    m_pVectorLight->insert(dat2);
    m_pVectorLight->insert(dat3);

    // clear all.
    m_pVectorLight->clear();

    IIterator<uint32_t>* pIterator = m_pVectorLight->getIterator();

    ASSERT_TRUE(0 == m_pVectorLight->getNumberOfElements());
    ASSERT_TRUE(false == pIterator->hasNext());
}
