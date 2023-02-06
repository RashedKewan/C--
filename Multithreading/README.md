#
<h1 align="center">Multithreading</h1>


The basic tool for working with threads is the std::thread class.
* A child of this class receives a function or a lambda expression, and produces a thread) runs this function in the new thread.)
* The ***join()*** method of this class transfers the control to the mother function, only after the thread finishes its work.
* Function ***std::thread::concurrency_hardware()*** returns the number of concurrent threads supported by the available hardware implementation.

As an example we will implement map multithreaded which mean we will implement the function that receives a function ***F*** and a vector ***v*** and returns :
```
map(F, v) = (F(v[0]), F(v[1]), ..., F(v[n-1]))
```
