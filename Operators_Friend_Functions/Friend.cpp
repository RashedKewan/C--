#include <iostream>
using namespace std;

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