### Development Log

## Week 1

# April 13th

- **mlian5**

- **Uploaded temporary code for reading files, the template MakeFile, the catch files, and the test files**

## Week 2

# April 17th 

- **mlian5**

- **Refactored Graph.cpp and Graph.h into src directory**

- **Worked on generating hashmap from airports.dat**

__The issue behind this was that we were processing a massive data file for two or three pieces of data per line__
__o circumvent this issue, we decided to parse the data into separate files, namely Airports.txt and Routes.txt__

- **Uploaded and tested the hashmap.**

- **Uploaded Utility class FileParser for writing Airports.txt and Routes.txt**

# April 19th

- **mlian5**

- **Continued building and testing fileparser** 

- **Uploaded Routes.txt and Airports.txt into flightData directory**

# April 20th

- **rtm4 (emailed)** 

- **Redesigned Graphs.cpp and Graphs.h to accompany parsing Airports.txt instead of airports.dat, same for routes.**

- **Wrote test cases to test hashmap was generated correctly based on Airports.txt**

- **Implement adjacency matrix in Graph.cpp and Graph.h**

***Issue: Segmentation Fault!!!***

__The issue that occurred with this is that when we generated a hashmap, there were numerous airports without IATA codes and we wrote our own unique identifiers for each airport. The way we implemented the unique identifier is we incremented everytime we parsed a different airports, which resulted in us trying to access indices outside the size of the adjacency matrix.__

**Rewrote fileParser to parse airports that have IATA codes and eliminate those that do not**

**Wrote multiple test cases to test Adjacency Matrix with different edge sizes**

## Week 3

# April 29th

- **mlian5**

- **Implemented BFS class and added additional methods to Graph Class to accommodate certain changes.**

- **Wrote light test cases to test BFS traversal method**

- **Encountered Segmentation fault due to unimplemented hash table for toy data**

## Week 4

# May 1st 

- **mlian5**

- **Worked on test cases for BFS traversal. Considered more edge cases such as cycles or cyclic graphs.**

- **Also considered cases in which there were no paths from source to destination airport to ensure the program terminated 

# May 4th

- **ghk3**

- **Emailed optimized code for Dijkstra's implementation using priority queue**

- **Emailed addititonal features built into the UI**

- **Added additional test cases**

# May 8th 

- **rtm4**

- **Emailed AStar class to avoid issues with having to merge projects**

- **Designed and implemented test case for A* Pathfinding**

- **Finished implementing longitude and latitude map. Also finished debugging previous function for calculating distance via haversine**

# May 9th

- **rtm4**

- **Finished implementation of AStar class**

- **Implemented additional features in the UI and additional features**

## Week 5

# May 10th

- **ghk3**

- **Worked on README documentation and adding information for building and running the project on linux**