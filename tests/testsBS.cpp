#include <iostream>
#include <gtest/gtest.h>
#include "../src/BlackScholesModel.hpp"

using namespace std;

class BSTest : public ::testing::Test {

protected:
    PnlRng *rng_;

    BSTest(){
        rng_ = pnl_rng_create(PNL_RNG_KNUTH);
    }

    virtual void SetUp() {
        pnl_rng_sseed(rng_, 0);
    }

    virtual void TearDown() {
    }

    ~BSTest(){
        pnl_rng_free(&rng_);
    }
};

TEST_F(BSTest, test_cholesky) {
    auto *BS = new BlackScholesModel(2, 0.02, 0.5, pnl_vect_create_from_scalar(2, 0.2), pnl_vect_create_from_scalar(2,10), 10, 10);
    PnlMat *L = BS->L_;
    PnlMat *result = pnl_mat_mult_mat(L, pnl_mat_transpose(L));
    PnlMat *id = pnl_mat_create_from_scalar(2,2,0.5);
    pnl_mat_set_diag(id, 1, 0);
    EXPECT_EQ(pnl_mat_isequal(result, id,0.01), 1);
    pnl_mat_free(&result);
    pnl_mat_free(&id);
    delete BS;
}

TEST_F(BSTest, test_bsNext) {
    PnlVect *vol = pnl_vect_create_from_scalar(2, 0.2);
    PnlVect *spot = pnl_vect_create_from_scalar(2,10);
    auto *BS = new BlackScholesModel(2, 0.02, 0, vol, spot, 10, 10);
    pnl_vect_rng_normal(BS->G_, BS->size_, rng_);
    EXPECT_NEAR(0.934, BS->next(1, 0, 0.02), 0.01);
    delete BS;
}

TEST_F(BSTest, test_bs1Dim) {
    PnlVect *vol = pnl_vect_create_from_scalar(1, 0.2);
    PnlVect *spot = pnl_vect_create_from_scalar(1,10);
    auto *BS = new BlackScholesModel(1, 0.02, 0, vol, spot, 10, 10);
    PnlMat *path = pnl_mat_create(11, 1);
    BS->asset(path, 10, 10, rng_);
    double r[11] = {10.000000,
            9.345968,
            6.898286,
            9.966401,
            6.878897,
            5.910790,
            5.012813,
            4.990035,
            5.492639,
            5.422659,
            5.840130};
    PnlMat *result = pnl_mat_create_from_ptr(11,1, r);
    ASSERT_EQ(pnl_mat_isequal(result, path, 0.1), 1);
    pnl_mat_free(&path);
    delete BS;
}

TEST_F(BSTest, test_bs5Dim) {
    PnlVect *vol = pnl_vect_create_from_scalar(5, 0.2);
    PnlVect *spot = pnl_vect_create_from_scalar(5,10);
    auto *BS = new BlackScholesModel(5, 0.02, 0.5, vol, spot, 10, 10);
    PnlMat *path = pnl_mat_create(11, 5);
    BS->asset(path, 10, 10, rng_);
    pnl_mat_free(&path);
    delete BS;
}

TEST_F(BSTest, test_bsAsset2_1Dim) {
    PnlVect *vol = pnl_vect_create_from_scalar(1, 0.2);
    PnlVect *spot = pnl_vect_create_from_scalar(1,10);
    auto *BS = new BlackScholesModel(1, 0.02, 0, vol, spot, 20, 20);
    PnlMat *path = pnl_mat_create(21, 1);
    PnlMat *past = pnl_mat_create_from_scalar(11, 1, 10);

    BS->asset(path, 10, 20, 20, rng_, past);
    double r[21] = {10.000000,
            10.000000,
            10.000000,
            10.000000,
            10.000000,
            10.000000,
            10.000000,
            10.000000,
            10.000000,
            10.000000,
            9.345968,
            6.898286,
            9.966401,
            6.878897,
            5.910790,
            5.012813,
            4.990035,
            5.492639,
            5.422659,
            5.840130,
            4.963433};
    PnlMat *result = pnl_mat_create_from_ptr(21,1, r);
    ASSERT_EQ(pnl_mat_isequal(result, path, 0.1), 1);
    pnl_mat_free(&path);
    delete BS;
}

TEST_F(BSTest, test_bsShift) {
    PnlVect *vol = pnl_vect_create_from_scalar(1, 0.2);
    PnlVect *spot = pnl_vect_create_from_scalar(1,10);
    auto *BS = new BlackScholesModel(5, 0.02, 0, vol, spot, 10, 10);
    PnlMat *shift = pnl_mat_create(10, 5);
    PnlMat *path = pnl_mat_create_from_scalar(10, 5, 10);
    BS->shiftAsset(shift, path, 2, 1, 5, 1);

    EXPECT_EQ(MGET(shift, 5, 2), 20);
    EXPECT_EQ(MGET(shift, 4, 2), 10);
    EXPECT_EQ(MGET(shift, 1, 1), 10);
    EXPECT_EQ(MGET(shift, 9, 4), 10);

    pnl_mat_free(&path);
    delete BS;
}

TEST_F(BSTest, test_bsSimul) {
    PnlVect *vol = pnl_vect_create_from_scalar(5, 0.2);
    PnlVect *spot = pnl_vect_create_from_scalar(5,10);
    auto *BS = new BlackScholesModel(5, 0.02, 0, vol, spot, 10, 10);

    PnlMat *simul = pnl_mat_create(11, 5);

    BS->trend_ = pnl_vect_create_from_scalar(5, 0.2);
    BS->simul_market(simul, 10, 10, rng_);

    pnl_mat_free(&simul);
    delete BS;
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}