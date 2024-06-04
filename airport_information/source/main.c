#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
	int id;
	char *from;
	char *to;
	char *hour;
	int line;
	int pistNo;
} Flight;

typedef struct Node {
	Flight flight;
	struct Node *next;
} Node;

int main() {
	char *buf = malloc(1024 * sizeof(char));
	FILE *file = fopen("ucusBilgi.txt", "r");
	Node *list;
	int i, j = 0;
	fread(buf, sizeof(char), 1024, file);
	for (i = 0; i < strlen(buf);) {
		int line, pistNo;
		char from[64], to[64], hour[64], id[64];
		for (j = 0; buf[j + i] != ' '; ++j) {
			id[j] = buf[j + i];
		}
		++i;
		for (j = 0; buf[j + i]  != ' '; ++j) {

		}
		i += j;
	}
	free(buf);
	return 0;
}


