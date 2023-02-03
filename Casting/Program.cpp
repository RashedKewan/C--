#include <iostream>
using namespace std;


class Point{
protected:
    int x;
    int y;
public:
    Point():x(0),y(0){};
    Point(int x_ , int y_):x(x_),y(y_){};
    void show(){
        cout << "(" << x << ", " << y << ")" << endl;
    }

};


class Complex : public Point{
public:
    Complex():Point(){};
    Complex(int x,int y): Point(x,y){};
    void show(){
        cout <<  x << " + " << y << "i" << y << endl;
    }
};


int main(int argc , const char * argv[]){
    Point A(3,4) , *B = new Complex{3,4};
    Point c ={1,2};
    A.show();
    B->show();
    static_cast<Complex*>(B)->show();
    return 0;
}