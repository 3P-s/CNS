#include <iostream>
#include <string>
using namespace std;

// Euclidean Algorithm to find GCD
int euclideanGCD(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Extended Euclidean Algorithm to find GCD and coefficients x, y
int extendedEuclidean(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extendedEuclidean(b, a % b, x1, y1);

    // Update x and y using results of recursive call
    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

int main()
{
    int a, b;

    // Taking input of two numbers
    cout << "Enter two numbers to find GCD and coefficients: ";
    cin >> a >> b;

    // Calling Euclidean Algorithm
    int gcd = euclideanGCD(a, b);
    cout << "GCD using Euclidean Algorithm: " << gcd << endl;

    // Calling Extended Euclidean Algorithm
    int x, y;
    int gcd_ext = extendedEuclidean(a, b, x, y);
    cout << "GCD using Extended Euclidean Algorithm: " << gcd_ext << endl;
    cout << "Coefficients: x = " << x << ", y = " << y << endl;

    return 0;
}
