/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:43:32 by tdieumeg          #+#    #+#             */
/*   Updated: 2016/05/19 17:43:34 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pwd.h>
#include "minishell.h"
#include "libft.h"

static int				env_get_values(char ***arr, const char *env_line,
		const int freeable)
{
	int					i;
	char				*tmp;

	i = 0;
	tmp = ft_strchr(env_line, '=');
	if (tmp)
	{
		if (freeable)
			free((*arr)[0]);
		if (((*arr)[0] = ft_strsub(env_line, 0, tmp - env_line)) == NULL)
			sh_error(0, NULL);
		if (freeable)
			free((*arr)[1]);
		if (((*arr)[1] = ft_strsub(env_line, tmp - env_line + 1,
				ft_strlen(env_line) - (tmp - env_line + 1))) == NULL)
			sh_error(0, NULL);
	}
	return (0);
}

char					*env_get(const t_env_list *sh_env, const char *key)
{
	const t_env_list	*tmp;
	char				*str;

	tmp = sh_env;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
		{
			if ((str = ft_strdup(tmp->value)) == NULL)
				sh_error(0, NULL);
			return (str);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int						env_insert(t_env_list **sh_env, const char *key,
		const char *value)
{
	t_env_list			*tmp;

	tmp = *sh_env;
	while (tmp)
	{
		if (ft_strequ(tmp->key, key))
		{
			free(tmp->value);
			if ((tmp->value = ft_strdup(value)) == NULL)
				sh_error(0, NULL);
			return (0);
		}
		tmp = tmp->next;
	}
	tmp = env_list_new(key, value);
	env_list_push(sh_env, tmp);
	return (0);
}

int						env_rebuild(t_env_list **sh_env)
{
	char				*value;
	struct passwd		*pw;

	pw = getpwuid(getuid());
	if ((value = ft_strdup(pw->pw_dir)) == NULL)
		sh_error(0, NULL);
	env_insert(sh_env, "HOME", value);
	free(value);
	if ((value = ft_strdup(pw->pw_name)) == NULL)
		sh_error(0, NULL);
	env_insert(sh_env, "LOGNAME", value);
	free(value);
	if ((value = ft_strnew(PATH_MAX)) == NULL)
		sh_error(0, NULL);
	getcwd(value, PATH_MAX);
	env_insert(sh_env, "PWD", value);
	env_insert(sh_env, "OLDPWD", value);
	free(value);
	return (0);
}

int						env_duplicate(t_env_list **sh_env, const char **env)
{
	int					i;
	int					env_len;
	char				**arr;
	t_env_list			*new;

	i = 0;
	env_len = arr_of_arr_count(env);
	if ((arr = (char **)ft_memalloc(sizeof(char *) * 3)) == NULL)
		sh_error(0, NULL);
	arr[2] = NULL;
	while (i < env_len)
	{
		env_get_values(&arr, env[i], i);
		new = env_list_new(arr[0], arr[1]);
		env_list_push(sh_env, new);
		++i;
	}
	arr_of_arr_free(&arr);
	return (0);
}
