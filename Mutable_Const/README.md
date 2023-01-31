# *Change Property Value  in Const Class*
To enable changing property value  in const class we need to add mutable before the property.
Suppose we have the following main:
```cpp
#include <iostream>
using namespace std;

int main(int argc , const char argv[]){
    Point A(1,2);
    const Point B(3,4);

    A.set_w(2.3);
    B.set_w(3.4);

    A.print();
    B.print();
    return 0;
}
```
The implement of `Point` is :
```cpp

class Point{
    int x;
    int y;
    mutable double weight;
    
    public:

    Point():x(0) , y(0) , weight(0){}
    Point(int x_,int y_):x(x_) , y(y_) , weight(0){}

    void set_x(int x_){x=x_;}
    void set_y(int y_){y=y_;}
    void set_w(int w ){weight=w;}
    void set_w(int w ) const {weight=w;}

    void print(){
        cout << "( "<< x << " , " << y << " , " << weight << " )" << endl;
    }
    void print()const{
        cout << "const ( "<< x << " , " << y << " , " << weight << " )" << endl;
    }
};

```

Note that since we defined B as a const object, it is not possible to change its x and y fields, but it is possible to change the weight field because we defined
Same as mutable.

Furthermore, we have two print functions and two w_set functions for const and non-const objects.

Note that a function not classed as const cannot work with const objects.