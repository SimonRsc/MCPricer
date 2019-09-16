//
// Created by simon on 12/09/19.
//
#include <iostream>
#include <assert.h>
#include "../src/CallOption.h"
#include "../src/BasketOption.h"
#include "gtest/gtest.h"
#include "../cmake-build-debug/tests/googletest-src/googletest/include/gtest/gtest.h"
#include "../src/AsianOption.h"
#include "../src/PerformanceOption.h"
#include <sstream>

using namespace std;

class PayoffTests : public ::testing::Test {

protected:
    PnlMat* matrix;
PnlVect *lambda;
    virtual void SetUp() {
        lambda = pnl_vect_create(3);
        LET(lambda,0) = 0.2;
        LET(lambda,1) = 0.35;
        LET(lambda,2) = 0.45;

        matrix = pnl_mat_create(10,4);
        MLET(matrix,0,0) = 3.25;
        MLET(matrix,1,0) = 4.75;
        MLET(matrix,2,0) = 3.98;
        MLET(matrix,3,0) = 5.33;
        MLET(matrix,4,0) = 2.66;
        MLET(matrix,5,0) = 7.81;

        MLET(matrix,0,1) = 8.82;
        MLET(matrix,1,1) = 7.02;
        MLET(matrix,2,1) = 9.0697;
        MLET(matrix,3,1) = 2.22;
        MLET(matrix,4,1) = 2.406;
        MLET(matrix,5,1) = 3.14;

        MLET(matrix,0,2) = 5;
        MLET(matrix,1,2) = 3.52;
        MLET(matrix,2,2) = 2.32;
        MLET(matrix,3,2) = 4.12;
        MLET(matrix,4,2) = 1.97;
        MLET(matrix,5,2) = 6.09;
    }

    virtual void TearDown() {
       pnl_mat_free(&matrix);

    }
    // Objects declared here can be used by all tests in the test case for Foo.
};

//Test basketOption
TEST_F(PayoffTests, BasketTests) {

BasketOption basketOption(lambda,5,5,5,3);
double resultPayoff = basketOption.payoff(matrix);
pnl_mat_free(&matrix);
EXPECT_FLOAT_EQ(resultPayoff,0.4015);
}

//Test a call with a basketOption
TEST_F(PayoffTests, CallWithBasket){
    lambda = pnl_vect_create_from_scalar(1,1);
    BasketOption basketOption(lambda,5,5,5,1);
    PnlMat* matrix = pnl_mat_create_from_scalar(10,1,12.5);
    double result = basketOption.payoff(matrix);
    pnl_mat_free(&matrix);
    EXPECT_FLOAT_EQ(result,7.5);
}

TEST_F(PayoffTests, CallTests) {
    PnlMat* matrix = pnl_mat_create_from_scalar(10,1,12.5);
    CallOption option(10,9,9,1);
    double res1 = option.payoff(matrix);

    CallOption optionBis(19,9,9,1);
    double res2 = optionBis.payoff(matrix);
    pnl_mat_free(&matrix);
    pnl_vect_free(&lambda);

    EXPECT_EQ(res1,2.5);
    EXPECT_EQ(res2,0);

}

TEST_F(PayoffTests, AsianOption){
    AsianOption asianOption(lambda, 3,5,5,3);
    double result = asianOption.payoff(this->matrix);
    EXPECT_NEAR(result,0.90,0.01);
}

TEST_F(PayoffTests,PerformanceOptionTest){
    PerformanceOption perfOption(lambda, 5,5,3);
    double result = perfOption.payoff(this->matrix);
    EXPECT_NEAR(result,1.68497,0.0001);

}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}