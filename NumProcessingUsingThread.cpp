#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

mutex gm;

void InputPrompt()
{
	cout << "-------------------------------------------------------------" << endl;
	cout << "Enter the type of sequence and number you want to process: "<<endl;
	cout << "1 -> Fibonacci." << endl;
	cout << "2 -> Lucas." << endl;
	cout << "3 -> Odd numbers." << endl;
	cout << "4 -> Tribonacci." << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "Enter : ";
	return;
}

int fibo(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else if (n > 1)
		return fibo(n - 1) + fibo(n - 2);
	return 0;
}

int luca(int n)
{
	if (n == 0)
		return 2;
	else if (n == 1)
		return 1;
	else if (n > 1)
		return luca(n - 1) + luca(n - 2);
	return 0;
}

int odd(int n)
{
	if (n > 0)
		return ((n * 2) - 1);
	return 0;
}

int tribo(int n)
{
	if (n == 0)
		return 0;
	else if (n == 1)
		return 0;
	else if (n == 2)
		return 1;
	else if (n > 2)
		return tribo(n - 1) + tribo(n - 2) + tribo(n - 3);
	return 0;
}

void func(int t, int n)
{
	int ans = 0;
	switch (t)
	{
	case 1:
		ans = fibo(n);
		gm.lock();
		cout << "Fibonacci(" << n << ") is " << ans << "." << endl;
		gm.unlock();
		break;
	case 2:
		ans = luca(n);
		gm.lock();
		cout << "Lucas(" << n << ") is " << ans << "." << endl;
		gm.unlock();
		break;
	case 3:
		ans = odd(n);
		gm.lock();
		cout << "Odd(" << n << ") is " << ans << "." << endl;
		gm.unlock();
		break;
	case 4:
		ans = tribo(n);
		gm.lock();
		cout << "Tribonacci(" << n << ") is " << ans << "." << endl;
		gm.unlock();
		break;
	default:
		gm.lock();
		cout << "Command number " << t << " is not defined. " << endl;
		gm.unlock();
		break;
	}
	return;
}

int main()
{
	int cases = 0;
	cout << "How many cases do you want to process: ";
	cin >> cases;
	InputPrompt();
	vector<thread> thd;
	thd.resize(cases);
	for (int i = 0; i < cases; i++)
	{
		int type, number;
		cin >> type >> number;
		thd.at(i) = thread(func, type, number);
	}
	for (int i = 0; i < cases; i++)
	{
		thd.at(i).join();
	}
	return 0;
}
