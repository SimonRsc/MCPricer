set(SRC
    CallOption.cpp
    BlackScholesModel.cpp
    MonteCarlo.cpp
    BasketOption.cpp
    AsianOption.cpp
    PerformanceOption.cpp
    ../tests/fakeSrc/FakeBlackScholesModel.cpp
    )

add_library(MCPricer ${SRC})