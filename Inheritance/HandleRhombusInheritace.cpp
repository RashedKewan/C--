#include <iostream>
using namespace std;

// Astract Class
class A{
protected:
    int x;

public:


    A() : x(0) {}
    A(int x_) : x(x_) {}

    virtual void print() = 0;
};

class B : virtual public A{
public:

    B() : A() {}
    B(int x) : A(x) {}
    // implement print method
    virtual void print() override { cout << "B: " << x << endl; }
};

class C : virtual public A{
public:

    C() : A() {}
    C(int x) : A(x) {}
   // implement print method
    virtual void print() override { cout << "C: " << x << endl; }
};

class D : public B, public C{
public:
    D() : A() {}
    D(int x) : A(x) {}

    virtual void print() override {
        cout << "D: " << x << endl;
    }
};

int main(int argc , const char* argv[]){

    D d(5);
    d.print();
    return 0;
}