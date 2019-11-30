#include "../tools.hpp"

#include <algorithm>

#include <string_view>

inline void gen_random_data(const char* file_name, size_t size)
{
  std::vector<size_t> v;
  for (size_t i = 0; i<size; ++i) {
    v.push_back(i);
  }

  std::random_shuffle(v.begin(), v.end());

  std::ofstream s{file_name};

  s << v ;
}
