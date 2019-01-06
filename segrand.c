#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void seg_catch(int);

int main(void)
{
	/* using volatile so that the optimizer won't
	 * remove this array entirely */
	volatile char victim[2];
	volatile char *v = victim;

	signal(SIGSEGV, seg_catch);

	/* assumes we'll get a segfault before exceeding
	 * the maximum value for ptrdiff_t */
	while (1)
	{
		printf("%zd\n", v - victim);
		*v++ = '!';
	}
}


void seg_catch(int sig)
{
	(void)sig;

	/* suppress the "Segmentation fault" output */
	exit(EXIT_SUCCESS);

	return;
}
