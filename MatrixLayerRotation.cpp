// MatrixRotation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

void printMat(vector<vector<int>>& mat)
{
    for (auto& row : mat)
    {
        for (auto& elem : row)
            cout << elem << ' ';
        cout << endl;
    }
}

//pair<int, int> rotateIndices(pair<int,int> initial, int rows, int cols, int length, int k)
//{
//    int i{ 0 }, 
//        j{ 0 };
//    
//    if (initial.first + initial.second + k < rows)
//        i = initial.first + k;
//    else if (initial.first + initial.second + k < rows + cols - 1)
//    {
//        i = rows - 1;
//        j = k - i;
//    }
//    else if (initial.first + initial.second + k < rows + cols * 2 - 2)
//    {
//        j = cols - 1;
//        i = rows - k + j;
//    }
//    else if (initial.first + initial.second + k < length)
//    {
//        j = length - k;
//    }
//
//    pair<int, int> my_pair{ i,j };
//    return my_pair;
//}

vector<int> matRingToVec(vector<vector<int>>& mat, int rows, int cols)
{
    vector<int> my_vec;
    for (int i = 0; i < rows; i++)
        my_vec.push_back(mat.at(i).at(0));
    for (int i = 1; i < cols; i++)
        my_vec.push_back(mat.at(rows-1).at(i));
    for (int i = rows-2; i > 0; i--)
        my_vec.push_back(mat.at(i).at(cols-1));
    for (int i = cols-1; i > 0; i--)
        my_vec.push_back(mat.at(0).at(i));

    return my_vec;
}

void uncoilIntoMat(vector<vector<int>>& mat, vector<int>& vec, int rows, int cols)
{
    int length = 2 * (rows + cols - 2);
    for (int i = 0; i < rows; i++)
    {
        mat.at(i).at(0) = vec.at(i);       
    }
    for (int i = 1; i < cols; i++)
    {
        mat.at(rows - 1).at(i) = vec.at(i + rows - 1);
    }
    for (int i = rows - 2; i > 0; i--)
        mat.at(i).at(cols - 1) = vec.at(rows+cols+1-i);
    for (int i = cols - 1; i > 0; i--)
    {
        //mat.at(0).at(i) = vec.at(2 * rows + cols - 2 - i);
        //mat.at(0).at(i) = vec.at(2 * rows + cols - i);
        mat.at(0).at(i) = vec.at(length - i);
    }
}

vector<int> poorShift(vector<int>& original, int k)
{
    vector<int> new_vec = original;
    int n = original.size();
    for (int i = 0; i < n; i++)
    {
        //new_vec.at(i) = original.at((i + k) % n); //opposite
        new_vec.at((i + k) % n) = original.at(i);
    }
    return new_vec;
}

void rotateMat(vector<vector<int>>& mat, int r)
{
    int n_rows = mat.size();
    int n_cols = mat.at(0).size();

    int tot_elems = n_rows * n_cols;
    int outer_elems = 2 * (n_rows + n_cols - 2);
    int rr = r % outer_elems;

    pair<int, int> coords{ 0,0 };

    vector<int> temp = matRingToVec(mat, n_rows, n_cols);
    temp = poorShift(temp, rr);

    vector<int> temp_vec(n_cols, 0);
    vector<vector<int>> temp_mat(n_rows, temp_vec);

    for (auto& i : temp)
        cout << i << ", ";
    cout << endl;
    uncoilIntoMat(temp_mat, temp, n_rows, n_cols);
    printMat(temp_mat);
}

int main()
{
    //vector<vector<int>> my_mat{ {1,2},
    //                            {3,4} };
    vector<vector<int>> my_mat{ {1,2, 3, 4},
                            {5,6,7,8},
                            {9,10,11,12},
                            {13,14,15,16} };

    rotateMat(my_mat,3);

    //printMat(temp_mat);
}

//if (rr == 0)
//    cout << "no rotation" << endl;
//else
//{
//    //coords = rotateIndices(coords, n_rows, n_cols, outer_elems, rr);
//    //cout << coords.first << "," << coords.second << endl;
//    //vector<int> holder(rr, 0);
//    //int j{ 0 };

//    //for (int i = 0; i < outer_elems; i++)
//    //{
//    //    holder.at(0) = mat.at(coords.first).at(coords.second);
//    //    mat.at(coords.first).at(coords.second) = mat.at(i).at(j);
//    //}
//}

