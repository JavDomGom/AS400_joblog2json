#include "joblogreader.h"

bool prefix(const char *pre, const char *str, size_t n)
{
	return strncmp(pre, str, n) == 0;
}

void processLogHeader(char *line, jobLog *jl)
{
	char arr[LOG_HEADER_MAXWORDS][LOG_HEADER_MAXSTRLEN + 1] = {0};
	char *pch;
	int i = 0;
	int k = 0;
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
	strcpy(jl->jobName, arr[1]);
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

void printStruct(jobLog *jl)
{
    printf("jl->user = %s\n", jl->user);
    printf("jl->jobName = %s\n", jl->jobName);
    printf("jl->dateTime = %s\n", jl->dateTime);
    printf("jl->IBMiOSProgramName = %s\n", jl->IBMiOSProgramName);
    printf("jl->IBMiOSProgramVersion = %s\n", jl->IBMiOSProgramVersion);
    printf("jl->IBMiOSProgramSize = %s\n", jl->IBMiOSProgramSize);
}