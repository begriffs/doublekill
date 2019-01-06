#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
 * Arguments:
 * 	-p pid
 * 	-x times (default 10)
 */

int main(int argc, char **argv)
{
	int c, times = 10;
	pid_t pid = 0;

	while ((c = getopt(argc, argv, "p:x:")) != -1)
	{
		switch (c)
		{
			case 'p':
				pid = strtoul(optarg, NULL, 10);
				break;
			case 'x':
				times = (int)strtoul(optarg, NULL, 10);
				break;
			default:
				return 1;
		}
	}

	if (0 == pid)
	{
		fprintf(stderr,
				"Usage: %s -p <pid> -x <times>\n", argv[0]);
		return 1;
	}

	while (times-- > 0)
	{
		if (kill(pid, SIGINT) != 0)
		{
			perror("Error killing");
			return 1;
		}
		fputc('.', stderr);
	}
	puts("");
	return 0;
}
