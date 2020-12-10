#ifndef JOBLOGREADER_H
#define JOBLOGREADER_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LOG_HEADER_MAXSTRLEN 10
#define LOG_HEADER_MAXWORDS 5
#define PAGE_HEADER_MAXSTRLEN 8
#define PAGE_HEADER_MAXWORDS 3
#define DATETIME_MAXSTRLEN 29
#define JOB_ATTR_MAXWORDS 2
#define JOB_ATTR_MAXSTRLEN 11

typedef struct
{
	char user[LOG_HEADER_MAXSTRLEN];
	char jobLogName[LOG_HEADER_MAXSTRLEN];
	char dateTime[DATETIME_MAXSTRLEN];
	char IBMiOSProgramName[PAGE_HEADER_MAXSTRLEN];
	char IBMiOSProgramVersion[PAGE_HEADER_MAXSTRLEN];
	char IBMiOSProgramSize[PAGE_HEADER_MAXSTRLEN];
	char jobName[JOB_ATTR_MAXSTRLEN];
	char jobNumber[JOB_ATTR_MAXSTRLEN];
	char jobDescription[JOB_ATTR_MAXSTRLEN];
	char jobLibrary[JOB_ATTR_MAXSTRLEN];
} jobLog;

bool prefix(const char *pre, const char *str, size_t n);
void processLogHeader(char *line, jobLog *jl);
void processPageHeader(char *line, jobLog *jl);
void processJobAttributes(char *line, jobLog *jl, int n_line);
void printStruct(jobLog *jl);

#define INIT_JOBLOG(X) jobLog X = {.user = "", .jobLogName = "", .dateTime = "", .IBMiOSProgramName = "", .IBMiOSProgramVersion = "", .IBMiOSProgramSize = "", .jobName = "", .jobNumber = ""}

#endif