//
// Created by Алим on 29.02.2024.
//

#ifndef STOCKMARKET_EXCEPTIONS_H
#define STOCKMARKET_EXCEPTIONS_H


#pragma once

#include <exception>


namespace StockMarket {

    class RequestNotFoundException : public std::exception {
    public:
        const char * what () {
            return "The request is not found";
        }
    };

    class TypesNotEqualException : public std::exception {
    public:
        const char * what () {
            return "The types of two requests are not equal";
        }
    };
} //end of namespace

#endif //STOCKMARKET_EXCEPTIONS_H