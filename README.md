![boostc icon](images/boostc-icon.png)

# [boostc](https://tkellehe.github.io/boostc/)
A library like [Boost _C++_](https://github.com/boostorg), but for C.
Provides compile time decisions similar to templating in a simple API.
Also has polyfills for C standards. Documentation can be viewed [here](https://tkellehe.github.io/boostc/docs/).

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
    bstc_unused(argc);
    bstc_unused(argv);
    // Note: It is recommended to do as typedef because there is no guarantee that the types will be the same.
    //       This problem is more relevant when the underlying structure is a more complex data structure.
    bstc_vect_t(int) vect;
    
    // Initialize the state of the vector.
    bstc_vect_init(&vect);
    
    // Default is to use stdlib allocator.
    bstc_vect_pushb(&vect, 1);
    bstc_vect_pushb(&vect, 12);
    bstc_vect_pushb(&vect, 13);
    bstc_vect_pushb(&vect, 14);
    
    // Can use basic array operator on the data.
    vect[0] += 10;
    
    // Can loop over the contents.
    {
        bstc_size_t i;
        for(i = 0; i < bstc_vect_len(&vect); ++i)
            printf("%i\n", vect[i]);
    }
    
    // Deallocate any memory.
    bstc_vect_destroy(&vect);
    
    return bstc_exit_success;
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
// The "id" portion is used within macros allowing variables to be declared without naming conflicts.
int _memory[1024];
int _pos = 0;
bstc_inline void* my_malloc(int sz, int id)
{
    bstc_unused(id);
    int* res = &_memory[_pos];
    _pos += sz / sizeof(int);
    return (void*)res;
}
bstc_inline void* my_realloc(void* mem, int sz, int id)
{
    bstc_unused(id);
    int* res = &_memory[_pos];
    bstc_memcpy((void*)res, mem, sz);
    _pos += sz / sizeof(int);
    return (void*)res;
}


int main(int argc, char *argv[])
{
    bstc_unused(argc);
    bstc_unused(argv);
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
    bstc_vect_init(vect_int, &vect);
    
    // Uses the allocator encoded into the template to realloc and malloc the memory.
    bstc_vect_pushb(vect_int, &vect, 1);
    bstc_vect_pushb(vect_int, &vect, 12);
    bstc_vect_pushb(vect_int, &vect, 13);
    bstc_vect_pushb(vect_int, &vect, 14);
    
    // Can still use basic array operator on the data.
    vect[0] += 10;
    
    // Can loop over the contents where the template is not necessary, but recommended for consistency.
    {
        bstc_size_t i;
        for(i = 0; i < bstc_vect_len(vect_int, &vect); ++i)
            printf("%i\n", vect[i]);
    }
    
    // Deallocates any memory allocated using what is encoded in the template.
    bstc_vect_destroy(vect_int, &vect);
    
    return bstc_exit_success;
}
```
