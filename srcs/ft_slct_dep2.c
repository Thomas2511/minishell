/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slct_dep2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlinden <jlinden@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/04 14:44:12 by jlinden           #+#    #+#             */
/*   Updated: 2014/03/15 15:11:42 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	load_term(void)
{
	put_flag(TERM_INIT);
	put_flag(DELETE_LINE);
	put_flag(HIDE_CURSOR);
}

void	restore_term(void)
{
	put_flag(SHOW_CURSOR);
	put_flag(TERM_END);
}
