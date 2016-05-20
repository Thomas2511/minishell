/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:42:02 by tdieumeg          #+#    #+#             */
/*   Updated: 2016/05/19 17:42:06 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int				builtin_display_env(t_env_list **sh_env)
{
	t_env_list	*tmp;

	tmp = *sh_env;
	while (tmp)
	{
		ft_putstr(tmp->key);
		ft_putstr("=");
		ft_putendl(tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

static int		builtin_setenv(const char **command,
		t_env_list **sh_env, t_list **tokens)
{
	(void)tokens;
	if (ft_strequ(command[0], "setenv"))
	{
		if (arr_of_arr_count(command) == 1)
			return (builtin_display_env(sh_env) + 1);
		if (arr_of_arr_count(command) > 3)
			return (ft_putendl_fd("setenv: too many arguments", STD_ERR));
		env_insert(sh_env, command[1], command[2]);
		return (1);
	}
	return (0);
}

static int		builtin_unsetenv(const char **command,
		t_env_list **sh_env, t_list **tokens)
{
	int			i;

	(void)tokens;
	if (ft_strequ(command[0], "unsetenv"))
	{
		if (arr_of_arr_count(command) < 2)
			return (ft_putendl_fd("unsetenv: not enough arguments", STD_ERR));
		i = 1;
		while (command[i])
		{
			env_list_del_if(sh_env, command[i]);
			++i;
		}
		return (1);
	}
	return (0);
}

static int		builtin_exit(const char **command,
		t_env_list **sh_env, t_list **tokens)
{
	int			i;
	int			exit_value;

	i = 0;
	exit_value = 0;
	if (ft_strequ(command[0], "exit"))
	{
		if (arr_of_arr_count(command) > 2)
			return (ft_putendl_fd("exit: too many arguments", STD_ERR));
		else
		{
			while (command[1] && command[1][i] && ft_isdigit(command[1][i]))
				++i;
			if (command[1] && !command[1][i])
				exit_value = ft_atoi(command[1]);
			arr_of_arr_free((char ***)&command);
			env_list_free(sh_env);
			utility_list_clear(tokens);
			exit(exit_value);
		}
	}
	return (0);
}

int				builtin_check(const char **command,
		t_env_list **sh_env, t_list **tokens)
{
	int			i;
	int			(*f_ptr[BUILTINS])(const char **, t_env_list **, t_list **);

	i = 0;
	f_ptr[0] = builtin_exit;
	f_ptr[1] = builtin_unsetenv;
	f_ptr[2] = builtin_setenv;
	f_ptr[3] = builtin_env;
	f_ptr[4] = builtin_cd;
	while (command && i < BUILTINS)
	{
		if ((f_ptr[i])((const char **)command, sh_env, tokens))
			return (1);
		++i;
	}
	return (0);
}
