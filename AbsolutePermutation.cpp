// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

vector<int> absolutePermutation(int n, int k)
/*For integer n an ordered set of n elements of index value is created e.g. n=4 [1,2,3,4] index value starts at 1 and not 0 for this problem
* 
* This set can be rearranged so that the absolute difference between the rearranged set and the index set is k for all positions e.g
*       n=4 k=2 gives           index set: [1,2,3,4] 
*                        - rearranged set: [3,4,1,2] 
*                        = difference set: [-2,-2,2,2]
* absolute value of difference set is [2,2,2,2] with all elements equal to k
* 
* This function returns the relevant rearranged set so all the difference set elements equal k and -1 if that is not possible.
*/
{
    vector<int> imp{ -1 }; //not possible
    vector<int> ap(n, 0);

    if (k == 0)
    // Special case: a difference of zero means the vector value matches the index value, thus ap = index set
    {
        for (int i = 1; i < n + 1; i++)
            ap.at(i - 1) = i;

        return ap;
    }

    if((n/k)%2 == 0)
    // The ratio of n and k must be even; else there will be a index value without a corresponding set value for which the difference is equal to k 
    // without reusing values. 
    {
        vector<int> holder;
        int temp = 0;

        for (int i = 0; i < k; i++)
        {
            temp = i + 1;

            while (temp <= n)
            //Create a chain of values with difference equal to k
            {
                holder.push_back(temp);
                temp += k;
            }

            if (holder.size() % 2 == 0)
            // If is odd then there is insuffcient values so that a k difference can be maintained
            {
                for (int j = 0; j < holder.size()-1; j += 2)
                //swap rearranged set value with correpsonding value in chain link
                {
                    ap.at(holder.at(j)-1) = holder.at(j + 1);
                    ap.at(holder.at(j + 1)-1) = holder.at(j);
                }
                
            }
            else
                return imp;

            holder.clear();
        }

    }
    else
        return imp;

    return ap;
}

int main()
{
    int n = 16;
    int k = 4;
    vector<int> ans = absolutePermutation(n, k);

    if (ans.at(0) == -1)
        cout << "not possible" << endl;
    for (int i = 0; i<ans.size(); i++)
        cout << ans.at(i) << ", ";
        //cout << abs(ans.at(i)-i-1) << ", ";
    cout << endl;
}
