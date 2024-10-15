#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<chrono>
#include<iomanip>


class flight{
public:
	typedef struct planeInfo{
		int flightID;
		int departureDate;
		std::string intlOrDome;
		int flightNo;
		int departureAirportID;
		int arrivalAirportID;
		double departureTime;
		double arrivalTime;
		int airplaneID;
		int airplaneModel;
		int airFares;
		int peakSeasonRates;
		int offSeasonRates;
		struct planeInfo* next;
	}planeInfo, * planeNode;

	
	
	std::vector<planeInfo>* readFlightInformation(std::string fileName);
	void printFlightData(std::vector<planeInfo>* a);
};

