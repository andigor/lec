#include "../tools.hpp"

#include <iostream>
#include <fstream>

size_t largest(std::ifstream& data)
{
  size_t val;
  size_t max = 0;
  while( data >> val ) {
    if (val > max) {
      max = val;
    }
  }
  return max;
}

size_t largest_2(std::ifstream& data)
{
  size_t val;
  size_t max = 0;
  size_t max_second = 0;
  while( data >> val ) {
    if ( val > max ) {
      max_second = max;
      max = val;
    }
    else if ( val > max_second ) {
      max_second = val;
    }
  }
  return max_second;
}

int main()
{
  std::ifstream data{"data.txt"};

  std::cout << largest_2( data ) << std::endl;

  return 0;
}

