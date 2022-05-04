// This code is not very effcient, however this is a first solution that illustates the concepts in a more readable format rather than having a function that 
// directly maps matrix elements to the rotated postions skipping turning each layer into a vector, moduluslly shifting it and inserting it back into the 
// appropriate matrix layer

#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

void printMat(vector<vector<int>>& mat)
//helper function to print matrix
{
    for (auto& row : mat)
    {
        for (auto& elem : row)
            cout << elem << ' ';
        cout << endl;
    }
    cout << endl;
}

void printVec(vector<int>& vec)
//helper function to print vector
{
    for (auto& elem : vec)
        cout << elem << ' ';
    cout << endl;
}

vector<int> matRingToVec(vector<vector<int>>& mat, int rows, int cols, int shift)
//Turns a matrix layer into a vector while preserving anti-clockwise order
{
    vector<int> my_vec;

    for (int i = 0; i < rows; i++) //Read entries downwards of first column
        my_vec.push_back(mat.at(i + shift).at(shift));

    for (int i = 1; i < cols - 1; i++)
        my_vec.push_back(mat.at(rows - 1 + shift).at(i + shift)); //Read entries (excluding first and last) forward of bottom row

    for (int i = rows-1; i > 0; i--) //Read entries (excluding first) upwards of last column
        my_vec.push_back(mat.at(i+shift).at(cols-1 + shift)); 

    for (int i = cols-1; i > 0; i--) // Read entries (excluding first) backwards of top row
        my_vec.push_back(mat.at(shift).at(i+shift));

    return my_vec;
}

void coilOntoMat(vector<vector<int>>& mat, vector<int>& vec, int rows, int cols, int shift)
//Insert a vector's entries onto a matrix layer while preserving order in an anti-clockwise direction
{
    int length = 2 * (rows + cols - 2); //total number of elements

    for (int i = 0; i < rows; i++) //Insert entries downwards into matrix layer's first column
        mat.at(i + shift).at(shift) = vec.at(i); 

    for (int i = 1; i < cols; i++) //Insert entries forwards into matrix layer's bottom row (excluding first)
        mat.at(rows - 1 + shift).at(i+shift) = vec.at(i + rows - 1);

    for (int i = rows - 2; i > 0; i--) //Insert entries upwards into matrix layer's last column (excluding first and last)
        mat.at(i + shift).at(cols - 1 + shift) = vec.at(2*rows + cols - 3 - i);

    for (int i = cols - 1; i > 0; i--) //Insert entries backwards into matrix layer's top row (excluding first)
        mat.at(shift).at(i+shift) = vec.at(length - i);
}

vector<int> circularShift(vector<int>& original, int k)
//Use modulus of vector length so that a circular shift of k places is performed
{
    vector<int> new_vec = original;
    int n = original.size();
    for (int i = 0; i < n; i++)
        new_vec.at((i + k) % n) = original.at(i);

    return new_vec;
}

void rotateMat(vector<vector<int>>& mat, int r)
//Function that rotates matrix layers of mat (min(n_rows,n_cols) is divisable by 2) r times 
{
    int n_rows = mat.size();
    int n_cols = mat.at(0).size();

    int outer_elems = 2 * (n_rows + n_cols - 2); //number elements in matrix layer
    //rr: number of rotations for layer e.g. layer has 8 elements and we wish to rotate 12 times, then a rotation of 4 times is equivalent
    //k: For multiple layers each inner layer's indices must be shifted to correct obtain it in the matrix, as functions assume layer is the outermost by default
    int rr = { 0 }, k{ 0 }; 
    int n_layer = min(n_rows, n_cols) / 2;

    vector<int> temp; //temporary vector for circular shift rotation

    for(int i = 0; i < n_layer; i++)
    {   
        rr = r % outer_elems;
        if (rr != 0)
        {
            temp = matRingToVec(mat, n_rows, n_cols, k);
            temp = circularShift(temp, rr);
            coilOntoMat(mat, temp, n_rows, n_cols, k);
        }

        // Move to next inner layer
        n_rows -= 2;
        n_cols -= 2;
        outer_elems = 2 * (n_rows + n_cols - 2);
        k++;

        temp.clear();
    }
    printMat(mat);
}

int main()
{
    int rotations = 3;
    //Test examples
                                            //For r=3
    vector<vector<int>> my_mat{ {1,2},      //          1 2    ->     3 1
                                {3,4} };    //          3 4           4 2

    //vector<vector<int>> my_mat{ {1,2, 3, 4},
    //                        {5,6,7,8},
    //                        {9,10,11,12},
    //                        {13,14,15,16} };

    //vector<vector<int>> my_mat{ {1,2, 3, 4, 5},
    //                            {6,7,8,9,10},
    //                            {11,12,13,14,15},
    //                            {16,17,18,19,20} };

    //vector<vector<int>> my_mat{ {1,2, 3, 4},
    //                    {5,6,7,8},
    //                    {9,10,11,12},
    //                    {13,14,15,16},
    //                    {17,18,19,20} };

 /*   vector<vector<int>> my_mat{
        {9718805, 60013003, 5103628, 85388216, 21884498, 38021292, 73470430, 31785927},

        {69999937, 71783860, 10329789, 96382322, 71055337, 30247265, 96087879, 93754371},

        {79943507, 75398396, 38446081, 34699742, 1408833, 51189, 17741775, 53195748},

        {79354991, 26629304, 86523163, 67042516, 54688734, 54630910, 6967117, 90198864},

        {84146680, 27762534, 6331115, 5932542, 29446517, 15654690, 92837327, 91644840},

        {58623600, 69622764, 2218936, 58592832, 49558405, 17112485, 38615864, 32720798},

        {49469904, 5270000, 32589026, 56425665, 23544383, 90502426, 63729346, 35319547},

        {20888810, 97945481, 85669747, 88915819, 96642353, 42430633, 47265349, 89653362},

        {55349226, 10844931, 25289229, 90786953, 22590518, 54702481, 71197978, 50410021},

        {9392211, 31297360, 27353496, 56239301, 7071172, 61983443, 86544343, 43779176} };*/

    rotateMat(my_mat,rotations);
}
