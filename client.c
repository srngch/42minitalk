#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	client(int pid, int signum);
int	send_sigusr1(int pid);
int	send_sigusr2(int pid);

int	main(int argc, char **argv)
{
	int	result;

	if (argc != 3)
	{
		printf("<usage> %s [pid] [signum]\n", argv[0]);
		printf("  [signum]\n");
		printf("  - 30: SIGUSR1\n");
		printf("  - 31: SIGUSR2\n");
		return (1);
	}
	else
		result = client(atoi(argv[1]), atoi(argv[2]));
	if (result == -1)
		return (1);
	return (0);
}

int	client(int pid, int signum)
{
	int	result;

	if (signum == SIGUSR1)
		result = send_sigusr1(pid);
	else if (signum == SIGUSR2)
		result = send_sigusr2(pid);
	else
	{
		printf("<alert> the signum is not defined.\n");
		result = -1;
	}
	if (result == -1)
		return (-1);
	printf("Sent signal: '%d' to %d\n", signum, pid);
	usleep(500);
	return (1);
}

int	send_sigusr1(int pid)
{
	int	result;

	result = kill(pid, SIGUSR1);
	if (result == -1)
	{
		perror("SIGUSR1 Signal Send error");
		return (-1);
	}
	return (1);
}

int	send_sigusr2(int pid)
{
	int	result;

	result = kill(pid, SIGUSR2);
	if (result == -1)
	{
		perror("SIGUSR2 Signal Send error");
		return (-1);
	}
	return (1);
}
