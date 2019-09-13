set(SRC
    fakeSrc/FakeBlackScholesModel.cpp
    fakeSrc/FakeBlackScholesModel.h
    ../src/MonteCarlo.hpp
    ../src/MonteCarlo.cpp
    ../src/CallOption.h
    ../src/CallOption.cpp
    ../src/BlackScholesModel.hpp
)


add_library(MCPricer ${SRC})
target_link_libraries(MCPricer ${PNL_LIBRARIES})


add_executable(PayoffTest testPayoff.cpp )
target_link_libraries(PayoffTest MCPricer)
target_link_libraries(PayoffTest ${PNL_LIBRARIES})


add_executable(pnlTests pnlTests.cpp )
target_link_libraries(pnlTests ${PNL_LIBRARIES})

add_executable(testMonteCarlo testMonteCarlo.cpp)
target_link_libraries(testMonteCarlo ${PNL_LIBRARIES})

target_link_libraries(testMonteCarlo MCPricer)

