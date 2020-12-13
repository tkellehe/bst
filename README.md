# bst
A library like [**B**oo**st** _C++_](https://github.com/boostorg), but for C.
Provides compile time decisions similar to templating in a simple API.
Also has polyfills for C standards.

## Why Make This?
I had began to write my own variation of _Boost C++_ to get better at _C++_.
I was able to write a lot of parts that competed well with Boost, but overall useless.
Therein, I began to wonder if I could take this and get it into a _C_ library.

So, this library is my attempt to make a _C_ version without copying _Boost C++_ directly for my own learning experience.

The name comes from taking _Object Oriented_ out of _Boost C++_.
At least that is what I say now.
It really is just an abbreviation of _Boost_, by removing the vowels...

### Interface Namespaces
The current interface is to prefix everything with `bst_`.
Also, to provide an interface without this prefix.
This may cause problems in your library if you have something with a similar name.
To avoid this, you can define `BST_NAMESPACE_ONLY` and it will remove the other non-stdc interfaces without the `bst_`.

### Compile Time Requirement
Currently, the goal is to write all of the library as compile time insertions of the code.
This allows more flexibility and makes it closer to _Boost C++_.
Another benefit is that you do not need to build this library.

### Insertion Code Bloat
Since most interfaces are inlined code, this can cause binaries to be quite large.
A simple solution is to instantiate your own function calling the inlining _bst_ functions.
Then the compiler will treat it as a function and potentially reducing the size of binaries.

# vector
Provides compile time decisions to create a _C++_ like vector in _C_. Uses the _template_ interface.

```c
#include <bst/vector.h>
#include <stdio.h>

int main()
{
    // Note: It is recommended to do as typedef because there is no guarantee that the types will be the same.
    //       This problem is more relevant when the underlying structure is a more complex data structure.
    vect_t(int) vect;
    
    vect_init(vect);
    // Default is to use stdlib allocator.
    vect_push(vect, 11);
    vect_push(vect, 12);
    
    // Can use basic array operator on the data.
    vect[0] += 10;
    
    // Can loop over the contents.
    {
        int i;
        for(i = 0; i < vect_len(vect); ++i) printf("%i\n", vect[i]);
    }
    
    vect_destroy(vect);
    
    return 0;
}
```
