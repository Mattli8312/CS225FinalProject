#pragma once
#include "Graph.h"
#include <queue>
#define INFN 100000

using namespace std;

/**
 * AStar is a heuristic-based pathfinding algorithm similar to Dijkstra's pathfinding algorithm
 * The heuristic algorithm used for this project is known as the f cost (f(x)) which is the sum of the 
 * g cost plus the h cost. The g cost is the cost of moving to a certain point from the starting point
 * and the h cost is the cost of moving to a certain point from the destination. i.e. the G cost is the distance from
 * the node we are traversing to the starting point and the h cost is the distance fronm that node to the 
 * final destination.
 * */

class AStar{
    /**
     * Similar to Djikstra's approach, we will be implementing a priority queue
     * to perform the A* search. Hence, we need this struct to populate the priority
     * queue and select the adjacent nodes with the smallest f cost. 
     **/
    struct Node{
            public: 
                /**
                 * Default constructor. Used to initialize node to empty 
                 **/
                Node(){
                    n1 = -1;
                    n2 = -1;
                    g_cost = -1;
                    h_cost = -1;
                }
                /**
                 * Custom constructor used to 
                 * @param n_1 source index
                 * @param n_2 destination index
                 * @param w weight of the path between the source and destination
                 **/
                Node(unsigned n_1, unsigned n_2, int g_, int h_){
                    n1 = n_1;
                    n2 = n_2;
                    g_cost = g_;
                    h_cost = h_;
                }
                /**
                 * Operator overload: use by Priority Queue to generate the minheap
                 * @param other Reference to another Node we are comparing against
                 **/
                bool operator > (const Node & other) const{
                    return (g_cost + h_cost) > (other.g_cost + other.h_cost);
                }
                //n1 is the parent, n2 is the child
                unsigned n1, n2;
                int g_cost, h_cost;
    };
    public:
        /**
         * Custom constructor which performs AStar on the given graph 
         * @param graph Pointer to the Graph structure we will implement AStar on
         * */
        AStar(Graph * graph);
        /**
         * Function which returns a series of routes needed to travel the 
         * minimum distance between two nodes on a graph
         * @param src unsigned integer for the src idx
         * @param des unsigned integer for the des idx
         * @param h_costs vector of integers containing heuristic h values. Used specifically for test cases
         **/
        vector<int> AStar_Traversal(unsigned src, unsigned des, vector<int> * h_costs);
        /**
         * Function which calculates the total AStar traversal using the euclidean distance
         * as the heuristic of the AStar will be calculated using the calculateDistance
         * function provided by the Graph class
         * @param src source index for the airport
         * @param des destination index for the destination airport
         **/
        vector<int> AStar_Traversal(unsigned src, unsigned des);
        /**
         * Helper function which returns the distance travelled from the destination to the source
         * @param dest destination index for the destination airport
         **/
        unsigned Distance_Travelled(unsigned dest);
    private:
        /**
         * pointer to the graph structure we will be implementing Astar on
         **/
        Graph * AStar_graph;
        /**
         * a vector which stores the nodes that are already completed similar to djikstra
         **/
        vector<bool> completed;
        /**
         * A vector of pairs which stores the parent and the g cost of each 
         * node in the graph. 
         * The index in the vertex is the child node
         **/
        vector<pair<int, int>> weight_paths;
};