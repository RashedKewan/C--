#include <iostream>
using namespace std;

class MyInt{
    int x;
public:
    MyInt():x(0){}
    MyInt(int x_):x(x_){}
    void print(){ cout << x << endl ; }
};

int main(int argc , const char * argv []){
    MyInt X(5);
    X.print();
   
    int* int_ptr = (int*)(&X);
    *int_ptr = 20;
    X.print();
    return 0;
}