set(SRC
    CallOption.cpp
    BlackScholesModel.cpp
    MonteCarlo.cpp
    BasketOption.cpp
    AsianOption.cpp
    PerformanceOption.cpp
    ReadData.cpp
    )

add_library(MCPricer ${SRC})

target_link_libraries(MCPricer jl_parser)
target_link_libraries(MCPricer mpark_variant)