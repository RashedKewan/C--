#include <iostream>
#include <functional>

int main(int argc,const char * argv[]){
    int y=0;
    std::function<int(int)> A = [](int x){return x+5;};
    std::function<int(void)> B = [&y](){
        y = 8;
        return y;};
    std::cout << A(3) << " " << B() << y;
    return 0;
}