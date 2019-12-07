#include "../tools.hpp"

#include <vector>
#include <fstream>
#include <cassert>

using median_t = std::vector<uint32_t>;
using median_of_medians_t = std::vector< median_t >;
  
template <class Iter>
median_t merge_sort( Iter begin, Iter end )
{
  const size_t len = end - begin;
  assert( len > 0 );

  if ( len == 1 ) {
    return median_t{begin, end};
  }

  
  auto half_1 = merge_sort( begin, begin + len/2);
  auto half_2 = merge_sort( begin + len/2, end);

  //merging:
  median_t ret;
  {
    auto iter1 = half_1.begin( );
    auto iter2 = half_2.begin( );
    for ( ;; ) {
      if ( iter1 == half_1.end() ) {
        ret.insert( ret.end(), iter2, half_2.end( ) );
        break;
      }
      if ( iter2 == half_2.end() ) {
        ret.insert( ret.end(), iter1, half_1.end( ) );
        break;
      }

      if ( *iter1 < *iter2 ) {
        ret.push_back( *iter1 );
        ++iter1;
      }
      else{
        ret.push_back( *iter2 );
        ++iter2;
      }
    }
  }
  
  return ret;
}

template <class Iter>
median_of_medians_t split_by_5( Iter begin, Iter end )
{
  median_of_medians_t ret;
  median_t cur_5;

  size_t counter = 0;
  for( ;; ) {
    if ( begin == end ) {
      if ( cur_5.size() > 0 ) {
        ret.push_back( cur_5 );
      }
      break;
    }

    if ( counter == 5 ) {
      counter = 0;
      ret.push_back( cur_5 );
      cur_5 = median_t( );
    }

    cur_5.push_back( *begin );

    ++counter;
    ++begin;
  }

  return ret;
}

template<class Iter>
median_of_medians_t sort_split_by_5(Iter begin, Iter end)
{
  auto split = split_by_5( begin, end );

  median_of_medians_t ret;

  for ( const auto& m : split ) {
    auto sorted = merge_sort( m.begin(), m.end() );
    ret.push_back( sorted );
  }

  return ret;
}

template<class Iter>
median_t collect_medians( Iter begin, Iter end )
{
  median_t ret;
  auto sorted_split = sort_split_by_5( begin, end );
  for ( const auto& ss : sorted_split ) {
    const auto mid_idx = ss.size() / 2;
    ret.push_back( ss.at( mid_idx ) );
  }
  return ret;
}

template<class Iter>
Iter partition( uint32_t pivot, Iter begin, Iter end )
{
  Iter pivot_iter = end;
  for ( auto iter = begin; iter != end; ++iter ) {
    if ( *iter == pivot ) {
      pivot_iter = iter;
      break;
    }
  }
  assert( pivot_iter != end );
  std::iter_swap(  pivot_iter, begin );

  Iter smaller = begin;
  Iter current = begin + 1;

  for (; ;) {
    if ( current == end ) {
      break;
    }
    if ( *current > *begin) {
    }
    else {
      ++smaller;
      std::iter_swap( current, smaller );
    }
    ++current;
  }
  std::iter_swap( begin, smaller );

  return smaller;
}


template<class Iter>
uint32_t find_element_of_order(
      size_t order
      , Iter begin
      , Iter end
      , size_t depth)
{
  ++depth;
  //std::string prefix( depth, '-' );
  if ( end - begin <= 5 ) {
    assert( order < 5 );
    auto arr = merge_sort( begin, end );
    return arr.at( order );
  }

  auto medians = collect_medians( begin, end );

  auto pivot = find_element_of_order( 
                              order / 5
                            , medians.begin( )
                            , medians.end( )
                            , depth
                            );
  auto pivot_pos = partition( pivot, begin, end );

  size_t pivot_order = ( pivot_pos - begin );

  if ( pivot_order == order ) {
    return pivot;
  }


  if ( order < pivot_order ) {
    return
      find_element_of_order(order, begin, pivot_pos, depth);
  }
  
  if ( order > pivot_order ) {
    const size_t new_order = order - pivot_order - 1;
    return 
      find_element_of_order( new_order, pivot_pos + 1, end, depth);
  }
}

int main()
{
  std::vector<uint32_t> data;
  {
    std::ifstream fs{"data.txt"};
    fs >> data;
  }

  uint32_t val = 
     find_element_of_order( 1234, data.begin(), data.end(), 0 );

  std::cout << "!!! value: " << val << std::endl;
  
  return 0;
}

