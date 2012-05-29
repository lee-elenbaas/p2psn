#include <iostream>
#include "test_task.h"
#include "full_polynomial_tests.h"

int main(int argc, char **argv) {
    using namespace std;
    using namespace lee::tests;
    using namespace lee::tests::math::polynomial;
        
    cout << "Math unit tests." << endl;
    
    cout << test_task{"full_polynomial ctor", full_polynomial_ctr_test};
    
    return 0;
}
