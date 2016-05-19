#include <unistd.h>
#include <signal.h>
#include "minishell.h"
#include "libft.h"

static int		shell_initialization(t_env_list **sh_env, const char **env)
{
	signal(SIGINT, signals_modification);
	signal(SIGQUIT, signals_modification);
	signal(SIGCONT, signals_modification);
	if (*env)
		env_duplicate(sh_env, env);
	else
		env_rebuild(sh_env);
	return (0);
}

static int		shell_main_loop(t_env_list **sh_env)
{
	int			bytes;
	char		*input;
	char		buffer[BUFF_SIZE + 1];

	input = NULL;
	display_prompt();
	while ((bytes = read(STD_IN, buffer, BUFF_SIZE)) > 0)
	{
		buffer[bytes] = '\0';
		utility_join(&input, buffer, 0);
		if (ft_strchr(input, '\n'))
		{
			input[ft_strlen(input) - 1] = '\0';
			command_handler(&input, sh_env);
			ft_memdel((void **)&input);
			ft_bzero(buffer, BUFF_SIZE);
			display_prompt();
		}
	}
	ft_putendl("");
	ft_memdel((void **)&input);
	return (0);
}

int				main(int ac, char **av, char **env)
{
	t_env_list		*sh_env;

	(void)av;
	(void)ac;
	sh_env = NULL;
	shell_initialization(&sh_env, (const char **)env);
	shell_main_loop(&sh_env);
	env_list_free(&sh_env);
	return (0);
}
