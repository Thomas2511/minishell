/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:43:23 by tdieumeg          #+#    #+#             */
/*   Updated: 2016/05/19 17:43:26 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int				env_list_copy(t_env_list **copy, t_env_list **original)
{
	t_env_list	*tmp;

	tmp = *original;
	while (tmp)
	{
		env_list_push(copy, env_list_new(tmp->key,
					tmp->value));
		tmp = tmp->next;
	}
	return (0);
}
