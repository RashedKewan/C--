#
<h1 align="center">Const & Pointers</h1>

In c++, we can qualify a pointer in several ways. First, we don't have to use const at all. In this case, we have a pointer just as we've been using up to this point. We can change the data the pointer is pointing to, and we can change the pointer itself and make it point somewhere else.

The const qualifier gives us more fine-grained control of what we allow to be changed.

We can have :
* pointers to constants 
* constant pointers 
* constant pointers to constants.

These will be very useful when we pass pointers to
functions. Let's take a look at each one of them.

* In the case of pointers to constants, the data pointed to by the pointers is constant and can't be changed.The pointer itself can change and point elsewhere.

Let's take a look at this example.
```cpp
int high_score{100};
int low_score { 65};
const int *score_ptr { &high_score };
*score_ptr = 50;         // ERROR
score_ptr  = &low_score; // OK
```
We have two integers declared and initialized. These are high score and low score. But this time when we declare the pointer, we use the const qualifier before the type that we point to.

So score pointer is a pointer to an ***integer constant***, and we initialize it to point to high score. If we attempt to change the value of the point to two data, in this case, high score, we'll get a compiler error.

However, we're free to assign another address to the pointer and have it point somewhere else.

```cpp
int high_score{100};
int low_score { 65};
int *const score_ptr { &high_score };
*score_ptr = 50;         // OK
score_ptr  = &low_score; // ERROR
```
In the case of constant pointers, it's the pointer itself that's constant.

So the data pointed to by the pointer can be changed via the pointer.However, the pointer itself cannot be changed and can't point to anything else.

Notice that we still use the const qualifier, however, we use it before the asterisk in the pointer declaration. So we're declaring score pointer as a const pointer to integer.

```cpp
int high_score{100};
int low_score { 65};
const int *const score_ptr { &high_score };
*score_ptr = 50;         // ERROR
score_ptr  = &low_score; // ERROR
```
In this case, it's a constant pointer to constants. We need to use the const qualifier twice in the pointer declaration.So the data pointed to by the pointer is constant and can't change, and the pointer itself is also constant and can't change.

Notice the syntax, score pointer is a constant pointer to an integer constant. In this case, if we try to modify either the data or the pointer, we get compiler errors.

The const qualifier is very useful and it's often used when passing pointers to functions.