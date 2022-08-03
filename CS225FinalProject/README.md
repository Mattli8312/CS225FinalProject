# Openflight Traversals and Algorithms &middot; [![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github-dev.cs.illinois.edu/cs225-sp21/ghk3-mlian5-rtm4/blob/master/LICENSE)

For our final project, we utilized the OpenFlights API found at [https://openflights.org/data.html](https://openflights.org/data.html), specifically using the **airports.dat** file, which stores 
IATA codes and the longitude and latitude coordinates of those airports, and the **routes.dat**, which stores the source and
destination routes between the various airports. 

The purpose of this program is to generate a graphical data structure given the series of airports and routes provided by the OpenFlights API and perform various pathfinding algorithms and traversals on them (BFS, Dijkstra, and A*). 

### Team members: Graham Kingston (ghk3), Matthew Lian (mlian5), Ryan Metzger (rtm4)

## Build the Project and all Necessary data files

To run this project on linux, make sure to use the following commands in the main directory:
```
$cd ghk3-mlian5-rtm4/
$make
$./finalproj
```

## Running testcases

To run testcases on linux, make sure to use the following commands in the main directory:
```
$make test
$./test
```

### Testcase descriptions:

The testcases tested various things such as 

* Hashmap Data Structure
	* The Hashmap data structure contains IATA keys mapped to indices on the Adjacency Matrix
	* To test we were generating a viable hash map, we checked to make sure certain IATA keys mapped to the correct indices on the matrix
* Adjacency Matrix
	* To test the Adjacency Matrix, we set a variable amount of edges and made sure that the matrix at row (source index) and col (des index) were connected
* Coordinate Mapper
	* Used Distance helper function and checked to make sure longitude and latitude pairs were correctly parsed
* BFS
	* Ran BFS on various test cases:
	* First tested with simply acyclic graph
	* Started testing on complex directed graphs with cycles or no end paths
* Dijkstra
	* Based graphs from online examples and ran Dijkstra on those graphs
* AStar
	* Giant testcase based on an online example graph with predetermined h costs. 

## Debugging
In the event that an error occurs, specifically a message "Can't open Airports.txt file: Use FileParser to generate txt"
pops up when the program is ran, make sure you have **Airports.txt** and **Routes.txt** in your flightData directory.
You can uncomment the following piece of code below found in **main.cpp** to generate the necessary files.

```cpp
int main(){
	...
	FileParser parser;
	parser.WriteAirportData("flightData/airports.dat");
	parser.WriteRouteData("flightData/routes.dat");
	...
}
```

## Project Commands

After executing `./finalproj` in the terminal, a command prompt like this will appear in the terminal
```
"Welcome to the flightpath simulator!!"
"This UI contains features that enables you to generate a series of routes"
"from a source and a destination airport around the world!"
"To start this UI, type on the keyboard"
"To open the menu of commands, type menu on the keyboard"
"To terminate the simulator, type exit on the keyboard"
"Command: "
```

To see the display of commands used for this UI, type in **menu** and a series of commands below will pop up
```
"The list of commands are as follows:"
	"l_p: Least paths implements the breadth first search traversal on the flights graph"
	"		- After typing in the IATA code of the source and destination airport, you can"
	"		  type in l_p right after to indicate you will implement BFS on the graph."
	"l_d_djk: Least Distance Djikstra implements the Djikstra pathfinding on the flights graph"
	"		- After typing in the IATA code of the source and destination airport, you can"
	"		  type in l_d_djk right after to indicate you will implement Djikstra's on the graph."
	"l_d_a*: Least Distance A* implements the A* pathfinding on the flights graph"
	"		- After typing in the IATA code of the source and destination airport, you can"
	"		  type in l_d_a* right after to indicate you will implement A* on the graph."
	"l_all: Prints out all paths implemented by BFS, Dijkstra, and AStar and displays information about that path."
	"		- After typing in the IATA code of the source and destination airport, you can"
	"		  type in l_all right after to indicate you will implement all three algorithms."
	"exit: enables you to exit the simulator. You are able to do this at any point before and after the graph traversal."
	"		  type in exit right after to indicate you will exit the simulator."
	"start: enables you to start the simulator. This should be your initial command"
	"		  type in start right after to indicate you will start the simulator."
```

To start the simulator, type in **start** and a prompt will ask you to type in the source airport and destination airport
IATA code alongside a third command, which specifies the algorithm(s) you will be implementing on the graph 

To find the minimum number of routes needed in order to travel from a source to destination airport, you would
use ```l_p```. For instance, if you wanted to find the minimum paths needed from GKA and YBF, you would type in the following

``` $GKA YBF l_p ```

To find the routes needed to travel the minimum distance between a source and destination airport, you would
use ```l_d_djk``` to implement Dijkstra's approach and ```l_d_a*``` to implement A*'s approach like below.

``` $GKA YBF l_d_djk ```

``` $GKA YBF l_d_a* ```

Finally, to list the result of all approaches, simply use ```l_all```. 

### Final Presentation Link

https://youtu.be/nor2q5sUvV0