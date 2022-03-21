// BiggerIsGreater.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//Use builtin function as most effcient solution
string biggerIS(string word)
{
    if (next_permutation(word.begin(), word.end()) == false)
        return "no answer";
    else        
        return word;
}

string biggerIsGreater(string word)
/*
* For a string the smallest rearrangement of letters such that it is lexiconically greater than the given string is returned ("abc" returns "acb") 
* if this is not possible then "no answer" is returned eg. (cba or aa)
*/
{
    bool flag = false;
    //Reverse string for easy for loop ranges
    reverse(word.begin(), word.end());

    for (int i = 0; i < word.size(); i++)
    {
        for (int j = 0; j < i+1; j++)
        {
            if (word.at(i) < word.at(j))
            {
                flag = true;
                swap(word.at(i),word.at(j));

                //Order elements so greatest lexiconical value is in least significant position "kva" becomes "vka" which is "akv" once flipped
                sort(word.begin(), word.begin() + i , greater<char>());
            }
        }

        if (flag == true)
            break;
    }

    if (flag == false)
        word = "no answer";
    else
        reverse(word.begin(), word.end());

    return word;
}

void tester(string word)
{
    string word1 = biggerIS(word);
    cout << "Next permutation result: " << word1 << endl;
    string word2 = biggerIsGreater(word);
    cout << "my function result: " << word2 << endl;
    cout << "Lexiconical difference: " << word1.compare(word2) << endl;

}

int main()
{
    string my_word = "v"; //bojdfanakdvjpinbidibefblijibjklnjodnb

    while(my_word != "-1")
    { 
        cout << "Enter -1 to end" << endl;
        cin >> my_word;
        tester(my_word);
    }
}
