#include <string>
#include <vector>

#include "../catch/catch.hpp"
#include "../src/Graph.h"
#include "../src/BFS.h"
#include "../src/Dijkstra.h"
#include "../src/AStar.h"


TEST_CASE("Test Vertex HashMap"){
	Graph test_1;
	test_1.FillDictionary("flightData/Airports.txt");

	int result1 = test_1.GetDictionaryData("YAM");
	int result2 = test_1.GetDictionaryData("YDB");
	int result3 = test_1.GetDictionaryData("THF");
	int result4 = test_1.GetDictionaryData("SOU");

	REQUIRE(result1 == 20);
	REQUIRE(result2 == 40);
	REQUIRE(result3 == 300);
	REQUIRE(result4 == 400);
}

TEST_CASE("Test Adjacency Matrix 1: 200 edges"){
	Graph test_2;
	test_2.FillDictionary("flightData/Airports.txt");
	test_2.GenerateMatrix(200);

	//Test Lower bounds
	int src0 = test_2.GetDictionaryData("AER"), dest0 = test_2.GetDictionaryData("KZN");
	int src1 = test_2.GetDictionaryData("LED"), dest1 = test_2.GetDictionaryData("UUA");
	
	bool res0 = test_2.IsConnected(src0 , dest0); REQUIRE(res0 == true);
	bool res1 = test_2.IsConnected(src1 , dest1); REQUIRE(res1 == true);

	//Test Upper bounds

	int src3 = test_2.GetDictionaryData("MNL"), dest3 = test_2.GetDictionaryData("LGP");
	int src4 = test_2.GetDictionaryData("MNL"), dest4 = test_2.GetDictionaryData("KLO");

	bool res3 = test_2.IsConnected(src3, dest3); REQUIRE(res3 == true);
	bool res4 = test_2.IsConnected(src4, dest4); REQUIRE(res4 == true);

	//Test Outside bounds

	src0 = test_2.GetDictionaryData("PPS"), dest0 = test_2.GetDictionaryData("MNL");
	res0 = test_2.IsConnected(src0, dest0); REQUIRE(res0 == false);
}

TEST_CASE("Test Adjacency Matrix 2: 1000 edges"){
	Graph test_3;
	test_3.FillDictionary("flightData/Airports.txt");
	test_3.GenerateMatrix(1000);
	
	//Test Lower bounds
	int src0 = test_3.GetDictionaryData("AER"), dest0 = test_3.GetDictionaryData("KZN");
	int src1 = test_3.GetDictionaryData("LED"), dest1 = test_3.GetDictionaryData("UUA");

	bool res0 = test_3.IsConnected(src0 , dest0); REQUIRE(res0 == true);
	bool res1 = test_3.IsConnected(src1 , dest1); REQUIRE(res1 == true);

	//Test Upper bounds

	int src3 = test_3.GetDictionaryData("PPS"), dest3 = test_3.GetDictionaryData("MNL");
	int src4 = test_3.GetDictionaryData("TLV"), dest4 = test_3.GetDictionaryData("CAI");

	bool res3 = test_3.IsConnected(src3, dest3); REQUIRE(res3 == true);
	bool res4 = test_3.IsConnected(src4, dest4); REQUIRE(res4 == true);

	//Test Outside bounds

	src0 = test_3.GetDictionaryData("VKO"), dest0 = test_3.GetDictionaryData("UCT");
	res0 = test_3.IsConnected(src0, dest0); REQUIRE(res0 == false);
}

/**
 * Test BFS on smaller Graph: 4 nodes
 * 0 --- > 1 
 * |
 * |
 * V
 * 2 --- > 3
 **/

TEST_CASE("Test BFS on smaller Graph: 4 nodes"){
	Graph test_4(4);
	test_4.SetEdge(0,1,1);
	test_4.SetEdge(0,2,1);
	test_4.SetEdge(2,3,1);

	BFS bfs_4(&test_4);
	std::vector<int> result_4 = bfs_4.BFS_Traversal(0, 3);
	std::vector<int> expected_4{0, 2, 3};
	for(unsigned i = 0; i < result_4.size(); i++){
		REQUIRE(result_4[i] == expected_4[i]);
	}
}

/**
 * Test BFS on graph with cycles
 * 0 --> 2 --> 5 --> 7 --> 8
 * |	 ^				  ^
 * V	 |				/
 * 1-- > 3 --> 4 --> 6
 **/
TEST_CASE("Test BFS on graph with a cycle: 9 nodes"){
	Graph test_5(9);
	test_5.SetEdge(0, 1, 1); test_5.SetEdge(0,2, 1);
	test_5.SetEdge(1, 3, 1); test_5.SetEdge(3,2, 1);
	test_5.SetEdge(2, 5, 1); test_5.SetEdge(5,7, 1);
	test_5.SetEdge(7, 8, 1); test_5.SetEdge(3,4, 1);
	test_5.SetEdge(4, 6, 1); test_5.SetEdge(6,8, 1);

	BFS bfs_5(&test_5);
	std::vector<int> result_5 = bfs_5.BFS_Traversal(0, 8);
	std::vector<int> expected_5{0,2,5,7,8};
	for(unsigned i = 0; i < result_5.size(); i++){
		REQUIRE(result_5[i] == expected_5[i]);
	}
}

/**
 * Test BFS on complex graph with various cycles
 **/

TEST_CASE("Test BFS on complex graph: 12 nodes 20 edges"){
	Graph test_6(12);
	unsigned int src_idx[20] = {0,0,0,1,2,2,2,2,3,4,4,5,5,6,7,7,8,9,10};
	unsigned int des_idx[20] = {1,2,3,4,1,4,5,3,6,9,5,7,8,5,10,11,11,10,11};

	for(unsigned int i = 0; i < 20; i++){
		test_6.SetEdge(src_idx[i], des_idx[i], 1);
	}

	BFS bfs_6(&test_6);
	std::vector<int> result_6 = bfs_6.BFS_Traversal(0,11);
	std::vector<int> expected_6{0,2,5,7,11};
	for(unsigned i = 0; i < result_6.size(); i++){
		REQUIRE(result_6[i] == expected_6[i]);
	}
}

TEST_CASE("Test Dijkstra on a simple graph: 5 nodes 8 weighted edges"){

	Graph test_7(5);
	unsigned int src_idx[8] = {0,0,0,1,1,2,2,3};
	unsigned int des_idx[8] = {1,2,4,3,4,1,4,4};
	int weights[8] = {1,5,12,2,7,4,3,3};
	
	for(unsigned int i = 0; i < 8; i++){
		test_7.SetEdge(src_idx[i], des_idx[i], weights[i]);
	}

	Dijkstra djk_7(&test_7);
	std::vector<int> result_7 = djk_7.Dijkstra_Traversal(0, 4);
	std::vector<int> expected_7 = {0,1,3,4};
	for(unsigned i = 0; i < expected_7.size(); i++){
		REQUIRE(result_7[i] == expected_7[i]);
	}
}

TEST_CASE("Test Dijkstra on a more complex graph: "){

	Graph test_8(8);
	unsigned int src_idx[15] = {0,0,1,2,3,4,4,5,5,5,6,6,6,7,7};
	unsigned int des_idx[15] = {2,4,3,7,6,5,7,4,7,1,2,0,4,5,3};
	int weights[15] = {26,38,29,34,52,35,37,35,28,32,40,58,93,28,39};

	for(unsigned i = 0; i < 15; i++){
		test_8.SetEdge(src_idx[i], des_idx[i], weights[i]);
	}

	Dijkstra djk_8(&test_8);
	std::vector<int> result_8 = djk_8.Dijkstra_Traversal(0, 6);
	std::vector<int> expected_8 = {0,2,7,3,6};
}

TEST_CASE("Test Dijkstra on a graph without a solution between two nodes:"){
	Graph test_9(6);
	//A B C D E F
	//0 1 2 3 4 5
	unsigned int src_idx[11] = {0,0,1,1,1,2,2,3,4,4,5};
	unsigned int des_idx[11] = {4,5,0,3,2,4,3,4,0,5,3};
	int weights[11] = {10, 90, 30, 40, 30, 60, 40, 100, 55, 45, 100};

	for(unsigned i = 0; i < 11; i++){
		test_9.SetEdge(src_idx[i], des_idx[i], weights[i]);
	}

	Dijkstra djk_9(&test_9);
	std::vector<int> result_9 = djk_9.Dijkstra_Traversal(0,1);
	REQUIRE(result_9.empty());
}

TEST_CASE("Test A Star on an undirected weighted graph with 16 nodes: from src 0 to des 15 "){
	Graph test_10(16);
	//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
	//A B C D E F G H I J K  L  M  N  O  P
	unsigned int src_idx_1[16] = {0,0,1,1,1,2,2,2,2,2,3,3,3,3,3,3};
	unsigned int des_idx_1[16] = {1,2,0,2,3,0,1,3,4,7,1,2,7,10,11,12};
	int 		 weights_1[16] = {5,5,5,4,3,5,4,7,7,8,3,7,11,16,13,14};
	
	unsigned int src_idx_2[16] = {4,4,4,5,5,6,6 ,7,7 ,7,7,8,8,9,9,9};
	unsigned int des_idx_2[16] = {2,5,7,4,6,5,13,2,3 ,4,8,7,9,8,13,15};
	int 		 weights_2[16] = {7,4,5,4,9,9,12,8,11,5,3,3,4,4,3,8};
	
	unsigned int src_idx_3[22] = {10,10,10,10,11,11,11,11,12,12,12,13,13,13,13,14,14,15,15,15};
	unsigned int des_idx_3[22] = { 3,11,13,15, 3,10,12,14, 3,11,14, 6, 9,10,15,11,12, 9,10,13};
	int 		 weights_3[22] = {16, 5, 7, 4,13, 5, 9, 4,14, 9, 5,12, 3, 7, 7, 4, 3, 8, 4, 7};

	vector<int> h_costs{16,17,13,16,16,20,17,11,10,8,4,7,10,7,5,0};

	for(unsigned i = 0; i < 16; i++){
		test_10.SetEdge(src_idx_1[i], des_idx_1[i], weights_1[i]);
		test_10.SetEdge(src_idx_2[i], des_idx_2[i], weights_2[i]);
	}

	for(unsigned i = 0; i < 22; i++){
		test_10.SetEdge(src_idx_3[i], des_idx_3[i], weights_3[i]);
	}

	
	AStar ast_10(&test_10);
	std::vector<int> result_10 = ast_10.AStar_Traversal(0, 15, &h_costs);
	std::vector<int> expected_10{0,2,7,8,9,15};
	for(unsigned i = 0; i < result_10.size(); i++){
		REQUIRE(result_10[i] == expected_10[i]);
	}
}

TEST_CASE("Test coordinate mapper: Ensure every point has correct longitude and latitude"){
	Graph test_11;
	test_11.FillDictionary("flightData/Airports.txt");

	pair<double, double> rkv = test_11.getCoordinates("RKV");
	REQUIRE(rkv.second > 64); REQUIRE(rkv.second < 65);
	REQUIRE(rkv.first > -22); REQUIRE(rkv.first < -21);
	
	pair<double, double> yvo = test_11.getCoordinates("YVO");
	REQUIRE(yvo.second > 48); REQUIRE(yvo.second < 49);
	REQUIRE(yvo.first > -78); REQUIRE(yvo.first < -77);

	pair<double, double> mvd = test_11.getCoordinates("MVD");
	REQUIRE(mvd.second > -35); REQUIRE(mvd.second < -34);
	REQUIRE(mvd.first > -57); REQUIRE(mvd.first < -56);
}