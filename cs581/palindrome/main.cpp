#include <string>
#include <iostream>

#include "longestSubPalindrome.h"

using namespace std;

int main()
{
    string l_string;

    cout << "Please input a string (case sensitive):" << endl;
    cin >> l_string;

    auto l_result = longestSubPalindrome(l_string);

    cout << "The longest subsequence which is a palindrome is: " << endl;
    cout << l_result << endl;
    cout << "Please note that this result may not be unique" << endl;

    cout << "Press enter to exit" << endl;
    cin.get();
    cin.get();
    return 0;
}
