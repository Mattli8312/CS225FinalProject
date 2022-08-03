#include "BFS.h"

BFS::BFS(Graph * graph){

    BFS_graph = graph;

    BFS_distance = 0;

}

vector<int> BFS::BFS_Traversal(unsigned src, unsigned dest){

    unsigned graph_size = BFS_graph->getSize();

    BFS_distance = 0;

    vector<bool> visited(graph_size, false);

    BFS_queue.push(vector<int>(1, src));

    visited[src] = true;

    while(!BFS_queue.empty()){

        vector<int> curr_ = BFS_queue.front();

        unsigned curr_src = curr_.back();
        
        visited[curr_src] = true;

        BFS_queue.pop();

        for(unsigned i = 0; i < graph_size; i++){

            if(BFS_graph->IsConnected(curr_src, i) && !visited[i]){

                vector<int> next_ = curr_;

                next_.push_back(i);

                BFS_queue.push(next_);

                if(i == dest){

                    for(unsigned i = 0; i < next_.size() - 1; i++){

                        /*Parse the total distance*/

                        BFS_distance += BFS_graph->getEdgeWeight(next_[i], next_[i+1]);

                    }   

                    return next_;

                }

            }

        }   

    }

    vector<int> result(0, -1);

    return result;    

}

unsigned BFS::Distance_Travelled(){

    return BFS_distance;

}