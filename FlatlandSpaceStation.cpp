// FlatlandSpaceStation.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getMaxDistSpaceStation(int n, vector<int>& c)
{
    int max_dist = c.at(0);

    if (c.size() != n)
    {
        sort(c.begin(), c.end());

        for (int i = 0; i < c.size() - 1; i++)
        {
            max_dist = max(max_dist, (c.at(i + 1) - c.at(i))/2);
        }
        
        max_dist = max(max_dist, n - 1 - c.back());
    }

    return max_dist;
}

int main()
{
    vector<int> space_station{ 0,1,4};
    int ans = getMaxDistSpaceStation(5, space_station);
    cout << ans;
}

