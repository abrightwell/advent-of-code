#include <stdlib.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 8192

int main() {
	FILE *file;
	char line[MAX_LINE_LENGTH];
	char *start;
	int floor;

	file = fopen("./input.txt", "r");

	floor = 0;

	while (fgets(line, sizeof(line), file)) {
		start = line;
		while (*start != '\n') {
			if (*start == '(') floor++;
			else if (*start == ')') floor--;
			
			start++;
		}
	}

	printf("Floor: %d\n", floor);

	fclose(file);
}
