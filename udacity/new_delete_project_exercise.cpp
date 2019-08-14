
#include <algorithm>
#include <iostream>
#include <list>

template <class T, int size>
class Pointer
{

public:
    Pointer();
    ~Pointer();
    bool collect();
};

template <class T, int size>
bool Pointer<T, size>::collect()
{
    bool memfreed = false;
    typename std::list<PtrDetails<T>>::iterator p;
    do
    {
        // Scan refContainer looking for unreferenced pointers.
        for (p = refContainer.begin(); p != refContainer.end(); p++)
        {
            for
                / TODO : Implement collect()

                         // If in-use, skip.

                         // Remove unused entry from refContainer.

                         // Free memory unless the Pointer is null.

                         // Restart the search.
                         break;
        }
    } while (p != refContainer.end()) : return memfreed;
}

template <class T, int size>
Pointer<T, size>::~Pointer()
{
    typename std::List<PtrDetails<T> >::iterator p;
    p = findPtrInfo(addr);

    // TODO: Finalize Pointer destructor
    // decrement ref count

    // Collect garbage when a pointer goes out of scope.

    // For real use, you might want to collect unused memory less frequently,
    // such as after refContainer has reached a certain size, after a certain number of Pointers have gone out of scope,
    // or when memory is low.
}
