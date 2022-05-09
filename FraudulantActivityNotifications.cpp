#include <iostream>
#include <vector>
#include <deque>
#include <algorithm> 
#include <map>

using namespace std;

void printVector(vector<int>& q)
//Helper function to print deque
{
    for (auto& i : q)
        cout << i << ", ";
    cout << endl;
}


int activityNotifications(vector<int>& expenditure, int d)
{
    int n_noti{ 0 }, med_indx{0};
    double med_count{0};
    const int max_expen{ 201 };
    vector<int> count_vec(max_expen-1, 0);

    for (int i = 0; i < d; i++)
        count_vec.at(expenditure.at(i))++;

    for (int i = d; i < expenditure.size(); i++)
    {
        med_count = 0;
        med_indx = 0;

        if (d % 2 == 0)
        {
            for (int j = 0; j < count_vec.size(); j++)
            {
                med_count += count_vec.at(j);
                if (med_count == d / 2)
                {
                    med_indx = j;
                }
                else if (med_count > d / 2)
                {
                    if (med_indx > 0)
                        med_indx += j;
                    else
                        med_indx = 2 * j;
                    break;
                }
            }

            if (expenditure.at(i) >= med_indx)
                n_noti++;
        }
        else
        {
            for (int j = 0; j < count_vec.size(); j++)
            {
                med_count += count_vec.at(j);
                if (med_count > d / 2)
                {
                    med_indx = j;
                    //cout << med_count;
                    break;
                }
            }

            if (expenditure.at(i) >= 2 * med_indx)
                n_noti++;
        }


        //cout << med_indx << endl;
        //printVector(count_vec);

        count_vec.at(expenditure.at(i - d))--;
        count_vec.at(expenditure.at(i))++;

    }

    return n_noti;
}

int main()
{
    vector<int> my_vec{ 1,2,3,4 ,11};  
    int window = 4;

    //vector<int> my_vec{ 2,3,4,2,3,6,8,4,5 };
    //int window = 5;

    int ans = activityNotifications(my_vec, window);
    cout << ans << endl;
}

//int activityNotifications(vector<int>& expenditure, int d)
//{
//    deque<int> windowed;
//    int n_alerts{ 0 };
//
//    for (int i = 0; i < d; i++)
//        windowed.push_back(expenditure.at(i));
//
//    for (int i = d; i < expenditure.size(); i++)
//    {
//        n_alerts += isAlert(windowed, expenditure.at(i));
//        windowed.pop_front();
//        windowed.push_back(expenditure.at(i));
//    }
//
//    return n_alerts;
//}
