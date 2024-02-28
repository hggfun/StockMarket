//
// Created by Алим on 29.02.2024.
//

#ifndef STOCKMARKET_STOCKMARKETV2_H
#define STOCKMARKET_STOCKMARKETV2_H

#pragma once

#include "../../helpers/helpers.h"

#include <vector>
#include <utility>


namespace StockMarket {

    class StockMarketV2 {
    private:
        std::vector<Request> buyRequests;
        std::vector<Request> sellRequests;
    public:
        void addRequest(const Request& request);

        void removeRequest(const Request& request);

        void modifyRequest(const Request& newRequest, const Request& oldRequest);

        std::pair<std::vector<Request>, std::vector<Request>> displayTopRequests();
    };

} // StockMarket

#endif //STOCKMARKET_STOCKMARKETV2_H
