
#include <iostream>
using namespace std;


class Point{
protected:
    int x;
    int y;
public:
    Point(): x(0),y(0){}
    Point(int x_, int y_): x(x_) , y(y_){}
    virtual void show(){
        cout << "( "<< x << ", "<< y << " )"<< endl;
    }
};

class Complex : public Point{
public : 
    Complex(): Point(){}
    Complex(int x_, int y_): Point(x_ ,y_){}
    void show() override{
        cout << x << " + "<< "i" << y << endl;
    }
};

int main(int argc , const char * argv[]){
    Point A(3,4) , *B = new Complex(3,4);
    
    A.show();
    B->show();
    B->Point::show();
    
    return 0;
}