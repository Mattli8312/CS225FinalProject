#pragma once
#include <queue>
#include "Graph.h"

using namespace std;

/**
 * BFS will be implemented on the graph class to implement a level-order
 * traversal on the graph.
 * */

class BFS{
    public:
        /**
         * Custom constructor which takes a pointer to
         * a graph as a parameter
         *@param graph Pointer to the Graph object
         **/
        BFS(Graph * graph);
        /**
         * Actual BFS traversal which returns a vector of airports to traverse
         * @param src integer index for source airport
         * @param dest integer index for destination airport
         * @return returns a vector of integers associated with the airports traversed
         **/
        vector<int> BFS_Traversal(unsigned src, unsigned dest);
        /**
         * Helper function used to calculate and return the total distance travelled 
         * Through this path
         **/
        unsigned Distance_Travelled();

    private:
        /**
         * Stores a pointer to a graph to implement the 
         * BFS traversal on
         **/
        Graph * BFS_graph;
        /**
         * Queue used for the 
         * BFS traversal
         **/
        queue<vector<int>> BFS_queue;
        /**
         * Used to store the total distance travelled 
         **/
        unsigned BFS_distance;
};