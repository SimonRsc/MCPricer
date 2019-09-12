set(SRC
        ../src/CallOption.cpp
        ../src/BasketOption.cpp
)

set(HEADERS
        ../src/CallOption.h
        ../src/BasketOption.h
        ../src/Option.hpp
)

add_library(MCPricer ${SRC} ${HEADERS})


add_executable(PayoffTest testPayoff.cpp )
target_link_libraries(PayoffTest MCPricer)
target_link_libraries(PayoffTest ${PNL_LIBRARIES})


add_executable(pnlTests pnlTests.cpp )
target_link_libraries(pnlTests ${PNL_LIBRARIES})
