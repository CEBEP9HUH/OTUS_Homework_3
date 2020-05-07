#include <memory>
#include <iostream>

template<typename T, size_t size, typename Alloc = std::allocator<T>>
class homework_container{
private:
    using size_type = size_t;
    T* data[size];
    size_type used = 0;
    Alloc allocator;
public:
    homework_container();
    ~homework_container();
    void insert(const T&);
    T operator[](const size_t i);
};

template<typename T, size_t size, typename Alloc>
homework_container<T, size, Alloc>::homework_container()
{

}

template<typename T, size_t size, typename Alloc>
homework_container<T, size, Alloc>::~homework_container()
{
    for(T* elem : data)
    {
        allocator.destroy(elem);
        allocator.deallocate(elem,1);
    }
}

template<typename T, size_t size, typename Alloc>
void homework_container<T, size, Alloc>::insert(const T& elem)
{
    if(used < size)
    {
        data[used] = allocator.allocate(1);
        allocator.construct(data[used++], elem); 
    }
}

template<typename T, size_t size, typename Alloc>
T homework_container<T, size, Alloc>::operator[](const size_t i)
{
    return *data[i];
}