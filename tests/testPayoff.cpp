//
// Created by simon on 12/09/19.
//
#include <iostream>
#include <assert.h>
#include "../src/CallOption.h"

using namespace std;

void test_call_payoff(){
    PnlMat* matrix = pnl_mat_create_from_scalar(10,1,12.5);
    CallOption option(10,10,1,1);
    double res1 = option.payoff(matrix);
    cout << res1 << endl;

    CallOption optionBis(19,10,1,1);
    double res2 = optionBis.payoff(matrix);
    cout << res2 << endl;
    pnl_mat_free(&matrix);

    assert(res1 == 2.5);
    assert(res2 == 0);


}

int main(void){
    test_call_payoff();
}

