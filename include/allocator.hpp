#pragma once
#include <forward_list>
#include <limits>
#include <exception>
#include <cstdlib>

template<typename T, size_t size = 10>
class homework_allocator{
private:
    std::forward_list<char*> memory;
    size_t allocated_memory_size = 0;
    size_t used_memory = 0;
public:
    using value_type        = T;

    using pointer           = T*;
    using const_pointer     = const T*;
    using reference         = T&;
    using const_reference   = const T&;

    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;

    template<typename U>
    struct rebind{
        using other = homework_allocator<U>;
    };

    homework_allocator() = default;
    ~homework_allocator();

    size_type max_size() const; 

    T* allocate(size_type n);
    void deallocate(T* p, size_type n);

    template<typename U, typename ...Args>
    void construct (U* p, Args&& ...args);
    template<typename U>
    void destroy(U* p);
};

template<typename T, size_t size>
homework_allocator<T, size>::~homework_allocator()
{
    for(auto& mem_block : memory)
        std::free(mem_block); 
}

template<typename T, size_t size>
typename homework_allocator<T, size>::size_type homework_allocator<T, size>::max_size() const
{
    return std::numeric_limits<size_type>::max() / size;
}


template<typename T, size_t size>
T* homework_allocator<T, size>::allocate(size_type n)
{
    if(used_memory + n > allocated_memory_size)
    {
        memory.push_front(reinterpret_cast<char*>(std::malloc(size * sizeof(T))));
        if(!memory.front())
        {
            throw(std::bad_alloc());
        }
        allocated_memory_size += size;
    }
    used_memory += n;
    return reinterpret_cast<T*>(memory.front() + (used_memory - n) * sizeof(T));    
}


template<typename T, size_t size>
void homework_allocator<T, size>::deallocate([[maybe_unused]]T* p, [[maybe_unused]]size_type n)
{

}

template<typename T, size_t size>
template<typename U, typename ...Args>
void homework_allocator<T, size>::construct(U* p, Args&& ...args)
{
    new(p) U(std::forward<Args>(args)...);
}

template<typename T, size_t size>
template<typename U>
void homework_allocator<T, size>::destroy(U* p)
{
    p->~U();
}