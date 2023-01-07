#include "VectorLight.hpp"
#include "Board.hpp"
//-------------------------------
#include "CppUTest/TestHarness.h"
#include "CppUTest/SimpleString.h"
#include "CppUTest/PlatformSpecificFunctions.h"
#include "CppUTest/TestMemoryAllocator.h"
#include "CppUTest/MemoryLeakDetector.h"

TEST_GROUP(VectorLightTest)
{
    void setup() { m_pVectorLight = new VectorLight(Board::PositionField::INVALID_FIELD); }

    void teardown() { delete m_pVectorLight; }

   public:
    VectorLight* m_pVectorLight;
};

TEST(VectorLightTest, InitTest)
{
    const uint32_t data = 0x5;

    m_pVectorLight->Insert(data);

    CHECK(data == m_pVectorLight->m_Array[0]);
    CHECK(Board::PositionField::INVALID_FIELD == m_pVectorLight->m_Array[VectorLight::VECTOR_SIZE - 1]);

    CHECK(Board::PositionField::INVALID_FIELD == m_pVectorLight->m_MarkArray[0]);
    CHECK(Board::PositionField::INVALID_FIELD == m_pVectorLight->m_MarkArray[VectorLight::VECTOR_SIZE - 1]);

    // Check the copy constructor.
    VectorLight vectorLightCopy = *m_pVectorLight;

    CHECK(data == vectorLightCopy.m_Array[0]);

    CHECK(Board::PositionField::INVALID_FIELD == vectorLightCopy.m_MarkArray[0]);
    CHECK(Board::PositionField::INVALID_FIELD == vectorLightCopy.m_MarkArray[VectorLight::VECTOR_SIZE - 1]);

    // Check assign operator.
    const Board::PositionField initialData[] = {3, 4, 5};

    vector<Board::PositionField> vectorStl{initialData[0], initialData[1], initialData[2]};
    VectorLight vectorLight(Board::PositionField::INVALID_FIELD);
    vectorLight = vectorStl;

    CHECK(vectorLight.GetNumberOfElements() == sizeof(initialData) / sizeof(initialData[0]));

    IteratorIf<uint32_t>* pIterator = vectorLight.GetIterator();
    uint32_t index                  = 0;
    for(pIterator->SetToBase(); pIterator->HasNext(); ++index)
    {
        CHECK(initialData[index] == pIterator->GetNext());
    }
}

TEST(VectorLightTest, InsertTest)
{
    uint32_t data[VectorLight::VECTOR_SIZE] = {0};

    for(uint32_t i = 0; i < VectorLight::VECTOR_SIZE; ++i)
    {
        data[i] = i;
        m_pVectorLight->Insert(data[i]);
    }

    IteratorIf<uint32_t>* pIterator = m_pVectorLight->GetIterator();

    uint32_t index = 0;
    for(pIterator->SetToBase(); pIterator->HasNext(); ++index)
    {
        CHECK(data[index] == pIterator->GetNext());
    }
}

TEST(VectorLightTest, HasNextVectorLightIteratorTest)
{
    IteratorIf<uint32_t>* beginTest = m_pVectorLight->GetIterator();
    CHECK(false == beginTest->HasNext());

    uint32_t data[VectorLight::VECTOR_SIZE] = {0};

    for(uint32_t i = 0; i < VectorLight::VECTOR_SIZE; ++i)
    {
        data[i] = i;
        m_pVectorLight->Insert(data[i]);
    }

    IteratorIf<uint32_t>* pIterator = m_pVectorLight->GetIterator();

    uint32_t index = 0;
    for(pIterator->SetToBase(); pIterator->HasNext(); ++index)
    {
        if((VectorLight::VECTOR_SIZE) == index)
        {
            CHECK(false == pIterator->HasNext());
        }
        else
        {
            CHECK(true == pIterator->HasNext());
            pIterator->GetNext();
        }
    }
}

TEST(VectorLightTest, IsPresentTest)
{
    const uint32_t dat1 = 0x4;
    const uint32_t dat2 = 0x6;
    const uint32_t dat3 = 0x7;
    const uint32_t dat4 = 0x5;

    // Add some data into collection:
    m_pVectorLight->Insert(dat1);
    m_pVectorLight->Insert(dat2);
    m_pVectorLight->Insert(dat3);

    // Check if all data that have been added exist in collection:
    CHECK(m_pVectorLight->IsPresent(dat1));
    CHECK(m_pVectorLight->IsPresent(dat2));
    CHECK(m_pVectorLight->IsPresent(dat3));

    // Check if data that has not been added, doesn't exist in collection.
    CHECK(!m_pVectorLight->IsPresent(dat4));

    // Add it now, and check it,
    m_pVectorLight->Insert(dat4);
    CHECK(m_pVectorLight->IsPresent(dat4));
}

TEST(VectorLightTest, RemoveTest1)
{
    const uint32_t data[] = {0x4, 0x6, 0x7, 0x5};

    // Add some data into collection:
    m_pVectorLight->Insert(data[0]);
    m_pVectorLight->Insert(data[1]);
    m_pVectorLight->Insert(data[2]);

    IteratorIf<uint32_t>* pIterator = m_pVectorLight->GetIterator();

    uint32_t index = 0;
    for(pIterator->SetToBase(); pIterator->HasNext(); ++index)
    {
        CHECK(data[index] == pIterator->GetNext());
    }

    // Try to remove not existing data.
    CHECK(false == m_pVectorLight->Remove(data[3]));

    // Try to remove existing data.
    const uint32_t removedData = data[1];
    CHECK(true == m_pVectorLight->Remove(removedData));

    // Go thru all elements. Removed element shall be not avaliable.
    for(pIterator->SetToBase(); pIterator->HasNext();)
    {
        const uint32_t currentData = pIterator->GetNext();
        CHECK(removedData != currentData);
    }
}

TEST(VectorLightTest, RemoveTest2)
{
    const uint32_t data[] = {0x8, 0x1, 0x6, 0x3, 0x4, 0x5, 0x2, 0x7, 0x0};

    for(uint32_t i = 0; i < (sizeof(data) / sizeof(data[0])); ++i)
    {
        m_pVectorLight->Insert(data[i]);
    }

    // Data to remove:
    const uint32_t removeData1 = data[0];
    const uint32_t removeData2 = data[3];
    const uint32_t removeData3 = data[7];
    const uint32_t removeData4 = data[8];
    CHECK(true == m_pVectorLight->Remove(removeData1));
    CHECK(true == m_pVectorLight->Remove(removeData2));
    CHECK(true == m_pVectorLight->Remove(removeData3));
    CHECK(true == m_pVectorLight->Remove(removeData4));

    const uint32_t dataAfterRemove[] = {0x1, 0x6, 0x4, 0x5, 0x2};

    // Go thru all elements. Removed element shall not be avaliable.
    IteratorIf<uint32_t>* pIterator = m_pVectorLight->GetIterator();
    uint32_t index                  = 0;
    for(pIterator->SetToBase(); pIterator->HasNext(); ++index)
    {
        const uint32_t currentData = pIterator->GetNext();
        CHECK(dataAfterRemove[index] == currentData);
    }
}

TEST(VectorLightTest, IsSpaceTest)
{
    // An empty collection.
    CHECK(true == m_pVectorLight->IsSpace());

    for(uint32_t i = 0; i < (VectorLight::VECTOR_SIZE - 1); ++i)
    {
        m_pVectorLight->Insert(i);
        CHECK(true == m_pVectorLight->IsSpace());
    }

    // Now collection has only one space.
    CHECK(true == m_pVectorLight->IsSpace());

    // Even releasing data from collection vacant space does not change. Still one.
    const uint32_t dataToRemove = 0x01;
    m_pVectorLight->Remove(dataToRemove);
    CHECK(true == m_pVectorLight->IsSpace());

    // Add again data that has been removed.
    m_pVectorLight->Insert(dataToRemove);
    CHECK(false == m_pVectorLight->IsSpace());
}

TEST(VectorLightTest, GetNumberOfElementsTest)
{
    // An empty collection.
    CHECK(0 == m_pVectorLight->GetNumberOfElements());

    // Consecutively insert data and check number of element in collection.
    for(uint32_t i = 0; i < VectorLight::VECTOR_SIZE; ++i)
    {
        m_pVectorLight->Insert(i);

        const uint32_t elementsInCollection = i + 1;
        CHECK(elementsInCollection == m_pVectorLight->GetNumberOfElements());
    }

    // Consecutively remove data and check number of element in collection.
    const uint32_t initialElements = m_pVectorLight->GetNumberOfElements();

    for(uint32_t i = 0, remainedElements = initialElements; i < VectorLight::VECTOR_SIZE; ++i, --remainedElements)
    {
        CHECK(remainedElements == m_pVectorLight->GetNumberOfElements());
        m_pVectorLight->Remove(i);
    }

    // Here all elements have been removed.
    CHECK(0 == m_pVectorLight->GetNumberOfElements());
}

TEST(VectorLightTest, ClearTest)
{
    const uint32_t dat1 = 0x4;
    const uint32_t dat2 = 0x6;
    const uint32_t dat3 = 0x7;

    // Add some data into collection:
    m_pVectorLight->Insert(dat1);
    m_pVectorLight->Insert(dat2);
    m_pVectorLight->Insert(dat3);

    // Clear all.
    m_pVectorLight->Clear();

    IteratorIf<uint32_t>* pIterator = m_pVectorLight->GetIterator();

    CHECK(0 == m_pVectorLight->GetNumberOfElements());
    CHECK(false == pIterator->HasNext());
}
