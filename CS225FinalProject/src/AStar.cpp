#include "AStar.h"

AStar::AStar(Graph * graph){

    AStar_graph = graph;

    vector<bool> temp(graph->getSize(), false);

    completed = temp;

    vector<pair<int, int>> temp_1(graph->getSize(), make_pair(-1, INFN));

    weight_paths = temp_1;

}

vector<int> AStar::AStar_Traversal(unsigned src, unsigned des, vector<int> * h_costs){

    //Must use a priority queue to store the open list

    priority_queue<Node, vector<Node>, greater<Node>> AStar_queue;
    
    //Initialzie the first node and push it into the queue.

    unsigned graph_size = AStar_graph->getSize();

    Node start(src, src, 0, 0);

    weight_paths[src].second = 0;

    AStar_queue.push(start);

    while(AStar_queue.size() > 0){

        Node curr_node = AStar_queue.top();

        unsigned curr_idx = curr_node.n2;

        unsigned parent_idx = curr_node.n1;

        completed[curr_idx] = true; //Set completed for this node to be true.
        
        weight_paths[curr_idx].first = parent_idx; //Set the current node's parent
        
        AStar_queue.pop();

        //Check if we meet the end
        if(curr_idx == des){
            break;
        }

        for(unsigned i = 0; i < graph_size; i++){

            if(AStar_graph->IsConnected(curr_idx, i) && !completed[i]){
                
                int gcost_ = AStar_graph->getEdgeWeight(curr_idx, i) + weight_paths[curr_idx].second;

                if(gcost_ < weight_paths[i].second){

                    //Set the g cost of the current node to the g cost of the parent node plus the edge weight
                    weight_paths[i].second = gcost_;

                    int hcost_ = h_costs->at(i);

                    Node next_node(curr_idx, i, gcost_, hcost_);

                    AStar_queue.push(next_node);

                }

            }

        }

    }
    vector<int> result_path;
    //Check condition if destination hasn't been met
    if(weight_paths[des].first == -1){

        return result_path;

    }

    unsigned curr_idx = des;

    result_path.push_back(curr_idx);

    while(curr_idx != src){

        curr_idx = weight_paths[curr_idx].first; //Set current index to parent

        result_path.push_back(curr_idx);

    }

    reverse(result_path.begin(), result_path.end());

    return result_path;

}

vector<int> AStar::AStar_Traversal(unsigned src, unsigned des){

    //Must use a priority queue to store the open list

    priority_queue<Node, vector<Node>, greater<Node>> AStar_queue;
    
    //Initialzie the first node and push it into the queue.

    unsigned graph_size = AStar_graph->getSize();

    Node start(src, src, 0, 0);

    weight_paths[src].second = 0;

    AStar_queue.push(start);

    while(AStar_queue.size() > 0){

        Node curr_node = AStar_queue.top();

        unsigned curr_idx = curr_node.n2;

        completed[curr_idx] = true; //Set completed for this node to be true.
        
        AStar_queue.pop();

        //Check if we meet the end
        if(curr_idx == des){
            break;
        }

        for(unsigned i = 0; i < graph_size; i++){

            if(AStar_graph->IsConnected(curr_idx, i) && !completed[i]){
                
                int gcost_ = AStar_graph->getEdgeWeight(curr_idx, i) + weight_paths[curr_idx].second;

                if(gcost_ < weight_paths[i].second){

                    //Set the g cost of the current node to the g cost of the parent node plus the edge weight
                    weight_paths[i].second = gcost_;

                    weight_paths[i].first = curr_idx; 

                    int hcost_ = AStar_graph->CalculateDistance(i, des);

                    Node next_node(curr_idx, i, gcost_, hcost_);

                    AStar_queue.push(next_node);

                }

            }

        }

    }
    vector<int> result_path;
    //Check condition if destination hasn't been met
    if(weight_paths[des].first == -1){

        return result_path;

    }

    unsigned curr_idx = des;

    result_path.push_back(curr_idx);

    while(curr_idx != src){

        curr_idx = weight_paths[curr_idx].first; //Set current index to parent

        result_path.push_back(curr_idx);

    }

    reverse(result_path.begin(), result_path.end());

    return result_path;

}

unsigned AStar::Distance_Travelled(unsigned dest){

    return weight_paths[dest].second; //Return the G cost of the final destination

}