#include "joblogreader.h"

bool prefix(const char *pre, const char *str, size_t n)
{
	return strncmp(pre, str, n) == 0;
}

char *rtrim(const char *s)
{
	while( isspace(*s) || !isprint(*s) ) ++s;
	return strdup(s);
}

char *ltrim(const char *s)
{
	char *r = strdup(s);
	if (r != NULL)
	{
		char *fr = r + strlen(s) - 1;
		while( (isspace(*fr) || !isprint(*fr) || *fr == 0) && fr >= r) --fr;
		*++fr = 0;
	}
	return r;
}

char *trim(const char *s)
{
	char *r = rtrim(s);
	char *f = ltrim(r);
	free(r);
	return f;
}

void processLogHeader(char *line, jobLog *jl)
{
	char arr[LOG_HEADER_MAXWORDS][LOG_HEADER_MAXSTRLEN + 1] = {0};
	char logDateTime[LOG_HEADER_DATETIME_MAXSTRLEN];
	char *pch, *date, *time, *timeZone;
	int i = 0, k = 0;
	pch = strtok(line, " ");

	while (pch != NULL && k < LOG_HEADER_MAXWORDS)
	{
		if(i >= 4) strncpy(arr[k++], pch, LOG_HEADER_MAXSTRLEN);
		pch = strtok(NULL, " ");
		i++;
	}
	
	date = arr[2];
	time = arr[3];
	timeZone = arr[4];

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

void processMsgHeader(char *line, jobLog *jl)
{
	char arr[MSG_HEADER_MAXWORDS][MSG_HEADER_MAXSTRLEN + 1] = {0};
	char msgDateTime[MSG_HEADER_DATETIME_MAXSTRLEN];
	char *pch, *word, *date, *time;
	int k = 0;
	bool isMsgIDNone, isMsgToPGMExt;
	pch = strtok(line, " ");

	while (pch != NULL && k < MSG_HEADER_MAXWORDS)
	{
		isMsgIDNone = !strcmp(arr[0], "*NONE");
		isMsgToPGMExt = !strcmp(arr[8], "*EXT");

		// When msgID is "*NONE" msgSEV field is empty.
		// When msgToPGM is "*EXT" msgToPGMLibrary field is empty.
		// In both cases it's replaced by the string "n/a".
		if ((isMsgIDNone && k == 2) || (isMsgToPGMExt && k == 9))
		{
			word = "n/a";
		} else {
			word = pch;
			pch = strtok(NULL, " ");
		}

		strncpy(arr[k++], word, MSG_HEADER_MAXSTRLEN);
	}
	
	date = arr[3];
	time = arr[4];

	snprintf(msgDateTime, sizeof msgDateTime, "%s %s", date, time);

	strcpy(jl->msgID, arr[0]);
	strcpy(jl->msgType, arr[1]);
	strcpy(jl->msgSEV, arr[2]);
	strcpy(jl->msgDatetime, msgDateTime);
	strcpy(jl->msgFromPGM, arr[5]);
	strcpy(jl->msgFromPGMLibrary, arr[6]);
	strcpy(jl->msgFromPGMInst, arr[7]);
	strcpy(jl->msgToPGM, arr[8]);
	strcpy(jl->msgToPGMLibrary, arr[9]);
	strcpy(jl->msgToPGMInst, arr[10]);
}

void printStructToJSON(jobLog *jl)
{
    printf("{\"user\": \"%s\", ", jl->user);
    printf("\"jobLogName\": \"%s\", ", jl->jobLogName);
    printf("\"dateTime\": \"%s\", ", jl->dateTime);
    printf("\"IBMiOSProgramName\": \"%s\", ", jl->IBMiOSProgramName);
    printf("\"IBMiOSProgramVersion\": \"%s\", ", jl->IBMiOSProgramVersion);
    printf("\"IBMiOSProgramSize\": \"%s\", ", jl->IBMiOSProgramSize);
    printf("\"jobName\": \"%s\", ", jl->jobName);
    printf("\"jobNumber\": \"%s\", ", jl->jobNumber);
	printf("\"jobDescription\": \"%s\", ", jl->jobDescription);
    printf("\"jobLibrary\": \"%s\", ", jl->jobLibrary);
	printf("\"msgID\": \"%s\", ", jl->msgID);
	printf("\"msgType\": \"%s\", ", jl->msgType);
	printf("\"msgSEV\": \"%s\", ", jl->msgSEV);
	printf("\"msgDatetime\": \"%s\", ", jl->msgDatetime);
	printf("\"msgFromPGM\": \"%s\", ", jl->msgFromPGM);
	printf("\"msgFromPGMLibrary\": \"%s\", ", jl->msgFromPGMLibrary);
	printf("\"msgFromPGMInst\": \"%s\", ", jl->msgFromPGMInst);
	printf("\"msgToPGM\": \"%s\", ", jl->msgToPGM);
	printf("\"msgToPGMLibrary\": \"%s\", ", jl->msgToPGMLibrary);
	printf("\"msgToPGMInst\": \"%s\", ", jl->msgToPGMInst);
	printf("\"msg\": \"%s\"}\n", jl->msg);
}
