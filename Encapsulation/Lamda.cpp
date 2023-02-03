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