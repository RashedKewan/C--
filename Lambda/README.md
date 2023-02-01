#
<h1 align="center"> Lambda</h1>

Syntax of lambda expression in C++:

 [ **list of closure vareables** ]( **list of arguments** ) -> Return_Type { **Body** }

**Return_Type** - not mandatory, it should be written only in case the expression has several return operators that return different types.
Ex:
```cpp
int main(int argc,const char * argv[]){
    int y=0;
    std::function<int(int)> A = [](int x){return x+5;};
    std::function<int(void)> B = [&y](){
        y = 8;
        return y;};
    std::cout << A(3) << " " << B() << y;
    return 0;
}
```
To get access to closed variables in the body of a lambda expression, you have to write their names in square brackets, you can also use
**= , &** characters.
|              |                                                                                      |
|:---          |:---                                                                                  |
| []           |  Closed variables are not used                                                       |
| [&]          |  Every closed variable is accessed by reference                                      |
| [=]          |  Every closed variable is accessed by value                                          |
| [y, x]       |  only x and y are accessed by value                                                  |
| [&y, &x]     |  There is access by reference only to x and y                                        |
| [&y, x]      |  There is access by reference to y and by value to x                                 |
| [=, &x , &y] | has access by value to every closed variable except x, y and access to x, y is by r  |