#include "Flight.h"


// 根据结构体内容解析不同的值
flight::planeInfo parseCsvLine(const std::string& line) {
    std::stringstream lineStream(line);
    std::string cell;
    flight::planeInfo emp;

    std::getline(lineStream, cell, ',');
    emp.flightID = std::stoi(cell);  // int

    std::getline(lineStream, cell, ',');
    emp.departureDate = std::stoi(cell);  // int

    std::getline(lineStream, cell, ',');
    emp.intlOrDome = cell;  // std::string

    std::getline(lineStream, cell, ',');
    emp.flightNo = std::stoi(cell);  // int

    std::getline(lineStream, cell, ',');
    emp.departureAirportID = std::stoi(cell);  // int

    std::getline(lineStream, cell, ',');
    emp.arrivalAirportID = std::stoi(cell);  // int

    std::getline(lineStream, cell, ',');
    emp.departureTime = std::stod(cell);  // float

    std::getline(lineStream, cell, ',');
    emp.arrivalTime = std::stod(cell);  // float

    std::getline(lineStream, cell, ',');
    emp.airplaneID = std::stoi(cell);  // int

    std::getline(lineStream, cell, ',');
    emp.airplaneModel = std::stoi(cell);  // int

    std::getline(lineStream, cell, ',');
    emp.airFares = std::stoi(cell);  // int

    std::getline(lineStream, cell, ',');
    emp.peakSeasonRates = std::stoi(cell);  // int

    std::getline(lineStream, cell, ',');
    emp.offSeasonRates = std::stoi(cell);  // int

    return emp;
}

std::vector<flight::planeInfo>* flight::readFlightInformation(std::string fileName) {
	// open file
	std::ifstream flightFile(fileName, std::ios::in);
	// opening file test
    if (!flightFile.is_open()) {
        std::cerr << "Error: Failed to open file: " << fileName << std::endl;
        return nullptr;
    }

	if (!flightFile) {
		std::cout << "open file failed" << std::endl;
		return nullptr;
	}

	std::string line;
	auto emp = new std::vector<planeInfo>;
    getline(flightFile, line);
	while (getline(flightFile, line)) {
		planeInfo emp1 = parseCsvLine(line);
		emp->push_back(emp1);
	}

	
	return emp;
}

void flight::printFlightData(std::vector<flight::planeInfo>* a) {
    for (const auto& plane : *a) {
        std::cout << "Flight ID: " << plane.flightID << std::endl;
        std::cout << "Departure date: " << plane.departureDate << std::endl;
        std::cout << "Intl/Dome: " << plane.intlOrDome << std::endl;
        std::cout << "Flight NO: " << plane.flightNo << std::endl;
        std::cout << "Departure Airport ID: " << plane.departureAirportID << std::endl;
        std::cout << "Arrival Airport ID: " << plane.arrivalAirportID << std::endl;
        std::cout << "Departure Time: " << std::fixed << std::setprecision(5) << plane.departureTime << "\n";
        std::cout << "Arrival Time: " << std::fixed << std::setprecision(5) << plane.arrivalTime << "\n";
        std::cout << "Airplane ID: " << plane.airplaneID << std::endl;
        std::cout << "Airplane Model: " << plane.airplaneModel << std::endl;
        std::cout << "Air Fares: " << plane.airFares << std::endl;
        std::cout << "Peak Season Rates: " << plane.peakSeasonRates << std::endl;
        std::cout << "Off Season Rates: " << plane.offSeasonRates << std::endl;
        std::cout << "flight time: " << plane.arrivalTime - plane.departureTime << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }
}
