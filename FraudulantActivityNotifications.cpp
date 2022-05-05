#include <iostream>
#include <vector>
#include <deque>
#include <algorithm> 

using namespace std;

void printDeque(deque<int>& q)
{
    for (auto& i : q)
        cout << i << ", ";
    cout << endl;
}

int isAlert(deque<int> expen_hist, int expen_today)
{
    sort(expen_hist.begin(), expen_hist.end());
    int n = expen_hist.size();
    double med{ 0.0 };
    
    if (n % 2 == 0)
        med = expen_hist.at((n / 2) - 1) + expen_hist.at((n / 2));
        //med = (expen_hist.at((n / 2) - 1) + expen_hist.at((n / 2))) / 2;
    else
        med = 2*expen_hist.at(int(n / 2));

    if (expen_today >= med)
        return 1;
    else
        return 0;

}

int activityNotifications(vector<int>& expenditure, int d)
{
    deque<int> windowed;
    int n_alerts{0};

    for (int i = 0; i < d; i++)
        windowed.push_back(expenditure.at(i));

    for (int i = d; i < expenditure.size(); i++)
    {
        n_alerts += isAlert(windowed, expenditure.at(i));
        windowed.pop_front();
        windowed.push_back(expenditure.at(i));
    }

    return n_alerts;
}

int main()
{
    vector<int> my_vec{ 1,2,3,4 };  
    int window = 4;

    //vector<int> my_vec{ 2,3,4,2,3,6,8,4,5 };
    //int window = 5;

    int ans = activityNotifications(my_vec, window);
    cout << ans << endl;
}
