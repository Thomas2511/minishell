/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_of_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:41:53 by tdieumeg          #+#    #+#             */
/*   Updated: 2016/05/19 17:41:56 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int				arr_of_arr_count(const char **arr_of_arr)
{
	int			i;

	i = 0;
	while (arr_of_arr && arr_of_arr[i])
		++i;
	return (i);
}

int				arr_of_arr_free(char ***arr)
{
	int			i;

	i = 0;
	while (*arr && (*arr)[i])
	{
		free((*arr)[i]);
		++i;
	}
	free(*arr);
	*arr = NULL;
	return (0);
}
