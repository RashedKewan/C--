# Templates of functions.

Let's look at the following problem: we need to implement function:
> *F(x) = x<sup>2</sup>*
* 

which knows how to work with x of type double and with x of type int.

1. Solution :

Is to write one function get double and returns double:
```cpp

double square (double x){
   return x*x;  
}

```
this functuon is going to work  for the both variable types,but the problem when we handle the variable type int it going to returns a double answer that requires **twice** as much space in memory.

2. Solution :

To solve this we use the Overload concept :
```cpp

double square (double x){
   return x*x;  
}

```
```cpp

int square (int x){
   return x*x;  
}

```
This solution no longer wastes the cache, but if we want to run this function on another type of objects, we will need more load.

3. Solution :
```cpp
#include <iostream>

template<typename T> T square (T x){
    return x*x;
}

int main(int argc , const char * argv[]){
    cout << square<int>(5) << "" << square<double>(5.1) << endl;
    return 0;
}

------------------------------
25  25.01

```

In this case the square function can receive any object, for which the * operator is defined.
```cpp
template <typename T1, typename T2, ...>  ret_type  Name(params){

}
```
When calling this function, we must write in triple brackets, the types.

# Templates For Classes

The general form of a template for a class is similar to a template of  function:

```cpp
template <typename T1, typename T2, ...>  class Name(params){

}
```

For example, to change our `vec` class to a class template that is suitable not only for int vectors but for all kinds of types is sufficient Make the following changes:
```cpp
template <typename T>
class vec{
   T* p;
   int len;

public:
   vec() : p(nullptr), len(0){}

   vec(int length) : len(length), p(new T[length]){
      cout << "constructor" << endl;
   }

   vec(vec& a) : len(a.len), p(new T[a.len]){
      for (int i = 0; i < len; i++)
      p[i] = a[i];
      cout << "copy_constructor" << endl;
   }

   vec(vec&& a) : len(a.len){
      p = a.p;
      a.p = nullptr;
      cout << "move_constructor" << endl;
   }

   ~vec(){
      if(!p) delete[] p;
      cout << "destructor" << endl;
   }

   void operator = (vec& a){
      if (&a == this) return;
         if(len != a.len){
         delete[] p;
         len = a.len;
         p = new T[len];
      }

      for (int i = 0; i < len; i++)
         p[i] = a[i];
      cout << "ass_operator" << endl;
   }

   void operator = (vec&& a){
      if (&a == this) return;

      len = a.len;
      p = a.p;
      a.p = nullptr;

      cout << "ass_move_operator" << endl;
   }

   friend vec operator + (vec& a, vec& b){
      if (a.len != b.len) return a;

      vec ret(a.len);
      for (int i = 0; i < a.len; i++)
         ret[i] = a[i] + b[i];
      return move(ret);
   }
   friend vec operator + (vec& a, vec&& b){
      if (a.len != b.len) return a;

      for (int i = 0; i < a.len; i++)
         b[i] += a[i];
      return move(b);
   }

   friend vec operator + (vec&& a, vec& b){
      if (a.len != b.len) return a;

      for (int i = 0; i < a.len; i++)
         a[i] += b[i];
      return move(a);
   }

   friend vec operator + (vec&& a, vec&& b){
      if (a.len != b.len) return a;

      for (int i = 0; i < a.len; i++)
         a[i] += b[i];
      return move(a);
   }

   T& operator [] (int i) { return p[i]; }

   friend ostream& operator <<(ostream& stream , vec& a){
      for (int i = 0; i < a.len; i++)
         stream << a[i] << "\t";
      return stream;
   }
   friend ostream& operator <<(ostream& stream , vec&& a){
      for (int i = 0; i < a.len; i++)
         stream << a[i] << "\t";
      return stream;
   }
};

int main(int argc , const char * argv[]) {
   int n = 5;
   vec<double > a(n), b(n);
   for(int i = 0; i < n; i++){
      a[i] = 1;
      b[i] = i;
   }
   vec<double > c = a + (b + a);
   vec<double > d = (a + b) + a;
   cout << a << endl;
   cout << b << endl;
   cout << c << endl;
   cout << d << endl;
   return 0;
}

```
Another example of using templates: we will write a function, which receives two functions
```
F : T → T, G : T → T

```
and restores their composition:

```cpp
/*
args : two functions that each one take an arg of type T and return value of type T.

returns:  a function that takes variable of type T the apply the compostion on it.
*/ 
template<typename T> function<T(T)> composition(function<T(T)> f , function<T(T)> g){
   return [f,g](T x){
      return f(g(x));
   };
}
```

```cpp
int F(int x){
   return x * x;
}
```

```cpp
int G(int x){
   return x + x;
}
```

```cpp
int main(int argc , const char * argv[]){
   function<int(int)> FG = composition<int>(F,G);
   cout <<  << endl;
   return 0;
}
------------------------------
36
```