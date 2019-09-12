set(SRC
    CallOption.cpp
)


add_library(MCPricer ../src/${SRC})

add_executable(pnlTests pnlTests.cpp )
target_link_libraries(pnlTests ${PNL_LIBRARIES})
target_link_libraries(pnlTests MCPricer)