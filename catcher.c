#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void int_catch(int);

static volatile sig_atomic_t intflag = 0;

int main(void)
{
	signal(SIGINT, &int_catch);
	while (1)
	{
		if (intflag > 0)
		{
			fputc('!', stderr);
			intflag--;
		}
		sleep(1);
	}
	return 0;
}

void int_catch(int sig)
{
	(void)sig;

	/* open a window where a repeat signal could
	 * hit the default handler before we reinstate */
	sleep(1);

	signal(SIGINT, &int_catch);
	intflag++;
	return;
}
