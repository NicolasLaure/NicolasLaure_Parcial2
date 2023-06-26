#include <iostream>
#include <windows.h>

using namespace std;

const int TEAM_SIZE = 6;
const int ATTACKS_QTY = 3;
struct Vector2
{
	int x;
	int y;
};
struct Pokemon
{
	string name{};
	int defense{};
	int maxDefense{};
	int healthPoints{};
	int damageAttack1{};
	int damageAttack2{};
	int damageAttack3{};
	bool isAlive{};

	int pokemonLevel{};

	Vector2 position{};

	void SetStats()
	{
		if (pokemonLevel == 1)
		{
			name = " ";
			maxDefense = 500;
			defense = maxDefense;
			healthPoints = 2;
			damageAttack1 = 40;
			damageAttack2 = 60;
			damageAttack3 = 100;
			isAlive = true;
		}
		else if (pokemonLevel == 2)
		{
			name = " ";
			maxDefense = 1000;
			defense = maxDefense;
			healthPoints = 3;
			damageAttack1 = 80;
			damageAttack2 = 110;
			damageAttack3 = 150;
			isAlive = true;
		}
		else
		{
			name = " ";
			maxDefense = 1500;
			defense = maxDefense;
			healthPoints = 4;
			damageAttack1 = 120;
			damageAttack2 = 200;
			damageAttack3 = 300;
			isAlive = true;
		}
	}

	void TakeDamage(int damage)
	{
		defense -= damage;

		if (defense <= 0)
		{
			defense = maxDefense;
			healthPoints--;
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


void PlayerTurn(Pokemon ownTeam[], Pokemon enemyTeam[]);
void BotTurn(Pokemon botTeam[], Pokemon playerTeam[]);

void PrintTeam(Pokemon team[]);
void DebugPrint(Pokemon team1[], Pokemon team2[]);

int DiceRoll(int sides);

//Global Variables
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
const int DEFAULT_TEXT_ATTRIBUTE = 7;
const int FULL_DEFENSE_TEXT_ATTRIBUTE = 10;
const int TWO_THIRDS_DEFENSE_TEXT_ATTRIBUTE = 14;
const int ONE_THIRD_DEFENSE_TEXT_ATTRIBUTE = 12;
const int DEAD_TEXT_ATTRIBUTE = 8;

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
	system("cls");
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
	cout << "Rules:\n\n\n";
	cout << "This game is about a pokemon combat, a team of determined pokemons against another team." << endl;
	cout << "Each team has 6 (six) pokemons that will fight for them:\n  1 (one) pokemon level 3 (Three)\n  2 (two) pokemons level 2 (two)\n  3 (three) pokemons level 1 (one)" << endl;

	cout << "\nThe level of a pokemon will determine their strength: \n";
	cout << "Level 1: Lives: 2\tDefense: 500\tAttack1: 40\tAttack2: 60\tAttack3: 100" << endl;
	cout << "Level 2: Lives: 3\tDefense: 1000\tAttack1: 80\tAttack2: 110\tAttack3: 150" << endl;
	cout << "Level 3: Lives: 4\tDefense: 1500\tAttack1: 120\tAttack2: 200\tAttack3: 300" << endl;

	cout << "To win the match you have to defeat every pokemon of the other team\nTo defeat an enemy, you have to lower their lives until it reaches zero\n";
	cout << "To lower a pokemon's life, you have to make his defense reach zero, \nthis way, each attack a pokemon strikes on another only affect the objective defense" << endl;
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
	bool isDebugModeOn = true;
	Pokemon team1[TEAM_SIZE];
	Pokemon team2[TEAM_SIZE];

	bool wantsToPlayAgain = false;
	do
	{
		SetTeams(team1, team2);

		system("cls");
		cout << "Player 1: Organize your team\n";
		SetPlayerTeam(team1, true);

		if (isSinglePlayer)
		{
			SetPlayerTeam(team2, false);
		}
		else
		{
			system("cls");
			cout << "Player 2: Organize your team\n";
			SetPlayerTeam(team2, true);
		}

		bool isRunning = true;
		while (isRunning)
		{
			system("cls");
			PrintTeam(team1);
			PrintTeam(team2);

			if (isDebugModeOn)
			{
				DebugPrint(team1, team2);
			}

			if (isSinglePlayer)
			{
				PlayerTurn(team1, team2);
				BotTurn(team2, team1);
			}
			else
			{
				PlayerTurn(team1, team2);

				system("cls");
				PrintTeam(team1);
				PrintTeam(team2);

				PlayerTurn(team2, team1);
			}

			int team1PokemonsAlive = 0;
			int team2PokemonsAlive = 0;

			for (int i = 0; i < TEAM_SIZE; i++)
			{
				if (team1[i].isAlive)
					team1PokemonsAlive++;

				if (team2[i].isAlive)
					team2PokemonsAlive++;
			}

			if (team1PokemonsAlive < 1)
			{
				if (isSinglePlayer)
					cout << "El Bot ha ganado la batalla\n";
				else
					cout << "El Jugador 2 ha ganado la batalla\n";
				isRunning = false;
			}
			else if (team2PokemonsAlive < 1)
			{
				if (isSinglePlayer)
					cout << "El Jugador 1 ha ganado la batalla\n";
				isRunning = false;
			}
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
		const int RANDOM_POKEMON_NAMES = 15;
		string PokemonNames[RANDOM_POKEMON_NAMES] =
		{
			"Articuno",
			"Wartortle",
			"ButterFly",
			"Ratata",
			"Pidgeotto",
			"Diglett",
			"Charizard",
			"Pikachu",
			"Kha'Zix",
			"Lapras",
			"Latias",
			"Nidoking",
			"Cubone",
			"Rapidash",
			"Chimchar"
		};

		for (int i = 0; i < TEAM_SIZE; i++)
		{
			int counter = 0;
			string randomName;
			do
			{
				randomName = PokemonNames[rand() % RANDOM_POKEMON_NAMES];
				counter = 0;
				for (int j = 0; j < TEAM_SIZE; j++)
				{
					if (team[j].name == randomName)
						counter++;
				}
			} while (counter != 0);

			team[i].name = randomName;
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
		if (!team[i].isAlive)
			SetConsoleTextAttribute(handle, DEAD_TEXT_ATTRIBUTE);

		if (team[i].name.length() >= 3)
			cout << team[i].name.at(0) << team[i].name.at(1) << team[i].name.at(2);
		else if (team[i].name.length() == 2)
			cout << team[i].name.at(0) << team[i].name.at(1);
		else
			cout << team[i].name.at(0);

		SetConsoleTextAttribute(handle, DEFAULT_TEXT_ATTRIBUTE);

		pos.Y++;
		SetConsoleCursorPosition(handle, pos);

		if (team[i].defense > team[i].maxDefense / 1.5 && team[i].isAlive)
		{
			SetConsoleTextAttribute(handle, FULL_DEFENSE_TEXT_ATTRIBUTE);
			cout << (char)219 << (char)219 << (char)219;
			SetConsoleTextAttribute(handle, DEFAULT_TEXT_ATTRIBUTE);
		}
		else if (team[i].defense > team[i].maxDefense / 3 && team[i].isAlive)
		{
			SetConsoleTextAttribute(handle, TWO_THIRDS_DEFENSE_TEXT_ATTRIBUTE);
			cout << (char)219 << (char)219;
			SetConsoleTextAttribute(handle, DEFAULT_TEXT_ATTRIBUTE);
		}
		else if (team[i].isAlive)
		{
			SetConsoleTextAttribute(handle, ONE_THIRD_DEFENSE_TEXT_ATTRIBUTE);
			cout << (char)219;
			SetConsoleTextAttribute(handle, DEFAULT_TEXT_ATTRIBUTE);
		}
		else if (!team[i].isAlive)
		{
			SetConsoleTextAttribute(handle, DEAD_TEXT_ATTRIBUTE);
			cout << "X_X";
			SetConsoleTextAttribute(handle, DEFAULT_TEXT_ATTRIBUTE);
		}

		pos.X += width + 1;
		pos.Y = coordinates.Y;
	}
	pos.X = 0;
	pos.Y = 10;
	SetConsoleCursorPosition(handle, pos);
}

void PlayerTurn(Pokemon ownTeam[], Pokemon enemyTeam[])
{
	cout << "Seleccione un Pokemon: (1-6) ";
	int pokemonSelection = PromptInput(1, 6) - 1;
	for (int i = 0; i < TEAM_SIZE; i++)
	{
		if (i == pokemonSelection)
		{
			cout << "El Pokemon elegido es: " << ownTeam[i].name << " tiene los siguientes ataques:\n";
			cout << "1. Placaje: " << ownTeam[i].damageAttack1 << " puntos de ataque\n";
			cout << "2. Corte: " << ownTeam[i].damageAttack2 << " puntos de ataque\n";
			cout << "3. Terremoto: " << ownTeam[i].damageAttack3 << " puntos de ataque\n";

			cout << "Seleccione un ataque --> ";
			int selectedAttack = PromptInput(1, 3);

			int selectedEnemy;
			bool isValidEnemy = true;
			do
			{
				cout << "Seleccione un Enemigo (1-6) --> ";
				selectedEnemy = PromptInput(1, 6) - 1;
				if (!enemyTeam[selectedEnemy].isAlive)
					isValidEnemy = false;
				else
					isValidEnemy = true;
			} while (!isValidEnemy);

			int defenseAgainst = DiceRoll(3);
			if (selectedAttack == 1 && defenseAgainst != selectedAttack)
			{
				enemyTeam[selectedEnemy].TakeDamage(ownTeam[pokemonSelection].damageAttack1);
				cout << "Ataque a " << enemyTeam[selectedAttack].name << " Restandole " << ownTeam[pokemonSelection].damageAttack1 << " Puntos de Vida" << endl;
				system("pause");
			}
			else if (selectedAttack == 2 && defenseAgainst != selectedAttack)
			{
				enemyTeam[selectedEnemy].TakeDamage(ownTeam[pokemonSelection].damageAttack2);
				cout << "Ataque a " << enemyTeam[selectedAttack].name << " Restandole " << ownTeam[pokemonSelection].damageAttack2 << " Puntos de Vida" << endl;
				system("pause");
			}
			else if (selectedAttack == 3 && defenseAgainst != selectedAttack)
			{
				enemyTeam[selectedEnemy].TakeDamage(ownTeam[pokemonSelection].damageAttack3);
				cout << "Ataque a " << enemyTeam[selectedAttack].name << " Restandole " << ownTeam[pokemonSelection].damageAttack3 << " Puntos de Vida" << endl;
				system("pause");
			}
			else if (defenseAgainst == selectedAttack)
			{
				cout << "El Pokemon  " << enemyTeam[selectedEnemy].name << " del enemigo ha esquivado el ataque.\n";
				system("pause");
			}

			if (enemyTeam[selectedEnemy].healthPoints <= 0)
				enemyTeam[selectedEnemy].isAlive = false;
		}
	}
}

void BotTurn(Pokemon botTeam[], Pokemon playerTeam[])
{
	bool isValidPokemon = true;
	int pokemonSelection;
	do
	{
		pokemonSelection = rand() % TEAM_SIZE;
		if (!botTeam[pokemonSelection].isAlive)
			isValidPokemon = false;
		else
			isValidPokemon = true;

	} while (!isValidPokemon);
	for (int i = 0; i < TEAM_SIZE; i++)
	{
		if (i == pokemonSelection)
		{
			cout << "El Pokemon elegido por el enemigo es: " << botTeam[i].name << endl;
			system("pause");
			int selectedAttack = rand() % ATTACKS_QTY;

			int selectedEnemy;
			bool isValidEnemy = true;
			do
			{
				selectedEnemy = rand() % TEAM_SIZE;
				if (!playerTeam[selectedEnemy].isAlive)
					isValidEnemy = false;
				else
					isValidEnemy = true;
			} while (!isValidEnemy);

			int defenseAgainst = DiceRoll(3);

			if (selectedAttack == 1 && defenseAgainst != selectedAttack)
			{
				playerTeam[selectedEnemy].TakeDamage(botTeam[pokemonSelection].damageAttack1);
				cout << "El enemigo acaba de atacar a tu " << playerTeam[selectedEnemy].name << " Restandole " << botTeam[pokemonSelection].damageAttack1;
				system("pause");
			}
			else if (selectedAttack == 2 && defenseAgainst != selectedAttack)
			{
				playerTeam[selectedEnemy].TakeDamage(botTeam[pokemonSelection].damageAttack2);
				cout << "El enemigo acaba de atacar a tu " << playerTeam[selectedEnemy].name << " Restandole " << botTeam[pokemonSelection].damageAttack2;
				system("pause");
			}
			else if (selectedAttack == 3 && defenseAgainst != selectedAttack)
			{
				playerTeam[selectedEnemy].TakeDamage(botTeam[pokemonSelection].damageAttack3);
				cout << "El enemigo acaba de atacar a tu " << playerTeam[selectedEnemy].name << " Restandole " << botTeam[pokemonSelection].damageAttack3;
				system("pause");
			}
			else if (defenseAgainst == selectedAttack)
			{
				cout << "Tu Pokemon  " << playerTeam[selectedEnemy].name << " ha esquivadp el ataque del enemigo.\n";
				system("pause");
			}

			if (playerTeam[selectedEnemy].healthPoints <= 0)
				playerTeam[selectedEnemy].isAlive = false;
		}
	}
}

int DiceRoll(int sides)
{
	return (rand() % sides) + 1;
}

void DebugPrint(Pokemon team1[], Pokemon team2[])
{
	for (int i = 0; i < TEAM_SIZE; i++)
	{
		cout << team1[i].name << " " << team1[i].pokemonLevel << "\t\t" << team2[i].name << " " << team2[i].pokemonLevel << endl << endl;
	}
}