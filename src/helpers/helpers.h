#ifndef STOCKMARKET_HELPERS_H
#define STOCKMARKET_HELPERS_H


#pragma once

#include <ostream>

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

        [[nodiscard]] std::string to_string() const {
            return "Price: " + std::to_string(price) + " Amount: " + std::to_string(amount) + " Type: " + (type == RequestType::Buy ? "Buy" : "Sell");
        }
    };

//    std::ostream& operator<<(std::ostream& stream, const Request& request) {
//        return stream << "Price: " << request.price << " Amount: " << request.amount << " Type: " << (request.type == RequestType::Buy ? "Buy" : "Sell");
//    }

} //end of namespace

#endif //STOCKMARKET_HELPERS_H