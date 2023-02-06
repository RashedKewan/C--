#
<h1 align="center">STL</h1>

***STL*** contains many different collections and we will look at some of them :

* vector
* string 
* list 
* set 
* map 
* regex

There is another version of a loop for working with collections :
```cpp
for ( type x : collection){
            ...
}
```
#  ***vector***

### **Construcors :**
----
|   |
|:--|
|vector<type>(size)
|vector<type>(size, value)

### **Operators :**
----
|   |
|:--|
|operator =
|operator [ ]
|operator ==
|operator !=
|operator  <
|operator  <=
|operator  >
|operator  >=
### **Functions :**
----
|   |                               |
|:--|:--                            |
|vector <type>::iterator begin()    |Functions return iterators of the first  term of a vector.
|vector <type>::iterator end()      |Functions return iterators of the last term of a vector.
|type *data()                       |Returns a pointer to an array.
|bool empty()                       |Checks whether the vector is empty.
|size_t size()                      |Returns length (in use).
|size_t clear()                     |Deletes all organs.
|iterator insert( iterator pos, const T& value )                     |Inserts a member before a pos place.
|iterator insert( const_iterator pos, InputIt first , InputIt last );|Inserts members from first to last before pos. insert functions return an iterator to the first element inserted.
|iterator erase( iterator pos )                      | Delete the member in pos index
|iterator erase( iterator first , iterator last );   | Deletes members from first place to last place. The erase functions return an iterator of the first element after the elements being erased.
|void push_back( const T& value );                   | Inserts a member at the end of the vector.
|void pop_back();                                    | Deletes a member from the end of the vector.


### **Examples :**
----

```cpp
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

------------------------
[ 3 13 5 7  ]
[ 3 13 5 7 25 99  ]

```

#  ***string***

For the string type, there are all previous functions ***( which are available for vectors )*** and more operators and the following functions:

|   ||
|:--|:--|
|operator +=|operator that concatenates the second operand to the first operand.
|operator +|operator returns a new string which is a concatenation of operands.
|string substr (size_t pos, size_t len)|operator returns a substring
|size_t find (const string& str, size_t pos = 0) |A function searches for a string  named str starting from position pos in our string and returns the position of the first letter in the first search.
|size_t find (const char* str, size_t pos = 0)   |A function searches for a  C-string named str starting from position pos in our string and returns the position of the first letter in the first search.
|int compare (const string& str)                 | Compares with a string or substring and returns 0 in case of equality.|
|int compare (size_t pos, size_t len, const string& str) |Compares with a string or substring and returns 0 in case of equality.|
|int compare (size_t pos, size_t len, const string& str, size_t subpos , size_t sublen) |Compares with a string or substring and returns 0 in case of equality.|



#  ***list***

For the list type, there are all previous functions ***( which are available for vectors )*** except for operator [] and the following functions:
|||
|:--|:--|
| void merge( list& other )                                 | where comp is a realization of b < a
| void merge( list& other , BinaryPredicate comp )          |where comp is a realization of b < a
| bool comp(const Type &a, const Type &b)                   | A function executes a merge operation and we will note that both the list itself and the other list must be sorted.
| void unique()                                             | where pred is a realization of b == a
| void unique( BinaryPredicate pred )                       | where pred is a realization of b == a
| bool pred(const Type &a, const Type &b)                   | A function deletes equal members (except the first) that are in a sequence.
| void sort()                                               | where comp is a realization of b < a
| void sort( BinaryPredicate comp )                         | where comp is a realization of b < a
| bool comp(const Type &a, const Type &b)                   | Sorting a list.


#  ***set***
For type set there are functions:
* begin()
* end()
* operator=
* empty()
* size()
* clear()

that work like with Vector.
and functions:
|||
|:--|:--|
|pair <iterator , bool > insert (const value_type& val)         |A function inserts the member into the group and returns an ordered pair set where p.first is an iterator of this member and p.second is true if there was an insertion and false if this member was in the group.
|iterator erase (const_iterator position)                       |Functions delete the members from the group and return an iterator to the thirsty member after deleted members
|size_type erase (const value_type& val)                        |it returns the number of deleted members.
|iterator erase (const_iterator first , const_iterator last)    |deleted in range of (last, first)
|iterator find (const value_type& val)                          |A function searches for a member and returns its iterator. If it does not exist, returns end
|size_type count (const value_type& val)                        |A function returns the number of members that are identical to a certain member
|iterator lower_bound (const value_type& val)                   |Function returns an iterator of first term t that satisfies t ⩾ val
|iterator upper_bound (const value_type& val)                   |Function returns an iterator of first term t that satisfies t > val



# ***Complexity of operations with collections***

|Collection |Search |Access |Delete |Insert|
|:--|:--|:--|:--|:--|
| string / vector |Sorted: O(log n) , Other: O(n) |Back: O(1) , Other: O(n)  | O(1) |Back: O(1) or O(n) , Other: O(n)  
|list|O(n) |Back / Front: O(1), With iterator: O(1), Index: O(n) |Back / Front: O(1), With iterator: O(1), Index: O(n) |Back / Front: O(1), With iterator: O(1), Index: O(n) 
|map / set|O(log n) | O(log n)  ||O(log n)  