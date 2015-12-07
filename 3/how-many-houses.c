#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct house {
	int x;
	int y;
	struct house *next;
};

bool contains_house(int x, int y, struct house* list) {
	struct house *current = list;
	bool found = false;

	while (current != NULL && !found) {
		found = ((x == current->x) && (y == current->y));
		current = current->next;
	}

	return found;
}

int count_houses(struct house *list) {
	struct house *current = list;
	int count = 0;

	while (current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}

int main() {
	FILE *file;
	char *instructions = NULL;
	char instruction;
	size_t num_instructions = 0;
	int count = 0;
	int x = 0;
	int y = 0;

	struct house *houses;
	struct house *current_house;
	struct house *new_house;

	file = fopen("./input.txt", "r");

	houses = (struct house*) malloc(sizeof(struct house));
	houses->x = 0;
	houses->y = 0;
	houses->next = NULL;

	current_house = houses;

	instruction = fgetc(file);

	while (!isspace(instruction) && !feof(file)) {
		switch (instruction) {
			case '<':
				x -= 1;
				break;
			case '>':
				x += 1;
				break;
			case '^':
				y += 1;
				break;
			case 'v':
				y -= 1;
				break;
			default:
				printf("INVALID INSTRUCTION!\n");
				exit(1);
		}

		if (!contains_house(x, y, houses)) {
			new_house = (struct house*) malloc(sizeof(struct house));
			new_house->x = x;
			new_house->y = y;
			new_house->next = NULL;

			current_house->next = new_house;
			current_house = new_house;
		}

		instruction = fgetc(file);
	}

	current_house = houses;

	printf("Count: %d\n", count_houses(houses));
	
	fclose(file);

	return 0;
}
