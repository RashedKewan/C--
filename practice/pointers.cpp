#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

int main(int argc , const char * argv[]){
    vector<int> v = {1,2,3,4};
    int arr[]{1,2,3,4};
    int* ptr{arr}; 
    cout << arr << &v << endl;

    return 0;
}