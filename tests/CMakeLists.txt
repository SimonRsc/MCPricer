set(SRC
    CallOption.cpp
)


add_library(MCPricer ../src/${SRC})


add_executable(PayoffTest testPayoff.cpp )
target_link_libraries(PayoffTest MCPricer)
target_link_libraries(PayoffTest ${PNL_LIBRARIES})


add_executable(pnlTests pnlTests.cpp )
target_link_libraries(pnlTests ${PNL_LIBRARIES})
