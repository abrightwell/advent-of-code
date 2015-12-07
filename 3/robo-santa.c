#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct house {
	int x;
	int y;
	struct house *next;
} House;

bool contains_house(int x, int y, House* list) {
	House *current = list;
	bool found = false;

	while (current != NULL && !found) {
		found = ((x == current->x) && (y == current->y));
		current = current->next;
	}

	return found;
}

int count_houses(House *list) {
	House *current = list;
	int count = 0;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}

void move_position(int *x, int *y, char direction) {
	
	switch (direction) {
		case '<':
			*x -= 1;
			break;
		case '>':
			*x += 1;
			break;
		case '^':
			*y += 1;
			break;
		case 'v':
			*y -= 1;
			break;
		default:
			printf("INVALID INSTRUCTION!\n");
			exit(1);
	}	
}

int main() {
	FILE *file;
	char *instructions = NULL;
	char instruction;
	int instruction_count = 0;
	int santas_x = 0;
	int santas_y = 0;
	int robots_x = 0;
	int robots_y = 0;

	House *houses;
	House *houses_tail;

	file = fopen("./input.txt", "r");

	houses = (House*) malloc(sizeof(House));
	houses->x = 0;
	houses->y = 0;
	houses->next = NULL;
	houses_tail = houses;

	instruction = fgetc(file);

	while (!isspace(instruction) && !feof(file)) {
		int x, y;

		/* Determine who moves next, calculate their new position. */
		if ((instruction_count % 2) > 0) {
			move_position(&robots_x, &robots_y, instruction);
			x = robots_x;
			y = robots_y;

		} else {
			move_position(&santas_x, &santas_y, instruction);
			x = santas_x;
			y = santas_y;
		}

		/* Check the list of houses visited by both. */
		if (!contains_house(x, y, houses)) { 
			House *new_house = (House*) malloc(sizeof(House));
			new_house->x = x;
			new_house->y = y;
			new_house->next = NULL;
			houses_tail->next = new_house;
			houses_tail = new_house;
		}

		instruction = fgetc(file);
		instruction_count++;
	}

	printf("Total Houses: %d\n", count_houses(houses));

	fclose(file);

	return 0;
}
