#pragma once

#include <iostream>
#include <conio.h>
#include <string>
#include <stdlib.h>
#include <Windows.h>
#include <chrono>
#include <fstream>
#include <sstream>
#include <algorithm>

// Specifications definition
#define MARGIN_TOP 1
#define MARGIN_LEFT 2
#define MAX_SIZE 10
// Color definition
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define HPGAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

using namespace std;
using namespace std::chrono;

extern bool UndoRedoMode;

struct PlayerAccount
{
	char Username[20];
	char Password[20];
	int score = 0;
	double time = 0;
};

struct State
{
	int gameboard[MAX_SIZE][MAX_SIZE];
	State *next;
	State *previous;
};

// [undo5, undo4, undo3, undo2, undo1, current]

struct States
{

	int size = 0;
	State *current;
	State *head;

	void getNewState(int map[][MAX_SIZE]);
	void Undo(int map[][MAX_SIZE]);
	void Redo(int map[][MAX_SIZE]);
	
};

struct saveState {
	int gameboard[MAX_SIZE][MAX_SIZE];
	PlayerAccount player;
};

void Clear();
void SetColor(int);
void Display2048();
void Menu(PlayerAccount &, int &, int[][10]);
void PrintMenu();
void SignUp(PlayerAccount &);
void NewGame(PlayerAccount &, int &, int[][10]);
void ShowInstruction();
void DrawBoard(int &, int[][MAX_SIZE], short &, short &);
void GoToxy(short, short);
short CountNumbers(int);
void NumberColor(int);

void GoUp(int &, int[][10]);
void GoDown(int &, int[][10]);
void GoLeft(int &, int[][10]);
void GoRight(int &, int[][10]);
void HandleEventFromKeyboard(int &, int[][10], int);

void RandomNumber(int &, int[][10]);
void PlayGame(PlayerAccount &, int &, int[][10]);
int Score(PlayerAccount &, int &, int[][10]);
void ShowScore(PlayerAccount &, int &, int[][10]);
bool isFull(int &, int[][10]);
void GameSetting(PlayerAccount &, int &, int[][10]);
bool GameWin(int &, int[][10]);
void DisplayWinPattern();

void StartTimer(high_resolution_clock::time_point &start);
double StopTimer(high_resolution_clock::time_point start);

bool UsernameExists(const string &);
void SaveNewPlayerAccountToFile(const PlayerAccount &);

bool comparePlayers(const PlayerAccount &, const PlayerAccount &);
void SortPlayersByScore();
void Top20Display();
void ScoreDisplayWhenReaching2048(PlayerAccount &);
