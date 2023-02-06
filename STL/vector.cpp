#include <iostream>
#include <vector>
using namespace std;

void print_vector(const vector<int>& v){
    std::cout << "[ ";
    for(auto num : v){
        std::cout << num  << " ";
    }
    std::cout << " ]"<< endl;
}


int main(int argc , const char * argv[]){
    vector<int> v = {3,13,5,7};
    
    print_vector(v);
    
    v.push_back(25);
    v.push_back(99);
    
    print_vector(v);

    return 0;
}