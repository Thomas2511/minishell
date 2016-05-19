/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:42:32 by tdieumeg          #+#    #+#             */
/*   Updated: 2016/05/19 17:42:34 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int		string_from_index_to_end(char **tmp,
		const char **env_command, int index)
{
	while (env_command[index])
	{
		utility_join(tmp, ft_strdup(env_command[index]), 1);
		++index;
		if (env_command[index])
			utility_join(tmp, " ", 0);
	}
	return (0);
}

int				builtin_env_execution(const char **env_command,
		t_env_list **copy, char verbose, int index)
{
	int			i;
	char		*tmp;

	i = index;
	tmp = NULL;
	while (verbose && env_command[i])
	{
		ft_putstr("#env arg[");
		ft_putnbr(i - index);
		ft_putstr("]: ");
		ft_putendl(env_command[i]);
		++i;
	}
	string_from_index_to_end(&tmp, env_command, index);
	command_handler(&tmp, copy);
	return (1);
}

int				builtin_env(const char **command,
		t_env_list **sh_env, t_list **tokens)
{
	t_env_list	*copy;

	(void)tokens;
	copy = NULL;
	if (ft_strequ(command[0], "env"))
	{
		env_list_copy(&copy, sh_env);
		if (arr_of_arr_count(command) == 1 ||
				!builtin_env_parse(command, &copy))
			builtin_display_env(&copy);
		env_list_free(&copy);
		return (1);
	}
	return (0);
}
