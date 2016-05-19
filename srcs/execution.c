#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "minishell.h"

static int		execution_son_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	return (0);
}

static int		execution_father_signals(void)
{
	signal(SIGINT, signals_modification);
	signal(SIGQUIT, signals_modification);
	signal(SIGTSTP, signals_modification);
	return (0);
}

int				execution(char **command, char **env)
{
	int			waitvar;
	pid_t		pid;

	waitvar = 0;
	if ((pid = fork()) < 0)
		sh_error(2, (const char **)command);
	if (!pid)
	{
		execution_son_signals();
		execve(command[0], command, env);
		sh_error(1, (const char **)command);
	}
	else
	{
		execution_father_signals();
		while (waitpid(-1, &waitvar, 0) >= 0)
			;
	}
	return (0);
}
