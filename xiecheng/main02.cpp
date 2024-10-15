#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>   // 用于时间函数
#include <limits>   
#include "Flight.h"
#include "flightSystem.h"
#include"flightInfoChanging.h"


int main() {
    // 1. 读取CSV文件
    std::string filename = "D:\\data.csv";
    flight myFlight;  // 创建flight对象实例
    std::vector<flight::planeInfo>* flightData = myFlight.readFlightInformation(filename);

    flightSystem system;
    flightInfoChanging newSystem;
    // 定义变量用于存储删除后的数据
    flight::planeNode deleteHead = nullptr;
    std::vector<flight::planeInfo>* deleteFlightData = nullptr;

    int choice = 0;
    do {
       
        std::cout << "\n请选择要执行的功能：\n";
        std::cout << "1. 数据排序\n";
        std::cout << "2. 输出当前的航班信息\n";
        std::cout << "3. 查找基础费用为质数的航班ID\n";
        std::cout << "4. 查找鞍点\n";
        std::cout << "5. 获取某一飞机的所有航班\n";
        std::cout << "6. 删除指定机型的航班\n";
        std::cout << "7. 对删除后的数据进行排序并输出\n";
        std::cout << "8. 在删除后的数据中查找费用为质数的航班ID\n";
        std::cout << "9. 在删除后的数据中查找鞍点\n";
        std::cout << "12. 增加新的航班\n";
        std::cout << "10. 查找航班\n";
        std::cout << "11. 删除航班\n";
        std::cout << "13. 退出程序\n";
        std::cout << "请输入您的选择：";

        //检查用户输入合法
        while (!(std::cin >> choice) || choice < 1 || choice > 15) {
            std::cin.clear();  
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
            std::cout << "输入无效，请输入1到10之间的整数：";
        }

        switch (choice) {
        case 1: {
            // 1. 数据排序
            auto start = std::chrono::steady_clock::now();
            std::sort(flightData->begin(), flightData->end(), cmp);
            auto finish = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
            std::cout << "排序完成。运行时间：" << duration.count() << " ms" << std::endl;
            break;
        }
        case 2: {
            // 2. 输出当前的航班信息
            auto start = std::chrono::steady_clock::now();
            myFlight.printFlightData(flightData);
            auto finish = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
            std::cout << "输出完成。运行时间：" << duration.count() << " ms" << std::endl;
            break;
        }
        case 3: {
            // 3. 查找基础费用为质数的航班ID
            auto start = std::chrono::steady_clock::now();
            system.findPrimeFareFlight(flightData);
            auto finish = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
            std::cout << "运行时间：" << duration.count() << " ms" << std::endl;
            break;
        }
        case 4: {
            // 4. 查找鞍点
            int depatureAirportId = 0, arrivalAirportId = 0;
            std::cout << "请输入您的出发机场ID（1-79）：";
            while (!(std::cin >> depatureAirportId) || depatureAirportId < 1 || depatureAirportId > 79) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "输入无效，请输入1到79之间的整数：";
            }
            std::cout << "请输入您的到达机场ID（1-79）：";
            while (!(std::cin >> arrivalAirportId) || arrivalAirportId < 1 || arrivalAirportId > 79) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "输入无效，请输入1到79之间的整数：";
            }
            auto start = std::chrono::steady_clock::now();
            std::vector<std::vector<int>> flightVec;
            flightVec = system.initTwoDimensionVec(flightData, depatureAirportId, arrivalAirportId);
            system.findArraySaddlePoints(flightVec);
            if (flightVec.empty()) std::cout << "没有此条航线" << std::endl;
            auto finish = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
            std::cout << "运行时间：" << duration.count() << " ms" << std::endl;
            break;
        }
        case 5: {
            // 5. 获取某一飞机的所有航班
            int planeId = 0;
            std::cout << "请输入飞机ID（1-142）：";
            while (!(std::cin >> planeId) || planeId < 1 || planeId > 142) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "输入无效，请输入1到142之间的整数：";
            }
            auto start = std::chrono::steady_clock::now();
            flight::planeNode head = system.newFlightList(flightData, planeId);
            system.printFlightList(head);
            // 释放链表内存
            delete head;
            auto finish = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
            std::cout << "运行时间：" << duration.count() << " ms" << std::endl;
            break;
        }
        case 6: {
            // 6. 删除指定机型的航班
            int planeModel = 0;
            std::cout << "请输入要删除的飞机机型（1-5）：";
            while (!(std::cin >> planeModel) || planeModel < 1 || planeModel > 5) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "输入无效，请输入1到5之间的整数：";
            }
            auto start = std::chrono::steady_clock::now();
            deleteHead = system.deleteFlightList(flightData, planeModel);
            system.printDeleteFlightList(deleteHead);
            // 将删除后的链表转换为数组，方便后续操作
            deleteFlightData = system.transListToArray(deleteHead);
            auto finish = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
            std::cout << "运行时间：" << duration.count() << " ms" << std::endl;
            break;
        }
        case 7: {
            // 7. 对删除后的数据进行排序并输出
            if (deleteFlightData == nullptr) {
                std::cout << "请先执行删除操作（选项6）。\n";
            }
            else {
                auto start = std::chrono::steady_clock::now();
                std::sort(deleteFlightData->begin(), deleteFlightData->end(), cmp);
                myFlight.printFlightData(deleteFlightData);
                auto finish = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
                std::cout << "运行时间：" << duration.count() << " ms" << std::endl;
            }
            break;
        }
        case 8: {
            // 8. 在删除后的数据中查找价格为质数的航班ID
            if (deleteFlightData == nullptr) {
                std::cout << "请先执行删除操作（选项6）。\n";
            }
            else {
                auto start = std::chrono::steady_clock::now();
                system.findPrimeFareFlight(deleteFlightData);
                auto finish = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
                std::cout << "运行时间：" << duration.count() << " ms" << std::endl;
            }
            break;
        }
        case 9: {
            // 9. 在删除后的数据中查找鞍点
            if (deleteFlightData == nullptr) {
                std::cout << "请先执行删除操作（选项6）。\n";
            }
            else {
                int depatureAirportId = 0, arrivalAirportId = 0;
                std::cout << "请输入您的出发机场ID（1-79）：";
                while (!(std::cin >> depatureAirportId) || depatureAirportId < 1 || depatureAirportId > 79) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "输入无效，请输入1到79之间的整数：";
                }
                std::cout << "请输入您的到达机场ID（1-79）：";
                while (!(std::cin >> arrivalAirportId) || arrivalAirportId < 1 || arrivalAirportId > 79) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "输入无效，请输入1到79之间的整数：";
                }
                auto start = std::chrono::steady_clock::now();
                std::vector<std::vector<int>> flightVec2;
                flightVec2 = system.initTwoDimensionVec(deleteFlightData, depatureAirportId, arrivalAirportId);
                system.findArraySaddlePoints(flightVec2);
                if (flightVec2.empty()) std::cout << "此条航线不存在" << std::endl;
                auto finish = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
                std::cout << "运行时间：" << duration.count() << " ms" << std::endl;
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
            std::cout << "删除成功 ";
        }
        case 12:
        {
            newSystem.insertFlihgtInfo(flightData);
			break;
        }
        case 13:
            std::cout << "程序已退出。\n";
            break;
        default:
            std::cout << "输入无效，请重新选择。\n";
            break;
        }

    } while (choice != 13);

    // 释放内存
    if (deleteHead != nullptr) {
        delete deleteHead;
    }
    delete flightData;
    if (deleteFlightData != nullptr) {
        delete deleteFlightData;
    }

    return 0;
}