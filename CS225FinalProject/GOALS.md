# Final Project Proposal (gtk3-mlian5-rtm4)

## Leading Question:

### The leading goal of this final project will be to implement a shortest-distance finder between to airports using flightpath datasets including routes and airports. What we can learn from this dataset is how to be able to extract useful information to design valuable tools to help us perform traversals on this graph such as the latitude and longitude coordinates of airports to calculate relative distances between the two. 

### The specific problem we are trying to solve involves calculating the amount of airports needed to traval the minimum distance between two airports. 

## Dataset Acquisition and Processing:

### The datatsets we will be using to solve this leading question will be the routes and airports dataset from https://openflights.org/data.html. 

### These two datasets will be in csv format and will have to be processed in our codebase to extract valuable information. For the routes dataset, we will extract the source airport and destination airport to create the set of edges on the graph and we will use the airports dataset to extract the coordinates of each airport to calculate the distance between airports. Using these two datasets, we will parse the data and convert into a directed graph. If the dataset has errors or missing entries, we will circumvent these issues by substituting in temporary entries to avoid issues with our graph traversals. 

## Graph Algorithms:

### The graph data algorithm we will use are shortest path algorithms: i.e. Dijkstra's and A* search algorithm. A * search is a heuristic algorithmt hat calculates a cost for traversing down a node by summing the distances between the previous node and current node and the distance between the current node and the destination node. 

### For the pathfinding algorithms, the parameters we will pass in is the starting airport and the destination airport and the outputs will some sort of list, such as a vector, to indicate the routes taken for the shortest path. For breadth-first search, we will also be passing in the source and destination airports. However, the output will be a list containing the least number of routes/flights taken to travel from source to destination airports. Our runtimes for these algorithms are projected to be O(n) where n is the number of nodes in the graph.

## TimeLine: 

### The Timeline of this project can be broken into three main components as specified in the contract: Process the data into a graph, design pathfinding and traversal algorithms, and buidling the test cases. The overall structure of the timeline can be broken down into subtasks as state below:

1. Have a working MakeFile and import all necessary files (datasets):
    - Projected due date: 4/11-4/13
2. Processing the csv files into a working graph structure:
    - Projected due date: 4/16-4/17
3. Finishing the Breadth-First search algorithm and implementing test cases:
    - Projected due date: 4/23-4/25
4. Finishing Djikstras and A* search algorithm and implementing: 
    - Projected due date: 5/1 - 5/8
    