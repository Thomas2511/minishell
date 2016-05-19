/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:43:13 by tdieumeg          #+#    #+#             */
/*   Updated: 2016/05/19 17:43:15 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <libft.h>

t_env_list			*env_list_new(const char *key, const char *value)
{
	t_env_list		*new;

	if ((new = (t_env_list *)ft_memalloc(sizeof(t_env_list))) == NULL)
		sh_error(0, NULL);
	new->next = NULL;
	if ((new->key = ft_strdup(key)) == NULL)
		sh_error(0, NULL);
	if ((new->value = ft_strdup(value)) == NULL)
		sh_error(0, NULL);
	return (new);
}

int					env_list_push(t_env_list **sh_env, t_env_list *new)
{
	t_env_list		*tmp;

	tmp = *sh_env;
	if (!*sh_env)
		*sh_env = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

int					env_list_del_link(t_env_list **link)
{
	free((*link)->key);
	free((*link)->value);
	free((*link));
	*link = NULL;
	return (0);
}

int					env_list_del_if(t_env_list **sh_env, const char *key)
{
	t_env_list		*tmp;
	t_env_list		*to_del;

	tmp = *sh_env;
	if (tmp && ft_strequ(tmp->key, key))
	{
		*sh_env = (*sh_env)->next;
		env_list_del_link(&tmp);
		return (1);
	}
	else
	{
		while (tmp && tmp->next)
		{
			if (ft_strequ(tmp->next->key, key))
			{
				to_del = tmp->next;
				tmp->next = tmp->next->next;
				env_list_del_link(&to_del);
				return (1);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

int					env_list_free(t_env_list **sh_env)
{
	t_env_list		*tmp;

	while (*sh_env)
	{
		tmp = *sh_env;
		(*sh_env) = (*sh_env)->next;
		env_list_del_link(&tmp);
	}
	tmp = NULL;
	return (0);
}
