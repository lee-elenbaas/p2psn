#include <iostream>
#include "tests/test_task.h"
#include "tests/full_polynomial_tests.h"

int main(int argc, char **argv) {
    using namespace std;
    using namespace lee::tests;
    using namespace lee::tests::math::polynomial;
        
    cout << "Math unit tests." << endl;
    
    full_polynomial_ctr_test t1;
    
    cout << t1 << endl;
    
    return 0;
}
