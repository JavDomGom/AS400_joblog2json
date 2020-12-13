#ifndef JOBLOGREADER_H
#define JOBLOGREADER_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define PREFIX_LOG_INI "INICIO"
#define PREFIX_LOG_END "FIN"
#define LOG_HEADER_MAXSTRLEN 10
#define LOG_HEADER_MAXWORDS 5
#define LOG_HEADER_DATETIME_MAXSTRLEN 29
#define PAGE_HEADER_MAXSTRLEN 8
#define PAGE_HEADER_MAXWORDS 3
#define JOB_ATTR_MAXWORDS 2
#define JOB_ATTR_MAXSTRLEN 11
#define MSG_HEADER_MAXSTRLEN 15
#define MSG_HEADER_MAXWORDS 11
#define MSG_HEADER_DATETIME_MAXSTRLEN 26
#define MSG_MAXSTRLEN 1024


typedef struct
{
	char user[LOG_HEADER_MAXSTRLEN];
	char jobLogName[LOG_HEADER_MAXSTRLEN];
	char dateTime[LOG_HEADER_DATETIME_MAXSTRLEN];
	char IBMiOSProgramName[PAGE_HEADER_MAXSTRLEN];
	char IBMiOSProgramVersion[PAGE_HEADER_MAXSTRLEN];
	char IBMiOSProgramSize[PAGE_HEADER_MAXSTRLEN];
	char jobName[JOB_ATTR_MAXSTRLEN];
	char jobNumber[JOB_ATTR_MAXSTRLEN];
	char jobDescription[JOB_ATTR_MAXSTRLEN];
	char jobLibrary[JOB_ATTR_MAXSTRLEN];
	char msgID[MSG_HEADER_MAXSTRLEN];
	char msgType[MSG_HEADER_MAXSTRLEN];
	char msgSEV[MSG_HEADER_MAXSTRLEN];
	char msgDatetime[MSG_HEADER_DATETIME_MAXSTRLEN];
	char msgFromPGM[MSG_HEADER_MAXSTRLEN];
	char msgFromPGMLibrary[MSG_HEADER_MAXSTRLEN];
	char msgFromPGMInst[MSG_HEADER_MAXSTRLEN];
	char msgToPGM[MSG_HEADER_MAXSTRLEN];
	char msgToPGMLibrary[MSG_HEADER_MAXSTRLEN];
	char msgToPGMInst[MSG_HEADER_MAXSTRLEN];
	char msg[MSG_MAXSTRLEN];
} jobLog;

bool prefix(const char *pre, const char *str, size_t n);
char *rtrim(const char *s);
char *ltrim(const char *s);
char *trim(const char *s);
void processLogHeader(char *line, jobLog *jl);
void processPageHeader(char *line, jobLog *jl);
void processJobAttributes(char *line, jobLog *jl, int n_line);
void processMsgHeader(char *line, jobLog *jl);
void printStructToJSON(jobLog *jl);

#define INIT_JOBLOG(X) jobLog X = { \
	.user = "", \
	.jobLogName = "", \
	.dateTime = "", \
	.IBMiOSProgramName = "", \
	.IBMiOSProgramVersion = "", \
	.IBMiOSProgramSize = "", \
	.jobName = "", \
	.jobNumber = "", \
	.jobDescription = "", \
	.jobLibrary = "", \
	.msgID = "", \
	.msgType = "", \
	.msgSEV = "", \
	.msgDatetime = "", \
	.msgFromPGM = "", \
	.msgFromPGMLibrary = "", \
	.msgFromPGMInst = "", \
	.msgToPGM = "", \
	.msgToPGMLibrary = "", \
	.msgToPGMInst = "", \
	.msg = "" \
}

#endif