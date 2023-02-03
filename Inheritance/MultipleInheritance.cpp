#include <iostream>
using namespace std;

class A{

protected:
    int x;

public:

    A() : x(0) {}
    A(int x_) : x(x_) {}

    virtual void print(){ cout << x << endl; }
};

class B{
protected:
    int y;

public:

    B() : y(0) {}
    B(int y_) : y(y_) {}

    virtual void print(){ cout << y << endl; }
};

class C : public A, public B{
public:
    C() : A(), B() {}
    C(int x, int y) : A(x), B(y) {}

    void print(){
        cout << "( " << x << ", " << y << " )" << endl;
    }
};

int main(int argc , const char * argv[]) {

    C c(1,2);
    c.print();

    return 0;
}
