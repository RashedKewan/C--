// why do we need a copy constructor?
// suppose we have this situation
#include <iostream>
using namespace std;

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


///////////     MAIN     /////////////
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