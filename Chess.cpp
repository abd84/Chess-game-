#include <iostream>
#include<fstream>
//#include <cstdlib>
#include<Windows.h>
#include<ctime>
#include<time.h>
using namespace std;






void size()
{
	static CONSOLE_FONT_INFOEX  fontex;
	fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetCurrentConsoleFontEx(hOut, 0, &fontex);
	fontex.FontWeight = 400;
	fontex.dwFontSize.X =48;
	fontex.dwFontSize.Y = 30;
	SetCurrentConsoleFontEx(hOut, NULL, &fontex);

}

void callchess(char chess[][50], string ch2);
void editchess(char chess[][50], string ch2);
void ismovevalid(char chess[][50], int, int, int, int, bool&);
void checkmate(int turns);
void endgame(int turns);
void handshake(int turns, char chess[][50], string ch2);
void forfeit(int turns);
void savegame(char chess[][50]);

void fillchess(char chess[][50], string ch2) {
	for (int j = 0; j < 17; j++) {
		for (int i = 0; i < 17; i++) {
			if (j % 2 == 0) {
				chess[j][i] = '_';
			}
			else if (j == 15) {
				if (i % 2 == 0) {
					chess[j][i] = '|';
				}
				else {
					if (i == 1 || i == 15) {
						chess[j][i] = 'R';
					}
					else if (i == 3 || i == 13) {
						chess[j][i] = 'H';
					}
					else if (i == 5 || i == 11) {
						chess[j][i] = 'B';
					}
					else if (i == 7) {
						chess[j][i] = 'Q';
					}
					else if (i == 9) {
						chess[j][i] = 'K';
					}
				}
			}
			else if (j == 1) {
				if (i % 2 == 0) {
					chess[j][i] = '|';
				}
				else {
					if (i == 1 || i == 15) {
						chess[j][i] = 'r';
					}
					else if (i == 3 || i == 13) {
						chess[j][i] = 'h';
					}
					else if (i == 5 || i == 11) {
						chess[j][i] = 'b';
					}
					else if (i == 7) {
						chess[j][i] = 'q';
					}
					else if (i == 9) {
						chess[j][i] = 'k';
					}
				}
			}
			else if (j == 13) {
				if (i % 2 == 0) {
					chess[j][i] = '|';
				}
				else {
					chess[j][i] = 'P';
				}
			}
			else if (j == 3) {
				if (i % 2 == 0) {
					chess[j][i] = '|';
				}
				else {
					chess[j][i] = 'p';
				}
			}
			else {
				if (i % 2 == 0) {
					chess[j][i] = '|';
				}
				else {
					chess[j][i] = '*';
				}
			}
		}
	}
	callchess(chess, ch2);
}

void callchess(char chess[][50], string ch2) {
	char x = 97;
	cout << "    ";
	for (x = 97; x < 105; x++) {
		cout << x << "       ";
	}
	cout << endl;
	int a = 8;
	for (int j = 0; j < 17; j++) {
		for (int i = 0; i < 17; i++) {
			cout << chess[j][i];
			if (j % 2 == 0) {
				cout << "___";
			}
			if (j % 2 != 0) {
				cout << "   ";
			}
		}
		cout << "\b\b\b";

		if (j % 2 != 0) {
			cout << " " << a;
			a--;
		}
		cout << endl;
	}
	cout << endl;
	editchess(chess, ch2);
}

void editchess(char chess[][50], string ch2) {
	static int turns = 0;
	turns++;
	bool white = 1;
	if (turns % 2 != 0) {
		cout << "White's turn" << endl;
		white = 1;
	}
	else if (turns % 2 == 0) {
		cout << "Black's turn" << endl;
		white = 0;
	}
	int finaltime = 0;
	if (ch2 == "1") {
		static int timer = clock();
		timer = clock();
		static int starttime = clock();
		cout << "Seconds since the game started: " << (timer / 1000) - (starttime / 1000) << endl; 
	}
	else if (ch2 == "3") {
		static int timeblack = 0;
		static int timewhite = 0;
		static bool firstrun = 1;
		if (white == 1) {
			if (firstrun == 1) {
				cout << "Time taken by black is: 0" << endl;
				firstrun = 0;
			}
			else {
				timeblack = (clock() / 1000) - timewhite;
				cout << "Time taken by black is: " << timeblack << endl;
			}
		}
		if (white == 0) {
			timewhite = (clock()/1000) - timeblack;
			cout << "Time taken by white is: " << timewhite << endl;
		}
		if (timewhite > 300 || timeblack > 300) {
			endgame(turns);
		}
	}
	else if (ch2 == "2") {
		static int timeblack = 0;
		static int timewhite = 0;
		static bool firstrun = 1;
		int totalblacktime = 0;
		int totalwhitetime = 0;
		if (white == 1) {
			if (firstrun == 1) {
				cout << "Time taken by black is: 0" << endl;
				firstrun = 0;
			}
			else {
				timeblack = (clock() / 1000) - timewhite;
				totalblacktime = (totalblacktime + timeblack)-10;
				cout << "Total time taken by black after 10 second decrement is: " << totalblacktime << endl;
			}
		}
		if (white == 0) {
			timewhite = (clock() / 1000) - timeblack;
			totalwhitetime = (totalwhitetime + timewhite)-10;
			cout << "Total time taken by white after 10 second decrement is: " << totalwhitetime << endl;
		}
		if (totalwhitetime > 600 || totalblacktime > 600) {
			endgame(turns);
		}
	}
	else if (ch2 == "4") {
		static int timeblack = 0;
		static int timewhite = 0;
		static bool firstrun = 1;
		int thisblackturn = 0;
		int thiswhiteturn = 0;
		if (white == 1) {
			if (firstrun == 1) {
				cout << "Time taken by black is: 0" << endl;
				firstrun = 0;
			}
			else {
				timeblack = (clock() / 1000) - timewhite;
				thisblackturn = timeblack - thisblackturn;
				cout << "Time taken by black is: " << thisblackturn << endl;
			}
		}
		if (white == 0) {
			timewhite = (clock() / 1000) - timeblack;
			thiswhiteturn = timewhite - thiswhiteturn;
			cout << "Time taken by white is: " << thiswhiteturn << endl;
		}
		if (thiswhiteturn > 15 || thisblackturn > 15) {
			endgame(turns);
		}
	}
	if (ch2 != "4") {
		cout << "Press escape to open the pause menu on the next turn\n";
	}
	char start[50];
	cout << endl;
	int i = 97;
	int y = 97;
	int x = 1;
	int j = 15;
	int z = 49;
	char temp1 = 'x';
	bool capital1 = 0;
	bool capital2 = 0;
	bool same = 0;
	bool valid = 0;
	int a = 1;
	int b = 15;
	char temp2;
	while (valid != 1) {
		if (GetAsyncKeyState(VK_ESCAPE) && ch2 != "4") {
			turns--;
			system("CLS");
			system("Color 0F");
			cout << "\t\t\t\t\t\bPress a key\n\n";
			cout << "\t\t\t\t\t\b1. Save and Exit\n\n";
			cout << "\t\t\t\t\t\b2. Handshake\n\n";
			cout << "\t\t\t\t\t\b3. Forfeit\n\n";
			int choice;
			cout << "\t\t\t\t\t\bYour choice: \n";
			cin >> choice;
			if (choice == 1) {
				savegame(chess);
			}
			else if (choice == 2) {
				handshake(turns, chess, ch2);
			}
			else if (choice == 3) {
				forfeit(turns);
			}
		}
		i = 97;
		y = 97;
		x = 1;
		j = 15;
		z = 49;
		temp1 = 'x';
		capital1 = 0;
		capital2 = 0;
		same = 0;
		if (white == 1) {
			temp1 = 'a';
			while (!(temp1 >= 65 && temp1 <= 90)) {
				cout << "Enter the starting position: ";
				cin.getline(start, 50);
				if (start[0] >= 97 && start[0] <= 104) {
					if (start[1] >= 49 && start[1] <= 56) {
						while (i != int(start[0])) {
							i++;
						}
					}
				}
				y = 97;
				x = 1;
				j = 15;
				z = 49;
				while (y != i) {
					x = x + 2;
					y++;
				}
				while (z != int(start[1])) {
					j = j - 2;
					z++;
				}
				temp1 = chess[j][x];
				if (!(temp1 >= 65 && temp1 <= 90)) {
					cout << "Incorrect value. Please enter again!" << endl;
				}
			}
		}
		if (white == 0) {
			temp1 = 'A';
			while (!(temp1 >= 97 && temp1 <= 122)) {
				cout << "Enter the starting position: ";
				cin.getline(start, 50);
				if (start[0] >= 97 && start[0] <= 104) {
					if (start[1] >= 49 && start[1] <= 56) {
						while (i != int(start[0])) {
							i++;
						}
					}
				}
				y = 97;
				x = 1;
				j = 15;
				z = 49;
				while (y != i) {
					x = x + 2;
					y++;
				}
				while (z != int(start[1])) {
					j = j - 2;
					z++;
				}
				temp1 = chess[j][x];
				if (!(temp1 >= 97 && temp1 <= 122)) {
					cout << "Incorrect value. Please enter again!" << endl;
				}
			}
		}
		if (chess[j][x] >= 65 && chess[j][x] <= 90) {
			capital1 = 1;
		}
		else {
			capital1 = 0;
		}
		cout << "Enter the new position: ";
		char end[50];
		cin.getline(end, 50);
		i = 97;
		if (end[0] >= 97 && end[0] <= 104) {
			if (end[1] >= 49 && end[1] <= 56) {
				while (i != int(end[0])) {
					i++;
				}
			}
		}
		y = 97;
		a = 1;
		b = 15;
		z = 49;
		while (y != i) {
			a = a + 2;
			y++;
		}
		while (z != int(end[1])) {
			b = b - 2;
			z++;
		}
		temp2 = chess[b][a];
		ismovevalid(chess, j, x, b, a, valid);
		if (chess[b][a] >= 65 && chess[b][a] <= 90) {
			capital2 = 1;
		}
		else {
			capital2 = 0;
		}
		if ((capital1 == 1 && capital2 == 1) || (capital1 == 0 && capital2 == 0)) {
			same = 1;
		}
		else {
			same = 0;
		}
		if (chess[b][a] == '*') {
			same = 0;
		}
		if (same == 1) {
			cout << "Incorrect value! Re-enter" << endl;
			valid = 0;
		}
	}
	if (valid == 1 && (chess[b][a] == 'K' || chess[b][a] == 'k')) {
		checkmate(turns);
	}
	if (same == 0 && chess[b][a] != '*') {
		temp2 = '*';
	}
	chess[b][a] = temp1;
	chess[j][x] = temp2;
	system("CLS");
	callchess(chess, ch2);
}

void ismovevalid(char chess[][50], int j, int x, int b, int a, bool& valid) {
	bool queenfound = 0;
	bool obstruction = 0;
	if (chess[j][x] == 'P') {
		if (x == a) {
			if ((b == j - 2 || b == j - 4) && j == 13) {
				valid = 1;
			}
			else if (b == j - 2) {
				if (chess[b][a] != '*') {
					cout << "Incorrect move. Please try again!" << endl;
					valid = 0;
				}
				else {
					valid = 1;
				}
			}
			else {
				cout << "Incorrect move. Please try again!" << endl;
				valid = 0;
			}
		}
		else if (chess[b][a] != '*') {
			if (a == x + 2 || a == x - 2) {
				if (b == j - 2) {
					valid = 1;
				}
				else {
					valid = 0;
					cout << "Incorrect move. Please try again!" << endl;
				}
			}
			else {
				valid = 0;
				cout << "Incorrect move. Please try again!" << endl;
			}
		}
		else {
			valid = 0;
			cout << "Incorrect move. Please try again!" << endl;
		}
	}
	if (chess[j][x] == 'p') {
		if (x == a) {
			if ((b == j + 2 || b == j + 4) && j == 3) {
				if (chess[b][a] != '*') {
					cout << "Incorrect move. Please try again!" << endl;
					valid = 0;
				}
				else {
					valid = 1;
				}
			}
			else if (b == j + 2) {
				if (chess[b][a] != '*') {
					cout << "Incorrect move. Please try again!" << endl;
					valid = 0;
				}
				else {
					valid = 1;
				}
			}
			else {
				valid = 0;
				cout << "Incorrect move. Please try again!" << endl;
			}
		}
		else if (chess[b][a] != '*') {
			if (a == x + 2 || a == x - 2) {
				if (b == j + 2) {
					valid = 1;
				}
				else {
					valid = 0;
					cout << "Incorrect move. Please try again!" << endl;
				}
			}
			else {
				valid = 0;
				cout << "Incorrect move. Please try again!" << endl;
			}
		}
		else {
			valid = 0;
			cout << "Incorrect move. Please try again!" << endl;
		}
	}
	if (chess[j][x] == 'R' || chess[j][x] == 'Q') {
		if (j == b) {
			if (a < x) {
				for (int i = a + 2; i < x; i = i + 2) {
					if (chess[b][i] != '*') {
						obstruction = 1;
					}
				}
			}
			else if (a > x) {
				for (int i = a - 2; i > x; i = i - 2) {
					if (chess[b][i] != '*') {
						obstruction = 1;
					}
				}
			}
			if (obstruction == 0) {
				if (chess[j][x] == 'Q') {
					queenfound = 1;
				}
				valid = 1;
			}
			else {
				cout << "Incorrect move. Please try again!" << endl;
				valid = 0;
			}
		}
		else if (a == x) {
			if (b < j) {
				for (int i = b + 2; i < j; i = i + 2) {
					if (chess[i][a] != '*') {
						obstruction = 1;
					}
				}
			}
			else if (b > j) {
				for (int i = b - 2; i > j; i = i - 2) {
					if (chess[i][a] != '*') {
						obstruction = 1;
					}
				}
			}
			if (obstruction == 0) {
				if (chess[j][x] == 'Q') {
					queenfound = 1;
				}
				valid = 1;
			}
			else {
				cout << "Incorrect move. Please try again!" << endl;
				valid = 0;
			}
		}
		else {
			valid = 0;
			cout << "Incorrect move. Please try again!" << endl;
		}
	}
	if (chess[j][x] == 'r' || chess[j][x] == 'q') {
		if (j == b) {
			if (a < x) {
				for (int i = a + 2; i < x; i = i + 2) {
					if (chess[b][i] != '*') {
						obstruction = 1;
						break;
					}
				}
			}
			else if (a > x) {
				for (int i = a - 2; i > x; i = i - 2) {
					if (chess[b][i] != '*') {
						obstruction = 1;
						break;
					}
				}
			}
			if (obstruction == 0) {
				if (chess[j][x] == 'q') {
					queenfound = 1;
				}
				valid = 1;
			}
			else {
				cout << "Incorrect move. Please try again!" << endl;
				valid = 0;
			}
		}
		else if (a == x) {
			if (b < j) {
				for (int i = b + 2; i < j; i = i + 2) {
					if (chess[i][a] != '*') {
						obstruction = 1;
						break;
					}
				}
			}
			else if (b > j) {
				for (int i = b - 2; i > j; i = i - 2) {
					if (chess[i][a] != '*') {
						obstruction = 1;
						break;
					}
				}
			}
			if (obstruction == 0) {
				if (chess[j][x] == 'q') {
					queenfound = 1;
				}
				valid = 1;
			}
			else {
				cout << "Incorrect move. Please try again!" << endl;
				valid = 0;
			}
		}
		else {
			valid = 0;
			cout << "Incorrect move. Please try again!" << endl;
		}
	}
	if ((chess[j][x] == 'B' || chess[j][x] == 'b' || chess[j][x] == 'Q' || chess[j][x] == 'q') && queenfound == 0) {
		if (b == j + 2 || b == j - 2) {
			if (a == x + 2 || a == x - 2) {
				valid = 1;
			}
		}
		else {
			cout << "Incorrect move. Please try again!" << endl;
			valid = 0;
		}
		if (b == j + 4 || b == j - 4) {
			if (a == x + 4 || a == x - 4) {
				if (b < j) {
					if (a < x) {
						if (chess[j - 2][x - 2] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
					else if (a > x) {
						if (chess[j - 2][x + 2] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
				}
				if (b > j) {
					if (a < x) {
						if (chess[j + 2][x - 2] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
					else if (a > x) {
						if (chess[j + 2][x + 2] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
				}
			}
		}
		if (b == j + 6 || b == j - 6) {
			if (a == x + 6 || a == x - 6) {
				if (b < j) {
					if (a < x) {
						if (chess[j - 2][x - 2] != '*' || chess[j - 4][x - 4] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
					else if (a > x) {
						if (chess[j - 2][x + 2] != '*' || chess[j - 4][x + 4] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
				}
				if (b > j) {
					if (a < x) {
						if (chess[j + 2][x - 2] != '*' || chess[j + 4][x - 4] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
					else if (a > x) {
						if (chess[j + 2][x + 2] != '*' || chess[j + 4][x + 4] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
				}
			}
		}
		if (b == j + 8 || b == j - 8) {
			if (a == x + 8 || a == x - 8) {
				if (b < j) {
					if (a < x) {
						if (chess[j - 2][x - 2] != '*' || chess[j - 4][x - 4] != '*' || chess[j - 6][x - 6] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
					else if (a > x) {
						if (chess[j - 2][x + 2] != '*' || chess[j - 4][x + 4] != '*' || chess[j - 6][x + 6] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
				}
				if (b > j) {
					if (a < x) {
						if (chess[j + 2][x - 2] != '*' || chess[j + 4][x - 4] != '*' || chess[j + 6][x - 6] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
					else if (a > x) {
						if (chess[j + 2][x + 2] != '*' || chess[j + 4][x + 4] != '*' || chess[j + 6][x + 6] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
				}
			}
		}
		if (b == j + 10 || b == j - 10) {
			if (a == x + 10 || a == x - 10) {
				if (b < j) {
					if (a < x) {
						if (chess[j - 2][x - 2] != '*' || chess[j - 4][x - 4] != '*' || chess[j - 6][x - 6] != '*' || chess[j - 8][x - 8] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
					else if (a > x) {
						if (chess[j - 2][x + 2] != '*' || chess[j - 4][x + 4] != '*' || chess[j - 6][x + 6] != '*' || chess[j - 8][x + 8] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
				}
				if (b > j) {
					if (a < x) {
						if (chess[j + 2][x - 2] != '*' || chess[j + 4][x - 4] != '*' || chess[j + 6][x - 6] != '*' || chess[j + 8][x - 8] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
					else if (a > x) {
						if (chess[j + 2][x + 2] != '*' || chess[j + 4][x + 4] != '*' || chess[j + 6][x + 6] != '*' || chess[j + 8][x + 8] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
				}
			}
		}
		if (b == j + 12 || b == j - 12) {
			if (a == x + 12 || a == x - 12) {
				if (b < j) {
					if (a < x) {
						if (chess[j - 2][x - 2] != '*' || chess[j - 4][x - 4] != '*' || chess[j - 6][x - 6] != '*' || chess[j - 8][x - 8] != '*' || chess[j - 10][x - 10] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
					else if (a > x) {
						if (chess[j - 2][x + 2] != '*' || chess[j - 4][x + 4] != '*' || chess[j - 6][x + 6] != '*' || chess[j - 8][x + 8] != '*' || chess[j - 10][x + 10] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
				}
				if (b > j) {
					if (a < x) {
						if (chess[j + 2][x - 2] != '*' || chess[j + 4][x - 4] != '*' || chess[j + 6][x - 6] != '*' || chess[j + 8][x - 8] != '*' || chess[j + 10][x - 10] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
					else if (a > x) {
						if (chess[j + 2][x + 2] != '*' || chess[j + 4][x + 4] != '*' || chess[j + 6][x + 6] != '*' || chess[j + 8][x + 8] != '*' || chess[j + 10][x + 10] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
				}
			}
		}
		if (b == j + 14 || b == j - 14) {
			if (a == x + 14 || a == x - 14) {
				if (b < j) {
					if (a < x) {
						if (chess[j - 2][x - 2] != '*' || chess[j - 4][x - 4] != '*' || chess[j - 6][x - 6] != '*' || chess[j - 8][x - 8] != '*' || chess[j - 10][x - 10] != '*' || chess[j - 12][x - 12] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
					else if (a > x) {
						if (chess[j - 2][x + 2] != '*' || chess[j - 4][x + 4] != '*' || chess[j - 6][x + 6] != '*' || chess[j - 8][x + 8] != '*' || chess[j - 10][x + 10] != '*' || chess[j - 12][x + 12] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
				}
				if (b > j) {
					if (a < x) {
						if (chess[j + 2][x - 2] != '*' || chess[j + 4][x - 4] != '*' || chess[j + 6][x - 6] != '*' || chess[j + 8][x - 8] != '*' || chess[j + 10][x - 10] != '*' || chess[j + 12][x - 12] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
					else if (a > x) {
						if (chess[j + 2][x + 2] != '*' || chess[j + 4][x + 4] != '*' || chess[j + 6][x + 6] != '*' || chess[j + 8][x + 8] != '*' || chess[j + 10][x + 10] != '*' || chess[j + 12][x + 12] != '*') {
							cout << "Incorrect move. Please try again!" << endl;
							valid = 0;
						}
						else valid = 1;
					}
				}
			}
		}
	}
	if (chess[j][x] == 'K' || chess[j][x] == 'k') {
		if (j == b) {
			if (a == x + 2 || a == x - 2) {
				valid = 1;
			}
			else {
				cout << "Incorrect move. Please try again!" << endl;
				valid = 0;
			}
		}
		else if (x == a) {
			if (b == j + 2 || b == j - 2) {
				valid = 1;
			}
			else {
				cout << "Incorrect move. Please try again!" << endl;
				valid = 0;
			}
		}
		else if (b == j + 2) {
			if (a == x + 2 || a == x - 2) {
				valid = 1;
			}
			else {
				cout << "Incorrect move. Please try again!" << endl;
			}
		}
		else if (b == j - 2) {
			if (a == x - 2 || a == x + 2) {
				valid = 1;
			}
			else {
				cout << "Incorrect move. Please try again!" << endl;
				valid = 0;
			}
		}
		else {
			cout << "Incorrect move. Please try again!" << endl;
			valid = 0;
		}
	}
	if (chess[j][x] == 'H' || chess[j][x] == 'h') {
		if (b == j + 4 || b == j - 4) {
			if (a == x + 2 || a == x - 2) {
				valid = 1;
			}
			else {
				cout << "Incorrect move. Please try again!" << endl;
				valid = 0;
			}
		}
		else if (a == x + 4 || a == x - 4) {
			if (b == j + 2 || b == j - 2) {
				valid = 1;
			}
			else {
				cout << "Incorrect move. Please try agian!" << endl;
				valid = 0;
			}
		}
		else {
			cout << "Incorrect move. Please try again!" << endl;
			valid = 0;
		}
	}
}

void checkmate(int turns) {
	system("CLS");
	cout << "\t\t\t\t\t\tCheckmate";
	if (turns % 2 == 0) {
		system("Color 0F");
		cout << endl << "\t\t\t\t\t\t\bBLACK  WINS!";
		Beep(725, 800);
	}
	else if (turns % 2 != 0) {
		system("Color F0");
		cout << endl << "\t\t\t\t\t\t\bWHITE  WINS!";
		Beep(725, 800);
	}
	system("pause>nul");
	exit(0);
}

void endgame(int turns) {
	system("CLS");
	if (turns % 2 == 0) {
		system("Color 0F");
		cout << "\t\t\t\t\t\t\bBLACK  WINS!";
		Beep(725, 800);
	}
	else if (turns % 2 != 0) {
		system("Color F0");
		cout << "\t\t\t\t\t\t\bWHITE  WINS!";
		Beep(725, 800);
	}
	system("pause>nul");
	exit(0);
}

void handshake(int turns, char chess[][50], string ch2) {
	system("CLS");
	if (turns % 2 == 0) {
		cout << endl << "\t\t\t\t\t\b    Black has started a handshake";
	}
	else if (turns % 2 != 0) {
		cout << endl << "\t\t\t\t\t\b    White has started a handshake";
	}
	cout << endl;
	cout << "\t\t\t\t\t\bDo you agree to handshake? Enter y/n: ";
	char shaking;
	cin >> shaking;
	if (shaking == 'y') {
		cout << "\t\t\t\t\t\b  The game has been considered a draw" << endl;
		Beep(725, 800);
		system("pause>nul");
		exit(0);
	}
	else if (shaking == 'n') {
		cout << "\t\t\t\t\t\t\bHandshake declined" << endl;
		system("pause>nul");
		system("CLS");
		cin.ignore();
		callchess(chess, ch2);
	}
}

void forfeit(int turns) {
	system("ClS");
	if (turns % 2 == 0) {
		system("Color F0");
		Beep(725, 800);
		cout << endl << "\t\t\t\t\t\bblack has surrendered\n\t\t\t\t\t\b   WHITE IS WINNER!";
		
	}
	else {
		system("Color 0F");
		Beep(725, 800);
		cout << endl << "\t\t\t\t\t\bWhite has surrendered\n\t\t\t\t\t\b   BLACK IS WINNER!";
		
	}
	system("pause>nul");
	exit(0);
}

void savegame(char chess[][50]) {
	cout << "\t\t\t\t\t\bWhich save slot?\n\t\t\t\t\t\b1\n\t\t\t\t\t\b2\n\t\t\t\t\t\b3\n\t\t\t\t\t\bEnter your choice: ";
	int choice;
	cin >> choice;
	if (choice == 1) {
		ofstream fr;
		fr.open("f1.txt");

		for (int i = 0; i < 17; i++)
		{
			for (int j = 0; j < 17; j++)
			{
				fr << chess[i][j];
			}
			fr << endl;
		}
		fr.close();
	}
	else if (choice == 2) {
		ofstream fr1;
		fr1.open("f2.txt");

		for (int i = 0; i < 17; i++)
		{
			for (int j = 0; j < 17; j++)
			{
				fr1 << chess[i][j];
			}
			fr1 << endl;
		}
		fr1.close();
	}
	else if (choice == 3) {
		ofstream fr2;
		fr2.open("f3.txt");

		for (int i = 0; i < 17; i++)
		{
			for (int j = 0; j < 17; j++)
			{
				fr2 << chess[i][j];
			}
			fr2 << endl;
		}
		fr2.close();
	}

	system("pause>nul");
	exit(0);
}

int main() {
	size();
	system("Color F0");
	string ch, ch1, ch2;
	char chess[50][50];
	do
	{
		size();
		cout << "                                       WELCOME TO CHESS\n\n\n                                      Enter your choice:\n\n\n                                       1->New game\n\n\n                                       2->Saved game\n\n\n                                       Your choice: \n";
		cin >> ch;
		Beep(323, 300);

		if (ch == "1")
		{

			system("Color 0F");
			srand(time(0));
			system("cls");
			cout << "                                     SELECT YOUR MODE\n\n\n                                       1-Classic\n\n\n                                       2-Rapid\n\n\n                                       3-Blitz\n\n\n                                       4-Lightening\n";
			cin >> ch2;
			Beep(323, 300);
			system("Color F0");
			srand(time(0));
			system("cls");

			if (ch2 == "1")
			{
			cin.ignore();
			fillchess(chess, ch2);
			}
			else if (ch2 == "2") {
				cin.ignore();
				fillchess(chess, ch2);
			}
			else if (ch2 == "3") {
				cin.ignore();
				fillchess(chess, ch2);
			}
			else if (ch2 == "4") {
				cin.ignore();
				fillchess(chess, ch2);
			}
		}
						else if (ch == "2")
						{
							int temp = 0;
				
							do {
								cout << "\t\t\t\t       Enter the option:\n\n\t\t\t\t       1->Saved game1\n\n\t\t\t\t       2->Saved game2\n\n\t\t\t\t       3->Saved game3\n\n\t\t\t\t       Your choice: \n";
								cin >> ch1;
								Beep(323, 300);
				
								if (ch1 == "1")
								{
									system("Color F0");
									ifstream fw("f1.txt");
									for (int i = 0; i < 17; i++)
									{

										for (int j = 0; j < 17; j++)
										{
											fw >> chess[i][j];
											//cout << chess[i][j];
										}
										cout << endl;
									}
									system("cls");
									cin.ignore();
									callchess(chess, ch2);
								}
								if (ch1 == "2")
								{
									system("Color F0");
									ifstream fw1("f2.txt");
									for (int i = 0; i < 17; i++)
									{

										for (int j = 0; j < 17; j++)
										{
											fw1 >> chess[i][j];
											//cout << chess[i][j];
										}
										cout << endl;
									}
									system("cls");
									cin.ignore();
									callchess(chess, ch2);
								}
								if (ch1 == "3")
								{
									system("Color F0");
									ifstream fw2("f3.txt");
									for (int i = 0; i < 17; i++)
									{

										for (int j = 0; j < 17; j++)
										{
											fw2 >> chess[i][j];
											//cout << chess[i][j];
										}
										cout << endl;
									}
									system("cls");
									cin.ignore();
									callchess(chess, ch2);
								}
				
							} while (ch1 != "1" && ch1 != "2" && ch1 != "3");
						}
				
					} while (ch != "1" && ch != "2");
					system("cls");
				}