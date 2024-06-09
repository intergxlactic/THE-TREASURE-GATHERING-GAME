#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
using namespace std;

const int MAP_HEIGHT = 14;
const int MAP_WIDTH = 34;

char map[MAP_HEIGHT][MAP_WIDTH] = { 
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
		{'#',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','X','#'},
		{'#',' ','#',' ','X',' ',' ',' ',' ','#',' ','X',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ','#','X',' ',' ',' ',' ',' ',' ','#'},
		{'#',' ','#','#','#','#',' ',' ',' ','#',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ','#'},
		{'#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ','#',' ','X',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ','#','#','#','#'},
		{'#',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ','#',' ',' ',' ','#',' ',' ',' ',' ','#','#','#','#','#','#',' ',' ','#'},
		{'#','X',' ',' ',' ',' ',' ',' ',' ','#','#','#','#','#','#',' ','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
		{'#','#','#','#','#','#','#','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
		{'#',' ','X',' ','#',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
		{'#',' ',' ',' ','#',' ',' ',' ',' ','#','X',' ','#',' ',' ',' ',' ','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
		{'#',' ','#','#','#',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ','#','#','#','#',' ',' ',' ',' ',' ','#'},
		{'#',' ',' ',' ',' ',' ',' ','X',' ','#','#','#','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ','X',' ','#'},
		{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','X',' ',' ',' ',' ',' ','#','X',' ',' ',' ',' ',' ',' ',' ','#'},
		{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
	};

int treasuresCollected = 0;
int breakCollected = 0;

void drawMap() {
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

void setCharacterPosition(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawTreasuresCollected() {
	COORD coord;
	coord.X = 0;
	coord.Y = MAP_HEIGHT;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	cout << "Treasures collected: " << treasuresCollected << endl;
	cout << "Break collected: " << breakCollected << endl;
}


void handleInput(int& characterX, int& characterY) {
	char input = _getch();

	switch (input) {
	case 'w':
		if (map[characterY - 1][characterX] != '#') {
			characterY--;
		}
		else {
			breakCollected++;
		}
		break;
	case 'a':
		if (map[characterY][characterX - 1] != '#') {
			characterX--;
		}
		else {
			breakCollected++;
		}
		break;
	case 's':
		if (map[characterY + 1][characterX] != '#') {
			characterY++;
		}
		else {
			breakCollected++;
		}
		break;
	case 'd':
		if (map[characterY][characterX + 1] != '#') {
			characterX++;
		}
		else {
			breakCollected++;
		}
		break;
	case 'q':
		exit(0);
	}


	if (characterX < 0 || characterX >= MAP_WIDTH || characterY < 0 || characterY >= MAP_HEIGHT) {
		characterX = MAP_WIDTH / 2;
		characterY = MAP_HEIGHT / 2;
	}

	if (map[characterY][characterX] == 'X') {
		map[characterY][characterX] = ' ';
		treasuresCollected++;
	}

}
void win_lost() {
	if (treasuresCollected == 13) {
		system("CLS");
		string win =  "YOU WON, CODGRATULATIONS!!!";
		for (int i = 0; i < 20; i++) {
			cout << win << endl;
		}
		exit(0);
	}

	if (breakCollected == 11) {
		system("CLS");
		string lost = "You lost... Try again..";
		for (int i = 0; i < 10; i++) {
			cout << lost << endl;
		}
		exit(0);
	}
}


void printConditions() {
	cout << "       THE TREASURE GATHERING GAME" << endl
		 << endl
		 << "GAME RULES:" << endl
		 << endl
		 << "If you hit the wall more than 10 times, you lose," << endl
		 << "If you collect all the treasures, you win," << endl
		 << "Press 'q' to exit the game" << endl 
		 << "Play only on the English layout" << endl;
}

void waitForEnter() {
	cout << "Press Enter to continue...";
	cin.get();
}

int main() {
	
	printConditions();
	cout << endl;
	waitForEnter();

	int posX = 1;
	int posY = 1;
	
	while (true) {
		system("CLS");
		drawMap();
		setCharacterPosition(posX, posY);
		cout << "@";
		drawTreasuresCollected();
		handleInput(posX, posY);
		win_lost();
	}
	return 0;
}
