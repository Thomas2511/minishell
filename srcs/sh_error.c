#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

static int			unknown_command(const char **command)
{
	int				i;

	i = 0;
	ft_putstr_fd("minishell: command not found: ", 2);
	while (command[i])
	{
		if (i)
			ft_putstr_fd(" ", 2);
		ft_putstr_fd(command[i], 2);
		++i;
	}
	ft_putendl_fd("", 2);
	return (0);
}

static int			malloc_error(const char **command)
{
	(void)command;
	ft_putendl_fd("minishell: malloc failure, exiting now", 2);
	exit(EXIT_FAILURE);
}

int					sh_error(const int error_code, const char **command)
{
	int				(*f_ptr[ERROR_FUNCTIONS])(const char **);

	f_ptr[0] = malloc_error;
	f_ptr[1] = unknown_command;
	if (error_code <= ERROR_FUNCTIONS)
		(f_ptr[error_code])(command);
	else
	{
		ft_putendl_fd("Unknown error code", 2);
		exit(EXIT_FAILURE);
	}
	return (0);
}
