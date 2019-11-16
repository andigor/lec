#include "../tools.hpp"

#include <fstream>
#include <iostream>
#include <tuple>

template <class T>
class range
{
private:
  T begin_;
  T end_;
public:
  using value_type = typename T::value_type;

  T begin() const {return begin_;}
  T end() const {return end_;}
  T mid() const {return begin() + size() / 2;}

  size_t size() const
  {
    return end_ - begin_;
  }
  
  template <class V>
  range(const std::vector<V>& v)
    : begin_( v.begin() )
    , end_( v.end() )
  {
  }

  range(const T& begin, const T& end)
    : begin_( begin )
    , end_( end )
  {
  }
};

template <class T>
auto make_range(const std::vector<T>& v)
{
  using it = typename std::vector<T>::const_iterator;
  return range< it >(v);
}

template <class Iter>
auto make_range(Iter begin, Iter end)
{
  return range< Iter >(begin, end);
}

template <class T>
std::tuple< std::vector<typename range<T>::value_type>, size_t >
  inversions_count(const range<T>& rng)
{
  using val_t = typename range<T>::value_type;

  if ( rng.size() > 1 ) {
    auto lr = make_range( rng.begin() , rng.mid() );
    auto [ls, lcnt] = inversions_count( lr ); 
    
    auto rr = make_range( rng.mid(), rng.end() );
    auto [rs, rcnt] = inversions_count( rr ); 

    size_t counter{};
    // merging
    std::vector< val_t > ret;
    auto li = ls.begin();
    auto ri = rs.begin();

    for(;;){
      if ( li == ls.end() ) {
        ret.insert( ret.end(), ri, rs.end() );
        break;
      }
      if ( ri == rs.end() ) {
        ret.insert( ret.end(), li, ls.end() );
        break;
      } 

      if ( *li <= *ri ) {
        ret.push_back( *li );
        ++li;
      }
      else {
        ret.push_back( *ri );
        ++ri;
        counter += ( ls.end() - li );
      }
    }
    return {ret, counter + rcnt + lcnt};
  }

  return {std::vector<val_t>{*rng.begin()}, 0};
}

int main()
{
  std::ifstream f{"IntegerArray.txt"};
  std::vector<uint32_t> data;
  f >> data;
  
  auto r = make_range(data);
  std::cout << r.size() << std::endl;
  auto [ v_,  count ] = inversions_count( r );
  std::cout << count << std::endl;
  return 0;
}
