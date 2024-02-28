#include "src/helpers/helpers.h"
#include "src/helpers/exceptions.h"
#include "src/checkers/StockMarketChecker.cpp"
#include "src/models/StockMarketV1/StockMarketV1.h"
#include "src/models/StockMarketV2/StockMarketV2.h"


int main() {

    StockMarket::StockMarketChecker<StockMarket::StockMarketV1> tester;

    tester.testTimeAddRequest();
    tester.testTimeRemoveRequest();
    tester.testTimeModifyRequest();
    tester.testTimeDisplayTopRequests();

    return 0;
}
