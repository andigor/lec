#include "../tools.hpp"

#include <iostream>
#include <fstream>
#include <tuple>

size_t count;

template <class Iter>
uint32_t narrow_to_highest( Iter begin, Iter end )
{
  auto len = end - begin;
  if (len > 2) {
    {
      auto l = *begin;
      auto r = *(begin + len/2);
      if (r < l) {
        ++count;
        return narrow_to_highest( begin, begin + len / 2 );
      }
    }
    {
      return narrow_to_highest( begin + len / 2, end );
    }
  }
  else {
    if ( *begin > *end) {
      ++count;
      return *begin;
    }
    else {
      return *end;
    }
  }
}

uint32_t find_max_in_unimodal( const std::vector<uint32_t>& data )
{
  auto max = narrow_to_highest( data.begin(), data.end() - 1 );
  return max;
}


int main()
{
  std::vector<uint32_t> data;
  std::ifstream data_stream{"data.txt"};
  data_stream >> data;
  

  std::cout << find_max_in_unimodal(data) << std::endl;
  std::cout << count << std::endl;

  return 0;
}

