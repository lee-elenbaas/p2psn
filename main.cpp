#include <iostream>
#include "tests/test_task.h"
#include "tests/full_polynomial_tests.h"
#include "tests/mod_tests.h"

int main(int argc, char **argv) {
    using namespace std;
    using namespace lee::tests;
    using namespace lee::tests::math::polynomial;
    using namespace lee::tests::math::modulu;
    
    cout << "Math unit tests." << endl;
    
    full_polynomial_ctr_test p1;
    mod_ctr_test m1;
    
    cout 
      << p1 << endl
      << m1 << endl;
    
    return 0;
}
