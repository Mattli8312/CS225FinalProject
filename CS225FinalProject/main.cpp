#include <iostream>
#include <vector>
#include "src/Graph.h"
#include "src/FileParser.h"
#include "src/Dijkstra.h"
#include "src/BFS.h"
#include "src/AStar.h"
/*Enables coloring of text on the console 
made possible by https://stackoverflow.com/questions/9158150/colored-output-in-c/9158263*/
#define RESET   "\033[0m"		/* White */
#define RED 	"\033[31m"		/* Red */
#define CYAN    "\033[36m"      /* Cyan */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */


void DisplayMenu(){
	cout<<BOLDGREEN<<"The list of commands are as follows:"<<RESET<<endl;
	cout<<"l_p: Least paths implements the breadth first search traversal on the flights graph"<<endl;
	cout<<"		- After typing in the IATA code of the source and destination airport, you can"<<endl;
	cout<<"		  type in"<<BOLDGREEN<<" l_p "<<RESET<<"right after to indicate you will implement BFS on the graph."<<endl;
	cout<<endl;
	cout<<"l_d_djk: Least Distance Djikstra implements the Djikstra pathfinding on the flights graph"<<endl;
	cout<<"		- After typing in the IATA code of the source and destination airport, you can"<<endl;
	cout<<"		  type in"<<BOLDGREEN<<" l_d_djk "<<RESET<<"right after to indicate you will implement Djikstra's on the graph."<<endl;
	cout<<endl;
	cout<<"l_d_a*: Least Distance A* implements the A* pathfinding on the flights graph"<<endl;
	cout<<"		- After typing in the IATA code of the source and destination airport, you can"<<endl;
	cout<<"		  type in"<<BOLDGREEN<<" l_d_a* "<<RESET<<"right after to indicate you will implement A* on the graph."<<endl;
	cout<<endl;
	cout<<"l_all: Prints out all paths implemented by BFS, Dijkstra, and AStar and displays information about that path."<<endl;
	cout<<"		- After typing in the IATA code of the source and destination airport, you can"<<endl;
	cout<<"		  type in"<<BOLDGREEN<<" l_all "<<RESET<<"right after to indicate you will implement all three algorithms."<<endl;
	cout<<endl;
	cout<<"exit: enables you to exit the simulator. You are able to do this at any point before and after the graph traversal."<<endl;
	cout<<"		  type in"<<RED<<" exit "<<RESET<<"right after to indicate you will exit the simulator."<<endl;
	cout<<endl;
	cout<<"start: enables you to start the simulator. This should be your initial command"<<endl;
	cout<<"		  type in"<<BOLDMAGENTA<<" start "<<RESET<<"right after to indicate you will start the simulator."<<endl;
	cout<<endl;
}

void StartSimulation(){
	string src_ = "", des_ = "", path_alg = "";
	string user_input = "";
	cout<<BOLDGREEN<<"Enter the source airport IATA, destination IATA, and the pathfinding algorithm"<<RESET<<endl;
	cout<<"Note. you must separate src, dest, and pathfinding alg with whitespace!"<<endl;
	cin>>src_>>des_>>path_alg;
	// cout<<"source:"<<src_<<endl;
	// cout<<"destination:"<<des_<<endl;
	// cout<<"pathfinding:"<<path_alg<<endl;

	/*initialize graph for traversal
	  Fill hashmap and matrix
	*/
	Graph flightpath; 
	flightpath.FillDictionary("flightData/Airports.txt");
	flightpath.GenerateMatrix(100000); //Set to 100000 temporarily

	unsigned distance_ = 0;
	/*
	First check whether the IATA's are valid.
	*/
	int src_idx = flightpath.GetDictionaryData(src_);
	int des_idx = flightpath.GetDictionaryData(des_);
	if(src_idx < 0 || des_idx < 0){
		cout<<RED<<"Invalid IATA codes:"<<RESET<<" Refer to Airports.txt in the flightData directory for existing IATAs"<<endl;
		return;
	}
	/*
	Then check which pathfinding command the user specified
	*/
	vector<int> resulting_path;
	if(path_alg == "l_p"  || path_alg == "l_all"){
		BFS flightbfs(&flightpath);
		resulting_path = flightbfs.BFS_Traversal((unsigned)src_idx, (unsigned)des_idx);
		distance_ = flightbfs.Distance_Travelled();
		cout<<"The minimum number of routes taken: "<<endl;
		vector<string> IATA_path = flightpath.ConvertToIATA(resulting_path);

		//Print out the IATA_path
		unsigned size_ = IATA_path.size();
		cout<<CYAN;
		for(unsigned i = 0; i < size_; i++){
			cout<<IATA_path[i];
			if(i + 1 != size_)
				cout<<"---->";
		}
		cout<<RESET<<": Distance Travelled: "<< distance_ << " km" << endl;

	}
	if(path_alg == "l_d_djk" || path_alg == "l_all"){
		Dijkstra flightdjk(&flightpath);
		resulting_path = flightdjk.Dijkstra_Traversal((unsigned)src_idx, (unsigned)des_idx);
		distance_ = flightdjk.Distance_Travelled((unsigned)des_idx);
		cout<<"The routes needed to travel the minimum distance using Djikstra:"<<endl;

		vector<string> IATA_path = flightpath.ConvertToIATA(resulting_path);

		//Print out the IATA_path
		unsigned size_ = IATA_path.size();
		cout<<CYAN;
		for(unsigned i = 0; i < size_; i++){
			cout<<IATA_path[i];
			if(i + 1 != size_){
				cout<<"---->";
			}
		}
		cout<<RESET<<": Distance Travelled: "<< distance_ << " km" << endl;
	}
	if(path_alg == "l_d_a*" || path_alg == "l_all"){
		AStar flightastar(&flightpath);
		resulting_path = flightastar.AStar_Traversal((unsigned)src_idx, (unsigned)des_idx);
		distance_ = flightastar.Distance_Travelled((unsigned)des_idx);
		cout<<"The routes needed to travel the minimum distance using A*:"<<endl;

		vector<string> IATA_path = flightpath.ConvertToIATA(resulting_path);

		//Print out the IATA_path
		unsigned size_ = IATA_path.size();
		cout<<CYAN;
		for(unsigned i = 0; i < size_; i++){
			cout<<IATA_path[i];
			if(i + 1 != size_){
				cout<<"---->";
			}
		}
		cout<<RESET<<": Distance Travelled: "<<  distance_ << " km" <<endl;
	}
	if(path_alg != "l_p" && path_alg != "l_d_djk" && path_alg != "l_d_a*" && path_alg != "l_all"){
		cout<<RED<<"Invalid Command. Type menu for reference to proper commands."<<RESET<<endl;
	}
	// unsigned s1 = flightpath.GetDictionaryData("YZF");
	// unsigned s2 = flightpath.GetDictionaryData("YXY");
	// unsigned s3 = flightpath.GetDictionaryData("YVR");
	// unsigned s4 = flightpath.GetDictionaryData("YYC");
	// unsigned s5 = flightpath.GetDictionaryData("NRT");

	// cout<<"YZF to YYC: "<<flightpath.getEdgeWeight(s1, s4)<<endl;
	// cout<<"YYC to NRT: "<<flightpath.getEdgeWeight(s4, s5)<<endl;

	// cout<<"YZF to YXY: "<<flightpath.getEdgeWeight(s1, s2)<<endl;
	// cout<<"YXY to YVR: "<<flightpath.getEdgeWeight(s2, s3)<<endl;
	// cout<<"YVR to NRT: "<<flightpath.getEdgeWeight(s3, s5)<<endl;
	
	return;
}

int main(/*int argc, const char * argv[]*/) {

	/**
	 * Below is a temporary utility object "parser" which is used
	 * to extract and write from the given datasets. Uncomment the three
	 * lines below if Airports.txt or Routes.txt doesn't exist in the flightData
	 * Directory */

	//FileParser parser;
	//parser.WriteAirportData("flightData/airports.dat");
	//parser.WriteRouteData("flightData/routes.dat");

	/**
	 * Main UI : allows user to interact with the program. 
	 **/
	string user_input = "";
	

	cout<<endl<<endl;
	cout<<CYAN<<"Welcome to the flightpath simulator!!"<<RESET<<endl;
	cout<<BOLDGREEN<<"This UI contains features that enables you to generate a series of routes"<<endl;
	cout<<"from a source and a destination airport around the world!"<<RESET<<endl;
	cout<<"To start this UI, type"<<BOLDMAGENTA<<" start "<<RESET<<"on the keyboard"<<endl;
	cout<<"To open the menu of commands, type"<<BOLDGREEN<<" menu "<<RESET<<"on the keyboard"<<endl;
	cout<<"To terminate the simulator, type"<<RED<<" exit "<<RESET<<"on the keyboard"<<endl;
	cout<<"Command: ";
	/*Retrieve user input*/
	cin>>user_input;
	cout<<endl;

	while(user_input != "exit"){
		if(user_input == "menu"){ /* Display the inputs and features */
			DisplayMenu();
		}
		else if(user_input == "start"){
			StartSimulation();
		}
		else{
			cout<<RED<<"Invalid Command. Type menu for reference to proper commands."<<RESET<<endl;
		}
		/*Retrieve user input*/
		cout<<"Command: ";
		cin>>user_input;
	}

	cout<<RED<<"Successfully terminated the simulator"<<RESET<<endl;
	
	return 0;
}