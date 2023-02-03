#include <iostream>
using namespace std;


class MyInt{
    int x;
    virtual void inc(){ x++;}
public:
    MyInt():x(0){}
    MyInt(int x_):x(x_){}
    void print(){cout << x << endl;}
};



class MyInt_Public{
    
public:
    int x;
    virtual void inc();
    MyInt_Public(){}

};

int main(int argc , const char * argv[]){
    MyInt X(5);
    X.print();
    MyInt_Public& Y = reinterpret_cast<MyInt_Public&>(X);
    Y.inc();
    X.print(); 
   return 0;
}