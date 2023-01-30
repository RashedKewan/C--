# *Why Do We Need Copy Constructor*
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
}
```
We want to implement `Vec`, the implementation could be:

```cpp
class Vec{
    int* p;
    int len;
    
    public:
    Vec();
    Vec(int length);
    void print();

    int& operator [] (int i ){
        return p[i];
    }
    
};

Vec::Vec(): p(nullptr) ,len(0){}
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
When the program is run, it will output the following:
```
constructor
1       1       1       1       1
1       1       1       1       1
1       1       1       10      1
1       1       1       10      1
```
This behavior is unacceptable because a change of vector leads to a change of vector b.
Notice that we constructed two vectors but only ran the constructor once. Why?

The answer is simple, vector b compiler built by default Copy Constructor. And this constructor simply copies the fields. 

That's why we accepted that two pointers are points to the same place in memory.
To solve the problem you need to write Constructor Copy!

We need first to add the copy constructor to Vec class:

```cpp
class Vec{
    .
    .
    .

    public:
    Vec(Vec& vec);

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

Vec::Vec(Vec& vec):len(vec.len) , p(new int[vec.len]){

    for(int i = 0 ; i<len ; i++){
        p[i] = vec[i];
    }
    cout << "Copy Constructor" << endl;
}

.
.
.

```

When the program is run, it will output the following:
```
constructor
1       1       1       1       1
1       1       1       1       1
1       1       1       1       1
1       1       1       10      1
```