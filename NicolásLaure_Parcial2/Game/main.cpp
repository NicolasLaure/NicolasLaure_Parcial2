#include <iostream>

using namespace std;

const int TEAM_SIZE = 6;

struct Pokemon
{
	string name{};
	int defense;
	int healthPoints{};
	int damageAttack1{};
	int damageAttack2{};
	int damageAttack3{};

	int pokemonLevel;

	void SetStats()
	{
		if (pokemonLevel == 1)
		{
			defense = 500;
			healthPoints = 2;
			damageAttack1 = 40;
			damageAttack2 = 60;
			damageAttack3 = 100;
		}
		else if (pokemonLevel == 2)
		{
			defense = 1000;
			healthPoints = 3;
			damageAttack1 = 80;
			damageAttack2 = 110;
			damageAttack3 = 150;
		}
		else
		{
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
void SetPlayerTeam(Pokemon team[], bool isHuman);
void RandomArrange(Pokemon team[]);


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
		cout << "1.single Player\n2.Two Players";
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
		cout << "Select an option -->";
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

	for (int i = 0; i < TEAM_SIZE; i++)
	{
		if (i == 0)
		{
			team1[i].pokemonLevel = 3;
			team1[i].SetStats();
			team2[i].pokemonLevel = 3;
			team2[i].SetStats();
		}
		else if (i == 1 || i == 2)
		{
			team1[i].pokemonLevel = 2;
			team1[i].SetStats();
			team2[i].pokemonLevel = 2;
			team2[i].SetStats();
		}
		else
		{
			team1[i].pokemonLevel = 1;
			team1[i].SetStats();
			team2[i].pokemonLevel = 1;
			team2[i].SetStats();
		}
	}

	bool wantsToPlayAgain = false;
	do
	{
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
				cout << poke.pokemonLevel;
			}
			cout << endl;
			for (Pokemon poke : team2)
			{
				cout << poke.pokemonLevel;
			}
			isRunning = false;
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

void SetPlayerTeam(Pokemon team[], bool isHuman)
{
	if (isHuman)
	{
		cout << "Choose if you want to arrange the order of your team or you want a random order\n 1.Arrange\n 2.Auto\n";
		int response = PromptInput(1, 2);
		if (response == 1)
		{
			Pokemon ownTeam[TEAM_SIZE];
			for (int i = 0; i < TEAM_SIZE; i++)
			{
				ownTeam[i] = team[i];
			}
			for (Pokemon pokemon : ownTeam)
			{
				if (pokemon.pokemonLevel == 1)
				{
					cout << "Choose the position you would like your " << pokemon.name << " to be, 1-6";
					//CONTINUE HEEEERRREEEEEEEEEEEE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				}
			}
		}
		else
			RandomArrange(team);
	}
	else
		RandomArrange(team);
}



void RandomArrange(Pokemon team[])
{
	for (int i = 0; i < TEAM_SIZE; i++)
	{
		int randomIndex = rand() % TEAM_SIZE;

		Pokemon temp = team[i];
		team[i] = team[randomIndex];
		team[randomIndex] = temp;
	}
}
