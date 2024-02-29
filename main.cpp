#include "src/helpers/exceptions.h"
#include "src/checkers/StockMarketChecker.h"
#include "src/models/StockMarketV1/StockMarketV1.h"
#include "src/models/StockMarketV2/StockMarketV2.h"


int main() {
    StockMarket::StockMarketChecker<StockMarket::StockMarketV1> tester;
    tester.doAllChecks();

    StockMarket::StockMarketChecker<StockMarket::StockMarketV2> tester2;
    tester2.doAllChecks();

    return 0;
}
