#include <iostream>
#include "pnl/pnl_vector.h"

int main(int argc, char **argv) {
    PnlVect *v1, *v2;
    v1 = pnl_vect_create_from_scalar (5, 2.5);
    v2 = pnl_vect_new ();
    pnl_vect_clone (v2, v1);
    std::cout << v1->array;
}
