#include "Path.h"
#include "CircleObject.h"
#include "Point2D.h"
#include <cstdlib>

void GenerateLilies(bool lily_grid[10][9], std::vector<std::unique_ptr<ShapeObject>>& objects)
{
	//czyszczenie siatki lilii
	for (int c = 0; c < 10; ++c)
		for (int r = 0; r < 9; ++r)
			lily_grid[c][r] = false;

	//proceduralne generowanie lilii
	int current_col = 0;
	int current_row = 4; //start na srodku
	lily_grid[current_col][current_row] = true;

	int last_dir = -1;

	while (current_col < 9) {
		int dir = rand() % 3; // 0 = góra, 1 = dół, 2 = prawo

		if (dir == 0) {
			if (current_row > 0 && last_dir != 1) {
				current_row--;
				last_dir = 0;
			}
			else {
				current_col++;
				last_dir = 2;
			}
		}
		else if (dir == 1) {
			if (current_row < 8 && last_dir != 0) {
				current_row++;
				last_dir = 1;
			}
			else {
				current_col++;
				last_dir = 2;
			}
		}
		else {
			current_col++;
			last_dir = 2;
		}

		lily_grid[current_col][current_row] = true;
	}

	//tworzenie obiektow graficznych lilii na podstawie wylosowanej siatki
	for (int c = 0; c < 10; ++c) {
		for (int r = 0; r < 9; ++r) {
			if (lily_grid[c][r]) {
				float cx = 80.0f + c * 64.0f + 32.0f;
				float cy = 12.0f + r * 64.0f + 32.0f;

				//lilia jako zielone kolo (prymityw)
				objects.push_back(std::make_unique<CircleObject>(Point2D(cx, cy), 28, DARKGREEN, true));
				objects.push_back(std::make_unique<CircleObject>(Point2D(cx, cy), 24, LIME, true));
			}
		}
	}
}