#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void int_catch(int);

int main(void)
{
	signal(SIGINT, &int_catch);
	while (1)
		sleep(1);
	return 0;
}

void int_catch(int sig)
{
	fputc('!', stderr);
	sleep(1);
	signal(SIGINT, &int_catch);
	(void)sig;
}
