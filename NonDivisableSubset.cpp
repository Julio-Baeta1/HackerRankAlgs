// NonDivisableSubset.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <set>

using namespace std;

void printVecSet(vector<set<int>>& vec_set)
{
    cout << "Number of trees: " << vec_set.size() << endl;
    for (auto& ii : vec_set)
    {
        for (auto& jj : ii)
        {
            cout << jj << ", ";
        }
        cout << endl;
    }
}

pair<bool,int> comparedSubSet(set<int>& a, set<int>& b)
{
    int missing_val = -1;
    set<int>::iterator it;

    for (auto& val : b)
    {
        it = a.find(val);
        if (it == a.end())
        {
            if (missing_val < 0)
                missing_val = val;
            else
            {
                missing_val = 0;
                return make_pair(false, missing_val);
            }
        }
    }

    return make_pair(true, missing_val);
}

vector<set<int>> combineSubSet(vector<set<int>>& SN, int& max_count)
{
    vector<set<int>> SnPlus1;
    int nn = SN.size();
    int count = 0;
    bool flag = false;
    pair<bool, int> comparable_subset;
    set<int> search_vals;

    for (int i = 0; i < nn - 1; i++)
    {
        for (int j = i + 1; j < nn; j++)
        {
            comparable_subset = comparedSubSet(SN.at(i), SN.at(j));

            if (comparable_subset.first == true)
            {
                search_vals = SN.at(i);
                search_vals.insert(comparable_subset.second);

                if (!SnPlus1.empty())
                {

                    for (int qq = 0; qq < SnPlus1.size(); qq++)
                    {
                        comparable_subset = comparedSubSet(SnPlus1.at(qq), search_vals);
                        //cout << qq << ": " << comparable_subset.second << endl;
                        if (comparable_subset.second == -1)
                        {
                            flag = true;
                            //cout << "green" << endl;
                        }
                    }
                }

                if (flag == false)
                {
                    count = 0;

                    for (int q = 0; q < nn; q++)
                    {
                        comparable_subset = comparedSubSet(SN.at(q), search_vals);
                        if (comparable_subset.first == true)
                            count++;
                    }

                    if (count == max_count)
                        SnPlus1.push_back(search_vals);
                }
                else
                    flag = false;
            }
        }
    }

    return SnPlus1;
}

int main()
{
    vector<int> S = { 1,7,2,4,3,13};
    int n = S.size();
    int k = 3;

    //Inital vector of sums that are not divisable by k
    vector<set<int>> Sn;
    set<int> temp;

    for (int i=0; i<n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if ((S[i] + S[j]) % k != 0)
            {
                temp.insert(S[i]);
                temp.insert(S[j]);
                Sn.push_back(temp);
                temp.clear();
            }
        }
    }

    //printVecSet(Sn);

    int nn = Sn.size();
    int max_count = 3;
    int ans = 2;

    //if (nn > max_count - 1)
    while(nn > max_count -1)
    {
       
        Sn = combineSubSet(Sn, max_count);

        if (!Sn.empty())
            ans = Sn.at(0).size();

        max_count++;
        nn = Sn.size();
    }
    
    
    cout << ans << endl;
    printVecSet(Sn);
}

//set<int> test;
//test.insert(3);
//test.insert(6);
//pair<bool, int> myval = comparedSubSet(Sn.at(1), test);
//cout << myval.second << endl;
