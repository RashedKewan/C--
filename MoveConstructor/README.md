#
<h1 align="center"> Move Constructor</h1>

## *Why Do We Need Move Constructor* ?
Suppose we have the following main:
```cpp
#include <iostream>
using namespace std;
int main(int argc , const char * argv[] ){
    int n = 5;
    Vec a(n) , b(n) , c(n);
    for (size_t i = 0; i < n; i++)
    {
        a[i] = 1;
        b[i] = i;
        c[i] = 2*i;
    }
    
    
    // Vec d = a + ( b + (c + a));
    Vec temp1 = c + a;
    Vec temp2 = b + temp1;
    Vec d = a + temp2;

    a.print();
    b.print();
    c.print();
    d.print();

    return 0;
}
```
The implement of `Vec` is after adding to our own class an operator + and calculate an expression a + ( b + ( c + a )):
```cpp
class Vec{
    int* p;
    int len;
    
    public:
    Vec();
    Vec(Vec& vec);
    Vec(int length);
    ~Vec();
    void print();

    int& operator [] (int i ){
        return p[i];
    }

    void operator = (Vec& vec){
        if(this == &vec)
            return;
        if(len != vec.len){
            delete[] p;
            len = vec.len;
            p = new int [len];
        }
        for(int i=0 ; i<len ; i++){
            p[i] = vec[i];
        }
        cout << "Assignment Operator" << endl;
    }

    Vec operator + (Vec& vec){
        if(len != vec.len){
            return *this;       
        }
        Vec ret(len);
        for(int i=0 ; i<len ; i++){
            ret[i] = p[i] + vec[i];
        }
        return ret;
    }
};

Vec::~Vec(){
    if(!p){
        delete[] p;
    }
    cout << "destructor" << endl;
}
Vec::Vec(): p(nullptr) ,len(0){}

Vec::Vec(Vec& vec):len(vec.len) , p(new int[vec.len]){

    for(int i = 0 ; i<len ; i++){
        p[i] = vec[i];
    }
    cout << "Copy Constructor" << endl;
}

Vec::Vec(int length): len(length),p(new int[length]){
    cout << "constructor" << endl;
}
void Vec::print(){
    for(int i=0 ; i < len; i++){
        cout << p[i] << '\t';
    }
    cout << endl;
}

```
Note that this program is not even compiled, because in the line :

> vec  temp1 = a + c  

we build a temp1 object by rvalue
And we haven't defined the Constructor Move.
Define Constructor Move naively (like Constructor Copy):

```cpp
class Vec{
    .
    .
    .

    public:
    // Move Constructor that receives reference to rvalue
    Vec(Vec&& vec);

    .
    .
    .
    
};
```


Then we need to implement it, in my situation im going to implement it out of the class:


```cpp
.
.
.

// Move Constructor Implementation
Vec::Vec(Vec&& vec): len(vec.len) , p(new int[vec.len]){
    for(int i=0 ; i<len ; i++){
        p[i] = vec[i];
    }
    cout << "Move Constructor" << endl ;
}

.
.
.

```


After running the program will output:
```
constructor
constructor
constructor
constructor
Move Constructor
destructor
constructor
Move Constructor
destructor
constructor
Move Constructor
destructor
1       1       1       1       1
0       1       2       3       4
0       2       4       6       8
2       5       8       11      14
destructor
destructor
destructor
destructor
destructor
destructor
```
Program already works but we allocated memory 9 times to build 4 vectors. 

The reason is simple: for example in a row:

> vec  temp1 = a + c   

for variable temp1 we re-allocated memory instead of using the memory already allocated for  **a + c** .

We will optimize the code:


```cpp
.
.
.

// Move Constructor Implementation
Vec::Vec(Vec&& vec): len(vec.len) , p(vec.p){
    vec.p = nullptr;
    cout << "Move Constructor" << endl ;
}

// for rvalue
void operator = (Vec&& vec){
    if(this == &vec)
        return;
    len = vec.len;    
    p = vec.p;
    vec.p = nullptr;
    cout << "Assignment Move Operator" << endl;
}

Vec operator + (Vec& vec){
    if(len != vec.len){
        return *this;       
    }
    Vec ret(len);
    for(int i=0 ; i<len ; i++){
        ret[i] = p[i] + vec[i];
    }
    return move(ret);
}

Vec operator + (Vec&& vec){
    if(len != vec.len){
        return *this;       
    }
    for(int i=0 ; i<len ; i++){
        vec[i] += p[i];
    }
    return move(vec);
}

.
.
.

```

```cpp
int main(int argc , const char * argv[] ){
    int n = 5;
    Vec a(n) , b(n) , c(n);
    for (size_t i = 0; i < n; i++)
    {
        a[i] = 1;
        b[i] = i;
        c[i] = 2*i;
    }
    
    
    Vec d = a + ( b + (c + a));
    // Vec temp1 = c + a;
    // Vec temp2 = b + temp1;
    // Vec d = a + temp2;

    a.print();
    b.print();
    c.print();
    d.print();

    return 0;
}
```
output:
```
constructor
constructor
constructor
constructor
Move Constructor
destructor
Move Constructor
Move Constructor
destructor
destructor
1       1       1       1       1
0       1       2       3       4
0       2       4       6       8
2       5       8       11      14
destructor
destructor
destructor
destructor
```

We added a + operator that receives an rvalue We changed Constructor Move We added an Assignment Move operator and we got that there
Already exactly 4 memory allocations.