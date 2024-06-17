#ifndef __PROGTEST__
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <array>
#include <deque>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <compare>
#include <algorithm>
#include <cassert>
#include <memory>
#include <iterator>
#include <functional>
#include <stdexcept>
using namespace std::literals;

class CDummy
{
public:
    CDummy                                  ( char                                  c )
            : m_C ( c )
    {
    }
    bool                               operator ==                             ( const CDummy                        & other ) const = default;
    friend std::ostream              & operator <<                             ( std::ostream                        & os,
                                                                                 const CDummy                        & x )
    {
        return os << '\'' << x . m_C << '\'';
    }
private:
    char                               m_C;
};
#endif /* __PROGTEST__ */

// #define TEST_EXTRA_INTERFACE


template <size_t N>
void combine(const std::vector<size_t>& input, size_t start, std::array<size_t, N>& combo, std::vector<std::array<size_t, N>>& results, size_t depth = 1) {
    for (size_t i = start; i < input.size(); ++i) {
        combo[depth] = input[i];
        if (depth + 1 == N) {
            results.push_back(combo); // When the combo is filled, store it
        } else {
            combine<N>(input, i + 1, combo, results, depth + 1); // Continue building the combo
        }
    }
}

template <size_t N>
std::vector<std::array<size_t, N>> createCombinations(const std::vector<size_t>& input) {
    std::vector<std::array<size_t, N>> results;

    if (N == 1) {
        // Handle the special case when N_ = 1
        for (size_t i = 0; i < input.size(); ++i) {
            std::array<size_t, N> singleElement{input[i]};
            results.push_back(singleElement);
        }
        return results;
    }
    if (input.size() < N || input.empty()) { return results; } // Ensure there are enough elements

    std::array<size_t, N> combo;
    combo[0] = input[0]; // First element is always the first in the input
    combine<N>(input, 1, combo, results); // Start combining from the second element

    return results;
}
template <typename T_>
class CSelfMatch
{
public:
    // constructor (initializer list)
    CSelfMatch(std::initializer_list<T_> list) : data(list) {}

    // constructor (a container)
    template <typename cont>
    CSelfMatch(const cont& container) : data(container.begin(), container.end()) {}
    // constructor (2 iterators)
    template <typename It>
    CSelfMatch(It beg, It end) : data(beg, end) {}
    // optionally: push_back
    void push_back(const T_& value) {
        data.push_back(value);
    }

    // size_t sequenceLen ( n ) const
    size_t sequenceLen(size_t n) const {
        if (n <= 0) {
            throw std::invalid_argument("n must be greater than zero");
        }

        size_t max_len=0;
        for (size_t i = 0; i < data.size(); i++) {
            std::vector<std::vector<T_>> subsequences;


            size_t len = data.size() - i;
            size_t start_index = 0;

            while((start_index+len) <= data.size() ){
                std::vector<T_>subsequence;
                for(size_t beh = start_index;beh<len+start_index;beh++){
                    subsequence.push_back(data[beh]);
                }
                subsequences.push_back(subsequence);
                start_index++;

            }



            for(size_t it1 = 0;it1<subsequences.size();it1++){
                size_t counter =0;
                for(size_t it2 = it1;it2<subsequences.size();it2++){
                    if(subsequences[it1]==subsequences[it2]){
                        counter++;
                    }
                }
                if(counter>=n){
                    size_t current_len = subsequences[it1].size();
                    if(current_len>max_len){
                        max_len = current_len;
                    }
                }
            }

        }

        return max_len;
    }

    template<size_t N_>
    std::vector<std::array<size_t, N_>> findSequences() const {
        if (N_ <= 0) {
            throw std::invalid_argument("N must be greater than zero");
        }

        std::vector<std::array<size_t, N_>> result;


        size_t max_len= sequenceLen(N_);

        std::vector<std::vector<size_t>> indexes;
        for (size_t i = 0; i < data.size(); i++) {
            size_t len = data.size() - i;

            if(len==max_len){

                std::vector<std::vector<T_>> subsequences;
                size_t start_index = 0;
                while((start_index+len) <= data.size() ){
                    std::vector<T_>subsequence;
                    for(size_t beh = start_index;beh<len+start_index;beh++){
                        subsequence.push_back(data[beh]);
                    }
                    subsequences.push_back(subsequence);
                    start_index++;

                }


                for(size_t it1=0;it1<subsequences.size();it1++){
                    std::vector<size_t> tmp_indexes;
                    for(size_t it2 = it1;it2<subsequences.size();it2++){
                        if(subsequences[it1]==subsequences[it2]){
                            tmp_indexes.push_back(it2);
                        }
                    }
                    if(tmp_indexes.size()>=N_){
                        indexes.push_back(tmp_indexes);
                    }
                }

            }

        }

        for(size_t i =0;i<indexes.size();i++){
            auto a = createCombinations<N_>(indexes[i]);
            for(auto & b:a){
                result.push_back(b);
            }
        }

        /* for(auto &res :result){
             for(auto &a: res){
                 std::cout<<a<<" ";
             }
             std::cout<<std::endl;
         }*/
        return result;
    }
    // template<size_t N_> std::vector<std::array<size_t, N_>> findSequences () const
private:
    std::vector<T_> data;
};


#ifndef __PROGTEST__
template<size_t N_>
bool                                   positionMatch                           ( std::vector<std::array<size_t, N_>> a,
                                                                                 std::vector<std::array<size_t, N_>> b )
{
    std::sort ( a . begin (), a . end () );
    std::sort ( b . begin (), b . end () );
    return a == b;
}
int                                    main ()
{
    
#ifdef TEST_EXTRA_INTERFACE
    CSelfMatch y0 ( "aaaaaaaaaaa"s );
  assert ( y0 . sequenceLen ( 2 ) == 10 );

  std::string s1 ( "abcd" );
  CSelfMatch y1 ( s1 . begin (), s1 . end () );
  assert ( y1 . sequenceLen ( 2 ) == 0 );

  CSelfMatch y2 ( ""s );
  y2 . push_back ( 'a', 'b', 'c', 'X' );
  y2 . push_back ( 'a' );
  y2 . push_back ( 'b', 'c' );
  assert ( y2 . sequenceLen ( 2 ) == 3 );
#endif /* TEST_EXTRA_INTERFACE */
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
