#include <iostream>
#include "cvwrapper.h"

using namespace std;
int main() {
    int tpu_len = sail::get_available_tpu_num();
    std::cout << "available tpu: " << tpu_len << std::endl;
    return 0;
}