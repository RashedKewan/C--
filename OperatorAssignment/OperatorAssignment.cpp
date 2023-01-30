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
    Vec(int length);
    ~Vec();
    void print();

    int& operator [] (int i ){
        return p[i];
    }
    
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


///////////     MAIN     /////////////
int main(int argc , const char * argv[] ){
    int n = 5;
    Vec a(n);
    for (size_t i = 0; i < n; i++)
    {
        a[i] = 1;
    }
    
    Vec b ;
    b = a;
    a.print();
    b.print();

    b[3] = 10;
    
    a.print();
    b.print();

    return 0;
}