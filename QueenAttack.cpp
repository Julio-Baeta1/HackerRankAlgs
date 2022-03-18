// QueenAttack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

using namespace std;

//int 

vector<int> maxQueenAttack(int n, int r_q, int c_q)
{
    vector<int> max_moves(8,0);
    
    max_moves.at(0) = c_q - 1; //Moves left
    max_moves.at(1) = n - c_q; //Moves right
    max_moves.at(2) = r_q - 1; //Moves down
    max_moves.at(3) = n - r_q; //Moves up

    max_moves.at(4) += min(r_q - 1, c_q - 1); //For diag Down/Left
    max_moves.at(5) += min(r_q - 1, n - c_q); //For diag Down/Right
    max_moves.at(6) += min(n - r_q, c_q - 1); //For diag Up/Left
    max_moves.at(7) += min(n - r_q, n - c_q); //For diag Up/Right

    return max_moves;
}

int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>>& obstacles) {

    pair<int, int> diff = { 0,0 };
    vector<int> max_moves = maxQueenAttack(n, r_q, c_q);
    vector<int> blocked_moves(8,0);

    for (int i = 0; i < k; i++)
    {
        diff = { r_q - obstacles.at(i).at(0), c_q - obstacles.at(i).at(1) };

        if (diff.first == 0)
        {
            if (diff.second > 0)
                blocked_moves.at(0) = max(blocked_moves.at(0), max_moves.at(0)+1 - diff.second);
            else
                blocked_moves.at(1) = max(blocked_moves.at(1), max_moves.at(1)+1 - abs(diff.second));
        }

        else if(diff.second == 0)
        {
            if (diff.first > 0)
                blocked_moves.at(2) = max(blocked_moves.at(2), max_moves.at(2) + 1 - diff.first);
            else
                blocked_moves.at(3) = max(blocked_moves.at(3), max_moves.at(3) + 1 - abs(diff.first));
        }

        else if (abs(diff.first) == abs(diff.second))
        {
            if (diff.first > 0)
            {
                if (diff.second > 0)
                    blocked_moves.at(4) = max(blocked_moves.at(4), max_moves.at(4) + 1 - diff.first);
                else
                    blocked_moves.at(5) = max(blocked_moves.at(5), max_moves.at(5) + 1 - diff.first);
            }
            else
            {
                if (diff.second > 0)
                    blocked_moves.at(6) = max(blocked_moves.at(6), max_moves.at(6) + 1 - diff.second);
                else
                    blocked_moves.at(7) = max(blocked_moves.at(7), max_moves.at(7) + 1 - abs(diff.second));
            }
        }

    }

    int total_moves = 0;
    for (int i = 0; i < 8; i++)
        total_moves += max_moves.at(i) - blocked_moves.at(i);
    
    return total_moves;
}

int main()
{
    int n = 5;
    int r_q = 4;
    int c_q = 3;
    vector<vector<int>> obstacles{ {5,5},{4,2},{2,3} };
    int k = obstacles.size();

    int ans = 0;

    ans = queensAttack(n, k, r_q, c_q, obstacles);

    cout << ans << endl;

    //for (int i = 1; i < 6; i++)
    //{
    //    for (int j = 1; j < 6; j++)
    //    {
    //        cout << "(" << (4 - i) << " , " << (3 - j) << ")  ";
    //    }
    //    cout << endl;
    //}
    //vector<int> ans_vec = maxQueenAttack(n, r_q, c_q);
    //for (auto& i : ans_vec)
    //{
    //    cout << i << endl;
    //    //cout << i.at(0) << " , " << i.at(1) << endl;
    //}
}

//int maxQueenAttack(int n, int r_q, int c_q)
//{
//    int queen_attack = 0;
//
//    queen_attack += r_q + c_q - 2; //For moves left and down
//    queen_attack += 2 * n - r_q - c_q; //For moves right and up
//
//    queen_attack += min(r_q - 1, c_q - 1); //For diag Down/Left
//    queen_attack += min(r_q - 1, n - c_q); //For diag Down/Right
//    queen_attack += min(n - r_q, c_q - 1); //For diag Up/Left
//    queen_attack += min(n - r_q, n - c_q); //For diag Up/Right
//
//    return queen_attack;
//}
