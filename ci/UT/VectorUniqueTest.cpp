#include "VectorUnique.hpp"
#include "Board.hpp"
#include <gtest/gtest.h>
////-------------------------------
//#include "CppUTest/TestHarness.h"
//#include "CppUTest/SimpleString.h"
//#include "CppUTest/PlatformSpecificFunctions.h"
//#include "CppUTest/TestMemoryAllocator.h"
//#include "CppUTest/MemoryLeakDetector.h"

// TEST_GROUP(VectorUniqueTest)
//{
//    static const uint32_t VECTOR_SIZE = 20;
//    void setup() { m_pVectorUnique = new VectorUnique<int, VECTOR_SIZE>(); }
//
//    void teardown() { delete m_pVectorUnique; }
//
//   public:
//    VectorUnique<int, VECTOR_SIZE>* m_pVectorUnique;
//};

// TEST(VectorUniqueTest, InitTest)
//{
//    static const uint32_t EVAL_VAL_TMP      = VectorUnique<int, VECTOR_SIZE>::EMPTY_VAL;
//    static const uint32_t NON_EMPTY_VAL_TMP = VectorUnique<int, VECTOR_SIZE>::NON_EMPTY_VAL;
//
//    //	// Check if constructor fills all cells with initVal.
//    //	// Check the first and the last one.
//    //	CHECK( 0 == m_pVectorUnique->m_List.size() );
//    //	LONGS_EQUAL( EVAL_VAL_TMP == m_pVectorUnique->m_MarkArray[ 0 ] );
//    //	CHECK( EVAL_VAL_TMP == m_pVectorUnique->m_MarkArray[ VECTOR_SIZE - 1 ] );
//    //
//    //	const uint32_t data = 0x5;
//    //	m_pVectorUnique->Insert( data );
//    //	CHECK( 1 == m_pVectorUnique->m_List.size() );
//    //	CHECK( NON_EMPTY_VAL_TMP == m_pVectorUnique->m_MarkArray[ data ] );
//    //
//    //
//    //	// Check the assign operator.
//    //	VectorUnique<int, VECTOR_SIZE> vectorUniqueCopy( *m_pVectorUnique );
//    //	CHECK( 1 == vectorUniqueCopy.m_List.size() );
//    //	CHECK( NON_EMPTY_VAL_TMP == vectorUniqueCopy.m_MarkArray[ data ] );
//    //
//    //	// Check assign operator.
//    //	const int initialData[] = { 3, 4 ,5 };
//    //	const vector<int> vectorStl{ initialData[0], initialData[1], initialData[2] };
//    //	VectorUnique<int, VECTOR_SIZE> vectorUnique2;
//    //	vectorUnique2 = vectorStl;
//    //	CHECK( vectorUnique2.GetNumberOfElements() == sizeof( initialData )/sizeof(initialData[0]) );
//    //
//    //	for ( auto cit = vectorUnique2.GetIteratorBegin(); cit != vectorUnique2.GetIteratorEnd();  ++cit)
//    //	{
//    //		CHECK( vectorUnique2.IsPresent( *cit ) );
//    //	}
//}
//
// TEST(VectorUniqueTest, InsertTest)
//{
//    uint32_t data[VECTOR_SIZE] = {0};
//
//    for(uint32_t i = 0; i < VECTOR_SIZE; ++i)
//    {
//        data[i] = i;
//        m_pVectorUnique->Insert(data[i]);
//    }
//
//    for(auto cit = m_pVectorUnique->GetIteratorBegin(); cit != m_pVectorUnique->GetIteratorEnd(); ++cit)
//    {
//        CHECK(m_pVectorUnique->IsPresent(*cit));
//    }
//}
//
// TEST(VectorUniqueTest, IsPresentTest)
//{
//    const uint32_t dat1 = 0x4;
//    const uint32_t dat2 = 0x6;
//    const uint32_t dat3 = 0x7;
//    const uint32_t dat4 = 0x5;
//
//    // Add some data into collection:
//    m_pVectorUnique->Insert(dat1);
//    m_pVectorUnique->Insert(dat2);
//    m_pVectorUnique->Insert(dat3);
//
//    // Check if all data that have been added exist in collection:
//    CHECK(m_pVectorUnique->IsPresent(dat1));
//    CHECK(m_pVectorUnique->IsPresent(dat2));
//    CHECK(m_pVectorUnique->IsPresent(dat3));
//
//    // Check if data that has not been added, doesn't exist in collection.
//    CHECK(!m_pVectorUnique->IsPresent(dat4));
//
//    // Add it now, and check it,
//    m_pVectorUnique->Insert(dat4);
//    CHECK(m_pVectorUnique->IsPresent(dat4));
//}
//
// TEST(VectorUniqueTest, RemoveTest1)
//{
//    const uint32_t data[] = {0x4, 0x6, 0x7, 0x5};
//
//    // Add some data into collection:
//    m_pVectorUnique->Insert(data[0]);
//    m_pVectorUnique->Insert(data[1]);
//    m_pVectorUnique->Insert(data[2]);
//
//    uint32_t index = 0;
//    for(auto cit = m_pVectorUnique->GetIteratorBegin(); cit != m_pVectorUnique->GetIteratorEnd(); ++cit)
//    {
//        CHECK(data[index++] == *cit);
//    }
//
//    // Try to remove not existing data.
//    CHECK(false == m_pVectorUnique->Remove(data[3]));
//
//    // Try to remove existing data.
//    const uint32_t removedData = data[1];
//    CHECK(true == m_pVectorUnique->Remove(removedData));
//
//    // Go thru all elements. Removed element shall be not avaliable.
//    for(auto cit = m_pVectorUnique->GetIteratorBegin(); cit != m_pVectorUnique->GetIteratorEnd(); ++cit)
//    {
//        CHECK(removedData != *cit);
//    }
//}
//
// TEST(VectorUniqueTest, RemoveTest2)
//{
//    const uint32_t data[] = {0x8, 0x1, 0x6, 0x3, 0x4, 0x5, 0x2, 0x7, 0x0};
//
//    for(uint32_t i = 0; i < (sizeof(data) / sizeof(data[0])); ++i)
//    {
//        m_pVectorUnique->Insert(data[i]);
//    }
//
//    // Data to remove:
//    const uint32_t removeData1 = data[0];
//    const uint32_t removeData2 = data[3];
//    const uint32_t removeData3 = data[7];
//    const uint32_t removeData4 = data[8];
//    CHECK(true == m_pVectorUnique->Remove(removeData1));
//    CHECK(true == m_pVectorUnique->Remove(removeData2));
//    CHECK(true == m_pVectorUnique->Remove(removeData3));
//    CHECK(true == m_pVectorUnique->Remove(removeData4));
//
//    const uint32_t dataAfterRemove[] = {0x1, 0x6, 0x4, 0x5, 0x2};
//
//    // Go thru all elements. Removed element shall not be avaliable.
//    uint32_t index = 0;
//    for(auto cit = m_pVectorUnique->GetIteratorBegin(); cit != m_pVectorUnique->GetIteratorEnd(); ++cit)
//    {
//        CHECK(dataAfterRemove[index++] == *cit);
//    }
//}
//
// TEST(VectorUniqueTest, IsSpaceTest)
//{
//    // An empty collection.
//    CHECK(true == m_pVectorUnique->IsSpace());
//
//    for(uint32_t i = 0; i < (VECTOR_SIZE - 1); ++i)
//    {
//        m_pVectorUnique->Insert(i);
//        CHECK(true == m_pVectorUnique->IsSpace());
//    }
//
//    // Now collection has only one space.
//    CHECK(true == m_pVectorUnique->IsSpace());
//
//    // Even releasing data from collection vacant space does not change. Still one.
//    const uint32_t dataToRemove = 0x01;
//    m_pVectorUnique->Remove(dataToRemove);
//    CHECK(true == m_pVectorUnique->IsSpace());
//
//    // Add again data that has been removed.
//    m_pVectorUnique->Insert(dataToRemove);
//    CHECK(true == m_pVectorUnique->IsSpace());
//}
//
// TEST(VectorUniqueTest, GetNumberOfElementsTest)
//{
//    // An empty collection.
//    CHECK(0 == m_pVectorUnique->GetNumberOfElements());
//
//    // Consecutively insert data and check number of element in collection.
//    for(uint32_t i = 0; i < VECTOR_SIZE; ++i)
//    {
//        m_pVectorUnique->Insert(i);
//
//        const uint32_t elementsInCollection = i + 1;
//        CHECK(elementsInCollection == m_pVectorUnique->GetNumberOfElements());
//    }
//
//    // Consecutively remove data and check number of element in collection.
//    const uint32_t initialElements = m_pVectorUnique->GetNumberOfElements();
//
//    for(uint32_t i = 0, remainedElements = initialElements; i < VECTOR_SIZE; ++i, --remainedElements)
//    {
//        CHECK(remainedElements == m_pVectorUnique->GetNumberOfElements());
//        m_pVectorUnique->Remove(i);
//    }
//
//    // Here all elements have been removed.
//    CHECK(0 == m_pVectorUnique->GetNumberOfElements());
//}
//
// TEST(VectorUniqueTest, ClearTest)
//{
//    const uint32_t dat1 = 0x4;
//    const uint32_t dat2 = 0x6;
//    const uint32_t dat3 = 0x7;
//
//    // Add some data into collection:
//    m_pVectorUnique->Insert(dat1);
//    m_pVectorUnique->Insert(dat2);
//    m_pVectorUnique->Insert(dat3);
//
//    // Clear all.
//    m_pVectorUnique->Clear();
//
//    CHECK(0 == m_pVectorUnique->GetNumberOfElements());
//    CHECK(m_pVectorUnique->GetIteratorBegin() == m_pVectorUnique->GetIteratorEnd());
//}
