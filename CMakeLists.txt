cmake_minimum_required(VERSION 3.27)
project(StockMarket)

set(CMAKE_CXX_STANDARD 17)

add_executable(StockMarket main.cpp
        src/helpers/exceptions.h
        src/helpers/helpers.h
        src/models/StockMarketV1/StockMarketV1.cpp
        src/models/StockMarketV1/StockMarketV1.h
        src/models/StockMarketV2/StockMarketV2.cpp
        src/models/StockMarketV2/StockMarketV2.h
        src/checkers/StockMarketChecker.h
)
