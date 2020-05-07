#include "allocator.hpp"
#include "container.hpp"
#include <iostream>
#include <map>

template<typename Alloc = std::allocator<int> >
void show_map(const size_t elem_count)
{
    auto fact = [](auto&& self, int i) -> int { return i < 2 ? 1 : i * self(self, i-1);};
    std::map<int, int, std::less<int>, Alloc> m;
    for(size_t i=0; i < elem_count; ++i)
    {
        m.insert(std::make_pair(i, fact(fact, i)));
    }
    for(const auto& elem : m)
    {
        std::cout << elem.first << " " << elem.second << "\n";
    }
}

template<size_t elem_count=10, typename Alloc = std::allocator<int>>
void show_my_container()
{
    homework_container<int, elem_count, Alloc> m;
    for(size_t i=0; i < elem_count; ++i)
    {
        m.insert(i);
    }
    for(size_t i = 0; i < elem_count; ++i)
        std::cout << m[i] << "\n";
}

int main()
{
    try
    {
        size_t elem_count = 10;

        show_map(elem_count);
        
        show_map<homework_allocator<int> >(elem_count);

        show_my_container();

        show_my_container<10, homework_allocator<int> >();
    }
    catch(const std::exception& exc)
    {
        std::cout << exc.what() << "\n";
    }
    return 0;
}