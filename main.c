// Raylib Tic-Tac-Toe
// Andrew Hamel Codes
// https://github.com/AndrewHamel111/raylib-tictactoe
// https://youtu.be/ki5l_It9Q9Y

#include <stdlib.h>
#include <time.h>

#include "raylib.h"
#include "raymath.h"

#define COLS 3
#define ROWS 3

const int screenWidth = 600;
const int screenHeight = 600;
const Vector2 screenSize = {screenWidth, screenHeight};

const int cellWidth = screenWidth / COLS;
const int cellHeight = screenHeight / ROWS;

const char* playerXWins = "PLAYER X WINS!";
const char* playerOWins = "PLAYER O WINS!";
const char* pressRToRestart = "Press 'r' to play again!";
const char* playerXTurnPrompt = "PLAYER X GO";
const char* playerOTurnPrompt = "PLAYER O GO";

typedef enum CellValue
{
	EMPTY,
	X,
	O
} CellValue;

typedef struct Cell
{
	int i;
	int j;
	CellValue value;
} Cell;

Cell grid[COLS][ROWS];

int tilesOccupied;

typedef enum GameState
{
	PLAYERX,
	PLAYERO,
	END
} GameState;

GameState state;
CellValue winner;

float timeGameStarted;
float timeGameEnded;

Texture2D atlas;

void CellDraw(Cell);
bool IndexIsValid(int, int);
bool CellMark(int, int, CellValue);
void GridInit(void);
void GameInit(void);
bool GameIsOver(CellValue*);

void UpdateDrawFrame(void);

int main()
{
	srand(time(0));

	InitWindow(screenWidth, screenHeight, "Raylib Tic-Tac-Toe by Andrew Hamel");

	atlas = LoadTexture("resources/tictactoe.png");

	GameInit();

	while(!WindowShouldClose())
	{
		UpdateDrawFrame();
	}

	UnloadTexture(atlas);
	
	CloseWindow();
	
	return 0;
}

void CellDraw(Cell cell)
{
	Rectangle dest = {cell.i * cellWidth, cell.j * cellHeight, cellWidth, cellHeight};

	Rectangle source;
	switch (cell.value)
	{
		case X:
			source = (Rectangle){0, 0, 100, 100};
			DrawTexturePro(atlas, source, dest, (Vector2){0, 0}, 0, RED);
			break;
		case O:
			source = (Rectangle){100, 0, 100, 100};
			DrawTexturePro(atlas, source, dest, (Vector2){0, 0}, 0, BLUE);
			break;
		default:
			break;
	}

	DrawRectangleLines(cell.i * cellWidth, cell.j * cellHeight, cellWidth, cellHeight, BLACK);
}

bool IndexIsValid(int i, int j)
{
	return i >= 0 && i < COLS && j >= 0 && j < ROWS;
}

bool CellMark(int i, int j, CellValue value)
{
	if (grid[i][j].value != EMPTY || value == EMPTY)
	{
		return false;
	}

	grid[i][j].value = value;
	tilesOccupied++;

	return true;
}

void GridInit(void)
{
	for (int i = 0; i < COLS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			grid[i][j] = (Cell)
			{
				.i = i,
				.j = j,
				.value = EMPTY
			};
		}
	}
}

void GameInit(void)
{
	GridInit();
	state = PLAYERX;
	tilesOccupied = 0;
	timeGameStarted = GetTime();
}

bool GameIsOver(CellValue* winner)
{
	// check the diagonals
	// TL BR
	if (grid[0][0].value != EMPTY && grid[0][0].value == grid[1][1].value && grid[1][1].value == grid[2][2].value)
	{
		*winner = grid[0][0].value;
		return true;
	}
	
	// BL TR
	if (grid[0][2].value != EMPTY && grid[0][2].value == grid[1][1].value && grid[1][1].value == grid[2][0].value)
	{
		*winner = grid[0][2].value;
		return true;
	}

	// check each horizontal line
	// TL TR
	if (grid[0][0].value != EMPTY && grid[0][0].value == grid[1][0].value && grid[1][0].value == grid[2][0].value)
	{
		*winner = grid[0][0].value;
		return true;
	}
	
	// LM RM
	if (grid[0][1].value != EMPTY && grid[0][1].value == grid[1][1].value && grid[1][1].value == grid[2][1].value)
	{
		*winner = grid[0][1].value;
		return true;
	}
	
	// BL BR
	if (grid[0][2].value != EMPTY && grid[0][2].value == grid[1][2].value && grid[1][2].value == grid[2][2].value)
	{
		*winner = grid[0][2].value;
		return true;
	}

	// check each vertical line
	// TL BL
	if (grid[0][0].value != EMPTY && grid[0][0].value == grid[0][1].value && grid[0][1].value == grid[0][2].value)
	{
		*winner = grid[0][0].value;
		return true;
	}

	// TM BM
	if (grid[1][0].value != EMPTY && grid[1][0].value == grid[1][1].value && grid[1][1].value == grid[1][2].value)
	{
		*winner = grid[1][0].value;
		return true;
	}
	
	// TR BR
	if (grid[2][0].value != EMPTY && grid[2][0].value == grid[2][1].value && grid[2][1].value == grid[2][2].value)
	{
		*winner = grid[2][0].value;
		return true;
	}

	*winner = EMPTY;
	return false;
}

void UpdateDrawFrame(void)
{
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		Vector2 mPos = GetMousePosition();
		int indexI = mPos.x / cellWidth;
		int indexJ = mPos.y / cellHeight;

		if (state != END && IndexIsValid(indexI, indexJ))
		{
			if (CellMark(indexI, indexJ, state == PLAYERX ? X : O))
			{
				if (tilesOccupied < 5 || !GameIsOver(&winner))
				{
					state = (state == PLAYERX) ? PLAYERO : PLAYERX;
				}
				else
				{
					state = END;
				}
			}
		}
	}

	if (state == END && IsKeyPressed(KEY_R))
	{
		GameInit();
	}

	BeginDrawing();

		ClearBackground(RAYWHITE);

		for (int i = 0; i < COLS; i++)
		{
			for (int j = 0; j < ROWS; j++)
			{
				CellDraw(grid[i][j]);
			}
		}

		if (state == END)
		{
			const char* text = (winner == X) ? playerXWins : playerOWins;

			DrawRectangle(0, 0, screenWidth,screenHeight, Fade(WHITE, 0.8f));
			DrawText(text, screenWidth / 2 - MeasureText(text, 40) / 2, screenHeight / 2 - 10, 40, DARKGRAY);
			DrawText(pressRToRestart, screenWidth / 2 - MeasureText(pressRToRestart, 20) / 2, screenHeight * 0.75f - 10, 20, DARKGRAY);

			int minutes = (int)(timeGameEnded - timeGameStarted) / 60;
			int seconds = (int)(timeGameEnded - timeGameStarted) % 60;
			DrawText(TextFormat("Time played: %d minutes, %d seconds.", minutes, seconds), 20, screenHeight - 40, 20, DARKGRAY);
		}
		else
		{
			const char* text = (state == PLAYERX) ? playerXTurnPrompt : playerOTurnPrompt;

			Vector2 messagePosition = (Vector2){screenWidth / 2, 40};

			int measure = MeasureText(text, 40);
			Rectangle textRect = (Rectangle){messagePosition.x - measure / 2 - 40, messagePosition.y - 40, measure + 80, 80};

			DrawRectangleRec(textRect, Fade(WHITE, 0.8f));
			DrawText(text, messagePosition.x - measure / 2, messagePosition.y - 20, 40, DARKGRAY);
		}

	EndDrawing();
}