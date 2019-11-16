#ifndef VECTOR_PRETTY_H_
#define VECTOR_PRETTY_H_

#include <iostream>
#include <vector>
#include <fstream>

template <typename C>
std::ostream& operator<<(std::ostream& os, const std::vector<C>& c) {
  char delim = '[';
  for (const auto& v : c) {
    os << delim;
    os << v; 
    delim = ' ';
  }
  os << "]";
  return os;
}

template <typename C>
std::ostream& operator<<(std::ofstream& os, const std::vector<C>& c) {
  for (const auto& v : c) {
    os << v << std::endl;
  }
  return os;
}

template <typename C>
std::istream& operator>>(std::ifstream& os, std::vector<C>& c) {
  C val;
  while( os >> val ) {
    c.push_back(val);
  }
  return os;
}
#endif

