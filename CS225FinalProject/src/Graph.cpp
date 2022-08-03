#include "Graph.h"
#define Radius 6371 //Radius of earth in Kilometers
Graph::Graph(){
    /*nothing*/
}

Graph::Graph(unsigned size){
    /*initialize everything to zero*/
    vector<vector<unsigned>> temp(size, vector<unsigned>(size, 0));

    AdjacencyMatrix = temp;

}

void Graph::SetEdge(unsigned src, unsigned dest, unsigned weight){

    AdjacencyMatrix[src][dest] = weight;

}

void Graph::FillDictionary(const string filename){
    
    ifstream text(filename);

	vector<string> out;

    int index = 0;

	if (text.is_open()) {

		istream_iterator<string> iter(text);

		while (!text.eof()) {

            //Handle processing
            int counter = 0;

            stringstream ss(*iter);

            string word, IATA;

            string log = "", lat = "";

            while(getline(ss, word, ',')){

                if(counter == 1){

                    //We are looking at the IATA

                    IATA = word;

                }

                else if(counter == 2){

                    lat = word;

                }

                else if(counter == 3){

                    log = word;

                    break;
                    
                }

                counter++;

            }

            if(IATA.length() != 2 && log != "" && lat != ""){ //If we parsed the right number and eliminated \N

                VertexDictionary[IATA] = index;

                double long_ = atof(log.c_str());

                double lat_ = atof(lat.c_str());

                // double long_ = stod(log), lat_ = stod(lat);

                // pair<double, double> coordinate(long_, lat_); //Store latitude and longitude coordinates

                // Coordinates.push_back(coordinate);

                Coordinates.push_back(make_pair(long_, lat_));

                IATADictionary.push_back(IATA); //Populate IATA dictionary

                index ++;

            }

			++iter;
		}

	}
    else{

        cout<<"Can't open Airports.txt file: Use FileParser to generate txt"<<endl;

    }
    return;
}

void Graph::PrintDictionary(){

    for (auto d: VertexDictionary){

        cout<<"{"<<d.first<<","<<d.second<<"}"<<endl;

    }

    cout<<VertexDictionary.size()<<endl;
}

int Graph::GetDictionaryData(string key){

    string result = "\"";
    
    result += key;
    
    result += "\"";
    
    if(VertexDictionary.find(result) == VertexDictionary.end()){
    
        return -1;
    
    }
    
    else 
    
        return VertexDictionary.at(result);

}

void Graph::GenerateMatrix(unsigned edges){

    unsigned size_dict = VertexDictionary.size();

    vector<vector<unsigned>> vec(size_dict, vector<unsigned>(size_dict, 0));

    AdjacencyMatrix = vec;
    
    ifstream text("flightData/Routes.txt");

	if (text.is_open()) {

		istream_iterator<string> iter(text);

        string src, dest;

		while (!text.eof() && edges--) {
            
            stringstream ss(*iter);

            string word;

            int count = 0;

            while(getline(ss, word, ',')){

                if(count == 0){ src = word; }

                if(count == 1){ dest = word; }

                count ++;
            }

            int src_idx = GetDictionaryData(src);

            int dest_idx = GetDictionaryData(dest);

            if(src_idx > -1 && dest_idx > -1 && src_idx < (int)size_dict && dest_idx < (int)size_dict){
                
                unsigned distance = CalculateDistance(src_idx, dest_idx);

                AdjacencyMatrix[src_idx][dest_idx] = distance;

            }
            ++iter;
		}
	}
    else{

        cout<<"Can't open Routes.txt file: Use FileParser to generate txt"<<endl;

    }
}

void Graph::PrintMatrix(){

    unsigned size_ = AdjacencyMatrix.size();

    cout<<size_<<endl;

    for(unsigned i = 0; i < size_; i++){
        
        for(unsigned j = 0; j < size_; j++){

            cout<<AdjacencyMatrix[i][j]<<",";

        }
        
        cout<<endl;

    }
}

bool Graph::IsConnected(unsigned sourceID, unsigned destID){

    if(sourceID > AdjacencyMatrix.size() || destID > AdjacencyMatrix.size())

        return false;
    
    else if(sourceID < 0 || destID < 0)

        return false;
    
    return AdjacencyMatrix[sourceID][destID] != 0;

}

unsigned Graph::getSize(){

    return AdjacencyMatrix.size();
    
}

int Graph::getEdgeWeight(unsigned src, unsigned dest){

    return AdjacencyMatrix[src][dest];

}

vector<string> Graph::ConvertToIATA(vector<int> & list){

    vector<string> result;

    for(unsigned i = 0; i < list.size(); i++){

        string curr_ = IATADictionary[(unsigned)list[i]];

        result.push_back(curr_);

    }

    return result;

}

pair<double, double> Graph::getCoordinates(string IATA){

    pair<double, double> result(-1.0, -1.0);

    int src_idx = GetDictionaryData(IATA);

    if(src_idx < 0)

        return result;

    return Coordinates.at(src_idx);

}

unsigned Graph::CalculateDistance(unsigned src, unsigned des){

    /*This function will use the Haversine algorithm and was made possible
    thanks to https://www.movable-type.co.uk/scripts/latlong.html
    */
   /*
   Formula:
        a = sin²(Δφ/2) + cos φ1 ⋅ cos φ2 ⋅ sin²(Δλ/2)
        c = 2 ⋅ atan2( √a, √(1−a) )
        d = R ⋅ c
   */

    pair<float, float> src_node = Coordinates.at(src);

    pair<float, float> des_node = Coordinates.at(des);

    double srcLat = src_node.second * M_PI / 180;

    double destLat = des_node.second * M_PI / 180;

    double delta_long = (des_node.first - src_node.first) * M_PI / 180;

    double delta_lat = destLat -  srcLat;

    double result = pow(sin(delta_lat/2),2) + cos(srcLat) * cos(destLat) * pow(sin(delta_long/2),2);
    
    result = 2 * atan2(sqrt(result), sqrt(1-result));

    result *= Radius;

    return result; 

}

