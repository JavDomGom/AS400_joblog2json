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
#define MSJ_HEADER_ID_MAXSTRLEN 8
#define MSJ_HEADER_TYPE_MAXSTRLEN 15
#define MSJ_HEADER_SEV_MAXSTRLEN 2
#define MSJ_HEADER_DATETIME_MAXSTRLEN 26
#define MSJ_HEADER_FROM_PGM_MAXSTRLEN 8
#define MSJ_HEADER_FROM_PGM_LIB_MAXSTRLEN 4
#define MSJ_HEADER_FROM_PGM_INST_MAXSTRLEN 4
#define MSJ_HEADER_TO_PGM_MAXSTRLEN 8
#define MSJ_HEADER_TO_PGM_LIB_MAXSTRLEN 8
#define MSJ_HEADER_TO_PGM_INST_MAXSTRLEN 4


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
	char msgID[MSJ_HEADER_ID_MAXSTRLEN];
	char msgType[MSJ_HEADER_TYPE_MAXSTRLEN];
	char msgSEV[MSJ_HEADER_SEV_MAXSTRLEN];
	char msgDatetime[MSJ_HEADER_DATETIME_MAXSTRLEN];
	char msgFromPGM[MSJ_HEADER_FROM_PGM_MAXSTRLEN];
	char msgFromPGMLibrary[MSJ_HEADER_FROM_PGM_LIB_MAXSTRLEN];
	char msgFromPGMInst[MSJ_HEADER_FROM_PGM_INST_MAXSTRLEN];
	char msgToPGM[MSJ_HEADER_TO_PGM_MAXSTRLEN];
	char msgToPGMLibrary[MSJ_HEADER_TO_PGM_LIB_MAXSTRLEN];
	char msgToPGMInst[MSJ_HEADER_TO_PGM_INST_MAXSTRLEN];
} jobLog;

bool prefix(const char *pre, const char *str, size_t n);
void processLogHeader(char *line, jobLog *jl);
void processPageHeader(char *line, jobLog *jl);
void processJobAttributes(char *line, jobLog *jl, int n_line);
void printStruct(jobLog *jl);

#define INIT_JOBLOG(X) jobLog X = {.user = "", .jobLogName = "", .dateTime = "", .IBMiOSProgramName = "", .IBMiOSProgramVersion = "", .IBMiOSProgramSize = "", .jobName = "", .jobNumber = ""}

#endif