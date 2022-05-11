// HighestValuePalindrome.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include<vector>
#include<stack>

using namespace std;

void printVecOfPairs(vector<pair<int, char>>& vp)
{
    for (auto& p : vp)
    {
        cout << p.first << "," << p.second << endl;
    }
}

bool swap9(string& s, int& k, pair<int,int>& coords)
{
    if (s.at(coords.first) != '9' && s.at(coords.second) != '9' && k > 1)
    {
        s.at(coords.first) = '9';
        s.at(coords.second) = '9';
        k -= 2;
        return true;
    }
    else if (s.at(coords.first) == '9' && s.at(coords.second) != '9' && k > 0)
    {
        s.at(coords.second) = '9';
        k--;
        return true;
    }
    else if (s.at(coords.first) != '9' && s.at(coords.second) == '9' && k > 0)
    {
        s.at(coords.first) = '9';
        k--;
        return true;
    }

    return false;

}

string highestValuePalindrome(string& s, int& n, int& k)
// include for empty char_stack
// add for case where all palindrome
{
    string s_palin = s;
    stack<char> char_stack;
    vector<pair<int,int>> swap_pairs;
    pair<int, int> temp;
    bool is_odd = false;

    if (n % 2 == 0)
    {
        for (int i = 0; i < int(n / 2); i++)
            char_stack.push(s.at(i));

        for (int i = int(n / 2); i < n; i++)
        {
            if (char_stack.top() != s.at(i))
            {
                temp = {n - 1 - i, i };
                swap_pairs.push_back(temp);
            }
            char_stack.pop();
        }
    }
    else
    {
        is_odd = true;
        for (int i = 0; i < int(n / 2); i++)
            char_stack.push(s.at(i));

        for (int i = int(n / 2)+1; i < n; i++)
        {
            if (char_stack.top() != s.at(i))
            {
                temp = { n - 1 - i, i };
                swap_pairs.push_back(temp);
            }
            char_stack.pop();
        }
    }

    int n_swaps = swap_pairs.size();
    bool flag = false;

    if (k < n_swaps)
        return "-1";

    while (k > n_swaps && n_swaps > 0)
    {
        temp = swap_pairs.back();

        flag = swap9(s_palin, k, temp);

        swap_pairs.pop_back();
        n_swaps--;          
    }

    for (auto& elem : swap_pairs)
    {
        if (s_palin.at(elem.first) > s_palin.at(elem.second))
            s_palin.at(elem.second) = s_palin.at(elem.first);
        else
            s_palin.at(elem.first) = s_palin.at(elem.second);
    
        k--;
    }

    for (int i = 0; i < k; i++)
    {
        if (k - i > 1 )
        {
            temp = {i, n - 1 - i};
            flag = swap9(s_palin, k, temp );
        }

        if (k == 1 && is_odd == true)
            s_palin.at(int(n / 2)) = '9';

        if (k < 1)
            break;
    }

    return s_palin;
}

int main()
{
    string my_str{ "1" };
    int k{ 1 };
    //string my_str{ "17321" };
    //int k{ 2 };
    //string my_str{ "921119" };
    //int k{ 3 };
    //string my_str{ "3943" };
    //int k{ 1 };
    //string my_str{ "0011" };
    //int k{ 1 };
    //string my_str{ "092282" };
    //int k{ 3 };
    int n = my_str.length();
    string max_palin = highestValuePalindrome(my_str, n, k);
    cout << max_palin << endl;
}

