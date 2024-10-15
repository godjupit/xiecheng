#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>   // ����ʱ�亯��
#include <limits>   
#include "Flight.h"
#include "flightSystem.h"
#include"flightInfoChanging.h"


int main() {
    // 1. ��ȡCSV�ļ�
    std::string filename = "D:\\data.csv";
    flight myFlight;  // ����flight����ʵ��
    std::vector<flight::planeInfo>* flightData = myFlight.readFlightInformation(filename);

    flightSystem system;
    flightInfoChanging newSystem;
    // ����������ڴ洢ɾ���������
    flight::planeNode deleteHead = nullptr;
    std::vector<flight::planeInfo>* deleteFlightData = nullptr;

    int choice = 0;
    do {
       
        std::cout << "\n��ѡ��Ҫִ�еĹ��ܣ�\n";
        std::cout << "1. ��������\n";
        std::cout << "2. �����ǰ�ĺ�����Ϣ\n";
        std::cout << "3. ���һ�������Ϊ�����ĺ���ID\n";
        std::cout << "4. ���Ұ���\n";
        std::cout << "5. ��ȡĳһ�ɻ������к���\n";
        std::cout << "6. ɾ��ָ�����͵ĺ���\n";
        std::cout << "7. ��ɾ��������ݽ����������\n";
        std::cout << "8. ��ɾ����������в��ҷ���Ϊ�����ĺ���ID\n";
        std::cout << "9. ��ɾ����������в��Ұ���\n";
        std::cout << "12. �����µĺ���\n";
        std::cout << "10. ���Һ���\n";
        std::cout << "11. ɾ������\n";
        std::cout << "13. �˳�����\n";
        std::cout << "����������ѡ��";

        //����û�����Ϸ�
        while (!(std::cin >> choice) || choice < 1 || choice > 15) {
            std::cin.clear();  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
            std::cout << "������Ч��������1��10֮���������";
        }

        switch (choice) {
        case 1: {
            // 1. ��������
            auto start = std::chrono::steady_clock::now();
            std::sort(flightData->begin(), flightData->end(), cmp);
            auto finish = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
            std::cout << "������ɡ�����ʱ�䣺" << duration.count() << " ms" << std::endl;
            break;
        }
        case 2: {
            // 2. �����ǰ�ĺ�����Ϣ
            auto start = std::chrono::steady_clock::now();
            myFlight.printFlightData(flightData);
            auto finish = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
            std::cout << "�����ɡ�����ʱ�䣺" << duration.count() << " ms" << std::endl;
            break;
        }
        case 3: {
            // 3. ���һ�������Ϊ�����ĺ���ID
            auto start = std::chrono::steady_clock::now();
            system.findPrimeFareFlight(flightData);
            auto finish = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
            std::cout << "����ʱ�䣺" << duration.count() << " ms" << std::endl;
            break;
        }
        case 4: {
            // 4. ���Ұ���
            int depatureAirportId = 0, arrivalAirportId = 0;
            std::cout << "���������ĳ�������ID��1-79����";
            while (!(std::cin >> depatureAirportId) || depatureAirportId < 1 || depatureAirportId > 79) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "������Ч��������1��79֮���������";
            }
            std::cout << "���������ĵ������ID��1-79����";
            while (!(std::cin >> arrivalAirportId) || arrivalAirportId < 1 || arrivalAirportId > 79) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "������Ч��������1��79֮���������";
            }
            auto start = std::chrono::steady_clock::now();
            std::vector<std::vector<int>> flightVec;
            flightVec = system.initTwoDimensionVec(flightData, depatureAirportId, arrivalAirportId);
            system.findArraySaddlePoints(flightVec);
            if (flightVec.empty()) std::cout << "û�д�������" << std::endl;
            auto finish = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
            std::cout << "����ʱ�䣺" << duration.count() << " ms" << std::endl;
            break;
        }
        case 5: {
            // 5. ��ȡĳһ�ɻ������к���
            int planeId = 0;
            std::cout << "������ɻ�ID��1-142����";
            while (!(std::cin >> planeId) || planeId < 1 || planeId > 142) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "������Ч��������1��142֮���������";
            }
            auto start = std::chrono::steady_clock::now();
            flight::planeNode head = system.newFlightList(flightData, planeId);
            system.printFlightList(head);
            // �ͷ������ڴ�
            delete head;
            auto finish = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
            std::cout << "����ʱ�䣺" << duration.count() << " ms" << std::endl;
            break;
        }
        case 6: {
            // 6. ɾ��ָ�����͵ĺ���
            int planeModel = 0;
            std::cout << "������Ҫɾ���ķɻ����ͣ�1-5����";
            while (!(std::cin >> planeModel) || planeModel < 1 || planeModel > 5) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "������Ч��������1��5֮���������";
            }
            auto start = std::chrono::steady_clock::now();
            deleteHead = system.deleteFlightList(flightData, planeModel);
            system.printDeleteFlightList(deleteHead);
            // ��ɾ���������ת��Ϊ���飬�����������
            deleteFlightData = system.transListToArray(deleteHead);
            auto finish = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
            std::cout << "����ʱ�䣺" << duration.count() << " ms" << std::endl;
            break;
        }
        case 7: {
            // 7. ��ɾ��������ݽ����������
            if (deleteFlightData == nullptr) {
                std::cout << "����ִ��ɾ��������ѡ��6����\n";
            }
            else {
                auto start = std::chrono::steady_clock::now();
                std::sort(deleteFlightData->begin(), deleteFlightData->end(), cmp);
                myFlight.printFlightData(deleteFlightData);
                auto finish = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
                std::cout << "����ʱ�䣺" << duration.count() << " ms" << std::endl;
            }
            break;
        }
        case 8: {
            // 8. ��ɾ����������в��Ҽ۸�Ϊ�����ĺ���ID
            if (deleteFlightData == nullptr) {
                std::cout << "����ִ��ɾ��������ѡ��6����\n";
            }
            else {
                auto start = std::chrono::steady_clock::now();
                system.findPrimeFareFlight(deleteFlightData);
                auto finish = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
                std::cout << "����ʱ�䣺" << duration.count() << " ms" << std::endl;
            }
            break;
        }
        case 9: {
            // 9. ��ɾ����������в��Ұ���
            if (deleteFlightData == nullptr) {
                std::cout << "����ִ��ɾ��������ѡ��6����\n";
            }
            else {
                int depatureAirportId = 0, arrivalAirportId = 0;
                std::cout << "���������ĳ�������ID��1-79����";
                while (!(std::cin >> depatureAirportId) || depatureAirportId < 1 || depatureAirportId > 79) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "������Ч��������1��79֮���������";
                }
                std::cout << "���������ĵ������ID��1-79����";
                while (!(std::cin >> arrivalAirportId) || arrivalAirportId < 1 || arrivalAirportId > 79) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "������Ч��������1��79֮���������";
                }
                auto start = std::chrono::steady_clock::now();
                std::vector<std::vector<int>> flightVec2;
                flightVec2 = system.initTwoDimensionVec(deleteFlightData, depatureAirportId, arrivalAirportId);
                system.findArraySaddlePoints(flightVec2);
                if (flightVec2.empty()) std::cout << "�������߲�����" << std::endl;
                auto finish = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
                std::cout << "����ʱ�䣺" << duration.count() << " ms" << std::endl;
            }
            break;
        }
        case 10:
        {
            
            int deAirport = 0;
            int arrAirport = 0;
            std::cout << "please input departure airport id and arrival airport id: ";
            std::cin >> deAirport;
            std::cin >> arrAirport;
            newSystem.showFlightInfo(flightData, deAirport, arrAirport);
            break;
        }
        case 11:
        {
            int flightId = 0;
			std::cout << "please input flight id: ";
            std::cin >> flightId;
            newSystem.deleteFlight(flightData, flightId);
            std::cout << "ɾ���ɹ� ";
        }
        case 12:
        {
            newSystem.insertFlihgtInfo(flightData);
			break;
        }
        case 13:
            std::cout << "�������˳���\n";
            break;
        default:
            std::cout << "������Ч��������ѡ��\n";
            break;
        }

    } while (choice != 13);

    // �ͷ��ڴ�
    if (deleteHead != nullptr) {
        delete deleteHead;
    }
    delete flightData;
    if (deleteFlightData != nullptr) {
        delete deleteFlightData;
    }

    return 0;
}