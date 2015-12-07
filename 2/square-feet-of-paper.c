#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 8192
#define MAX_TOKEN_LENGTH 256

int main() {
	FILE *file;
	char line[MAX_LINE_LENGTH];
	char length_str[MAX_TOKEN_LENGTH];
	char width_str[MAX_TOKEN_LENGTH];
	char height_str[MAX_TOKEN_LENGTH];
	int amount = 0;

	file = fopen("./input.txt", "r");

	while (fgets(line, sizeof(line), file)) {
		int length, width, height;
		int area[3];
		int min_area;
		int i;

		sscanf(line, "%[^x]x%[^x]x%s", length_str, width_str, height_str);
	
		length = atoi(length_str);
		width = atoi(width_str);
		height = atoi(height_str);

		area[0] = (length * width);
		area[1] = (width * height);
		area[2] = (height * length);

		min_area = area[0];

		for (i = 1; i < 3; i++) {
			if (area[i] < min_area)
				min_area = area[i];
		}

		for (i = 0; i < 3; i++)
			amount += (2 * area[i]);

		amount += min_area;
	}

	printf("Amount: %d sqft\n", amount);

	fclose(file);
}
