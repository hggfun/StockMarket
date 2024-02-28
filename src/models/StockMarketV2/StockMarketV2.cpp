//
// Created by Алим on 29.02.2024.
//

#include "StockMarketV2.h"
#include "../../helpers/helpers.h"
#include "../../helpers/exceptions.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

namespace StockMarket {
    void StockMarketV2::addRequest(const Request& request) {
        if (request.type == RequestType::Buy) {
            buyRequests.push_back(request);
        } else {
            sellRequests.push_back(request);
        }
    }

    void StockMarketV2::removeRequest(const Request& request) {
        if (request.type == RequestType::Buy) {
            auto pos = std::find(buyRequests.begin(), buyRequests.end(), request);
            if (pos == buyRequests.end()) throw RequestNotFoundException();

            buyRequests.erase(pos);
        } else {
            auto pos = std::find(sellRequests.begin(), sellRequests.end(), request);
            if (pos == sellRequests.end()) throw RequestNotFoundException();

            sellRequests.erase(pos);
        }
    }

    void StockMarketV2::modifyRequest(const Request& newRequest, const Request& oldRequest) {
        if (newRequest.type != oldRequest.type) throw TypesNotEqualException();

        if (oldRequest.type == RequestType::Buy) {
            auto pos = std::find(buyRequests.begin(), buyRequests.end(), oldRequest);
            if (pos == buyRequests.end()) throw RequestNotFoundException();

            buyRequests[std::distance(buyRequests.begin(), pos)] = newRequest;
        } else {
            auto pos = std::find(sellRequests.begin(), sellRequests.end(), oldRequest);
            if (pos == sellRequests.end()) throw RequestNotFoundException();

            sellRequests[std::distance(sellRequests.begin(), pos)] = newRequest;
        }
    }

    std::pair<std::vector<Request>, std::vector<Request>> StockMarketV2::displayTopRequests() {
        std::sort(buyRequests.begin(), buyRequests.end());
        std::sort(sellRequests.begin(), sellRequests.end());

        std::vector<Request> topBuyRequests, topSellRequests;

        auto current = buyRequests.begin();
        auto end = buyRequests.end();
        for (int i = 0; i < 10; ++i) {
            if (current == end) break;
            topBuyRequests.push_back(*current);
        }

        current = sellRequests.begin();
        end = sellRequests.end();
        for (int i = 0; i < 10; ++i) {
            if (current == end) break;
            topSellRequests.push_back(*current);
        }
        return {topBuyRequests, topSellRequests};
    }
} // StockMarket