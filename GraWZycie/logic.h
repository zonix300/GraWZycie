#pragma once
#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>

#define WIDTH 100
#define HEIGHT 100

ALLEGRO_DISPLAY* global_display;
ALLEGRO_EVENT_QUEUE* global_queue;
ALLEGRO_TIMER* global_timer;

typedef enum {
	DEAD, 
	ALIVE
}States;

typedef struct {
	States state;
} Cell;




void init_logic(ALLEGRO_DISPLAY* display,
				ALLEGRO_EVENT_QUEUE* queue,
				ALLEGRO_TIMER* timer) {
	global_display = display;
	global_queue = queue;
	global_timer = timer;
}
void init_grid(Cell grid[HEIGHT][WIDTH]){
	srand(time(0));
	for (size_t i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			grid[i][j].state = DEAD;
			
		}
	}
	grid[50][50].state = ALIVE;
	grid[51][51].state = ALIVE;
	grid[52][50].state = ALIVE;
	grid[52][51].state = ALIVE;
	grid[51][52].state = ALIVE;

}

void draw_grid(Cell grid[HEIGHT][WIDTH]) {
	for (size_t i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < WIDTH; j++)
		{
			if (grid[i][j].state == ALIVE)
			{
				al_draw_filled_rectangle(j * 5, i * 5, (j + 1) * 5, (i + 1) * 5, al_map_rgb(255, 255, 255));
			}
			if (grid[i][j].state == DEAD)
			{
				al_draw_filled_rectangle(j * 5, i * 5, (j + 1) * 5, (i + 1) * 5, al_map_rgb(0, 0, 0));
			}
		}
	}
}

void next_generation(Cell grid[HEIGHT][WIDTH]) {
	Cell new_grid[HEIGHT][WIDTH] = { DEAD };

	for (size_t i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			int alive_cells = 0;
			for (int k = -1; k <= 1; k++) {
				for (int l = -1; l <= 1; l++) {
					if (k == 0 && l == 0) continue;
					int row = (i + k) % HEIGHT;
					int col = (j + l) % HEIGHT;
					if (i + k >= HEIGHT) {
						row = 0;
					}
					if (j + l >= WIDTH) {
						col = 0;
					}
					if (grid[row][col].state == ALIVE) {
						alive_cells++;
					}
				}
			}
			switch (alive_cells) {
			case 0:
			case 1:
				new_grid[i][j].state = DEAD;
				break;
			case 2:
			case 3:
				if (grid[i][j].state == DEAD && alive_cells == 3) {
					new_grid[i][j].state = ALIVE;
				}
				if (grid[i][j].state == ALIVE) {
					new_grid[i][j].state = ALIVE;
				}
				break;
			default:
				new_grid[i][j].state = DEAD;
				break;
			}
			
		}
	}
	for (size_t i = 0; i < HEIGHT; i++) {
		for (size_t j = 0; j < WIDTH; j++) {
			grid[i][j] = new_grid[i][j];
		}
	}
	draw_grid(grid);
}

