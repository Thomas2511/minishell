/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:43:48 by tdieumeg          #+#    #+#             */
/*   Updated: 2016/05/19 17:43:50 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"
#include "libft.h"

static int		check_for_specials(char c, t_list **tokens, char **to_push)
{
	const char	*specials = SPECIAL_CHARACTERS;

	if (ft_strchr(specials, c))
	{
		if (ft_strlen(*to_push))
		{
			ft_lstpushback(tokens, *to_push, ft_strlen(*to_push) + 1);
			ft_bzero(*to_push, ft_strlen(*to_push));
		}
		(*to_push)[0] = c;
		ft_lstpushback(tokens, *to_push, 2);
		(*to_push)[0] = '\0';
		return (1);
	}
	return (0);
}

static int		check_for_separators(char c, t_list **tokens, char **to_push)
{
	const char	*separators = SEPARATION_CHARACTERS;

	if (ft_strchr(separators, c))
	{
		if (ft_strlen(*to_push))
		{
			ft_lstpushback(tokens, *to_push, ft_strlen(*to_push) + 1);
			ft_bzero(*to_push, ft_strlen(*to_push));
		}
		return (1);
	}
	return (0);
}

int				lexer(char **input, t_list **tokens)
{
	int			i;
	int			j;
	char		*to_push;

	i = 0;
	j = 0;
	to_push = NULL;
	if ((to_push = ft_strnew(ft_strlen(*input))) == NULL)
		sh_error(0, NULL);
	while ((*input)[i])
	{
		if (check_for_specials((*input)[i], tokens, &to_push) ||
				check_for_separators((*input)[i], tokens, &to_push))
			j = 0;
		else
		{
			to_push[j] = (*input)[i];
			++j;
		}
		++i;
	}
	if (ft_strlen(to_push))
		ft_lstpushback(tokens, to_push, ft_strlen(to_push) + 1);
	ft_memdel((void **)&to_push);
	return (0);
}
