#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool prefix();

int main(int argc, char * argv[])
{
	if (argc < 2) return 1;
	char * filename = argv[1];
	char * iniPrefix = "INICIO";
	char * endPrefix = "FIN";
	char * line = NULL;
	FILE * fp;
	size_t len = 0;
	ssize_t read;

	fp = fopen(filename, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) {
		printf("%s", line);

		if (prefix(line, iniPrefix, strlen(iniPrefix))) {
			char * user;
			char const *needle = "USUARIO";
			size_t needle_length = strlen(needle);
			char const *needle_pos = strstr(line, needle);

			// not found, at end of str or not preceded and followed by whitespace:
			if (!needle_pos || !needle_pos[needle_length] || !isspace((char unsigned)needle_pos[needle_length]) ||
				needle_pos != line && !isspace((char unsigned)needle_pos[-1]))
			{
				fprintf(stderr, "\"%s\" couldn't be found. :(\n\n", needle);
				return EXIT_FAILURE;
			}   

			// extract the user following the word at needle_pos:
			sscanf(needle_pos + needle_length, "%99s", user);
			printf("Found \"%s\" after \"%s\"\n\n", user, needle);
		}

		if (prefix(line, endPrefix, strlen(endPrefix))) {
			printf("Press ENTER key to continue ...\n");
			getchar();
		}
	}

	free(line);
	exit(EXIT_SUCCESS);
}

bool prefix(const char *pre, const char *str, size_t n)
{
	return strncmp(pre, str, n) == 0;
}