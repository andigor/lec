#include <iostream>

#include <vector>
#include <algorithm>

#include "../tools.hpp"

size_t cmp_count;

std::vector<int> merge(
                const std::vector<int>& v1, 
                const std::vector<int>& v2 )
{
  std::vector<int> ret;

  auto iter1  = v1.begin();
  auto iter2  = v2.begin();

  for(;;) {
    if ( iter1 == v1.end() ) {
      ret.insert( ret.end(), iter2, v2.end( ) );
      break;
    }
    if ( iter2 == v2.end() ) {
      ret.insert( ret.end(), iter1, v1.end( ) );
      break;
    }
    if ( *iter1 < *iter2 ) {
      ret.push_back( *iter1  );
      ++iter1;
      ++cmp_count;
    }
    else {
      ret.push_back( *iter2  );
      ++iter2;
      //++cmp_count;
    }
  }
  return ret;
}



int main()
{
  std::vector<int> v2 = {2,5,8};
  std::vector<int> v1 = {1,4,7};
  std::vector<int> v3 = {3,6,9};
  std::vector<int> v4 = {10,11,12};

  auto m1 = merge( v1, v2 );
  std::cout << m1 << std::endl;
  std::cout << cmp_count << std::endl;

  auto m2 = merge( m1, v3 );
  std::cout << m2 << std::endl;
  std::cout << cmp_count << std::endl;

  auto m3 = merge( m2, v4 );
  std::cout << m3 << std::endl;

  std::cout << cmp_count << std::endl;

  return 0;
}

