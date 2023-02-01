#include <iostream>
#include <functional>

template<typename T> 
std::function<T(T)> composition(std::function<T(T)> f , std::function<T(T)> g){
    return [f , g](T x){ return f(g(x));};
}

int F(int x){
    return x * x;
}

int G(int x){
    return x + x;
}

int main(int argc , const char * argv[]){
    std::function<int(int)> FG = composition<int>(F,G);
    std::cout << FG(3) << std::endl;
    return 0;
}