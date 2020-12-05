#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSTRLEN 10
#define MAXWORD 9

bool prefix();

int main(int argc, char * argv[])
{
	if (argc < 2) return 1;

	char * filename = argv[1];
	char * iniPrefix = "INICIO";
	char * endPrefix = "FIN";
	char * line = NULL;
	char * IBMiOSProgram_Name;
	char * IBMiOSProgram_Version;
	int IBMiOSProgram_Size;
	int n_line = 0;
	size_t len = 0;
	ssize_t read;
	FILE * fp;

	fp = fopen(filename, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1)
	{
		printf("[%d] %s", n_line, line);

		if (prefix(line, iniPrefix, strlen(iniPrefix)))
		{
			char arr[MAXWORD][MAXSTRLEN + 1] = {0};
			char *pch;
			int i = 0;
			pch = strtok (line," ");

			while (pch != NULL && i < MAXWORD)
			{
				strncpy(arr[i++], pch, MAXSTRLEN);
				pch = strtok (NULL, " ");
			}
			
			char * user = arr[4];
			char * jobName = arr[5];
			char * date = arr[6];
			char * time = arr[7];
			char * timeZone = arr[8];
			size_t dateLen = strlen(date);
			size_t timeLen = strlen(time);
			size_t timeZoneLen = strlen(timeZone);

			// 3 additional bytes for spaces and EOL.
			char logDateTime[dateLen + timeLen + timeZoneLen + 3];
			
			snprintf(logDateTime, sizeof logDateTime, "%s %s %s", date, time, timeZone);
		}

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

bool prefix(const char *pre, const char *str, size_t n)
{
	return strncmp(pre, str, n) == 0;
}