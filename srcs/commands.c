/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:42:50 by tdieumeg          #+#    #+#             */
/*   Updated: 2016/05/19 17:42:52 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int		env_list_to_arr_of_arr(t_env_list **sh_env, char ***env)
{
	int			i;
	int			list_len;
	char		*lhs;
	t_env_list	*tmp;

	i = 0;
	list_len = utility_list_len(*sh_env);
	lhs = NULL;
	tmp = *sh_env;
	if ((*env = (char **)ft_memalloc(sizeof(char *) * (list_len + 1))) == NULL)
		sh_error(0, NULL);
	(*env)[list_len] = NULL;
	while (i < list_len)
	{
		lhs = ft_strjoin(tmp->key, "=");
		(*env)[i] = ft_strjoin(lhs, tmp->value);
		ft_memdel((void **)&lhs);
		tmp = tmp->next;
		++i;
	}
	return (0);
}

static int		tokens_to_command(t_list **tmp, char ***command)
{
	int			i;
	int			list_len;

	i = 0;
	if (!(*tmp))
		return (0);
	list_len = utility_count_to_spe(*tmp);
	if (*command)
		arr_of_arr_free(command);
	if (list_len)
	{
		if ((*command = (char **)ft_memalloc(sizeof(char *) * (list_len + 1)))
				== NULL)
			sh_error(0, NULL);
		(*command)[list_len] = NULL;
	}
	while (i < list_len)
	{
		(*command)[i] = ft_strdup((*tmp)->content);
		*tmp = (*tmp)->next;
		++i;
	}
	*tmp = (*tmp == NULL ? NULL : (*tmp)->next);
	return (1);
}

static int		test_path(char **split, char **command)
{
	int			i;
	char		*str;

	i = 0;
	str = NULL;
	while (split[i])
	{
		str = ft_strdup(split[i]);
		utility_join(&str, "/", 0);
		utility_join(&str, *command, 0);
		if (!access(str, F_OK))
		{
			ft_memdel((void **)command);
			*command = str;
			return (1);
		}
		ft_memdel((void **)&str);
		++i;
	}
	return (0);
}

static int		command_absolute_path(char **command, t_env_list *sh_env)
{
	char		*str;
	char		**split;
	char		return_value;

	if (!access(*command, F_OK))
		return (1);
	str = env_get(sh_env, "PATH");
	if (!str)
		str = ft_strdup(ARB_PATH);
	split = ft_strsplit(str, ':');
	ft_memdel((void **)&str);
	return_value = test_path(split, command);
	arr_of_arr_free(&split);
	return (return_value);
}

int				command_handler(char **input, t_env_list **sh_env)
{
	char		**env;
	char		**command;
	t_list		*tokens;
	t_list		*head;

	env = NULL;
	command = NULL;
	tokens = NULL;
	lexer(input, &tokens);
	head = tokens;
	ft_memdel((void **)input);
	env_list_to_arr_of_arr(sh_env, &env);
	while (tokens_to_command(&tokens, &command))
	{
		if (builtin_check((const char **)command, sh_env, &tokens))
			continue ;
		else if (command && command_absolute_path(&(command[0]), *sh_env))
			execution(command, env);
		else if (command)
			sh_error(1, (const char **)command);
	}
	arr_of_arr_free(&command);
	arr_of_arr_free(&env);
	utility_list_clear(&head);
	return (0);
}
