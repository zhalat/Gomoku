//framework
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>

using namespace ::testing;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::Sequence;

//app test
#include "Graph.h"
using namespace graph;
using namespace std;

using pairs=std::pair<Node,Node>;
using edgeConnector=std::tuple<Node,Node,EdgeVal>;

class GraphTestFixtureBase: public ::testing::Test
{
   public:
	static constexpr unsigned int k_size{6};

	GraphTestFixtureBase() = default;
	void SetUp() override
	{
		m_graph = new Graph{k_size};
	}

	void TearDown() override
	{
		delete m_graph;
	}

	Graph* m_graph{nullptr};
};

TEST_F(GraphTestFixtureBase, emptyGraphAfterInit)
{
	//no neighbors
	for(Node node=0; node<k_size; ++node)
	{
		vector<Node> neighbours = m_graph->getNeighbors(node);
		ASSERT_TRUE(neighbours.empty());
	}

	//adjacented only to itself
	for(Node x=0; x<k_size; ++x)
	{
		for(Node y=0; y<k_size; ++y)
		{
			if(x==y)
			{
				ASSERT_TRUE(m_graph->adjacent(x, y))<<"node should be always connected to itself";
				ASSERT_EQ(Graph::k_edgeConnectVal, m_graph->getEdgeValue(x, y))<<"node should be always connected to itself";
			}
			else
			{
				ASSERT_FALSE(m_graph->adjacent(x, y));
				ASSERT_EQ(Graph::k_edgeDisconnectVal, m_graph->getEdgeValue(x, y));
			}
		}
	}

	ASSERT_EQ(0,m_graph->getEdgeCntr());
}

TEST_F(GraphTestFixtureBase, zeroGraphSize)
{
	try{
		Graph graph{0};
		FAIL() << "Expected throw";
	}
	catch(InvalidGraphSizeExcept& err)
	{
		//its OK, don't check message.
		ASSERT_TRUE(true);
	}
    catch(...) {
        FAIL() << "Get unexpected throw";
    }
}

TEST_F(GraphTestFixtureBase, NeighboursTest)
{
	std::vector<edgeConnector>	connection{ {0,1,100},
											{0,2,200},
											{0,3,400},
											{1,3,300}};

	for(const auto& el :  connection)
	{
		EXPECT_TRUE(m_graph->setEdgeValue(std::get<0>(el), std::get<1>(el), std::get<2>(el)));
	}

	const auto neighbors0 = m_graph->getNeighbors(0);
	const auto neighbors1 = m_graph->getNeighbors(1);
	const auto neighbors2 = m_graph->getNeighbors(2);
	const auto neighbors3 = m_graph->getNeighbors(3);

	std::vector<Node>neighbors0Expected {1,2,3};
	std::vector<Node>neighbors1Expected {0,3};
	std::vector<Node>neighbors2Expected {0};
	std::vector<Node>neighbors3Expected {0,1};

	ASSERT_EQ( neighbors0, neighbors0Expected );
	ASSERT_EQ( neighbors1, neighbors1Expected );
	ASSERT_EQ( neighbors2, neighbors2Expected );
	ASSERT_EQ( neighbors3, neighbors3Expected );
}

//--------------------------------------
class GraphTestParametrizedTestFixture1: public GraphTestFixtureBase,
										 public testing::WithParamInterface<pairs>
{};

INSTANTIATE_TEST_SUITE_P(ConnectionsDiagonal,
						 GraphTestParametrizedTestFixture1,
						 testing::ValuesIn( std::vector<pairs>{ {0,0},
															    {1,1},
																{2,2},
																{GraphTestFixtureBase::k_size-1,GraphTestFixtureBase::k_size-1}}) );

INSTANTIATE_TEST_SUITE_P(ConnectionsOutDiagonal,
						 GraphTestParametrizedTestFixture1,
						 testing::ValuesIn( std::vector<pairs>{ {0,1},
															    {1,0},
																{2,0},
																{0,2},
																{GraphTestFixtureBase::k_size-2,GraphTestFixtureBase::k_size-1},
								 	 	 	 	 	 	 	 	{GraphTestFixtureBase::k_size-1,GraphTestFixtureBase::k_size-2}}) );

TEST_P(GraphTestParametrizedTestFixture1, adjacentTest) {
	pairs param = GetParam();

	if(param.first == param.second)
	{
		ASSERT_TRUE(m_graph->adjacent(param.first, param.second));
	}
	else
	{
		ASSERT_FALSE(m_graph->adjacent(param.first, param.second));
	}
}
//--------------------------------------
class GraphTestParametrizedTestFixture2: public GraphTestFixtureBase,
										 public testing::WithParamInterface<edgeConnector>
{};

INSTANTIATE_TEST_SUITE_P(ConnectionsDiagonal,
						 GraphTestParametrizedTestFixture2,
						 testing::ValuesIn( std::vector<edgeConnector>{ {0,0,100},
															    		{1,1,101},
																		{2,2,102},
																		{GraphTestFixtureBase::k_size-1,GraphTestFixtureBase::k_size-1, 104}}) );
INSTANTIATE_TEST_SUITE_P(ConnectionsOutDiagonal,
						 GraphTestParametrizedTestFixture2,
						 testing::ValuesIn( std::vector<edgeConnector>{ {0,1,100},
															    		{1,0,101},
																		{2,0,102},
																		{GraphTestFixtureBase::k_size-2,GraphTestFixtureBase::k_size-1, 104}}) );

TEST_P(GraphTestParametrizedTestFixture2, edgeTest) {
	edgeConnector param = GetParam();

	if(std::get<0>(param) == std::get<1>(param))
	{
		ASSERT_FALSE(m_graph->setEdgeValue(std::get<0>(param), std::get<1>(param), std::get<2>(param)));
	}
	else
	{
		ASSERT_TRUE(m_graph->setEdgeValue(std::get<0>(param), std::get<1>(param), std::get<2>(param)));
		ASSERT_EQ(m_graph->getEdgeValue(std::get<0>(param), std::get<1>(param)),std::get<2>(param));
	}
}
