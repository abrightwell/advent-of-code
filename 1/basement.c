#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 8192

int main() {
	FILE *file;
	char line[MAX_LINE_LENGTH];
	char *start;
	int floor;
	int position;

	file = fopen("./input.txt", "r");

	floor = 0;
	position = 1;

	while (fgets(line, sizeof(line), file)) {
		start = line;
		while (*start != '\n') {
			if (*start == '(') floor++;
			else if (*start == ')') floor--;

			if (floor < 0)
				break;

			position++;
			start++;
		}
	}

	printf("Basement Position: %d\n", position);
	printf("Floor: %d\n", floor);

	fclose(file);
}
