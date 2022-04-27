// LarryArray.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>

using namespace std;

vector<int>::iterator orderThreeIter(vector<int>::iterator three_vec)
//Sort ordered 3 element set so that first entry is the smallest through a rotation
{
    //default do nothing for ABC/ACB 
    int temp{ 0 };
    if(*(three_vec+1) < *(three_vec + 2) && *(three_vec + 1) < *three_vec ) // BAC/CAB to ACB/ABC 
    {
        temp = *three_vec;
        *three_vec = *(three_vec+1);
        *(three_vec+1) = *(three_vec + 2);
        *(three_vec+2) = temp;
    }
    else if (*(three_vec + 2) < *(three_vec + 1) && *(three_vec + 2) < *three_vec) // BCA/CBA to ABC/ACB
    {
        temp = *three_vec;
        *three_vec = *(three_vec + 2);
        *(three_vec + 2) = *(three_vec + 1);
        *(three_vec + 1) = temp;
    }

    return three_vec; 
}

bool canRotateSwap(vector<int>::iterator three_vec)
//Test if oredered 3 element can be orderd as monotonic increasing through rotation ABC->BCA->CAB->ABC
{
    if (*(three_vec + 2) > *(three_vec + 1) && *(three_vec + 1) > *three_vec) // if it is ABC
        return true;
    else if (*(three_vec + 1) > *three_vec && *three_vec > *(three_vec + 2)) // if it is BCA
        return true;
    else if (*three_vec > *(three_vec + 2) && *(three_vec + 2) > *(three_vec + 1)) // if it is CAB
        return true;
    else
        return false;
}

void LarryArray(vector<int>& my_vec)
{
    int n = my_vec.size();
    vector<int>::iterator sorted_pos = my_vec.begin(); //all elements before are sorted
    vector<int>::iterator iter = find(my_vec.begin(), my_vec.end(), 1);

    for (int i = 1; i < n - 2; i++) //sort n-3 elements
    {
        while (*sorted_pos > i) //if dereferenced sorted index = i, then element is in its correct position to be in sorted array 
        {
            if (iter - sorted_pos < 2) //Smallest element is one position away from its correct 
                iter--;
            else                      //Smallest element is at least 2 postions away from its correct postion, however roation can only take place for 3 
                iter -= 2;            // set so it can only move a maximum of 2 places per a rotation

            iter = orderThreeIter(iter); 
        }

        sorted_pos++; //move sorted position
        iter = find(my_vec.begin(), my_vec.end(), i + 1); // get iterator for next value
    }

    bool ans = false;
    ans = canRotateSwap(sorted_pos);

    if (ans == true)
    {
        cout << "YES" << endl;
        iter = orderThreeIter(sorted_pos);
    }
    else
        cout << "NO" << endl;

    //cout << "Print vec" << endl;
    //for (auto& i : my_vec)
    //    cout << i << endl;
}

int main()
{
    vector<int> my_vec{ 7,9,15,8,10,16,6,14,5,13,17,12,3,11,4,1,18,2 };//{ 1,2,3,5,4,6,8,7,9 };//{ 1,6,5,2,4,3 };//{3, 1, 2, 4};
    LarryArray(my_vec);
    
}
