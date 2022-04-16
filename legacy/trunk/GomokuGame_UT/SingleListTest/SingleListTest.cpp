/*
 * SingleListTest.cpp
 *
 *  Created on: 31 oct, 2016
 *      Author: halsoft
 */
#include <assert.h>     		// for assert.
#include <iostream>
#include "SingleListTest.hpp"

#define NUMELEM( x )    ( sizeof( x )/sizeof( x[ 0 ] ) )

void SingleListTest::IsEmptyTest()
{
	const uint32_t data = 10;

	CPPUNIT_ASSERT( m_pSingleList->IsEmpty() );
	m_pSingleList->AddToTail( data );
	CPPUNIT_ASSERT( !m_pSingleList->IsEmpty() );
	m_pSingleList->RemoveFromTail();
	CPPUNIT_ASSERT( m_pSingleList->IsEmpty() );
}

void SingleListTest::AddToTailTest()
{
	const uint32_t data[] = { 10, 20, 30 };
	bool isCompared = false;

	m_pSingleList->AddToTail( data[ 0 ] );
	m_pSingleList->AddToTail( data[ 1 ] );
	m_pSingleList->AddToTail( data[ 2 ] );

	IteratorIf<uint32_t>* pIteratorIf = m_pSingleList->GetIterator();

	for( uint32_t i = 0; pIteratorIf->HasNext(); ++i )
	{
		CPPUNIT_ASSERT( data[i] == pIteratorIf->GetNext() );
		CPPUNIT_ASSERT( i == ( pIteratorIf->GetIndex() - 1 ) );
		isCompared = true;
	}

	CPPUNIT_ASSERT( isCompared );
}

void SingleListTest::AddToHeadTest()
{
	const uint32_t data[] = { 10, 20, 30, 40 };
	bool isCompared = false;

	m_pSingleList->AddToHead( data[ 0 ] );
	m_pSingleList->AddToHead( data[ 1 ] );
	m_pSingleList->AddToHead( data[ 2 ] );
	m_pSingleList->AddToHead( data[ 3 ] );

	IteratorIf<uint32_t>* pIteratorIf = m_pSingleList->GetIterator();

	for( uint32_t i = ( NUMELEM( data ) - 1 ); pIteratorIf->HasNext(); --i )
	{
		CPPUNIT_ASSERT( data[i] == pIteratorIf->GetNext() );
		isCompared = true;
	}

	CPPUNIT_ASSERT( isCompared );
}

void SingleListTest::RemoveFromTailTest()
{
	const uint32_t data[] = { 10, 20, 30, 40, 50, 60 };
	const uint32_t dataSize = NUMELEM( data );
	const uint32_t indexOfLastElement = NUMELEM( data ) - 1;
	uint32_t removedElementCntr = 0;
	uint32_t i = 0;
	IteratorIf<uint32_t>* pIteratorIf = m_pSingleList->GetIterator();

	m_pSingleList->AddToTail( data[ 0 ] );
	m_pSingleList->AddToTail( data[ 1 ] );
	m_pSingleList->AddToTail( data[ 2 ] );
	m_pSingleList->AddToTail( data[ 3 ] );
	m_pSingleList->AddToTail( data[ 4 ] );
	m_pSingleList->AddToTail( data[ 5 ] );

	for( ;removedElementCntr < dataSize;  )
	{
		// Remove element form the tail.
		CPPUNIT_ASSERT( data[ indexOfLastElement - removedElementCntr ] == m_pSingleList->RemoveFromTail() );
		++removedElementCntr;

		// Check that the rest are untouched.
		for( i = 0; pIteratorIf->HasNext(); ++i )
		{
			CPPUNIT_ASSERT( data[i] == pIteratorIf->GetNext() );
		}
		const uint32_t remainedElementInList = dataSize - removedElementCntr;
		CPPUNIT_ASSERT( i == remainedElementInList );

		pIteratorIf->SetToBase();
	}

	CPPUNIT_ASSERT( m_pSingleList->IsEmpty() );
}

void SingleListTest::RemoveFromHeadTest()
{
	const uint32_t data[] = { 10, 20, 30, 40, 50, 60 };
	const uint32_t dataReversed[] = { 60, 50, 40, 30, 20, 10 };
	const uint32_t dataSize = NUMELEM( data );
	const uint32_t indexOfLastElement = NUMELEM( data ) - 1;
	uint32_t removedElementCntr = 0;
	uint32_t j = 0;
	IteratorIf<uint32_t>* pIteratorIf = m_pSingleList->GetIterator();

	m_pSingleList->AddToHead( data[ 0 ] );
	m_pSingleList->AddToHead( data[ 1 ] );
	m_pSingleList->AddToHead( data[ 2 ] );
	m_pSingleList->AddToHead( data[ 3 ] );
	m_pSingleList->AddToHead( data[ 4 ] );
	m_pSingleList->AddToHead( data[ 5 ] );

	for( uint32_t i = 0; i < dataSize;  ++i )
	{
		// Remove element form the head.
		CPPUNIT_ASSERT( dataReversed[ i ] == m_pSingleList->RemoveFromHead() );
		removedElementCntr++;
		const uint32_t remainedElementInList = dataSize - removedElementCntr;

		// Check that the rest are untouched.
		for( j = 0; pIteratorIf->HasNext(); ++j )
		{
			CPPUNIT_ASSERT( dataReversed[j + removedElementCntr] == pIteratorIf->GetNext() );
		}

		CPPUNIT_ASSERT( j == remainedElementInList );

		pIteratorIf->SetToBase();
	}

	CPPUNIT_ASSERT( m_pSingleList->IsEmpty() );
}

void SingleListTest::IsPresentTest()
{
	const uint32_t data[] = { 10, 20, 30, 40 };
	m_pSingleList->AddToTail( data[ 0 ] );
	m_pSingleList->AddToTail( data[ 1 ] );
	m_pSingleList->AddToTail( data[ 2 ] );

	CPPUNIT_ASSERT( true == m_pSingleList->IsPresent( data[ 0 ] ) );
	CPPUNIT_ASSERT( true == m_pSingleList->IsPresent( data[ 1 ] ) );
	CPPUNIT_ASSERT( true == m_pSingleList->IsPresent( data[ 2 ] ) );
	CPPUNIT_ASSERT( false == m_pSingleList->IsPresent( data[ 3 ] ) );
}

void SingleListTest::RemoveNodeTest()
{
	const uint32_t data[] = { 10, 20, 30, 40 };
	m_pSingleList->AddToTail( data[ 0 ] );

	CPPUNIT_ASSERT( data[ 0 ] == m_pSingleList->RemoveNode( data[ 0 ] ) );
	CPPUNIT_ASSERT( false == m_pSingleList->IsPresent( data[ 0 ] ) );

	m_pSingleList->AddToTail( data[ 0 ] );
	m_pSingleList->AddToTail( data[ 1 ] );
	m_pSingleList->AddToTail( data[ 2 ] );

	CPPUNIT_ASSERT( data[ 2 ] == m_pSingleList->RemoveNode( data[ 2 ] ) );
	CPPUNIT_ASSERT( false == m_pSingleList->IsPresent( data[ 2 ] ) );
}

void SingleListTest::SizeTest()
{
	const uint32_t data[] = { 10, 20, 30, 40 };

	// List is empty.
	CPPUNIT_ASSERT( 0 == m_pSingleList->Size() );

	for( uint32_t i = 0; i < NUMELEM( data ); ++i )
	{
		m_pSingleList->AddToTail( data[ i ] );

		const uint32_t expectedElementsInList = i + 1;
		CPPUNIT_ASSERT( expectedElementsInList == m_pSingleList->Size() );
	}
}
