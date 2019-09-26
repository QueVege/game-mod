#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstring>
#include <cctype>
#include "stdlib.h"
#include "conio.h"

using namespace std;

class Player {
	public:
		int health;
		char name[20];
		
		Player(char *n, int h);
		int getDamageSmall();
		int getDamageLarge();
		int getHeal();
	};

Player::Player(char *n, int h) {
	health = h;
	strcpy(name, n);
}

// получает урон небольшого диапазона (18-25)

int Player::getDamageSmall() {
	
	int points = rand() % 7 + 18;
	health -= points;
	if (health < 0) health = 0;
	return points;
}

// получает урон большого диапазона (10-35)

int Player::getDamageLarge() {

	int points = rand() % 25 + 10;
	health -= points;
	if (health < 0) health = 0;
	return points;
}

// восстанавливает здоровье (18-25)

int Player::getHeal() {

	int points = rand() % 7 + 18;
	health += points;
	if (health > 100) health = 100;
	return points;
}

bool isNameCorrect(char *n) {
	for (int i = 0; i < strlen(n); ++i) {
		if(!isalpha(n[i]))
			return false;
	}
	return true;
}

void action(int a, Player &actPlayer, Player &pasPlayer) {
	
	if (!a) {				
		cout << pasPlayer.name << " has got " << pasPlayer.getDamageSmall() << " small range damage points from " << actPlayer.name << ".\n";
	}
	else if (a == 1) {
		cout << pasPlayer.name << " has got " << pasPlayer.getDamageLarge() << " large range damage points from " << actPlayer.name << ".\n";
	}
	else {
		cout << actPlayer.name << " has got " << actPlayer.getHeal() << " health points.\n";
	}
}

int main() {
	
	cout << "*** LET'S START THE GAME! ***\n\n";
	
	srand(time(0));
	
	int maxHealth = 100;
	
	char compName [20],
		 userName [20];
	
	strcpy(compName, "Computer");
	
	cout << "Please, enter your name: ";
	gets(userName);
	
	// проверка корректности имени пользователя

	while(!isNameCorrect(userName)) {
		
		cout << "\nThe name may only contain latin letters.\nPlease, try again: ";
		gets(userName);
	}
		
	Player comp(compName, maxHealth), user(userName, maxHealth);
	
	int counter = 0, a;
	
	do {
		
		cout << "\n# " << ++counter << "\t";
		
		if(rand() % 2) {				// чей ход: Компьютера или Игрока
												
			cout << "Your turn!\n\n";
			
			a = rand() % 3;				// выбор действия
	
			action(a, user, comp);
		}
		else {
			
			cout << "Computer's turn!\n\n";
			
			if (comp.health > maxHealth * 0.35)	// выбор действия в зависимости от состояния здоровья Компьютера
				a = rand() % 3;							
			
			else
				a = rand() % 5;			// при низком здоровье Компьютера (35% и ниже) 
								// вероятность восстановления здоровья возрастает до 0.6 
			action(a, comp, user);
		}
		
		cout << "\n";
		cout << comp.name << "'s health: " << comp.health << "\n";
		cout << user.name << "'s health: " << user.health << "\n\n";
		
	} while(comp.health && user.health);
	
	cout << "\n* * * * * * *    " << user.name;
	
	if (!comp.health) 
		cout << ", you WIN!";
	else
		cout << ", you lose...";
		
	cout << "    * * * * * * *\n\n";
	
	return 0;
}
