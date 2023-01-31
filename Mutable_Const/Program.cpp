#include <iostream>
using namespace std;

class Point{
    int x;
    int y;
    mutable double weight;
    
    public:

    Point():x(0) , y(0) , weight(0){}
    Point(int x_,int y_):x(x_) , y(y_) , weight(0){}

    void set_x(int x_){x=x_;}
    void set_y(int y_){y=y_;}
    void set_w(int w){weight=w;}
    void set_w(int w)const{weight=w;}
    void print(){
        cout << "( "<< x << " , " << y << " , " << weight << " )" << endl;
    }
    void print()const{
        cout << "const ( "<< x << " , " << y << " , " << weight << " )" << endl;
    }
};

int main(int argc , const char argv[]){
    Point A(1,2);
    const Point B(3,4);

    A.set_w(2.3);
    B.set_w(3.4);

    A.print();
    B.print();
    return 0;
}