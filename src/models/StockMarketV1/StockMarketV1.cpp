#include "StockMarketV1.h"
#include "../../helpers/helpers.h"
#include "../../helpers/exceptions.h"

#include <set>
#include <vector>
#include <utility>

namespace StockMarket {
    void StockMarketV1::addRequest(const Request& request) {
        if (request.type == RequestType::Buy) {
            buyRequests.insert(request);
        } else {
            sellRequests.insert(request);
        }
    }

    void StockMarketV1::removeRequest(const Request& request) {
        if (request.type == RequestType::Buy) {
            auto pos = buyRequests.find(request);
            if (pos == buyRequests.end()) throw RequestNotFoundException();

            buyRequests.erase(pos);
        } else {
            auto pos = sellRequests.find(request);
            if (pos == sellRequests.end()) throw RequestNotFoundException();

            sellRequests.erase(pos);
        }
    }

    void StockMarketV1::modifyRequest(const Request& newRequest, const Request& oldRequest) {
        if (newRequest.type != oldRequest.type) throw TypesNotEqualException();

        removeRequest(oldRequest);
        addRequest(newRequest);
    }

    std::pair<std::vector<Request>, std::vector<Request>> StockMarketV1::displayTopRequests() {
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