#ifndef STOCKMARKET_STOCKMARKETV1_H
#define STOCKMARKET_STOCKMARKETV1_H

#pragma once

#include "../../helpers/helpers.h"

#include <set>
#include <vector>
#include <utility>


namespace StockMarket {

    class StockMarketV1 {
    private:
        std::set<Request> buyRequests;
        std::set<Request> sellRequests;
    public:
        void addRequest(const Request& request);

        void removeRequest(const Request& request);

        void modifyRequest(const Request& newRequest, const Request& oldRequest);

        std::pair<std::vector<Request>, std::vector<Request>> displayTopRequests();
    };

} // StockMarket

#endif //STOCKMARKET_STOCKMARKETV1_H
