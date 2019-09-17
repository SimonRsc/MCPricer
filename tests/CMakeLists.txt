# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

configure_file(../data/call.dat call.dat)
configure_file(../data/basket_1.dat basket_1.dat)
configure_file(../data/asian.dat asian.dat)

# Link against gtest or gtest_main as needed. Eg
add_executable(sample gtest-sample.cpp)
target_link_libraries(sample gtest)
add_test (NAME sample COMMAND sample)

add_executable(PayoffTest testPayoff.cpp )
target_link_libraries(PayoffTest MCPricer)
target_link_libraries(PayoffTest ${PNL_LIBRARIES})
target_link_libraries(PayoffTest gtest)

add_executable(pnlTests pnlTests.cpp )
target_link_libraries(pnlTests ${PNL_LIBRARIES})

add_executable(testsBS testsBS.cpp )
target_link_libraries(testsBS MCPricer)
target_link_libraries(testsBS gtest)
target_link_libraries(testsBS ${PNL_LIBRARIES})

add_executable(testMonteCarlo testMonteCarlo.cpp )
target_link_libraries(testMonteCarlo MCPricer)
target_link_libraries(testMonteCarlo gtest)
target_link_libraries(testMonteCarlo ${PNL_LIBRARIES})

add_executable(testReadData testReadData.cpp)
target_link_libraries(testReadData MCPricer)
target_link_libraries(testReadData gtest)
target_link_libraries(testReadData ${PNL_LIBRARIES})

add_executable(MainPricer ../src/MainPricer.cpp )
target_link_libraries(MainPricer MCPricer)
target_link_libraries(MainPricer ${PNL_LIBRARIES})

add_executable(testDelta testDelta.cpp)
target_link_libraries(testDelta MCPricer)
target_link_libraries(testDelta gtest)
target_link_libraries(testDelta ${PNL_LIBRARIES})