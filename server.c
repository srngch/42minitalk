#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	handler_sigusr1(int signo);
void	handler_sigusr2(int signo);
int		server(void);

int	main(void)
{
	int	pid;
	int	result;

	pid = getpid();
	printf("SERVER PID: %d\n", pid);
	result = server();
	if (result == -1)
	{
		printf("<ERROR> server error\n");
		return (1);
	}
	while (1)
	{
		sleep(1);
	}
	return (0);
}

int	server(void)
{
	struct sigaction	sigusr1;
	struct sigaction	sigusr2;

	// for SIGUSR1
	sigusr1.sa_handler = handler_sigusr1;
	sigemptyset(&sigusr1.sa_mask);
	sigusr1.sa_flags = 0;
	if (sigaction(SIGUSR1, &sigusr1, 0) == -1)
	{
		printf("signal(SIGUSR1) error");
		return (-1);
	}
	// for SIGUSR2
	sigusr2.sa_handler = handler_sigusr2;
	sigemptyset(&sigusr2.sa_mask);
	sigusr2.sa_flags = 0;
	if (sigaction(SIGUSR2, &sigusr2, 0) == -1)
	{
		printf("signal(SIGUSR2) error");
		return (-1);
	}
	return (1);
}

void	handler_sigusr1(int signo)
{
	printf("Received Signal: SIGUSR1(%d)\n", signo);
}

void	handler_sigusr2(int signo)
{
	printf("Received Signal: SIGUSR2(%d)\n", signo);
}
