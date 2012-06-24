#include <iostream>
#include "tests/test_task.h"
#include "tests/polynomial/full_polynomial_tests.h"
#include "tests/modulu/mod_tests.h"
#include "tests/bitsetint/bitsetint_tests.h"

int main(int argc, char **argv) {
    using namespace std;
    using namespace lee::tests;
    using namespace lee::tests::math::polynomial;
    using namespace lee::tests::math::modulu;
    using namespace lee::tests::math::bitsetint;
    
    cout << "Math unit tests." << endl;
    
    full_polynomial_ctr_test p1;
    mod_ctr_test m1;
    mod_stream_test m2;
    bitsetint_ctr_test i1;
    
    cout 
      << p1 << endl
      << m1 << endl
      << m2 << endl
      << i1 << endl;
    
    return 0;
}
