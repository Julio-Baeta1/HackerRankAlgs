// extraLongFactorial.cpp

#include <iostream>
#include <string>

using namespace std;

class bigInt {
private:
    string digits;
    int num_digits;

public:
    bigInt(string num = "0", int num_length = 1)
        :digits{ num }, num_digits{ num_length } 
    {
        digits = num;
        num_digits = digits.length(); 
    }

    string getDigits() const { return digits;}

    int getNumDigits() const { return num_digits;}

    void setDigits(string& new_digits) 
    {
        digits = new_digits;
        num_digits = digits.length();
    }
};

int badIntConv(char& ch) {
    return (int)ch - 48;
}

bigInt multiplyBigInt(bigInt& A, bigInt& B)
{
    const int n = A.getNumDigits();
    const int m = B.getNumDigits();
    string a = A.getDigits();
    string b = B.getDigits();

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    string c(n+m, '0');

    int temp, temp_overflow, temp_c = 0;
    bool c_overflow = false;

    for (int i = 0; i <n; i++)

    {
        for (int j = 0; j < m; j++)
        {
            temp = badIntConv(a.at(i)) * badIntConv(b.at(j));
            
            if (temp > 9) {
                temp_overflow = temp / 10;
                temp = temp % 10;
            }
            else
                temp_overflow = 0;

            temp_c = badIntConv(c.at(i+j)) + temp;

            if (temp_c > 9) {
                temp_overflow++;
                temp_c = temp_c % 10;
            }

            c.at(i+j) = to_string(temp_c)[0];

            temp_c = badIntConv(c.at(i + j+1)) + temp_overflow;

            if (temp_c > 9) {
                c_overflow = true;
                temp_c = temp_c % 10;
            }

            c.at(i + j + 1) = to_string(temp_c)[0];

            int k = 2;
            while (c_overflow == true && k+i+j < n+m) {
                temp_c = badIntConv(c.at(i + j + k)) + 1;
                if (temp_c > 9)
                {
                    c.at(i + j + k) = to_string(temp_c % 10)[0];
                    k++;
                }
                else
                {
                    c.at(i + j + k) = to_string(temp_c)[0];
                    c_overflow = false;
                }
            }
        }
    }

    while (c.back() == '0')
        c.pop_back();

    reverse(c.begin(), c.end());

    return bigInt(c);
}

bigInt factorialBigInt(int n)
{
    bigInt temp_int{ "1" };
    bigInt temp_int_2{ "1" };
    string temp_string = "";
    for (int nn = 1; nn < n + 1; nn++)
    {
        temp_string = to_string(nn);
        temp_int_2.setDigits(temp_string);
        temp_int = multiplyBigInt(temp_int, temp_int_2);
    }

    return temp_int;
}

int main()
{
    bigInt C = factorialBigInt(25);
    cout << C.getDigits() << endl;

    return 0;
}
