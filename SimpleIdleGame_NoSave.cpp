#include <iostream>
#include <ctime>
#include <string>

using namespace std;

long long int coin = 0;
time_t LastSaveTime = 0;
int Level[10] = { 0,10,25,50,100,200,500,1000,2000,5000 };
int Income[10] = { 1,2,4,8,15,30,50,100,250,500 };
int rate = 1;
unsigned int Lv = 0;

void GameInterface();

void StartInterface()
{
	while (true)
	{
		string Choice;
		cout << "-----------------------------------" << endl;
		cout << "Welcome to Great Little Idle Game!" << endl;
		cout << "-----------------------------------" << endl;
		cout << "Please select movement : " << endl;
		cout << "1 -> Comtinue Game" << endl;
		cout << "2 -> New Game" << endl;
		cout << "3 -> Exit" << endl;
		cout << endl;
		cout << "Your Choice : ";
		while (cin >> Choice)
		{
			if (Choice != "1" && Choice != "2" && Choice != "3")
			{
				cout << "Error.  Command not defined, please select again." << endl;
				cout << "Your Choice : ";
			}
			else
				break;
		}
		if (Choice == "1")
		{
			if (LastSaveTime == 0)//No saved game
			{
				string n;
				cout << "No game saved, start a new game? (Y/N) : ";
				cin >> n;
				while (n != "Y" && n != "N")
				{
					cout << "Please enter Y or N ! " << endl;
					cout << "Start a new game? (Y/N) : ";
					cin >> n;
				}
				if (n == "Y")//New game
				{
					cout << "Starting a new game...." << endl;
					coin = 0;
					rate = Income[0];
					Lv = 0;
					LastSaveTime = clock();
					GameInterface();
				}
				else
				{
					cout << "Returning to main menu...." << endl;
					cout << "-----------------------------------" << endl;
					cout << endl;
					continue;
				}
			}
			else//Load Game
			{
				GameInterface();
			}
			continue;
		}
		else if (Choice == "2")//New Game
		{
			cout << "Starting a new game...." << endl;
			coin = 0;
			rate = Income[0];
			Lv = 0;
			LastSaveTime = clock();
			GameInterface();
		}
		else if (Choice == "3")
		{
			cout << "Ending game...." << endl;
			return;
		}
	}
	return;
}

void GameInterface()
{
	while (true)
	{
		cout << "---------------------------" << endl;
		cout << "Resource: " << coin << endl;
		cout << "Income: " << rate << " per second." << endl;
		cout << "---------------------------" << endl;
		cout << endl;
		cout << "---------------------" << endl;
		cout << "Please select choice: " << endl;
		cout << "1 -> Collect coin(s)." << endl;
		cout << "2 -> Upgrade income." << endl;
		cout << "3 -> Save and Quit" << endl;
		cout << "---------------------" << endl;
		cout << "Your choice: ";
		int c = 0;
		while (true)
		{
			cin >> c;
			if (c != 1 && c != 2 && c != 3)
			{
				cout << "Invalid command, please enter again : ";
			}
			else
				break;
		}
		if (c == 1)//collect
		{
			time_t Buffer = clock();
			long long int gained = (static_cast<long long int>(Buffer - LastSaveTime) / 1000) * rate;
			coin += gained;
			cout << "You had collected " << gained << " coin(s) !" << endl;
			LastSaveTime = Buffer;
		}
		else if (c == 2)//upgrade
		{
			cout<< "---------------------" << endl;
			cout << "Your current level is on level " << Lv + 1 << ", ";
			if (Lv >= 9)
			{
				cout << "it is the highest level, no need to upgrade !" << endl;
				cout << "Returning you back to game menu." << endl;
			}
			else
			{
				cout << "need " << Level[Lv + 1] << " coins to upgrade." << endl;
				cout << "Your have " << coin << " coin(s) currently, do you want to upgrade ?" << endl;

				string cho;
				cout << "(Y/N) : ";
				cin >> cho;
				while (cho != "Y" && cho != "N")
				{
					cout << "Please enter Y or N ! " << endl;
					cout << "Do you want to upgrade ? (Y/N) : ";
					cin >> cho;
				}

				if (cho == "Y")
				{
					if (coin >= Level[Lv + 1])
					{
						coin -= Level[Lv + 1];
						Lv++;
						rate = Income[Lv];
						cout << "Upgrade successful, you now have " << rate << " coins / sec." << endl;
						cout << "Returning to game menu." << endl;
					}
					else
					{
						cout << "Upgrade failed : not enough coins." << endl;
						cout << "Returning to game menu." << endl;
					}
				}
				else//cho == "N"
				{
					cout << "Upgrade cancelled.  Returning to game menu." << endl;
					continue;
				}
			}
		}
		else
		{
			cout << "----------------" << endl;
			cout << "Bye ! " << endl;
			cout << "----------------" << endl;
			break;
		}
	}
	
	return;
}

int main()
{
	rate = Income[0];
	StartInterface();
	return 0;
}