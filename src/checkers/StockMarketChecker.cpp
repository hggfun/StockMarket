#include "../helpers/helpers.h"
#include "../helpers/exceptions.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <utility>


namespace StockMarket {

    template <typename T>
    class StockMarketChecker {
    public:
        void testTimeAddRequest() {
            T stockMarket;
            std::vector<Request> requests;
            for (int i = 1; i < 101; ++i) {
                requests.emplace_back(i*200, i*5,  i % 2 == 0 ? RequestType::Buy : RequestType::Sell);
            }

            auto start = std::chrono::high_resolution_clock::now();
            for (auto request : requests) {
                stockMarket.addRequest(request);
            }
            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Add Request 100 times took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds\n";
        }

        void testTimeRemoveRequest() {
            T stockMarket;
            std::vector<Request> requests;
            for (int i = 1; i < 101; ++i) {
                requests.emplace_back(i*200, i*5,  i % 2 == 0 ? RequestType::Buy : RequestType::Sell);
                stockMarket.addRequest(requests.back());
            }

            try {
                auto start = std::chrono::high_resolution_clock::now();
                for (auto request : requests) {
                    stockMarket.removeRequest(request);
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Remove Request 100 times took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds\n";
            } catch (RequestNotFoundException& ex) {
                std::cout << ex.what() << "\n";
            }
        }

        void testTimeModifyRequest() {
            T stockMarket;
            std::vector<std::pair<Request, Request>> requests;
            for (int i = 1; i < 101; ++i) {
                requests.emplace_back(Request(i*200, i*5,  i % 2 == 0 ? RequestType::Buy : RequestType::Sell), Request(i*201, i*6,  i % 2 == 0 ? RequestType::Buy : RequestType::Sell));
                stockMarket.addRequest(requests.back().first);
            }

            try {
                auto start = std::chrono::high_resolution_clock::now();
                for (auto requestPair : requests) {
                    stockMarket.modifyRequest(requestPair.first, requestPair.second);
                }
                auto end = std::chrono::high_resolution_clock::now();
                std::cout << "Modify Request 100 times took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds\n";
            } catch (RequestNotFoundException& ex) {
                std::cout << ex.what() << "\n";
            } catch (TypesNotEqualException& ex) {
                std::cout << ex.what() << "\n";
            }
        }

        void testTimeDisplayTopRequests() {
            T stockMarket;
            std::vector<Request> requests;
            for (int i = 1; i < 101; ++i) {
                requests.emplace_back(i*200, i*5, i % 2 == 0 ? RequestType::Buy : RequestType::Sell);
                stockMarket.addRequest(requests.back());
            }

            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 100; ++i) {
                auto topRequests = stockMarket.displayTopRequests();
            }
            auto end = std::chrono::high_resolution_clock::now();

            std::cout << "Display Top Requests 100 times took: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds\n";
        }
    };
} // StockMarket