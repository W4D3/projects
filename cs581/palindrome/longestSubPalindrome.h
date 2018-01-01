#ifndef __LONGESTSUBPALINDROME_H__
#define __LONGESTSUBPALINDROME_H__

#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

using namespace std;

string longestSubPalindrome(const string& a_string)
{
    using ui = unsigned int;
    // Type composing DP table. First ui is the length of the longest
    // subpalindrome, next ui is the index of the parent table index, the
    // char is the character added to the subpalindrome at the table entry
    // (char is null if no character was added)
    using uiT = tuple<ui, ui, char>;
    using table = vector<uiT>;

    auto l_numChar = a_string.size();
    // Number of elements in lower triangle of n^2 table
    auto l_numElem = l_numChar * (l_numChar + 1)/2;

    if(!l_numChar) return string();

    // Initialize table
    table l_table(l_numElem);

    auto l_index = 0;
    // Initialize corner of (0,0)
    l_table[l_index] = make_tuple(1,l_index,a_string[0]);
    l_index++;

    // Fill in table row-wise
    for(auto i = 1; i < l_numChar; ++i)
    {
        // Left most character in substring ending at i
        auto l_char = a_string[i];

        // Fill in base case of (i,i)
        l_table[l_index] = make_tuple(1,l_index,l_char);
        l_index++;

       // Fill in case of (i-1,i)
        if(l_char == a_string[i-1]) l_table[l_index] =
            make_tuple(2, l_index,l_char);
        else l_table[l_index] = make_tuple(1, l_index, l_char);
        l_index++;

       // Fill in substrings (i-2,i) to (0,i)
        for(auto j = i-2; j >= 0; --j)
        {
           // Index for (j+1,i-1)
            auto l_innerIndex = l_index - i - 2;

           // If beginning and ending charaters of substring match,
           // longest subpalindrome occurs using substring (j+1,i-1)
            if(l_char == a_string[j]) l_table[l_index] =
                make_tuple(get<0>(l_table[l_innerIndex]) + 2,
                           l_innerIndex, l_char);

           // If not, longest subpalindrome is either (j,i-1) or (j+1,i)
            else
            {
                auto l_maxIndex = get<0>(l_table[l_index-1]) < get<0>(l_table[l_innerIndex+1]) ? l_innerIndex+1 : l_index-1;
                l_table[l_index] = make_tuple(get<0>(l_table[l_maxIndex]), l_maxIndex, '\0');
            }
            l_index++;
        }
    }

    string l_resultString;

    // Traceback the final string. Note: the longest substring may not
    // be unique
    // Following parent pointers and collecting added characters gives
    // half of the palindrome
    l_index = l_numElem - 1;
    while(true)
    {
        auto l_nextInd = get<1>(l_table[l_index]);
        auto l_char = get<2>(l_table[l_index]);

        if(l_char != '\0') l_resultString += l_char;
        if(l_nextInd == l_index) break;

        l_index = l_nextInd;
    }

    // Other half of the palindrome is now added by mirroring the
    // l_resultString
    auto l_beg = l_resultString.rbegin();
    if(get<0>(l_table[l_numElem-1]) % 2 == 1) l_beg++;
    l_resultString.append(string(l_beg, l_resultString.rend()));

    return l_resultString;
}

#endif // __LONGESTSUBPALINDROME_H__
