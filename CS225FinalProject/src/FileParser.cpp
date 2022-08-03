#include "FileParser.h"
/**
 * Temporary Methods only used for simplifying the datasets we are working with
 **/
/**
 * Default Constructor
 * No Parameters
 **/
FileParser::FileParser(){
    /*nothing*/
}

void FileParser::WriteAirportData(const string filename){

    //This code was made possible thanks to https://www.geeksforgeeks.org/csv-file-management-using-c/

    fstream fin;

    ofstream outputFile("flightData/Airports.txt");

    fin.open(filename, ios::in);

    string line, word, temp;

    int idx = 0;
    while(fin >> temp){
        
        int count = 0;

        getline(fin, line); //Read the first line and store in line variable

        string longitude, latitude;

        stringstream ss(line);

        string name;

        while(getline(ss, word, ',')){

            if(count == 3){
                //Fourth element is the 3-letter IATA code: count = 4
                name = word;
            }
            if(count == 5){
                //Accessed the element storing the latitude coordinates
                latitude = word;
            }
            if(count == 6){
                //Accessed the element storing the longitude coordinates
                longitude = word;
                break;
            }
            count++;
        }
        
        //Eliminate airports withouot IATA codes
        if(name.length() != 2){

            outputFile << idx << "," << name << "," << latitude << "," << longitude << "\n";
        
            idx ++;
        
        }
    }

    fin.close();

    outputFile.close();

    return;
}

void FileParser::WriteRouteData(const string filename){

    ifstream text(filename);

	ofstream output("flightData/Routes.txt");

	if (text.is_open()) {

		istream_iterator<string> iter(text);

		while (!text.eof()) {

			stringstream ss(*iter); //break up the string

            string word, src, dest;
            
            int count = 0;

            while(getline(ss, word, ',')){
                
                if(count == 2){

                    src = word;

                }
                if(count == 4){

                    dest = word;

                    break;

                }

                count++;

            }

            if(count == 4){

                output << src << "," << dest << "\n";

            }

			++iter;
		}
	}

    output.close();

    return;
}