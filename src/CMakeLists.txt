set(SRC
    CallOption.cpp
    BlackScholesModel.cpp
    MonteCarlo.cpp
    BasketOption.cpp
    AsianOption.cpp
    PerformanceOption.cpp
    )

add_library(MCPricer ${SRC})