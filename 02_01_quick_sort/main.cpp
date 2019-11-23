#include "../tools.hpp"

#include <vector>

template<typename T, int N> using raw_array = T[N];

template <class Iter>
size_t quick_sort( Iter begin, Iter end )
{
  if ( begin == end || begin + 1 == end ) {
    return 0;
  }

  //std::iter_swap( begin , end - 1 );

  {
    auto m1 = begin;
    auto len = end - begin;
    auto m2 = begin + len / 2 ;
    if ( len % 2 == 0 ) {
      --m2;
    }
    auto m3 = end - 1;

    decltype(auto) arr = raw_array<Iter,3>{m1, m2, m3};
    // auto arr = {m1, m2, m3};

    if ( *arr[0] > *arr[1] ) {
      std::swap(arr[0], arr[1]);
    }
    if ( *arr[1] > *arr[2] ) {
      std::swap(arr[1], arr[2]);
    }
    if ( *arr[0] > *arr[1] ) {
      std::swap(arr[0], arr[1]);
    }

    std::cout 
      << *arr[0] << " "
      << *arr[1] << " "
      << *arr[2] 
      << std::endl;
      
    std::iter_swap(begin, arr[1]);
  }

  auto pivot = begin;
  auto smaller = begin;
  auto cur = begin + 1;
  
  size_t cmp_count = 0;
  for (;;) {
    ++cmp_count;
    if ( *cur > *pivot ) {

    }
    else {
      auto bigger_begin = smaller + 1;
      std::iter_swap( bigger_begin, cur );
      ++smaller;
    }

    ++cur;
    if ( cur == end ) {
      break;
    }
  }


  std::iter_swap( pivot, smaller );

  //size_t len_smaller = smaller - begin;
  //size_t cmp_smaller_amount = len_smaller - 1;

  //cmp_smaller_amount += quick_sort( begin, smaller );
  cmp_count += quick_sort( begin, smaller );

  ++smaller; // start of bigger part
  //size_t len_bigger = end - smaller;
  //size_t cmp_bigger_amount = len_bigger- 1;
  //cmp_bigger_amount += quick_sort( smaller, end );
  cmp_count += quick_sort( smaller, end );

  //return cmp_smaller_amount + cmp_bigger_amount;
  return cmp_count;
}


int main()
{
  std::ifstream f{"QuickSort.txt"};
  std::vector<uint32_t> data;
  f >> data;

  auto cmp_amount = quick_sort( data.begin(), data.end( ) );

  //std::cout << data << std::endl;

  std::cout << cmp_amount << std::endl;
  return 0;
}

