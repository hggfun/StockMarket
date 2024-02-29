#include "StockMarketV2.h"
#include "../../helpers/exceptions.h"

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
        std::vector<Request> topBuyRequests, topSellRequests;

        for (auto request : buyRequests) {
            if (topBuyRequests.size() < 10) {
                topBuyRequests.push_back(request);
            } else {
                if (topBuyRequests.front() < request)
                    topBuyRequests.front() = request;
                std::sort(topBuyRequests.begin(), topBuyRequests.end());
            }
        }
        std::reverse(topBuyRequests.begin(), topBuyRequests.end());

        for (auto request : sellRequests) {
            if (topSellRequests.size() < 10) {
                topSellRequests.push_back(request);
            } else {
                if (request < topSellRequests.back())
                    topSellRequests.back() = request;
                std::sort(topSellRequests.begin(), topSellRequests.end());
            }
        }

        return {topBuyRequests, topSellRequests};
    }
} // StockMarket