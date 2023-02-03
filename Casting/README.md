#
<h1 align="center">Casting</h1>

Casting functions:

* static_cast 
* dynamic_cast

In C++ there are casting of primitive types and casting in inheritance (up and down). The difference between them is that  the first to perform Casting during the roll and the second during the run.
Casting functions


* reinterpret_cast 

Performs unsafe casting.

```cpp

#include <iostream>
using namespace std;


class Point{
protected:
    int x;
    int y;
public:
    Point():x(0),y(0){};
    Point(int x_ , int y_):x(x_),y(y_){};
    void show(){
        cout << "(" << x << ", " << y << ")" << endl;
    }

};


class Complex{
public:
    Complex():Point(){};
    Complex(int x,int y): Point(x,y){};
    void show(){
        cout << x << x << " + " << y << "i" << y << endl;
    }
}

int main(int argc , const char * argv[]){
    Point A(3,4) , *B=new Complex(3,4);
    A.show();
    B->show();
    static_cast<Complex>(B)->show();
    return 0;
}
-----------------------------

(3, 4)
(3, 4)
3 + i4

```