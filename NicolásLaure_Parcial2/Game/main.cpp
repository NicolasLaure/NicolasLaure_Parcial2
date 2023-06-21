#include <iostream>
#include <windows.h>

using namespace std;

const int TEAM_SIZE = 6;

struct Vector2
{
	int x;
	int y;
};
struct Pokemon
{
	string name{};
	int defense{};
	int healthPoints{};
	int damageAttack1{};
	int damageAttack2{};
	int damageAttack3{};

	int pokemonLevel{};

	Vector2 position{};

	void SetStats()
	{
		if (pokemonLevel == 1)
		{
			name = " ";
			defense = 500;
			healthPoints = 2;
			damageAttack1 = 40;
			damageAttack2 = 60;
			damageAttack3 = 100;
		}
		else if (pokemonLevel == 2)
		{
			name = " ";
			defense = 1000;
			healthPoints = 3;
			damageAttack1 = 80;
			damageAttack2 = 110;
			damageAttack3 = 150;
		}
		else
		{
			name = " ";
			defense = 1500;
			healthPoints = 4;
			damageAttack1 = 120;
			damageAttack2 = 200;
			damageAttack3 = 300;
		}
	}
};

void Initialize();
void Menu();
void GameLoop(bool isSinglePlayer);
void PrintRules();
int PromptInput(int min, int max);
string StringInput();
void SetTeams(Pokemon team1[], Pokemon team2[]);
void SetPlayerTeam(Pokemon team[], bool isHuman);
void RandomArrange(Pokemon team[]);
void ManualArrange(Pokemon pokemon, Pokemon team[], int position);
void NamePokemons(Pokemon team[]);


void PrintTeam(Pokemon team[]);


//Global Variables
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
const int DEFAULT_TEXT_ATTRIBUTE = 7;
const int FULL_DEFENSE_TEXT_ATTRIBUTE = 10;
const int TWO_THIRDS_DEFENSE_TEXT_ATTRIBUTE = 14;
const int ONE_THIRD_DEFENSE_TEXT_ATTRIBUTE = 12;
void main()
{
	Initialize();
	Menu();
}


void Initialize()
{
	srand(time(0));
}

/**
	Prints The Main Menu
**/
void Menu()
{
	cout << "Pocket Mutants (nintendon't sue me please :) ) \n \n";
	cout << "1.Play \n2.Rules \n3.Quit \n";
	switch (PromptInput(1, 3))
	{
	case 1:
		int response;

		system("cls");
		cout << "1.single Player\n2.Two Players\n";
		response = PromptInput(1, 2);
		if (response == 1)
			GameLoop(true);
		else
			GameLoop(false);

		break;
	case 2:
		PrintRules();
		break;
	case 3:
		system(0);
		break;
	default:
		break;
	}
}

/**
	Prints The rules and goes back to menu after pressing any key
**/
void PrintRules()
{
	//print
	system("pause");
	Menu();
}

/**
   Returns an input of type int entered by the user between the range given
   (int min, int max)
   returns int (response)
**/
int PromptInput(int min, int max)
{
	int response;
	bool hasFailed = false;
	do
	{
		cout << "Select an option --> ";
		cin >> response;
		if (cin.fail())
		{
			hasFailed = true;
			cin.clear();
			cin.ignore();
		}
		else
			hasFailed = false;
	} while (response < min || response > max || hasFailed);

	return response;
}

/**
	Game CoreLoop
**/
void GameLoop(bool isSinglePlayer)
{
	Pokemon team1[TEAM_SIZE];
	Pokemon team2[TEAM_SIZE];

	bool wantsToPlayAgain = false;
	do
	{
		SetTeams(team1, team2);

		cout << "Player 1: Organize your team\n";
		SetPlayerTeam(team1, true);
		if (isSinglePlayer)
		{
			SetPlayerTeam(team2, false);
		}
		else
		{
			cout << "Player 2: Organize your team\n";
			SetPlayerTeam(team2, true);
		}

		bool isRunning(true);
		while (isRunning)
		{
			for (Pokemon poke : team1)
			{
				cout << poke.name << ", ";
			}
			cout << endl;
			for (Pokemon poke : team2)
			{
				cout << poke.name << ", ";
			}
			isRunning = false;
			cout << endl;
			system("cls");
			PrintTeam(team1);
			PrintTeam(team2);
			system("pause");
		}

		bool isValidInput = true;
		do
		{
			char response;
			cout << "Do you want to play again? Y/N\n";
			cin >> response;
			if (cin.fail())
			{
				isValidInput = false;
				cin.clear();
				cin.ignore();
			}
			else
			{
				switch (response)
				{
				case 'y':
				case 'Y':
					wantsToPlayAgain = true;
					break;
				case 'n':
				case 'N':
					wantsToPlayAgain = false;
					break;
				default:
					isValidInput = false;
					break;
				}

			}
		} while (!isValidInput);

	} while (wantsToPlayAgain);
}

void SetTeams(Pokemon team1[], Pokemon team2[])
{
	for (int i = 0; i < TEAM_SIZE; i++)
	{
		if (i == 0)
		{
			team1[i].pokemonLevel = 3;
			team1[i].SetStats();
			team1[i].position.y = 4;

			team2[i].pokemonLevel = 3;
			team2[i].SetStats();
			team2[i].position.y = 0;
		}
		else if (i == 1 || i == 2)
		{
			team1[i].pokemonLevel = 2;
			team1[i].SetStats();
			team1[i].position.y = 4;

			team2[i].pokemonLevel = 2;
			team2[i].SetStats();
			team2[i].position.y = 0;
		}
		else
		{
			team1[i].pokemonLevel = 1;
			team1[i].SetStats();
			team1[i].position.y = 4;

			team2[i].pokemonLevel = 1;
			team2[i].SetStats();
			team2[i].position.y = 0;

		}
	}
}
void SetPlayerTeam(Pokemon team[], bool isHuman)
{

	if (isHuman)
	{
		NamePokemons(team);

		cout << "Choose if you want to arrange the order of your team or you want a random order\n 1.Arrange\n 2.Auto\n";
		int response = PromptInput(1, 2);
		if (response == 1)
		{

			Pokemon ownTeam[TEAM_SIZE];

			for (int i = 0; i < TEAM_SIZE; i++)
			{
				ownTeam[i].name = " ";
			}

			for (int i = 0; i < TEAM_SIZE; i++)
			{
				bool isValidPlace = true;
				do
				{
					cout << "Choose the position you would like your " << team[i].name << " to be, 1-6  ---> ";
					int positionResponse = PromptInput(1, TEAM_SIZE) - 1;
					if (ownTeam[positionResponse].name == " ")
					{
						isValidPlace = true;
						ManualArrange(team[i], ownTeam, positionResponse);
					}
					else
					{
						isValidPlace = false;
						cout << "This Place is already used by another Pokemon \n";
					}

				} while (!isValidPlace);
			}
			for (int i = 0; i < TEAM_SIZE; i++)
			{
				team[i] = ownTeam[i];
			}
		}
		else
			RandomArrange(team);
	}
	else
	{
		for (int i = 0; i < TEAM_SIZE; i++)
		{
			switch (i)
			{
			case 0:
				team[i].name = "Articuno";
				break;
			case 1:
				team[i].name = "Wartortle";
				break;
			case 2:
				team[i].name = "ButterFly";
				break;
			case 3:
				team[i].name = "Ratata";
				break;
			case 4:
				team[i].name = "Pidgeotto";
				break;
			case 5:
				team[i].name = "Diglett";
				break;
			default:
				break;
			}
		}

		RandomArrange(team);
	}
}

void NamePokemons(Pokemon team[])
{
	for (int i = 0; i < TEAM_SIZE; i++)
	{
		cout << "Choose a name for your " << i + 1 << " Pokemon, a Beautiful level " << team[i].pokemonLevel << " Pokemon --> ";
		team[i].name = StringInput();
	}
}

string StringInput()
{
	bool isValidInput = true;
	string response;
	do
	{
		cin >> response;
		if (cin.fail())
		{
			isValidInput = false;
			cin.clear();
			cin.ignore();
		}
		else
			isValidInput = true;
	} while (!isValidInput);

	return response;
}
void RandomArrange(Pokemon team[])
{
	for (int i = 0; i < TEAM_SIZE; i++)
	{
		int randomIndex = rand() % TEAM_SIZE;

		Pokemon temp = team[i];
		team[i] = team[randomIndex];
		team[randomIndex] = temp;
		team[i].position.x = i;
	}
}

void ManualArrange(Pokemon pokemon, Pokemon team[], int position)
{
	team[position] = pokemon;
	team[position].position.x = position;
}

void PrintTeam(Pokemon team[])
{
	COORD coordinates = { 0,0 };
	COORD pos = { coordinates.X , coordinates.Y };
	int width = 3;
	for (int i = 0; i < TEAM_SIZE; i++)
	{
		if (i % 2 == 0 || i == 0)
			pos.Y = team[i].position.y + 1;
		else
			pos.Y = team[i].position.y;

		SetConsoleCursorPosition(handle, pos);

		if (team[i].name.length() >= 3)
			cout << team[i].name.at(0) << team[i].name.at(1) << team[i].name.at(2);
		else if (team[i].name.length() == 2)
			cout << team[i].name.at(0) << team[i].name.at(1);
		else
			cout << team[i].name.at(0);

		pos.Y++;
		SetConsoleCursorPosition(handle, pos);

		if (team[i].defense > team[i].defense / 1.5)
		{
			SetConsoleTextAttribute(handle, FULL_DEFENSE_TEXT_ATTRIBUTE);
			cout << (char)219 << (char)219 << (char)219;
			SetConsoleTextAttribute(handle, DEFAULT_TEXT_ATTRIBUTE);
		}
		else if (team[i].defense > team[i].defense / 3)
		{
			SetConsoleTextAttribute(handle, TWO_THIRDS_DEFENSE_TEXT_ATTRIBUTE);
			cout << (char)219 << (char)219;
			SetConsoleTextAttribute(handle, DEFAULT_TEXT_ATTRIBUTE);
		}
		else
		{
			SetConsoleTextAttribute(handle, ONE_THIRD_DEFENSE_TEXT_ATTRIBUTE);
			cout << (char)219;
			SetConsoleTextAttribute(handle, DEFAULT_TEXT_ATTRIBUTE);
		}

		pos.X += width + 1;
		pos.Y = coordinates.Y;
	}
	pos.X = 0;
	pos.Y = 10;
	SetConsoleCursorPosition(handle, pos);
}