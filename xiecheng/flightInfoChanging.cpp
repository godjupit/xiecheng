#include "Flight.h"
#include "flightSystem.h"
#include"flightInfoChanging.h"

void flightInfoChanging::showFlightInfo(std::vector<flight::planeInfo>* flightData, int deAirport, int arrAirport) {
	int cheapestFare = 100000;
	double shortestDuration = 100000.0;
	int cheapestFlightId = 0;
	int shortestestFlightId = 0;
	std::vector<flight::planeInfo> directFlight;

	for (const auto& plane : *flightData) {
		if (plane.arrivalAirportID == arrAirport && plane.departureAirportID) {
			
			{
				if (plane.airFares < cheapestFare) cheapestFare = plane.airFares;
				cheapestFlightId = plane.flightID;
			}

			if (plane.arrivalTime - plane.departureTime < shortestDuration) 
			{
				shortestDuration = (plane.arrivalTime - plane.departureTime);
				shortestestFlightId = plane.flightID;
			}
			directFlight.push_back(plane);
		}
	}
	int mode = 0;
	for (const auto& plane : directFlight) {
		if (plane.flightID == cheapestFlightId) {
			mode = 1;
			
		}
		else if (plane.flightID == shortestestFlightId) {
			
			mode = 2;
		}
		else if ((plane.arrivalTime - plane.departureTime) > 1) {
			mode = 3;
		}
		else if ((plane.flightID == cheapestFlightId) && (plane.flightID == shortestestFlightId)) {
			mode = 4;
		}
		else if ((plane.flightID == cheapestFlightId) && ((plane.arrivalTime - plane.departureTime) > 1)) {
			mode = 5;
		}
		else if ((plane.flightID == shortestestFlightId) && ((plane.arrivalTime - plane.departureTime) > 1)) {
			mode = 6;
		}
		else if (((plane.flightID == cheapestFlightId) && ((plane.arrivalTime - plane.departureTime) > 1)) && (plane.flightID == shortestestFlightId)) {
			mode = 7;
		}
		else {
			mode = 0;
		}

		switch (mode)
		{
		case 1:
			std::cout << plane.flightID << " (cheapest)\n";
		case 2:
			std::cout << plane.flightID << " (shortest duration)\n";
		case 3:
			std::cout << plane.flightID << " (cheapest, +1 day)\n";
		case 4:
			std::cout << plane.flightID << " (cheapest, shortest duration)\n";
		case 5:
			std::cout << plane.flightID << " (cheapest, +1 day)\n";
		case 6:
			std::cout << plane.flightID << " (shortest duration, +1 day)\n";
		case 7:
			std::cout << plane.flightID << " (cheapest, shortest duration, +1 day)\n";
		case 0:
			std::cout << plane.flightID << "\n";
		default:
			break;
		
		}
		
	}
	

}

void flightInfoChanging::deleteFlight(std::vector<flight::planeInfo>* flightData, int flightId) {
	int count = 0;
	for (auto it = flightData->begin(); it != flightData->end(); it++) {

		if (it->flightID == flightId) {
			flightData->erase(it);
			break;
		}
	}
}


void flightInfoChanging::insertFlihgtInfo(std::vector<flight::planeInfo>* flightData) {
	flight::planeInfo plane;
	std::cout << "Enter flight ID: ";
	std::cin >> plane.flightID;
	std::cout << "Enter departure airport ID: ";
	std::cin >> plane.departureAirportID;
	std::cout << "Enter arrival airport ID: ";
	std::cin >> plane.arrivalAirportID;
	std::cout << "Enter departure time: ";
	std::cin >> plane.departureTime;
	std::cout << "Enter arrival time: ";
	std::cin >> plane.arrivalTime;
	std::cout << "Enter air fares: ";
	std::cin >> plane.airFares;
	flightData->push_back(plane);
}
