#include "func.h"

int main()
{
	PlayerAccount p;// accout nè, tutu phát triển thành mảng nhe
	

	int size = 4;				   // kích thước board
	int board[MAX_SIZE][MAX_SIZE]; // size max = 10
	UndoRedoMode = true;
	Display2048();

	Menu(p, size, board);

	return 0;
}