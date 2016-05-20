/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:42:16 by tdieumeg          #+#    #+#             */
/*   Updated: 2016/05/19 17:42:19 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int			solo_cd(t_env_list **sh_env)
{
	char			*destination;

	destination = env_get(*sh_env, "HOME");
	if (destination)
	{
		chdir(destination);
		env_insert(sh_env, "OLDPWD", env_get(*sh_env, "PWD"));
		env_insert(sh_env, "PWD", destination);
		free(destination);
	}
	return (1);
}

static int			standard_cd(const char **command, t_env_list **sh_env)
{
	char			cwd[PATH_MAX];
	char			*destination;

	destination = NULL;
	if (command[1][0] == '~' && ft_strlen(command[1]) == 1)
		return (solo_cd(sh_env));
	else if (command[1][0] == '-' && ft_strlen(command[1]) == 1)
		destination = env_get(*sh_env, "OLDPWD");
	else
		destination = ft_strdup(command[1]);
	if (destination && !test_destination(&destination, 0))
	{
		chdir(destination);
		env_insert(sh_env, "OLDPWD", env_get(*sh_env, "PWD"));
		env_insert(sh_env, "PWD", getcwd(cwd, PATH_MAX));
	}
	free(destination);
	return (1);
}

int					builtin_cd(const char **command,
		t_env_list **sh_env, t_list **tokens)
{
	int				count;

	(void)tokens;
	count = arr_of_arr_count(command);
	if (ft_strequ(command[0], "cd"))
	{
		if (count == 1)
			return (solo_cd(sh_env));
		if (count == 2)
			return (standard_cd(command, sh_env));
		return (ft_putendl_fd("cd: too many arguments", STD_ERR));
	}
	return (0);
}
