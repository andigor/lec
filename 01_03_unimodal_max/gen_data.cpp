#include "../tools.hpp"

#include <iostream>
#include <vector>

#include <algorithm>

int main()
{
  std::vector<size_t> v;
  for (size_t i = 0; i<10000000; ++i) {
    v.push_back(i);
  }
  for (size_t i = 101; i>0; --i) {
    v.push_back(i);
  }

  //std::random_shuffle(v.begin(), v.end());

  std::ofstream s{"data.txt"};

  s << v ;
  return 0;
}

