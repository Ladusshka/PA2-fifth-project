# PA2-fifth-project
The task is to implement a class template that can search for substrings that occur repeatedly in the specified string (this problem can be interesting for data compression or for plagiarism detection)..

We assume a general sequence of data. This can be, for example, a string (a sequence of characters), an array of integers, a list of pairs, ... The class will work with general sequences, but the following text will use string terminology (string, substring) for clarity. An unbroken slice of the specified input string (substring for short) can occur in multiple different places in the original string. For example, in the string abcXabcYabc, the substring abc occurs 3 times, in the string ababab, the substring abab occurs 2 times (from position 0 and from position 2).

The first problem to be solved will be to find the length of the longest substring that occurs at least N times in the given string. For example, for the string ababab and N=1, length 6 (the whole string) will be found, for N=2, length 4 will be found (the string abab from positions 0 and 2), for N=3 it will be found length 2 (string ab from positions 0, 2 and 4) and for larger N the length 0 will be found.

The second problem to be solved will be to find combinations of the positions of the occurrence of the longest substring that occurs at least N times in the specified string. The result will be a vector of Tuples, where the value is the position of the occurrence of the substring in the original string. For example, for the string abcXabcYabcZdefXdef and N=2, we have two different longest substrings that occur at least 2x in the original string: the string abc at positions 0, 4, and 8, and the string def at positions 12 and 16. The result is all combinations of occurrences, so for the substring abc we have 3 combinations (combination number 3 over 2) and for substring def we have one occurrence combination (combination number 2 over 2):

[0, 4]
[0, 8]
[4, 8]
[12, 16]
Note that the result is not a [0, 12] pair (they are different strings), also note that the index values ​​in each pair are of increasing size.
CSelfMatch class interface
constructor ( initializer_list )
    initializes the search engine, the sequence of elements to be processed is passed as std::initializer_list.
constructor (container)
    initializes the search engine, the processed sequence of elements will be copied from the specified container. The container can be any STL container that provides a forward iterator.
constructor ( begin, end )
    initializes the search engine, the processed sequence of elements will be copied from the range of the specified pair of iterators. Passed iterators satisfy at least the properties of a forward iterator.
push_back ( ... )
    adds elements to the sequence being processed. The parameter can be any number of elements to add to the end of an existing sequence. The method can be called repeatedly. Implementation of this method is optional, see     below.
size_t sequenceLen ( n )
the method searches the stored sequence for the longest (continuous) subsequence that occurs at least n times. The return value is the length of this longest subsequence found. If there is no subsequence that occurs at least n times, the result will be 0. For n=0, throw a std::invalid_argument exception.
std::vector<std::array<size_t, N> >findSequences<N> ()
the method searches the stored sequence for the longest (continuous) subsequence that is found in the stored sequence at least N times. For the longest subsequences found, it determines the positions of occurrences in the original string and returns a vector with tuples of all combinations of occurrences. The return value is std::vector<std::array<size_t, N> >, so the tuples are stored as an array of fixed length N. In order to use the N parameter in the type declaration, the N value is passed as a generic parameter to the findSequences method. Throw a std::invalid_argument exception for N=0.
T_
the generic class parameter specifies the element type of the stored/processed sequence. The element is guaranteed only a minimalistic interface: copy, move, destroy and match/difference with the == and != operators. Other operations may not exist. An example of a minimalist element is the CDummy class in the attached file.
