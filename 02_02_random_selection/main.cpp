#include "../tools.hpp"

#include <vector>
#include <cassert>

template<class Iter>
uint32_t find_element_of_order(size_t order, Iter begin, Iter end)
{
  if ( end - begin == 1 ) {
    return order;
  }

  uint32_t pivot = *begin;

  auto smaller = begin;
  auto current = begin + 1;

  while ( current != end ) {
    if ( *current > pivot ) {
    }
    else {
      ++smaller;
      std::iter_swap( smaller, current );
    }
    ++current;
  }
  std::iter_swap( smaller, begin );

  size_t found_order = smaller - begin;

  if ( found_order > order ) {
    return find_element_of_order( order, begin, smaller );
  }
  else if ( found_order < order ) {
    uint32_t new_order = order - found_order - 1;
    return find_element_of_order( new_order, smaller + 1, end );
  }
  return pivot;
}

int main()
{
  std::ifstream f{"unsorted.txt"};
  std::vector<uint32_t> data;
  f >> data;

  std::cout << find_element_of_order( 50, data.begin(), data.end() )
    << std::endl;

  return 0;
}

