#include <iostream>
using namespace std;


class MyInt{
    int x;
public:
    MyInt():x(0){}
    MyInt(int x_):x(x_){}
    void print(){cout << x << endl;}
};

union U{
    MyInt X;
    int y;
    U(){}
};

int main(int argc , const char * argv[]){
    U u;
    u.X =  MyInt(5);
    u.X.print();
    u.y = 10;
    u.X.print();
    return 0;
}