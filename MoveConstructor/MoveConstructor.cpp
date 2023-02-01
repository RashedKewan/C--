// why do we need a copy constructor?
// suppose we have this situation
#include <iostream>
using namespace std;
class Vec{
    int* p;
    int len;
    
    public:
    Vec();
    Vec(Vec& vec);
    Vec(Vec&& vec);
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

// Optimized Move Constructor Implementation

Vec::Vec(Vec&& vec) :len(move(vec.len)) , p(vec.p){
    vec.p = nullptr;
    cout << "Move Constructor" << endl ;
}

// Vec::Vec(Vec&& vec):len(vec.len) , p(new int[vec.len]){
//     for(int i = 0 ; i<len ; i++){
//         p[i] = vec[i];
//     }
//     cout << "Move Constructor" << endl;
// }

Vec::Vec(int length): len(length),p(new int[length]){
    cout << "constructor" << endl;
}
void Vec::print(){
    for(int i=0 ; i < len; i++){
        cout << p[i] << '\t';
    }
    cout << endl;
}



///////////     MAIN     /////////////
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