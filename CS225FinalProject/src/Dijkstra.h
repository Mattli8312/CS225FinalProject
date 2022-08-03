#pragma once
#include "Graph.h"
#include <queue>

using namespace std;

/**
 * Djikstra class will be used to process the routes needed to travel  
 * the minimum distance between the source and destination airport.
 * This, alongside A* pathfinding will play an important role in the UI
 * feature for the users, specifically, the feature that allows the user
 * to calculate the paths to travel the minimum distance between the source
 * and destination airport. 
 **/
class Dijkstra{
    public:
        /**
         * Instead of using the lazy approach, we will be implementing Djikstra's 
         * with a priority Queue. THis Node struct will help with that
         **/
        struct Node{
            public: 
                /**
                 * Default constructor. Used to initialize node to empty 
                 **/
                Node(){
                    n1 = -1;
                    n2 = -1;
                    weight = -1;
                }
                /**
                 * Custom constructor used to 
                 * @param n_1 source index
                 * @param n_2 destination index
                 * @param w weight of the path between the source and destination
                 * */
                Node(unsigned n_1, unsigned n_2, int w){
                    n1 = n_1;
                    n2 = n_2;
                    weight = w;
                }
                /**
                 * Operator overload: use by Priority Queue to generate the minheap
                 * @param other Reference to another Node we are comparing against
                 **/
                bool operator > (const Node & other) const{
                    return weight > other.weight;
                }
                unsigned n1, n2;
                int weight;
        };
        /**
         *Custom constructor in which the user passes in a pointer to the
         * graph structure we will perform Djiksta's algorithm on
         * @param graph An address to the graph structure we will perform
         * Djiksta's on
         **/
        Dijkstra(Graph * graph);
        /**
         * Actual BFS traversal which returns a vector of airports to traverse
         * @param src integer index for source airport
         * @param dest integer index for destination airport
         * @return returns a vector of integers associated with the airports traversed
         **/
        vector<int> Dijkstra_Traversal(unsigned src, unsigned dest);
        /**
         * Helper function used to calculate and return the total distance travelled 
         * Through this path
         * @param dest Used to grab the destination index 
         **/
        unsigned Distance_Travelled(unsigned dest);
    private:
        /**
         *Pointer to a graph to analyze with Djiksta's pathfinding algorithm 
         **/
        Graph * Dijkstra_graph;
        /**
         * Used to backtrack from the path and store the parent with the 
         * minimum distance from the current node to that parent node.
         * The value is used to store the minimum weighted path and the key is used to store the 
         * parent index, i.e. the index connected to the incoming edge for the index in the vector
         **/
        vector<pair<int, int>> weight_paths;
};