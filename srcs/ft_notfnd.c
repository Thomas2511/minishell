/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_notfnd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/29 12:32:34 by tdieumeg          #+#    #+#             */
/*   Updated: 2014/03/05 17:16:27 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_notfnd(char *split)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(split, 2);
}
