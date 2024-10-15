#include"flightSystem.h"

#include"Flight.h"
// 判断素数
bool flightSystem::isPrime(int n) {
	if (n == 2) return true;
	for (int i = 2; i < n; i++) {
		if (n % i == 0) return false;
	}
	return true;
}
// 查找素数
void flightSystem::findPrimeFareFlight(std::vector<flight::planeInfo>* flightData) {
	for (const auto& plane : *flightData) {
		if (flightSystem::isPrime(plane.airFares)) {
			std::cout <<"flight id: "<< plane.flightID << "  basic fares: " << plane.airFares << std::endl;
		}
	}
}

std::vector<std::vector<int>> flightSystem::initTwoDimensionVec(std::vector<flight::planeInfo>* flightData, int departAirportId, int arrivalAirportId) {
	std::vector<std::vector<int>> dataVec;
	for (const auto& plane : *flightData) {
		if (plane.departureAirportID == departAirportId && plane.arrivalAirportID == arrivalAirportId) {
			std::vector<int> a;

			a.push_back(plane.flightID);
			a.push_back(plane.airFares);
			a.push_back(plane.peakSeasonRates);
			a.push_back(plane.offSeasonRates);
			
			dataVec.push_back(a);
		}
	}
	for (const auto& row : dataVec) {  // 遍历每一行
		for (const auto& elem : row) {  // 遍历每一列
			std::cout << elem << " ";  // 输出每个元素
		}
		std::cout << std::endl;  // 换行，显示下一行的元素
	}
	return dataVec;
}
//判断是否行最大列最小
bool flightSystem::ifRowMaxAndColumnMin(std::vector<std::vector<int>> temp, int row, int column) {
	auto maxRowElement = *std::max_element(temp[row].begin()+1, temp[row].end());
	int minColumnElement = 100000;
	for (int i = 0; i < temp.size(); i++) {
		if (temp[i][column] < minColumnElement) minColumnElement = temp[i][column];
	}
	if (maxRowElement  == minColumnElement) return true;
	else return false;
}

void flightSystem::findArraySaddlePoints(std::vector<std::vector<int>> temp) {
	
	for (int i = 0; i < temp.size(); i++) {
		for (int j = 1; j < temp[0].size(); j++) {

			if (ifRowMaxAndColumnMin(temp, i, j)) {
				std::cout << "saddle points flight id：" << temp[i][0] << std::endl;
			}
		}
	}



}

bool cmp(flight::planeInfo a, flight::planeInfo b) {
	if (a.departureAirportID != b.departureAirportID)  return a.departureAirportID > b.departureAirportID;
	else {
		if (a.arrivalAirportID != b.arrivalAirportID) {
			return a.arrivalAirportID > b.arrivalAirportID;
		}
		else {
			return (a.arrivalTime - a.departureTime) < (b.arrivalTime - b.departureTime);
		}
	}

}

bool compare(flight::planeInfo a, flight::planeInfo b) {
	if ( a.arrivalAirportID != b.departureTime) {
		return a.arrivalTime < b.departureTime;
	}
}
// 构建链表
flight::planeNode flightSystem::newFlightList(std::vector<flight::planeInfo>* flightData, int planeId) {
	std::vector<flight::planeInfo> onePlaneData;
	
	for (const auto& plane: *flightData) {
		if (planeId == plane.airplaneID) {
			onePlaneData.push_back(plane);
		}
	}
	std::sort(onePlaneData.begin(), onePlaneData.end(), compare);
	flight::planeNode head = new flight::planeInfo;
	flight::planeNode current;
	current = head;
	for (const auto& plane : onePlaneData) {
		flight::planeNode newNode = new flight::planeInfo;
		*newNode = plane;
		newNode->next = nullptr;

		current->next = newNode;
		current = newNode;
	}
	return head;  
}
// 输出链表
void flightSystem::printFlightList(flight::planeNode head) {
	flight::planeNode current = head->next;
	while (current != nullptr) {
		
		std::cout << " departure airport id: " << current->departureAirportID << ", arrival airport id is: " << current->arrivalAirportID 
			<< ", departure time is: " << current->departureTime << ", arrival time is: " << current->arrivalTime << std::endl;;
		
		current = current->next;
	}
}
// 删除后的数据构成的链表
flight::planeNode flightSystem::deleteFlightList(std::vector<flight::planeInfo>* flightData, int planeModel) {
	std::vector<flight::planeInfo> onePlaneData;
	int i = 0;
	// delete from the struct array
	for (int i = flightData->size() - 1; i >= 0; --i) {
		const auto& plane = (*flightData)[i];
		if (planeModel == plane.airplaneModel) {
			onePlaneData.push_back(plane);
			flightData->erase(flightData->begin() + i);
		}

	}

	flight::planeNode head = new flight::planeInfo;
	flight::planeNode current = head;


	for (const auto& plane : onePlaneData) {
		flight::planeNode newNode = new flight::planeInfo;
		*newNode = plane;
		newNode->next = nullptr;

		current->next = newNode;
		current = newNode;
	}
	return head;
}

void flightSystem::printDeleteFlightList(flight::planeNode head) {
	flight::planeNode current = head->next;
	while (current != nullptr) {

		std::cout << "flight id is: " << current->flightID << std::endl;
		current = current->next;
	}
}

flight::planeNode flightSystem::merge(flight::planeNode left, flight::planeNode right) {
	flight::planeNode head = new flight::planeInfo;
	flight::planeNode h = head;
	while (left && right) {
		if (left->departureAirportID < right->departureAirportID) {
			h->next = left;
			left = left->next;
		}
		else {
			h->next = right;
			right = right->next;
		}
		h = h->next;
	}
	h->next = left == NULL ? right : left;
	return head->next;
}

flight::planeNode flightSystem::mergeSort(flight::planeNode head) {
	if (!head->next) return head;
	flight::planeNode slow = head;
	flight::planeNode fast = head->next;
	while (fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
	}
	auto r_head = slow->next;
	slow->next = NULL;
	auto left = mergeSort(head);
	auto right = mergeSort(r_head);
	return merge(left, right);
}

flight::planeNode flightSystem::mergeSortList(flight::planeNode head) {
	if (!head || !head->next) return head;
	return mergeSort(head);
}

void flightSystem::printSortList(flight::planeNode head) {
	flight::planeNode current = head->next;
	while (current != nullptr) {
		std::cout << "flight id is: " << current->flightID << ",  departure airport id is: " << current->departureAirportID 
			<< ",  arrival airport is: " << current->arrivalAirportID << ",  flight time is: " << 
			current->arrivalTime - current->departureTime << std::endl;
		current = current->next;
	}
}

std::vector<flight::planeInfo>*  flightSystem::transListToArray(flight::planeNode head) {
	auto newVec = new std::vector<flight::planeInfo>;
	flight::planeNode h = head->next;
	while (h != NULL) {
		newVec->push_back(*h);
		h = h->next;
	}
	return newVec;
}
