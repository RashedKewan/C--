#
<h1 align="center"> Destructor</h1>

## *Why Do We Need Destructor* ?
Suppose we have the following main:
```cpp
#include <iostream>
using namespace std;

int main(int argc , const char * argv[] ){
    int n = 5;
    Vec a(n);
    for (size_t i = 0; i < n; i++)
    {
        a[i] = 1;
    }
    
    Vec b = a;
    a.print();
    b.print();

    b[3] = 10;
    
    a.print();
    b.print();

    return 0;
```
The implement of `Vec` is:
```cpp

class Vec{
    int* p;
    int len;
    
    public:
    Vec();
    Vec(Vec& vec);
    Vec(int length);
    void print();

    int& operator [] (int i ){
        return p[i];
    }
    
};

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
The memory was allocated twice, but never freed.
To solve this we need to implement the Destructor:
```cpp
class Vec{
    .
    .
    .

    public:
    // Destructor
    ~Vec();

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

// Destructor Implementation
Vec::~Vec(){
    if(!p){
        delete[] p;
    }
    cout << "destructor" << endl;
}

.
.
.

```

When the program is run, it will output the following:
```
constructor
Copy Constructor
1       1       1       1       1
1       1       1       1       1
1       1       1       1       1
1       1       1       10      1
destructor
destructor
```