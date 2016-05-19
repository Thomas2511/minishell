/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:42:43 by tdieumeg          #+#    #+#             */
/*   Updated: 2016/05/19 17:42:46 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int		check_for_name_value(const char *arg, t_env_list **copy)
{
	char		*equal;
	char		*key;
	char		*value;

	equal = ft_strchr(arg, '=');
	key = ft_strsub(arg, 0, equal - arg);
	value = ft_strsub(arg, equal - arg + 1, ft_strlen(arg) - (equal - arg + 1));
	if (ft_strlen(key) > 0)
		env_list_push(copy, env_list_new(ft_strdup(key), ft_strdup(value)));
	free(key);
	free(value);
	return (0);
}

static int		check_for_flags(const char **env_command, int *cur,
		t_env_list **copy, char *verbose)
{
	int			i;

	i = 0;
	while (env_command[*cur][i])
	{
		if (env_command[*cur][i] == 'u')
		{
			env_list_del_if(copy, env_command[*cur + 1]);
			++(*cur);
			if (*verbose)
				ft_putstr("#env unset:\t");
			if (*verbose)
				ft_putendl(env_command[*cur + 1]);
			return (1);
		}
		if (env_command[*cur][i] == 'P')
		{
			env_list_del_if(copy, "PATH");
			env_list_push(copy, env_list_new("PATH", env_command[*cur + 1]));
			++(*cur);
			return (1);
		}
		++i;
	}
	return (0);
}

static int		check_for_options(const char *arg,
		t_env_list **copy, char *verbose)
{
	int			i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == 'v')
			*verbose = 1;
		if (arg[i] == 'i')
		{
			env_list_free(copy);
			if (*verbose)
				ft_putendl("#env clearing environ");
		}
		++i;
	}
	return (0);
}

static int		check_for_illegal(const char *arg)
{
	int			i;
	const char	*legal = "ivuP";

	i = 0;
	while (arg[i])
	{
		while (arg[i] == '-')
			++i;
		if (!ft_strchr(legal, arg[i]))
		{
			ft_putstr_fd("env: illegal option -- ", 2);
			ft_putendl_fd(arg, 2);
			ft_putstr_fd("usage: env [-iv] [-P utilpath] [-u name]", 2);
			ft_putendl_fd("[name=value ...] [utility [argument ...]]", 2);
			return (1);
		}
		++i;
	}
	return (0);
}

int				builtin_env_parse(const char **env_command, t_env_list **copy)
{
	int			i;
	char		verbose;

	i = 1;
	verbose = 0;
	while (env_command[i] && env_command[i][0] == '-')
	{
		if (check_for_illegal(env_command[i]))
			return (1);
		check_for_options(env_command[i], copy, &verbose);
		check_for_flags(env_command, &i, copy, &verbose);
		++i;
	}
	while (env_command[i] && ft_strchr(env_command[i], '='))
	{
		check_for_name_value(env_command[i], copy);
		++i;
	}
	if (env_command[i])
		return (builtin_env_execution(env_command, copy, verbose, i));
	return (0);
}
