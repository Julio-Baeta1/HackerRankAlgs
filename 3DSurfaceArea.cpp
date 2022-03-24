// 3DSurfaceArea.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

int sumSides(int row, int col, vector<vector<int>>& c)
{
    int rows = c.size();
    int cols = c.at(0).size();
    int tot = 2 * rows * cols;

    if (cols == rows)
    {
        //cout << "square" << endl;
        for (int i = 0; i < cols; i++)
        {
            tot += c.at(0).at(i);
            tot += c.at(rows - 1).at(i);
            tot += c.at(i).at(0);
            tot += c.at(i).at(cols - 1);

            for (int j = 1; j < rows; j++)
            {
                tot += abs(c.at(j).at(i) - c.at(j - 1).at(i));
                tot += abs(c.at(i).at(j) - c.at(i).at(j - 1));
                if (c.at(i).at(j) == 0)
                    tot -= 2;
                if (c.at(j).at(i) == 0 && j > i )
                    tot -= 2;
            }
        }
        if (c.at(0).at(0) == 0)
            tot -= 2;
    }

    else
    {
        for (int i = 0; i < cols; i++)
        {
            tot += c.at(0).at(i);
            tot += c.at(rows - 1).at(i);

            for (int j = 1; j < rows; j++)
            {
                tot += abs(c.at(j).at(i) - c.at(j - 1).at(i));
            }
        }

        for (int i = 0; i < rows; i++)
        {
            tot += c.at(i).at(0);
            tot += c.at(i).at(cols - 1);

            for (int j = 1; j < cols; j++)
            {
                tot += abs(c.at(i).at(j) - c.at(i).at(j - 1));
                if (c.at(i).at(j) == 0)
                    tot -= 2;
            }

            if (c.at(i).at(0) == 0)
                tot -= 2;
        }
    }

    return tot;
}


int main()
{
    const int col = 3;
    const int row = 2;
    vector<vector<int>> instr{ {1,3,4},{2,2,3},{1,2,4} }; //60
    //vector<vector<int>> instr{ {0,1,1},{1,0,2},{1,2,3} }; //42
    //vector<vector<int>> instr{ {1,1,1},{1,1,2},{1,2,3} }; //42
    //vector<vector<int>> instr{ {0,1,1},{1,1,2},{1,2,3} }; //40
    //vector<vector<int>> instr{ {0,0,1},{0,0,2},{1,2,3} }; //34
    //vector<vector<int>> instr{ {0,0,0},{0,0,0},{1,2,3} }; //24
    //vector<vector<int>> instr{ {1,2,3},{4,5,6},{7,8,9} }; //102
    //vector<vector<int>> instr{ {1,2,3},{2,3,4}}; //44
    //vector<vector<int>> instr{ {3,4},{2,3},{1,2} }; //44
    //vector<vector<int>> instr{ {1},{2},{3} }; //24

    int ans = 0;
    ans = sumSides(row,col,instr);
    cout << ans << endl;

}
