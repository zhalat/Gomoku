#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "DataContainers/VectorUnique.h"

class VectorUniqueTest: public ::testing::Test
{
public:
    static constexpr uint32_t k_VECTOR_SIZE = 20;

    void SetUp() { m_pVectorUnique = new VectorUnique<int, k_VECTOR_SIZE>(); }
    void TearDown() { delete m_pVectorUnique; }
    VectorUnique<int, k_VECTOR_SIZE>* m_pVectorUnique;
};

TEST_F(VectorUniqueTest, InsertTest)
{
    for(uint32_t i = 0; i < k_VECTOR_SIZE; ++i)
    {
        m_pVectorUnique->insert(i);
        ASSERT_TRUE(m_pVectorUnique->isPresent(i));
    }

    for(auto cit = m_pVectorUnique->getIteratorBegin(); cit != m_pVectorUnique->getIteratorEnd(); ++cit)
    {
        ASSERT_TRUE(m_pVectorUnique->isPresent(*cit));
    }
}

 TEST_F(VectorUniqueTest, IsPresentTest)
{
    const uint32_t dat1 = 0x4;
    const uint32_t dat2 = 0x6;
    const uint32_t dat3 = 0x7;
    const uint32_t dat4 = 0x5;

    // Add some data into collection:
    m_pVectorUnique->insert(dat1);
    m_pVectorUnique->insert(dat2);
    m_pVectorUnique->insert(dat3);

    // Check if all data that have been added exist in collection:
    ASSERT_TRUE(m_pVectorUnique->isPresent(dat1));
    ASSERT_TRUE(m_pVectorUnique->isPresent(dat2));
    ASSERT_TRUE(m_pVectorUnique->isPresent(dat3));

    // Check if data that has not been added, doesn't exist in collection.
    ASSERT_TRUE(!m_pVectorUnique->isPresent(dat4));

    // Add it now, and check it,
    m_pVectorUnique->insert(dat4);
    ASSERT_TRUE(m_pVectorUnique->isPresent(dat4));
}

 TEST_F(VectorUniqueTest, RemoveTest1)
{
    const uint32_t data[] = {0x4, 0x6, 0x7, 0x5};

    // Add some data into collection:
    m_pVectorUnique->insert(data[0]);
    m_pVectorUnique->insert(data[1]);
    m_pVectorUnique->insert(data[2]);

    uint32_t index = 0;
    for(auto cit = m_pVectorUnique->getIteratorBegin(); cit != m_pVectorUnique->getIteratorEnd(); ++cit)
    {
        ASSERT_TRUE(data[index++] == *cit);
    }

    // Try to remove not existing data.
    ASSERT_FALSE(m_pVectorUnique->remove(data[3]));

    // Try to remove existing data.
    const uint32_t removedData = data[1];
    ASSERT_TRUE(m_pVectorUnique->remove(removedData));

    // Go thru all elements. Removed element shall be not avaliable.
    for(auto cit = m_pVectorUnique->getIteratorBegin(); cit != m_pVectorUnique->getIteratorEnd(); ++cit)
    {
        ASSERT_TRUE(removedData != *cit);
    }
}

 TEST_F(VectorUniqueTest, RemoveTest2)
{
    const uint32_t data[] = {0x8, 0x1, 0x6, 0x3, 0x4, 0x5, 0x2, 0x7, 0x0};

    for(const auto el: data)
    {
        m_pVectorUnique->insert(el);
    }

    // Data to remove:
    const uint32_t removeData1 = data[0];
    const uint32_t removeData2 = data[3];
    const uint32_t removeData3 = data[7];
    const uint32_t removeData4 = data[8];
    ASSERT_TRUE(m_pVectorUnique->remove(removeData1));
    ASSERT_TRUE(m_pVectorUnique->remove(removeData2));
    ASSERT_TRUE(m_pVectorUnique->remove(removeData3));
    ASSERT_TRUE(m_pVectorUnique->remove(removeData4));

    const uint32_t dataAfterRemove[] = {0x1, 0x6, 0x4, 0x5, 0x2};

    // Go thru all elements. Removed element shall not be avaliable.
    uint32_t index = 0;
    for(auto cit = m_pVectorUnique->getIteratorBegin(); cit != m_pVectorUnique->getIteratorEnd(); ++cit)
    {
        ASSERT_TRUE(dataAfterRemove[index++] == *cit);
    }
}

 TEST_F(VectorUniqueTest, IsSpaceTest)
{
    // An empty collection.
    ASSERT_TRUE(m_pVectorUnique->isSpace());

    for(uint32_t i = 0; i < (k_VECTOR_SIZE - 1); ++i)
    {
        m_pVectorUnique->insert(i);
        ASSERT_TRUE(m_pVectorUnique->isSpace());
    }

    // Now collection has only one space.
    ASSERT_TRUE( m_pVectorUnique->isSpace());

    // Even releasing data from collection vacant space does not change. Still one.
    const uint32_t dataToRemove = 0x01;
    m_pVectorUnique->remove(dataToRemove);
    ASSERT_TRUE(m_pVectorUnique->isSpace());

    // Add again data that has been removed.
    m_pVectorUnique->insert(dataToRemove);
    ASSERT_TRUE(m_pVectorUnique->isSpace());
}

 TEST_F(VectorUniqueTest, GetNumberOfElementsTest)
{
    // An empty collection.
    ASSERT_TRUE(0 == m_pVectorUnique->getNumberOfElements());

    // Consecutively insert data and check number of element in collection.
    for(uint32_t i = 0; i < k_VECTOR_SIZE; ++i)
    {
        m_pVectorUnique->insert(i);

        const uint32_t elementsInCollection = i + 1;
        ASSERT_EQ(elementsInCollection, m_pVectorUnique->getNumberOfElements());
    }

    // Consecutively remove data and check number of element in collection.
    const uint32_t initialElements = m_pVectorUnique->getNumberOfElements();

    for(uint32_t i = 0, remainedElements = initialElements; i < k_VECTOR_SIZE; ++i, --remainedElements)
    {
        ASSERT_TRUE(remainedElements == m_pVectorUnique->getNumberOfElements());
        m_pVectorUnique->remove(i);
    }

    // Here all elements have been removed.
    ASSERT_EQ(0 , m_pVectorUnique->getNumberOfElements());
}

 TEST_F(VectorUniqueTest, ClearTest)
{
    const uint32_t dat1 = 0x4;
    const uint32_t dat2 = 0x6;
    const uint32_t dat3 = 0x7;

    // Add some data into collection:
    m_pVectorUnique->insert(dat1);
    m_pVectorUnique->insert(dat2);
    m_pVectorUnique->insert(dat3);

    // clear all.
    m_pVectorUnique->clear();

    ASSERT_TRUE(0 == m_pVectorUnique->getNumberOfElements());
    ASSERT_TRUE(m_pVectorUnique->getIteratorBegin() == m_pVectorUnique->getIteratorEnd());
}
