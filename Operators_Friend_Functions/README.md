#
<h1 align="center">Operators & Friend Functions</h1>


A **friend function** (operator) is a function that is defined in a class but does not belong to it.
It is not a class method, however it has access to all fields and methods of a class.

To understand what such functions are for, let's go back to the vec class.

```cpp
#include <iostream>
using namespace std;

class Vec{

    int len;
    int* p;

public:
    // empty constructor
    Vec();
    // copy constuctor
    Vec(Vec& vec);
    // move constructor
    Vec(Vec&& vec);
    // destructor
    ~Vec();
    // constructor according to the length
    Vec(int len);

    void print();
    void operator = (Vec& other);
    void operator = (Vec&& other);

    int& operator [] (int i){return p[i];}
    
    Vec operator + (Vec& other){
        if(other.len != len){
            return *this;
        }
        Vec ret(len);
        for (size_t i = 0; i < len; i++)
        {
            ret[i] = other[i] + p[i];
        }
        return move(ret); 
    }

    Vec operator + (Vec&& other){
        if(other.len != len){
            return *this;
        }
        
        for (size_t i = 0; i < len; i++)
        {
            other[i] += + p[i];
        }
        return move(other); 
    }
};
Vec::Vec():len(0) , p(nullptr){}
Vec::~Vec(){
    delete[] p;
    cout << "destructor" << endl;
}
Vec::Vec(int length):len(length) , p(new int[length]){
    cout << "constructor" << endl;
}
Vec::Vec(Vec& vec):len(vec.len) , p(new int[vec.len]){
    cout << "copy_constructor" << endl;
}
Vec::Vec(Vec&& vec):len(move(vec.len)) , p(vec.p){
    vec.p = nullptr;
    cout << "move_constructor" << endl;
}

void Vec::print(){
    for (size_t i = 0; i < len; i++)
    {
        cout << p[i] << '\t';
    }
    cout << endl;
    
}
```


```cpp
int main(int argc , const char argv[]){
    int n=5;
    Vec a(n) , b(n);
    for (size_t i = 0; i < n; i++)
    {
        a[i] = 1;
        b[i] = i;
    }
    
    Vec c = a + (b+a);
    Vec d = (a+b) + a;

    a.print();
    b.print();
    b.print();
    d.print();

    return 0;
}
```
output :
```
constructor
constructor
constructor
move_constructor
destructor
move_constructor
destructor
constructor
move_constructor
destructor
move_constructor
destructor
1       1       1       1       1
0       1       2       3       4
0       1       2       3       4
2       3       4       5       6
destructor
destructor
destructor
destructor
```
Note that in the line :
>  Vec c = a + ( b + a )

we allocated memory once,but in the line 
> Vec d = (a+b) + a;

we allocated memory twice.
This is done because in the first case we once called

> Vec operator + (Vec& other)

and a second time to

> Vec operator + (Vec&& other)

and in the second case twice to

> Vec operator + (Vec& other).

The problem is that we don't know if left argument of + is rvalue or lvalue
( we only have knowledge about right argument ).
A solution is the **friend operator!**
We need to handle all the optiones that can occure for the + operator,like:

|      Situation    |      Function                             | 
|   :----           |      :----                                |
| rvalue + rvalue   | friend Vec operator + (Vec&& a , Vec&& b) |
| rvalue + lvalue   | friend Vec operator + (Vec&& a , Vec& b)  |
| lvalue + rvalue   | friend Vec operator + (Vec& a , Vec&& b)  |
| lvalue + lvalue   | friend Vec operator + (Vec& a , Vec& b)   |


```cpp

class Vec{

    int len;
    int* p;

public:
    Vec();
    // copy constuctor
    Vec(Vec& vec);
    // move constructor
    Vec(Vec&& vec);
    Vec(int len);
    // destructor
    ~Vec();

    void print();
    int& operator [] (int i){return p[i];}
    void operator = (Vec& other);
    void operator = (Vec&& other);

    friend Vec operator + (Vec& a , Vec& b ){
        if(a.len != b.len )return a;
        Vec ret(a.len);
        for (size_t i = 0; i < a.len; i++)
        {
            ret[i] = a[i] + b[i];
        }
        return move(ret);
    }

    friend Vec operator + (Vec&& a , Vec& b ){
        if(a.len != b.len )return a;
        for (size_t i = 0; i < a.len; i++)
        {
            a[i] += b[i];
        }
        return move(a);
    }
 

    friend Vec operator + (Vec& a , Vec&& b ){
        if(a.len != b.len )return a;
        for (size_t i = 0; i < a.len; i++)
        {
            b[i] += a[i];
        }
        return move(b);
    }

   friend Vec operator + (Vec&& a , Vec&& b ){
        if(a.len != b.len )return a;
        for (size_t i = 0; i < a.len; i++)
        {
            a[i] += b[i];
        }
        return move(a);
    }
};
```
## Nice to know aboute std::move function:
The `std::move` function is a standard library function in C++ that is used to cast an lvalue expression to an rvalue expression. An rvalue expression is an expression that can appear on the right-hand side of an assignment, and it represents an object that is typically either a temporary value or is about to be moved from.

The main purpose of std::move is to transfer ownership of an object from one scope to another. This can be useful, for example, when returning a large object from a function, or when using move semantics to implement efficient and scalable algorithms.

> *When an object is moved, its resources (such as memory or file handles) are transferred to the new owner without making a copy. This can be more efficient than copying the object, especially for large or complex objects.*

It's important to note that after a move operation, the original object is left in a valid but unspecified state, and it should not be used anymore. This is why std::move is often used in conjunction with move constructors, which are constructors that are specifically designed to take ownership of an object's resources and leave the original object in a valid but unspecified state.


