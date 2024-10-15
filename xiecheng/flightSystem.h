#include"Flight.h"


class flightSystem {
public:
	bool isPrime(int n);
	
	void findPrimeFareFlight(std::vector<flight::planeInfo>* flightData);
	
	std::vector<std::vector<int>> initTwoDimensionVec(std::vector<flight::planeInfo>* flightData, int departAirportId, int arrivalAirportId);
	bool ifRowMaxAndColumnMin(std::vector<std::vector<int>> temp, int row, int column);
	void findArraySaddlePoints(std::vector<std::vector<int>> temp);
	
	flight::planeNode newFlightList(std::vector<flight::planeInfo>* flightData, int planeId);
	void printFlightList(flight::planeNode head);
	
	flight::planeNode deleteFlightList(std::vector<flight::planeInfo>* flightData, int planeId);
	void printDeleteFlightList(flight::planeNode head);

	flight::planeNode mergeSortList(flight::planeNode head);
	static flight::planeNode mergeSort(flight::planeNode head);
	static flight::planeNode merge(flight::planeNode left, flight::planeNode right);
	void printSortList(flight::planeNode head);

	std::vector<flight::planeInfo>*  transListToArray(flight::planeNode head);
};

bool cmp(flight::planeInfo a, flight::planeInfo b);
bool compare(flight::planeInfo a, flight::planeInfo b);