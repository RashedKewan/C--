#
<h1 align="center">Encapsulation</h1>


**Encapsulation** in the C++ language is performed by reserved words private and protected.
Is it really impossible to access a private variable or method outside the class? Answer is no!!! Let's look at some options
such as:

* Access to the private field by `pointer` :

```cpp
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

-----------------------------
5
20
```
* Access to the private field by `union` :
```cpp
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

-----------------------------
5
10
```
* Access to the private method by `cast_reinterpret` :
```cpp
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


-----------------------------
5
6
```

These examples explain to us that the use of public or protected is more of an agreement than a prohibition.
Is there another encapsulation? The answer is yes, for example encapsulation by Lambda expression:


```cpp
#include <iostream>
#include <functional>
using namespace std;


void inc(int x, function<void(int)>& SetX , function<int(void)>& GetX , function<void(void)>& DelX){
    int* p = new int;
    *p = x;
    SetX = [p](int x){*p = x;};
    GetX = [p](){return *p;};
    DelX = [p](){delete p;};

}


int main(int argc , const char * argv[]){
    int x = 7;
    function<void(int)> SetX;
    function<int(void)> GetX ;
    function<void(void)> DelX;

    inc( x , SetX , GetX , DelX );
    cout << GetX() << endl;
    SetX(12);
    cout << GetX() << endl;
    SetX(20);
    cout << GetX() << endl;
    DelX();

    return 0;
}

-----------------------------
7
12
20
```
The place in memory that we allocated in the Inc function can only be accessed through the SetX, GetX and DelX functions. 

Note that after running the Inc function the pointer p no longer exists and the address of this location in dynamic memory exists only in the SetX, GetX and DelX functions who received it (by value).