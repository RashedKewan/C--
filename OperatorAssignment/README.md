# *Why Do We Need Operator Assignment*
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

When the program is run, it will output the following:
```
constructor
1       1       1       1       1
1       1       1       1       1
1       1       1       10      1
1       1       1       10      1
```
We are back to the same problem, why? 

Because now command:

a = b; 

is running the Assignment operator and not Constructor Copy
Because object b already exists.

To solve this we need to implement the Operator Assignment.

```cpp
class Vec{
    .
    .
    .

    public:
    Vec& operator = (Vec& vec){
        if(this == &vec){
            return;
        }
        if(len != vec.len){
            delete[] p;
            len = vec.len;
            p = new int[len];
        }
        for (size_t i = 0; i < len; i++)
        {
            p[i]=vec[i];
        }
        cout << "Assignment Operator" << endl;

        
    }

    .
    .
    .
    
};
```
When the program is run, it will output the following:

```
constructor
Assignment Operator
1       1       1       1       1
1       1       1       1       1
1       1       1       1       1
1       1       1       10      1
destructor
destructor
```