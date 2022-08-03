#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>
#include<stdio.h>
#include<iterator>
#include<algorithm>
#include<cmath>

/**
 * Graph Structure which we will implement
 * various traversal and pathfinding algorithms
 * on
 **/
using namespace std;

class Graph{
    public:
        /**default constructor
        */
        Graph();
        /**
         * Custom Constructors which enables people to define the 
         * size of the graph i.e. number of nodes
         * @param size The number of nodes in the graph
         **/
        Graph(unsigned size);
        /**
         *Create an edge between two nodes on the graph
         *@param src an unsigned index to the src node on the graph
         *@param dest an unsigned index to the dest node on the graph
         @param weight an integer representing the weight of an edge
         **/
        void SetEdge(unsigned src, unsigned dest, unsigned weight);
        /**
         * Reading the filename and parsing the data into the hashmap
         * @param filename airports.dat which will be parsed for information including 3-letter IATA code
         **/
        void FillDictionary(const string filename);
        /**
         * Getter for accessing values given certain keys
         * @param key contains the 3-letter IATA code for accessing the value
         * @return returns a value string corresponding to the input key in the map
         **/
        int GetDictionaryData(string key);
        /**
         * Utility function used for printing out all 
         * keys and corresponding indices for VertexDictionary
         **/
        void PrintDictionary(); 
        /**
         * Function used for generating the adjacency matrix with a given
         * number of edges. Parses Routes.txt for data
         * @param edges user defined number of edges in graph
         **/
        void GenerateMatrix(unsigned edges);
        /**
         * Utility function to print the matrix;
         **/
        void PrintMatrix();
        /**
         * Function used for checking whether two airports are
         * connected via the matrix.
         * @param sourceID  index src value for adjacency matrix (Row integer)
         * @param destID index value for adjacency matrix (Column integer)
         **/
        bool IsConnected(unsigned sourceID, unsigned destID);
        /**
         * Getter function to return the number of airports in the
         * graph matrix
         **/
        unsigned getSize();
        /**
         * Getter function which returns
         * The weight of the edge between the src and dest
         * @param src src index on the matrix
         * @param dest dest index on the 
         **/
        int getEdgeWeight(unsigned src, unsigned dest);
        /**
         *Utility function which converts a vector of indices on the grpah  
         *to a list of IATA codes.
         *@param list a ref to the vector of indices
         **/
        vector<string> ConvertToIATA(vector<int> & list);
        /**
         * Helper function which grabs the longitude and latitude coordinates of each airport in the graph. Used for testing
         * @param IATA IATA string which 
         **/
        pair<double, double> getCoordinates(string IATA);
        /**
         * Utility function used to calculate weights between paths, i.e. distance between two airports in kilometers 
         * @param src source index, i.e. source airport from which we are calculating the distance from.
         * @param des destination index, i.e. destination airport from which we are calculating the distance to.
         **/
        unsigned CalculateDistance(unsigned src, unsigned des);
    private:
        /**
         * A Hashmap will allow for us to access each Airports ID 
         * based on the given 3-letter IATA code provided in the airports.dat folder
         * The key will store the 3-letter IATA and the value will store the unique identifier which will be used as an
         * index to the adjacency matrix down below.
         **/
        unordered_map<string, int> VertexDictionary;
        /**
         * An adjacency matrix will be used t represent our graph structure. 
         * This will store unsigned values representing the distance between two respective nodes. In this case, this will
         * be used to represent the distance in kilometers using the utility function (calculateDistance) provided above.
         **/
        vector<vector<unsigned>> AdjacencyMatrix;
        /**
         * A vector used to convert the index value to the 
         * IATA code value. Used to processing the indices in the path
         * back to the IATA code to be displayed to the used*/
        vector<string> IATADictionary;
        /**
         * A vector used to grab every longitude and latitude coordinate of every 
         * index (node) in the adjacency matrix
         **/
        vector<pair<float, float>> Coordinates;
};