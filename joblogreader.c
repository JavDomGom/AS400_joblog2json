#include "joblogreader.h"

bool prefix(const char *pre, const char *str, size_t n)
{
	return strncmp(pre, str, n) == 0;
}

void processLogHeader(char *line, jobLog *jl)
{
	char arr[LOG_HEADER_MAXWORDS][LOG_HEADER_MAXSTRLEN + 1] = {0};
	char *pch;
	int i = 0, k = 0;
	pch = strtok(line, " ");

	while (pch != NULL && k < LOG_HEADER_MAXWORDS)
	{
		if(i >= 4) strncpy(arr[k++], pch, LOG_HEADER_MAXSTRLEN);
		pch = strtok(NULL, " ");
		i++;
	}
	
	char *date = arr[2];
	char *time = arr[3];
	char *timeZone = arr[4];

	char logDateTime[DATETIME_MAXSTRLEN];
	snprintf(logDateTime, sizeof logDateTime, "%s %s %s", date, time, timeZone);

	strcpy(jl->user, arr[0]);
	strcpy(jl->jobLogName, arr[1]);
	strcpy(jl->dateTime, logDateTime);
}

void processPageHeader(char *line, jobLog *jl)
{
	char arr[PAGE_HEADER_MAXWORDS][PAGE_HEADER_MAXSTRLEN] = {0};
	char *pch;
	int i = 0;
	pch = strtok(line, " ");

	while (pch != NULL && i < PAGE_HEADER_MAXWORDS)
	{
		strncpy(arr[i++], pch, PAGE_HEADER_MAXSTRLEN);
		pch = strtok(NULL, " ");
	}

	strcpy(jl->IBMiOSProgramName, arr[0]);
	strcpy(jl->IBMiOSProgramVersion, arr[1]);
	strcpy(jl->IBMiOSProgramSize, arr[2]);
}

void processJobAttributes(char *line, jobLog *jl, int n_line)
{
	char arr[JOB_ATTR_MAXWORDS][JOB_ATTR_MAXSTRLEN] = {0};
	char *pch;
	int a_field, b_field, i = 0, k = 0;
	pch = strtok(line, " .:");
	switch (n_line)
	{
	case 2:
		a_field = 3;
		b_field = 7;
		break;
	case 3:
		a_field = 2;
		b_field = 4;
		break;
	}

	while (pch != NULL && k < JOB_ATTR_MAXWORDS)
	{
		if(i == a_field || i == b_field) strncpy(arr[k++], pch, JOB_ATTR_MAXSTRLEN);
		pch = strtok(NULL, " .:");
		i++;
	}

	switch (n_line)
	{
	case 2:
		strcpy(jl->jobName, arr[0]);
		strcpy(jl->jobNumber, arr[1]);
		break;
	case 3:
		strcpy(jl->jobDescription, arr[0]);
		strcpy(jl->jobLibrary, arr[1]);
		break;
	}
}

void printStruct(jobLog *jl)
{
    printf("jl->user = %s\n", jl->user);
    printf("jl->jobLogName = %s\n", jl->jobLogName);
    printf("jl->dateTime = %s\n", jl->dateTime);
    printf("jl->IBMiOSProgramName = %s\n", jl->IBMiOSProgramName);
    printf("jl->IBMiOSProgramVersion = %s\n", jl->IBMiOSProgramVersion);
    printf("jl->IBMiOSProgramSize = %s\n", jl->IBMiOSProgramSize);
    printf("jl->jobName = %s\n", jl->jobName);
    printf("jl->jobNumber = %s\n", jl->jobNumber);
	printf("jl->jobDescription = %s\n", jl->jobDescription);
    printf("jl->jobLibrary = %s\n", jl->jobLibrary);
}