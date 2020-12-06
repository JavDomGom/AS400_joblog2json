#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSTRLEN 10
#define MAXWORD 5

bool prefix();
void processLogHeader();
void processPageHeader();

typedef struct {
	char *user;
	char *jobName;
	char *dateTime;
} JobLog;

int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char * filename = argv[1];
	char * iniPrefix = "INICIO";
	char * endPrefix = "FIN";
	char * line = NULL;
	int n_line = 0;
	size_t len = 0;
	ssize_t read;
	FILE * fp;
	JobLog jl;

	fp = fopen(filename, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1)
	{
		printf("[%d] %s", n_line, line);
		
		// If line starts with iniPrefix.
		if (prefix(line, iniPrefix, strlen(iniPrefix)))
		{
			processLogHeader(line, &jl);
			printf("user: %s\n", jl.user);
			printf("jobName: %s\n", jl.jobName);
			printf("dateTime: %s\n", jl.dateTime);
		}

		// If second line.
		if (n_line == 1)
		{
			processPageHeader(line, &jl);
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

void processLogHeader(char * line, JobLog *jl)
{
	char arr[MAXWORD][MAXSTRLEN + 1] = {0};
	char *pch;
	int i = 0;
	int k = 0;
	pch = strtok(line, " ");

	while (pch != NULL && k < MAXWORD)
	{
		if(i >= 4) strncpy(arr[k++], pch, MAXSTRLEN);
		pch = strtok(NULL, " ");
		i++;
	}

	jl->user = arr[0];
	jl->jobName = arr[1];
	
	char *date = arr[2];
	char *time = arr[3];
	char *timeZone = arr[4];

	size_t dateLen = strlen(date);
	size_t timeLen = strlen(time);
	size_t timeZoneLen = strlen(timeZone);

	// 3 additional bytes for spaces and EOL.
	char logDateTime[dateLen + timeLen + timeZoneLen + 3];
	snprintf(logDateTime, sizeof logDateTime, "%s %s %s", date, time, timeZone);
	strcpy(jl->dateTime, logDateTime);
}

void processPageHeader(char * line, JobLog *jl)
{
	char arr[3][7 + 1] = {0};
	char *pch;
	int i = 0;
	pch = strtok(line, " ");

	while (pch != NULL && i < 3)
	{
		strncpy(arr[i++], pch, 7);
		pch = strtok(NULL, " ");
	}

	char *IBMiOSProgramName = arr[0];
	char *IBMiOSProgramVersion = arr[1];
	char *IBMiOSProgramSize = arr[2];

	printf("IBMiOSProgramName: %s\n", IBMiOSProgramName);
	printf("IBMiOSProgramVersion: %s\n", IBMiOSProgramVersion);
	printf("IBMiOSProgramSize: %s\n", IBMiOSProgramSize);

	printf("Press ENTER key to continue ...\n");
	getchar();
}