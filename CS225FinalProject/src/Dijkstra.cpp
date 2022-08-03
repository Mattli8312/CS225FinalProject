#include "Dijkstra.h"

Dijkstra::Dijkstra(Graph * graph){
    
    Dijkstra_graph = graph;

    //Initialize parent_nodes to -1 to indicate no known path between any other nodes
    //In the graph
    vector<pair<int,int>> temp(Dijkstra_graph->getSize(), make_pair(-1, 0));

    weight_paths = temp;

}
vector<int> Dijkstra::Dijkstra_Traversal(unsigned src, unsigned dest){

    priority_queue<Node, vector<Node>, greater<Node>> Dijkstra_Queue;

    Dijkstra_Queue.push(Node(src, src, 0));

    unsigned graph_size = Dijkstra_graph->getSize();

    vector<bool> completed(graph_size, false);

    while(Dijkstra_Queue.size() >  0){

        Node curr_ = Dijkstra_Queue.top(); //Points to current node

        Dijkstra_Queue.pop();

        unsigned curr_idx = curr_.n2;

        if(completed[curr_idx]) continue;

        weight_paths[curr_idx].first = curr_.n1;

        weight_paths[curr_idx].second = curr_.weight;

        for(unsigned i = 0; i < graph_size; i++){

            if(Dijkstra_graph->IsConnected(curr_idx, i) && !completed[i]){

                Dijkstra_Queue.push(Node(curr_idx, i, weight_paths[curr_idx].second + Dijkstra_graph->getEdgeWeight(curr_idx, i)));

            }

        }

        completed[curr_idx] = true; //Signify that we are finished with this node

    }

    //After populating the weight_paths, we must backtrack

    vector<int> result_path;

    int curr_node = dest;

    if(weight_paths[curr_node].first == -1){

        return result_path;

    }

    while(curr_node != (int)src){

        curr_node = weight_paths[curr_node].first;

        result_path.push_back(curr_node);

    }
    
    reverse(result_path.begin(), result_path.end());

    result_path.push_back(dest);

    return result_path;

}

unsigned Dijkstra::Distance_Travelled(unsigned dest){

    //Sum all of the weights of each edge

    return weight_paths[dest].second;

}