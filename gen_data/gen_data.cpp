#include "gen_data.hpp"

#include <string_view>

std::string_view find_arg(const char* name, int argc, const char** argv)
{
  for ( int i = 0; i<argc; ++i ) {
    std::string_view s_argv ( argv[i] );
    if ( s_argv == name ) {
      ++i;
      if ( i >= argc ) {
        throw std::length_error( "no value1" );
      }
      return std::string_view( argv[i] );
    }
  }
  throw std::length_error( "no value2" );
}

int main(int argc, const char** argv)
{
  std::string_view file_path = find_arg("-f", argc, argv);
  std::string_view scount     = find_arg("-c", argc, argv);
  std::cout << file_path << " " << scount << std::endl;
  size_t count = std::stol( scount.data( ) );

  gen_random_data(file_path.data(), count);

  return 0;
}
