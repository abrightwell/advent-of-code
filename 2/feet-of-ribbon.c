#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 8192
#define MAX_TOKEN_LENGTH 256

int compare(const void *a, const void *b) {
	int int_a = *((int *) a);
	int int_b = *((int *) b);

	return (int_a - int_b);
}

int main() {
	FILE *file;
	char line[MAX_LINE_LENGTH];
	char length_str[MAX_TOKEN_LENGTH];
	char width_str[MAX_TOKEN_LENGTH];
	char height_str[MAX_TOKEN_LENGTH];
	int amount = 0;

	file = fopen("./input.txt", "r");

	while (fgets(line, sizeof(line), file)) {
		int dimension[3];
		int bow_length;
		int i;

		sscanf(line, "%[^x]x%[^x]x%s", length_str, width_str, height_str);
	
		dimension[0] = atoi(length_str);
		dimension[1] = atoi(width_str);
		dimension[2] = atoi(height_str);

		bow_length = (dimension[0] * dimension[1] * dimension[2]);

		qsort(dimension, 3, sizeof(int), compare);

		amount += (dimension[0] * 2) + (dimension[1] * 2);

		amount += bow_length;
	}

	printf("Amount: %d ft\n", amount);

	fclose(file);
}
