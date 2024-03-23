#pragma once
#include <stdio.h> 
#include <conio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "logic.h"


int pos_x;
int pos_y;

void get_mouse_position(ALLEGRO_EVENT event, int* x, int* y) {
	*x = event.mouse.x;
	*y = event.mouse.y;
}

void draw_on_click(ALLEGRO_EVENT event, Cell grid[HEIGHT][WIDTH]) {
	get_mouse_position(event, &pos_x, &pos_y);
	printf("x: %d\n", pos_x / 10);
	printf("y: %d\n", pos_y / 10);
	grid[pos_y / 10][pos_x / 10].state = ALIVE;
	draw_grid(grid);


}

void erase_on_click(ALLEGRO_EVENT event, Cell grid[HEIGHT][WIDTH]) {
	get_mouse_position(event, &pos_x, &pos_y);
	printf("x: %d\n", pos_x / 10);
	printf("y: %d\n", pos_y / 10);
	grid[pos_y / 10][pos_x / 10].state = DEAD;
	draw_grid(grid);
}

