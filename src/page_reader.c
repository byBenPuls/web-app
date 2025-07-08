#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fsize(FILE *fp) {
	int prev = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	fseek(fp, prev, SEEK_SET);
	return sz;
}

void read_file(char *content, int size, FILE *file) {
	size_t bytesRead = fread(content, 1, size, file);
	content[bytesRead] = '\0';
}

char *read_page(const char *filename) {
	FILE *fptr = fopen(filename, "r");

	if (fptr == NULL) {
		perror("ERROR");
		return NULL;
	}

	int size = fsize(fptr);
	char *content = malloc(fsize(fptr) + 1);

	read_file(content, size, fptr);

	fclose(fptr);

	return content;
}
