//
// Created by lamur on 12/09/2019.
//

#include <iostream>
#include <assert.h>
#include <gtest/gtest.h>
#include "../src/BlackScholesModel.hpp"

using namespace std;

class BSTest : public ::testing::Test {

protected:
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    // Objects declared here can be used by all tests in the test case for Foo.
};

TEST_F(BSTest, test_cholesky) {
    auto *BS = new BlackScholesModel(2, 0.02, 0, pnl_vect_create_from_scalar(2, 0.2), pnl_vect_create_from_scalar(2,10));
    PnlMat *L = BS->L_;
    PnlMat *result = pnl_mat_mult_mat(L, pnl_mat_transpose(L));
    PnlMat *id = pnl_mat_create_diag(pnl_vect_create_from_scalar(2,1));
    EXPECT_EQ(pnl_mat_isequal(result, id,0.01), 1);
}

TEST_F(BSTest, test_bsNext) {
    PnlVect *vol = pnl_vect_create_from_scalar(2, 0.2);
    PnlVect *spot = pnl_vect_create_from_scalar(2,10);
    auto *BS = new BlackScholesModel(2, 0.02, 0, vol, spot);
    PnlRng *rng = pnl_rng_create(PNL_RNG_KNUTH);
    pnl_rng_sseed(rng, 0);
    EXPECT_NEAR(0.934, BS->next(1, 0, 1, rng), 0.01);
    pnl_rng_free(&rng);
    pnl_vect_free(&vol);
    pnl_vect_free(&spot);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}