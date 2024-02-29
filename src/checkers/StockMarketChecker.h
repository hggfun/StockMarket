#ifndef STOCKMARKET_STOCKMARKETCHECKER_H
#define STOCKMARKET_STOCKMARKETCHECKER_H

#pragma once

#include "../helpers/helpers.h"
#include "../helpers/exceptions.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <utility>
#include <algorithm>


namespace StockMarket {

    template <typename T>
    class StockMarketChecker {
    public:
        void measureTimeAddRequest() {
            T stockMarket;
            std::vector<Request> requests;
            for (int i = 1; i < 1001; ++i) {
                requests.emplace_back(i*200, i*5,  i % 2 == 0 ? RequestType::Buy : RequestType::Sell);
            }

            auto start = std::chrono::high_resolution_clock::now();
            for (auto request : requests) {
                stockMarket.addRequest(request);
            }
            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Add Request 1000 times took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds\n";
        }

        void measureTimeRemoveRequest() {
            T stockMarket;
            std::vector<Request> requests;
            for (int i = 1; i < 1001; ++i) {
                requests.emplace_back(i*200, i*5,  i % 2 == 0 ? RequestType::Buy : RequestType::Sell);
                stockMarket.addRequest(requests.back());
            }

            try {
                auto start = std::chrono::high_resolution_clock::now();
                for (auto request : requests) {
                    stockMarket.removeRequest(request);
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Remove Request 1000 times took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds\n";
            } catch (RequestNotFoundException& ex) {
                std::cout << ex.what() << "\n";
            }
        }

        void measureTimeModifyRequest() {
            T stockMarket;
            std::vector<std::pair<Request, Request>> requests;
            for (int i = 1; i < 1001; ++i) {
                requests.emplace_back(Request(i*200, i*5,  i % 2 == 0 ? RequestType::Buy : RequestType::Sell), Request(i*201, i*6,  i % 2 == 0 ? RequestType::Buy : RequestType::Sell));
                stockMarket.addRequest(requests.back().second);
            }

            try {
                auto start = std::chrono::high_resolution_clock::now();
                for (auto requestPair : requests) {
                    stockMarket.modifyRequest(requestPair.first, requestPair.second);
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Modify Request 1000 times took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds\n";
            } catch (RequestNotFoundException& ex) {
                std::cout << ex.what() << "\n";
            } catch (TypesNotEqualException& ex) {
                std::cout << ex.what() << "\n";
            }
        }

        void measureTimeDisplayTopRequests() {
            T stockMarket;
            std::vector<Request> requests;
            for (int i = 1; i < 1001; ++i) {
                requests.emplace_back(i*200, i*5, i % 2 == 0 ? RequestType::Buy : RequestType::Sell);
                stockMarket.addRequest(requests.back());
            }

            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 1000; ++i) {
                stockMarket.displayTopRequests();
            }
            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Display Top Requests 1000 times took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds\n";
        }

        void checkInsertAndDisplayTopRequests() {
            T stockMarket;
            std::vector<Request> requests;
            for (int i = 1; i < 41; ++i) {
                requests.emplace_back(i*200, i*5, i < 21 ? RequestType::Buy : RequestType::Sell);
                stockMarket.addRequest(requests.back());
            }
            std::pair<std::vector<Request>, std::vector<Request>> topRequests = stockMarket.displayTopRequests();

            for (size_t i = 0; i < 10; ++i) {
                if (!(topRequests.first[i] == requests[19-i])) {
                    std::cout << "Incorrect insertion or displaying with returned: " << topRequests.first[i].to_string() << " and expected: " << requests[19-i].to_string() << "\n";
                    return;
                }
            }

            for (size_t i = 0; i < 10; ++i) {
                if (!(topRequests.second[i] == requests[20+i])) {
                    std::cout << "Incorrect insertion or displaying with returned: " << topRequests.second[i].to_string() << " and expected: " << requests[20+i].to_string() << "\n ";
                    return;
                }
            }

            std::cout << "Insert and display operations are correct\n";
        }

        void checkRemoveRequest() {
            T stockMarket;
            std::vector<Request> requests;
            for (int i = 1; i < 41; ++i) {
                requests.emplace_back(i*200, i*5, i < 21 ? RequestType::Buy : RequestType::Sell);
                stockMarket.addRequest(requests.back());
            }
            stockMarket.removeRequest(requests[10]);
            requests.erase((requests.begin()+10));
            stockMarket.removeRequest(requests[30]);
            requests.erase(requests.begin() + 30);
            std::pair<std::vector<Request>, std::vector<Request>> topRequests = stockMarket.displayTopRequests();

            for (size_t i = 0; i < 10; ++i) {
                if (!(topRequests.first[i] == requests[18-i])) {
                    std::cout << "Incorrect removing with returned: " << topRequests.first[i].to_string() << " and expected: " << requests[19-i].to_string() << "\n";
                    return;
                }
            }

            for (size_t i = 0; i < 10; ++i) {
                if (!(topRequests.second[i] == requests[19+i])) {
                    std::cout << "Incorrect removing with returned: " << topRequests.second[i].to_string() << " and expected: " << requests[20+i].to_string() << "\n ";
                    return;
                }
            }

            std::cout << "Remove operation is correct\n";
        }

        void checkModifyRequests() {
            T stockMarket;
            std::vector<Request> requests;
            for (int i = 1; i < 41; ++i) {
                requests.emplace_back(i*200, i*5, i < 21 ? RequestType::Buy : RequestType::Sell);
                stockMarket.addRequest(requests.back());
            }

            stockMarket.modifyRequest({5000, 55, RequestType::Buy}, requests[10]);
            requests[10].price = 5000;
            std::sort(requests.begin(), requests.begin()+20);
            stockMarket.modifyRequest({100, 155, RequestType::Sell}, requests[30]);
            requests[30].price = 100;
            std::sort(requests.begin()+20, requests.begin()+40);

            std::pair<std::vector<Request>, std::vector<Request>> topRequests = stockMarket.displayTopRequests();

            for (size_t i = 0; i < 10; ++i) {
                if (!(topRequests.first[i] == requests[19-i])) {
                    std::cout << "Incorrect modifying with returned: " << topRequests.first[i].to_string() << " and expected: " << requests[19-i].to_string() << "\n";
                    return;
                }
            }

            for (size_t i = 0; i < 10; ++i) {
                if (!(topRequests.second[i] == requests[20+i])) {
                    std::cout << "Incorrect modifying with returned: " << topRequests.second[i].to_string() << " and expected: " << requests[20+i].to_string() << "\n ";
                    return;
                }
            }

            std::cout << "Modify operation is correct\n";
        }

        void doAllChecks() {
            measureTimeAddRequest();
            measureTimeRemoveRequest();
            measureTimeModifyRequest();
            measureTimeDisplayTopRequests();
            checkInsertAndDisplayTopRequests();
            checkRemoveRequest();
            checkModifyRequests();
            std::cout << "......................................................................\n\n";
        }
    };
} // StockMarket

#endif //STOCKMARKET_STOCKMARKETCHECKER_H
