//
// Created by Алим on 29.02.2024.
//

#ifndef STOCKMARKET_HELPERS_H
#define STOCKMARKET_HELPERS_H


#pragma once

namespace StockMarket {

    enum class RequestType {
        Buy,
        Sell
    };

    struct Request {
        int price;
        int amount;
        RequestType type;

        Request(int price, int amount, RequestType type) : price(price), amount(amount), type(type){};

        bool operator<(const Request& other) const {return price < other.price;};
        bool operator==(const Request& other) const {return price == other.price && amount == other.amount && type == other.type;};
    };

} //end of namespace

#endif //STOCKMARKET_HELPERS_H