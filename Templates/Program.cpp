#include <iostream>

template<typename T> T square (T x){
    return x*x;
}

int main(int argc , const char * argv[]){
    std::cout << square<int>(5) << " " << square<double>(5.1) << std::endl;
    return 0;
}