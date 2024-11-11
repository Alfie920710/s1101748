#include <iostream>
#include <vector>
using namespace std;
int Add(int a, int b)
{
    int* carry = new int;

    while (b != 0)
    {
       *carry = (a & b) << 1;
       a = a ^ b;
       b = *carry; 
    } 

    delete carry;
    return a;
}
int main()
{
    int *n = new int;
    cout << "How many integers : ";
    cin >> *n;

    int sum = 0;
    int* curr = new int;
    
    cout<< "Enter integers : ";
    for(int i = 0; i < *n; i++)
    {
        cin >> *curr;
        sum = Add(sum , *curr);
    }
    cout<<"Result: "<<sum<<endl;

    delete curr;
    return 0;
}