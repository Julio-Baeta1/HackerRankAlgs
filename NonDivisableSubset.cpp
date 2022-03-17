// NonDivisableSubset.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

int longestSubset(vector<int>& s, int& n, int& k)
/*
* Rather considering the remiander of the sum of two integers, consider the remainder of each integer first and then sum them.
* If the sum of two remainders equals k then it is invalid i.e k=3 we cannot add remainder 1 to 2 as that will be 3 (7+8=15 or 1+2=3)
* Thus excluding remainder 0 and k/2 for even k:
*       We count the number of remainders for modulus i and k-i and add the largest number to the running total
* For 0 we increase the running total by 1 if a multiple of k exists in the original set since (3+1=4 or 0+1=1)
* Lastly if K is even then i=k/2=k-k/2 thus we can only include a maximum of one so we increase the running total by one if it exists
*/

{
    map<int, int> modulus_tree;
    int temp = 0;

    for (int i = 0; i < k; i++)
        modulus_tree.insert({ i,0 });

    for (int i = 0; i < n; i++)
        modulus_tree.at(s.at(i) % k)++;

    int subset_size = 0;
    int k_half = k/2;

    if (k % 2 == 0)
    {
        if (modulus_tree.at(k/2) > 0)
            subset_size++;
        k_half--;
    }

    for (int i = 1; i <= k_half; i++)
    {
        subset_size += max(modulus_tree.at(i), modulus_tree.at(k - i));
    }

    if (modulus_tree.at(0) > 0)
        subset_size++;

    return subset_size;
}

//Smarter use sum of modulus
int main()
{
    vector<int> S = { 1,7,2,4,3,13 };
    //S = { 3,17,12,9,11,15,7};
    S = { 278, 576, 496, 727, 410, 124, 338, 149, 209, 702, 282, 718, 771, 575, 436 };
    int n = S.size();
    int k = 7;
    int ans= 0;

    ans = longestSubset(S, n, k);
    cout << ans;
}

/*
//Brute force method
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printVecSet(vector<set<int>>& vec_set)
//Function to print a vector of int sets
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
//Function to compare two int set
//If sets contain the exact same elements bool = true, missing_val = -1
//If sets are almost equal but for one element in each bool =true, missing_val: is the missing element value
//Else returns bool = flase and missing_element = 0
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
//Function to combine sets of size n, to make new sets of size n+1
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
            //If there exists a possibility of combining sets
            {
                search_vals = SN.at(i);
                search_vals.insert(comparable_subset.second);

                if (!SnPlus1.empty())
                //Test if potential n+1 set is not already created 
                {

                    for (int qq = 0; qq < SnPlus1.size(); qq++)
                    {
                        comparable_subset = comparedSubSet(SnPlus1.at(qq), search_vals);
                        if (comparable_subset.second == -1)
                        {
                            flag = true;
                        }
                    }
                }

                if (flag == false)
                //Potential n+1 set does not exist
                {
                    count = 0;

                    for (int q = 0; q < nn; q++)
                    //Counts number of n sets as a n+1 set requires n+1, comparable n sets to be created 
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

    vector<set<int>> Sn;
    set<int> temp;

    for (int i=0; i<n-1; i++)
    //Inital vector of sums that are not divisable by k
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

    int nn = Sn.size();
    int max_count = 3;
    int ans = 2;

    while(nn > max_count -1)
    //if nn < n+1, there is insuffcient sets to make one n+1 set, so end
    {
       
        Sn = combineSubSet(Sn, max_count);

        if (!Sn.empty())
            ans = Sn.at(0).size();

        max_count++;
        nn = Sn.size();
    }
    
    
    cout << ans << endl;
    printVecSet(Sn);
}*/
