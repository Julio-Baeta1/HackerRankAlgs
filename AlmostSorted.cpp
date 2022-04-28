// AlmostSorted.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>

using namespace std;

bool printYes(int& first, int& second, bool revYes)
//Helper function that prints operation to make array sorted, returns true so that unsortable condition is not trigggered
{
    if (revYes == false)
        cout << "yes" << endl << "swap " << first + 1 << " " << second + 1;
    else if (revYes == true)
        cout << "yes" << endl << "reverse " << first + 1 << " " << second + 1;

    return true;
}

void almostSorted(vector<int>& alm_vec)
{
    int first_index{-1}, second_index{ 0 };  //Indices to swap or for range between to reverese
    bool flag_succ=false, swap_true=false, rev_true = false; //flag_succ: if array can be sorted,  swap_true: use swap,  rve_true: use reverse

    for (int i = 1; i < alm_vec.size(); i++)
    {
        if (alm_vec.at(i) < alm_vec.at(i-1)) //e.g 5,1
        {
            
            if (first_index == -1) //first occurence
                first_index = i - 1;

            else if (first_index > -1) //occurence after the first
            {
                if (second_index == 0) //second occurence
                {
                    second_index = i;

                    if (alm_vec.at(first_index) == alm_vec.at(first_index + 1) + 1 && alm_vec.at(first_index) == alm_vec.at(i) + 2) // 5,4,3 i.e. reveresable
                        rev_true = true;
                    else                        //Is swappable
                        swap_true = true;
                }

                else if (rev_true == true && alm_vec.at(second_index) == alm_vec.at(i) + 1) //next entry in reveresable list
                    second_index = i;

                //Cannot allow more than one operation i.e. more than one swap or a swap and a reverese
                else if (swap_true == true)
                    rev_true = true;
                else if (rev_true == true)
                    swap_true = true;
            }
        }
    }


    if (first_index != -1 && second_index == 0) //case for when adjacent entries must be swapped 
    {
        second_index = first_index + 1;
        swap_true = true;
    }


    if (rev_true == false && swap_true == false) // Array already sorted
    {
        cout << "yes" << endl;
        flag_succ = true;
    }

    else if (rev_true == true && swap_true == false) //Reverse 1,5,4,3,2,6
    {
        if (first_index == 0) //No left most entry to consider in reverse
        {
            if (second_index == alm_vec.size() - 1) //No right most entry to consider in reverse
                flag_succ = printYes(first_index, second_index, true);
            else if (alm_vec.at(first_index) < alm_vec.at(second_index + 1) ) //Test right most entry 
                flag_succ = printYes(first_index, second_index, true);
        }
        else if (alm_vec.at(first_index-1) < alm_vec.at(second_index)) //Test left most entry 1,5,4,3,2 1<2 so can reverse
        {
            if (second_index == alm_vec.size() - 1)
                flag_succ = printYes(first_index, second_index, true);
            else if (alm_vec.at(first_index) < alm_vec.at(second_index + 1)) //5,4,3,2,6 5<6 so can reverese
                flag_succ = printYes(first_index, second_index, true);
        }
    }

    else if (rev_true == false && swap_true == true) //Swap 1,9,3,...,8,2,10
    {
        if (alm_vec.at(second_index) <= alm_vec.at(first_index + 1) && alm_vec.at(first_index) >= alm_vec.at(second_index - 1))
        // Test if in between entries are valid e.g. 9,3,...,8,2 we can swap 9 and 2 because 2<3 and 9>8
        {
            if (first_index == 0) //no left most entry to consider
            {
                if (second_index == alm_vec.size() - 1) //no right most entry to consider
                    flag_succ = printYes(first_index, second_index, false);
                else if (alm_vec.at(first_index) < alm_vec.at(second_index + 1)) // Test right most entry
                    flag_succ = printYes(first_index, second_index, false);
            }
            else if (alm_vec.at(second_index) > alm_vec.at(first_index - 1)) //Test left most entry 1,9,...,8,2 2>1 so can swap
            {
                if (second_index == alm_vec.size() - 1)
                    flag_succ = printYes(first_index, second_index, false);
                else if (alm_vec.at(first_index) < alm_vec.at(second_index + 1)) // 9,3,...,2,10 9<10 so can swap
                    flag_succ = printYes(first_index, second_index, false);
            }
        }
    }
    else if (rev_true == true && swap_true == true) // Cannot be sorted in one operation
    {
        cout << "no" << endl;
        flag_succ = true;
    }

    if (flag_succ == false) //Catch if array cannot be sorted in one operation
        cout << "no" << endl;

}

int main()
{
    vector<int> my_vec{1,2,3,6,4,5};
    almostSorted(my_vec);
}
