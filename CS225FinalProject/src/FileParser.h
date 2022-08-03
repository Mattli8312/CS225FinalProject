#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<stdio.h>
#include<vector>

/**
 * FileParser will be used for extracting new information including the IATA, Coordinates, 
 * and Unique Identifier. It simply writes from airports.dat and routes.dat files
 **/
using namespace std;

class FileParser{
    public:
        /**
         * Default Constructor
         * @param //None
         **/
        FileParser();
        /**
         * Method used for writing the airport data to airport.txt
         * @param filename Airports.dat
         **/
        void WriteAirportData(const string filename);
        /**
         * Method used for extracting and writing to routes.txt
         * @param filename Routes.dat
         **/
        void WriteRouteData(const string filename);
};