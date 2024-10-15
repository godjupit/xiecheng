#pragma once

#include"Flight.h"

class flightInfoChanging {
public:	
	void showFlightInfo(std::vector<flight::planeInfo>* flightData, int deAirport, int arrAirport);
	void deleteFlight(std::vector<flight::planeInfo>* flightData,int flightId);
	void insertFlihgtInfo(std::vector<flight::planeInfo>* flightData);


};