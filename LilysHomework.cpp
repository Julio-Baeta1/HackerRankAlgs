// LilysHomework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

void ascVsDes(vector<int>& vec, vector<int>& sorted_vec)
{
    int asc{ 0 }, des{ 0 };
    int n = vec.size()-1;

    for (int i = 0; i < n+1; i++)
    {
        if (vec.at(i) != sorted_vec.at(i))
            asc++;
        if (vec.at(n-i) != sorted_vec.at(i))
            des++;
    }

    if(des < asc)
        reverse(sorted_vec.begin(), sorted_vec.end());
}

int lilysHomeworkMap(vector<int>& vec)
//Sorted arrays are most beautiful, note that it can be either ascending or descending and must be tested for which will give minimal swaps
{
    int n_swap{ 0 };
    unordered_map<int, int> u_map;
    unordered_map<int, int>::iterator it, it2;
    vector<int> sorted_vec = vec;

    for (auto& i : vec)
        cout << i << ",";
    cout << endl;

    for (int i = 0; i < vec.size(); i++)
        u_map[vec.at(i)] = i;

    sort(sorted_vec.begin(), sorted_vec.end());
    ascVsDes(vec, sorted_vec);

    for (int i = 0; i < vec.size(); i++)
    {
        if (vec.at(i) != sorted_vec.at(i))
        {
            n_swap++;
            it = u_map.find(sorted_vec.at(i));
            it2 = u_map.find(vec.at(i));
            swap(vec.at(i), vec.at(it->second));
            it2->second = it->second;
            it->second = i;
            
        }
    }

    for (auto& i : vec)
        cout << i << ",";
    cout << endl;

    return n_swap;
}

int lilysHomework(vector<int>& vec)
//Sorted arrays are most beautiful, note that it can be either ascending or descending and must be tested for which will give minimal swaps
{
    vector<int> sorted_vec = vec;
    int n_swap{ 0 };
    vector<int>::iterator it;
    //map<int,int> 

    sort(sorted_vec.begin(), sorted_vec.end());

    for (int i = 0; i < vec.size(); i++)
    {
        if (vec.at(i) != sorted_vec.at(i))
        {
            n_swap++;
            it = find(vec.begin(), vec.end(), sorted_vec.at(i));
            iter_swap(vec.begin() + i, it);
        }
    }

    for (auto& i : vec)
        cout << i << ",";
    cout << endl;

    return n_swap;
}

int main()
{
    vector<int> my_vec{ 7,15,12,3 };
    int ans = lilysHomeworkMap(my_vec);

    cout << ans << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
