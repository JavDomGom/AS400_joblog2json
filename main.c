#include <stdio.h>
#include <string.h>
#include "joblogreader.h"


int main(int argc, char *argv[])
{
	if (argc < 2) return 1;

	char *filename = argv[1], *line = NULL, *msgFragment;
	int n_line = 0, n_msgs = 0;
	size_t len = 0;
	ssize_t read;
	FILE *fp;

	INIT_JOBLOG(jl);

	fp = fopen(filename, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1)
	{
		// printf("[%d] %s", n_line, line);
		
		// If line starts with PREFIX_LOG_INI.
		if (prefix(line, PREFIX_LOG_INI, strlen(PREFIX_LOG_INI))) processLogHeader(line, &jl);

		// If line starts with PREFIX_LOG_END don't process and continue.
		if (prefix(line, PREFIX_LOG_END, strlen(PREFIX_LOG_END)))
		{
			n_line = 0;
			continue;
		}

		// If 2th line.
		if (n_line == 1) processPageHeader(line, &jl);

		// If 3th or 4th lines.
		if (n_line == 2 || n_line == 3) processJobAttributes(line, &jl, n_line);

			// If line starts with PREFIX_MSG_HEADER don't process and continue..
		if (prefix(line, PREFIX_MSG_HEADER, strlen(PREFIX_MSG_HEADER))) continue;

		// If n_line is greater than 4.
		if (n_line > 4)
		{
			// If line doesn't starts with space is the message header.
			// if (!prefix(line, " ", 1))
			if (line[0] != 32)
			{
				// Print last message if exist.
				if (n_msgs > 0) printStructToJSON(&jl);

				// Clean last message if exist.
				strcpy(jl.msg, "");

				processMsgHeader(line, &jl);
				n_msgs++;
				// printf("[%d] Press ENTER key to continue ...\n", n_msgs);
				// getchar();
			} else if(line[2] == 32) {
				msgFragment = trim(line);
				strcat(strcat(jl.msg, " "), msgFragment);
			}
		}

		n_line++;
	}

	free(line);
	exit(EXIT_SUCCESS);
}