![boostc icon](images/boostc-icon.png)

# [boostc](https://tkellehe.github.io/boostc/)
A library like [Boost _C++_](https://github.com/boostorg), but for C.
Provides compile time decisions similar to templating in a simple API.
Also has polyfills for C standards. Documentation can be viewed [here](https://tkellehe.github.io/boostc/docs/).

## Why Make This?
I began to write my own variation of _Boost C++_ to get better at _C++_.
I was able to write a lot of parts that competed well with Boost, but overall useless.
Therein, I began to wonder if I could take this and get it into a _C_ library.

So, this library is my attempt to make a _C_ version without copying _Boost C++_ directly for my own learning experience.

### Compile Time Requirement
Currently, the goal is to write all of the library as compile time insertions of the code.
This allows more flexibility and makes it closer to _Boost C++_.
Another benefit is that you do not need to build this library.

### Insertion Code Bloat
Since most interfaces are inlined code, this can cause binaries to be quite large.
A simple solution is to instantiate your own function to wrap the _boostc_ functions.
Then the compiler will treat it as a single function and potentially reducing the size of binaries.

# vector
Provides compile time decisions to create a _C++_ like vector in _C_. Uses the _container traits_ interface.

```c
#include <boostc/container/vector.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    bstc_unused_param(argc);
    bstc_unused_param(argv);
    // Note: It is recommended to do as typedef because there is no guarantee that the types will be the same.
    //       This problem is more relevant when the underlying structure is a more complex data structure.
    bstc_vect_t(int) vect;
    
    // Initialize the state of the vector.
    bstc_vect_init(vect);
    
    // Default is to use stdlib allocator.
    bstc_vect_pushb(vect, 1);
    bstc_vect_pushb(vect, 12);
    bstc_vect_pushb(vect, 13);
    bstc_vect_pushb(vect, 14);
    
    // Can use basic array operator on the data.
    vect[0] += 10;
    
    // Can loop over the contents.
    {
        bstc_size_t i;
        for(i = 0; i < bstc_vect_len(vect); ++i)
            printf("%i\n", vect[i]);
    }
    
    // Deallocate any memory.
    bstc_vect_destroy(vect);
    
    return 0;
}
```

## Iterators

The vector API provides a C++ like iterator interface for accessing elements in the vector.
The current generic iterator API provides the following functionalities for forward and reverse iterators:
 * `bstc_(r?)iter_t` : A function that represents the type declaration of the iterator.
 * `bstc_(r?)iter_nxt` : A function that moves the iterator to the next position.
 * `bstc_(r?)iter_eq` : A function that compares if two iterators represent the same element.
 * `bstc_(r?)iter_val` : A function to get the current value of the iterator.
 * `bstc_(r?)iter_set` : A function to set the current value of the iterator.
 * `bstc_(r?)iter_swap` : A function to swap the contents of two iterators.

```c
#include <boostc/container/vector.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    bstc_unused_param(argc);
    bstc_unused_param(argv);
    // Declare a vector that contains type 'int'.
    bstc_vect_t(int) vect;
    // Also declare a forward and reverse iterator for a vector of type 'int'.
    bstc_vect_iter_t(int) iter;
    bstc_vect_riter_t(int) riter;
    
    // Initialize the state of the vector.
    bstc_vect_init(vect);
    
    // Add some elements to the vector.
    bstc_vect_pushb(vect, 1);
    bstc_vect_pushb(vect, 2);
    bstc_vect_pushb(vect, 3);
    
    // Can loop over the contents and check if reached the end.
    {
        printf("forward iterator:\n");
        for(iter = bstc_vect_begin(vect); iter != bstc_vect_end(vect); ++iter)
            printf("    %i\n", *iter);
    }
    // Can also use the functions provided to be more explicit.
    {
        printf("forward iterator & vector functions:\n");
        for(iter = bstc_vect_begin(vect); !bstc_vect_iter_eq(iter, bstc_vect_end(vect)); bstc_vect_iter_nxt(iter))
            printf("    %i\n", bstc_vect_iter_val(iter));
    }

    iter = bstc_vect_begin(vect);
    // The recommended way is to use the functions provided to access elements.
    bstc_vect_iter_set(iter, bstc_vect_iter_val(iter) + 10);
    // But, the vector iterator interface provides both.
    *iter += 10;

    // For the reverse iterators, the functions provided are the best option since the access is not direct.
    {
        printf("reverse iterator & vector functions:\n");
        // Note: That you can use 'riter != bstc_vect_rend(vect)' if it is more readable.
        for(riter = bstc_vect_rbegin(vect); !bstc_vect_riter_eq(riter, bstc_vect_rend(vect)); bstc_vect_riter_nxt(riter))
            printf("    %i\n", bstc_vect_riter_val(riter));
    }
    
    // Deallocate any memory.
    bstc_vect_destroy(vect);
    
    return 0;
}
```

## Changing Allocators

The basic implementation works by taking the default traits if the first parameter does not syntactically appear as a container trait.
A container trait is basically a tuple of symbols that follows a particular pattern that makes it look like a boostc container.
The default layout of this pattern can be generated using the trait vector macro.
Then you can do things like changing the default allocator.

```c
#include <boostc/container/vector.h>
#include <stdio.h>

// This is a simple allocator that is not the best, but provides as a simple example.
int _memory[1024];
int _pos = 0;
void* my_malloc(int sz)
{
    int* res = &_memory[_pos];
    _pos += sz / sizeof(int);
    return (void*)res;
}
void* my_realloc(void* mem, int sz)
{
    bstc_unused_param(mem);
    int* res = &_memory[_pos];
    _pos += sz / sizeof(int);
    return (void*)res;
}


int main(int argc, char *argv[])
{
    bstc_unused_param(argc);
    bstc_unused_param(argv);
    // It is recommended to create a definition for the macro type to make it more readable.
    // The type provided first is the underlying type of the vector.
    // The symbol tuple is merely indicated by parentheses and the three symbols provided.
    // They must be provided in the following order: free, malloc, realloc.
    #define vect_int bstc_vect_traits(int, bstc_alloc_traits(bstc_alloc_nofree, my_malloc, my_realloc))

    // You can print out what was actually encoded into the symbol tuple:
    printf("vect_int: %s\n", BSTC_TOSTRING(vect_int));

    // Passing it into a vector function will cause it to extract the symbol representing the type.
    bstc_vect_t(vect_int) vect;
    
    // Initializes the state by extracting the symbol encoded representing the init function.
    bstc_vect_init(vect_int, vect);
    
    // Uses the allocator encoded into the template to realloc and malloc the memory.
    bstc_vect_pushb(vect_int, vect, 1);
    bstc_vect_pushb(vect_int, vect, 12);
    bstc_vect_pushb(vect_int, vect, 13);
    bstc_vect_pushb(vect_int, vect, 14);
    
    // Can still use basic array operator on the data.
    vect[0] += 10;
    
    // Can loop over the contents where the template is not necessary, but recommended for consistency.
    {
        bstc_size_t i;
        for(i = 0; i < bstc_vect_len(vect_int, vect); ++i)
            printf("%i\n", vect[i]);
    }
    
    // Deallocates any memory allocated using what is encoded in the template.
    bstc_vect_destroy(vect_int, vect);
    
    return 0;
}
```
