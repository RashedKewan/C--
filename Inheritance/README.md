#
<h1 align="center">Inheritance</h1>

In C++ there is three types of inheritance:
|    |          |           |   |
|:-- |:--       |:--        |:--|
| 1  | class b :|public a   | All public fields of `a` are public fields of `b` and all protected fields of `a` are protected fields of `b`
| 2  | class b :|protected a| All public fields of `a` are protected fields of `b` and all protected fields of `a` are protected fields of `b`
| 3  | class b :|private a  | All public fields of `a` are private fields of `b` and all protected fields of `a` are private fields of `b`

In the `child` class it is possible to override (functions) of the `parent` class

```cpp
#include <iostream>
using namespace std;
class Point{
protected:
    int x;
    int y;
public:
    Point(): x(0),y(0){}
    Point(int x_, int y_): x(x_) , y(y_){}
    void show(){
        cout << "( "<< x << ", "<< y << " )"<< endl;
    }
};

class Complex : public Point{
public : 
    Complex(): Point(){}
    Complex(int x_, int y_): Point(x_ ,y_){}
    void show(){
        cout << x << " + "<< "i" << y << endl;
    }
};

int main(int argc , const char * argv[]){
    Point A(3,4);
    Complex B(3,4);

    A.show();
    B.show();
    B.Point::show();
    
    return 0;
}
```


One of the possibilities of using inheritance is that instead of a reference parameter or a pointer of the parent class type, you can place or
Point to a variable of the child class type (not a mistake). But the behavior of the tread is different here:

```cpp
int main(int argc , const char * argv[]){
    Point A(3,4), *B = new Complex(3,4);

    

    A.show();
    B->show();
    B->Point::show();
    
    return 0;
}
```

To explain to the compiler that it is necessary to look for a show function that corresponds to the object pointed to by the pointer B, show must be defined
as a virtual function in the parent class.

**virtual** simply says to compiler "hey generate virual table for this function so that if it's overwritten you can point to it".

**If we decide not to use virtual, the compiler will search for the function with the given name in the base class.**
```cpp
class Point{
protected:
    int x;
    int y;
public:
    Point(): x(0),y(0){}
    Point(int x_, int y_): x(x_) , y(y_){}
    virtual void show(){
        cout << "( "<< x << ", "<< y << " )"<< endl;
    }
};

class Complex : public Point{
public : 
    Complex(): Point(){}
    Complex(int x_, int y_): Point(x_ ,y_){}
    void show() override{
        cout << x << " + "<< "i" << y << endl;
    }
};
```
#
# Interfaces and abstract classes
If in the definition of a class there appears a line of virtual function declaration with assignment to 0 like:

```cpp
class A{
    ...
public:
    ...
    virtual float fun(double) = 0;
    ...
};

```
This means that fun is a "pure virtual function" and the entire class is **abstract**.

It is impossible to define variables of the abstract class type,
And if another class is inherit from it, then it is not possible to implement variables from this inherited class, **unless the class actually implements
these methods.**

In case the inherited class does not implement this function, the assignment must be made to 0. Otherwise we will receive an error message from the linker.
Informally a class that contains only pure virtual functions is called an **interface.**
And a class that also contains implemented parts is called an **abstract** class.

#
<h1 align="center">Multiple Inheritance</h1>

```cpp

#include <iostream>
using namespace std;


class Point{
protected:
    int x;
    int y;
public:
    Point(): x(0),y(0){}
    Point(int x_, int y_): x(x_) , y(y_){}
    virtual void show(){
        cout << "( "<< x << ", "<< y << " )"<< endl;
    }
};

class Complex : public Point{
public : 
    Complex(): Point(){}
    Complex(int x_, int y_): Point(x_ ,y_){}
    void show() override{
        cout << x << " + "<< "i" << y << endl;
    }
};

int main(int argc , const char * argv[]){
    Point A(3,4) , *B = new Complex(3,4);
    
    A.show();
    B->show();
    B->Point::show();
    
    return 0;
}
--------------------------
( 1, 2)
```
In most cases multiple inheritance works without problems except for cases where it is not well defined, one of these cases is a case
The rhombus :

          A
         / \
        B   C
         \ /
          D
for instance:
```cpp
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

class B : public A{
public:

    B() : A() {}
    B(int x) : A(x) {}
    // implement print method
    virtual void print() override { cout << "B: " << x << endl; }
};

class C : public A{
public:

    C() : A() {}
    C(int x) : A(x) {}
   // implement print method
    virtual void print() override { cout << "C: " << x << endl; }
};

class D : public B, public C{
public:
    D() : B() {}
    D(int x) : B(x) {}

    void print(){
        cout << "D: " << x << endl;
    }
};
```
This code will not be compiled because class D has two copies of variable x, one from B and one from C. 

The solution is all ways in which you can wire the same field to define as virtual and then a class inherits them from the last parent class before the split.

```cpp
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
// virtual keyword added
class B : virtual public A{
public:

    B() : A() {}
    B(int x) : A(x) {}
    // implement print method
    virtual void print() override { cout << "B: " << x << endl; }
};
// virtual keyword added
class C : virtual public A{
public:

    C() : A() {}
    C(int x) : A(x) {}
   // implement print method
    virtual void print() override { cout << "C: " << x << endl; }
};

class D : public B, public C{
public:
// change the super to be A
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
--------------------------
D: 5
```