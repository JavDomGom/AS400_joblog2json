#include <stdio.h>
#include <string.h>
#include "joblogreader.h"

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1];
	char *iniPrefix = "INICIO";
	char *endPrefix = "FIN";
	char *line = NULL;
	int n_line = 0;
	size_t len = 0;
	ssize_t read;
	FILE *fp;

	INIT_JOBLOG(jl);

	fp = fopen(filename, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1)
	{
		printf("[%d] %s", n_line, line);
		
		// If line starts with iniPrefix.
		if (prefix(line, iniPrefix, strlen(iniPrefix))) processLogHeader(line, &jl);

		// If second line.
		if (n_line == 1) processPageHeader(line, &jl);

		// If third or fourth lines.
		if (n_line == 2) processJobAttributes(line, &jl);

		printStruct(&jl);

		printf("Press ENTER key to continue ...\n");
		getchar();

		// If line ends with endPrefix.
		if (prefix(line, endPrefix, strlen(endPrefix))) {
			printf("Press ENTER key to continue ...\n");
			getchar();
			n_line = 0;
		} else {
			n_line++;
		}
	}

	free(line);
	exit(EXIT_SUCCESS);
}