set(SRC
    CallOption.cpp
    BlackScholesModel.cpp
    MonteCarlo.cpp
    BasketOption.cpp
    AsianOption.cpp
    PerformanceOption.cpp
    ProfitLoss.cpp
    ../tests/fakeSrc/FakeBlackScholesModel.cpp
    ReadData.cpp
    PricingResults.cpp
    HedgingResults.cpp
    PnlVectToJson.cpp
    )

add_library(MCPricer ${SRC})

target_link_libraries(MCPricer jl_parser)
target_link_libraries(MCPricer mpark_variant)






