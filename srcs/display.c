/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdieumeg <tdieumeg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:43:05 by tdieumeg          #+#    #+#             */
/*   Updated: 2016/05/19 17:43:06 by tdieumeg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include "minishell.h"
#include "libft.h"

static int			check_for_tilde(char **cwd)
{
	char			*home;
	char			*tmp;
	struct passwd	*pw;

	pw = getpwuid(getuid());
	if ((home = ft_strdup(pw->pw_dir)) == NULL)
		sh_error(0, NULL);
	if (ft_strnequ(*cwd, home, ft_strlen(home)))
	{
		tmp = ft_strsub(*cwd, ft_strlen(home),
				ft_strlen(*cwd) - ft_strlen(home));
		free(*cwd);
		*cwd = ft_strjoin("~", tmp);
		free(tmp);
	}
	free(home);
	return (0);
}

int					display_prompt(void)
{
	char			*cwd;
	struct passwd	*pw;
	int				written;

	cwd = NULL;
	pw = NULL;
	written = 0;
	if ((cwd = ft_strnew(PATH_MAX)) == NULL)
		sh_error(0, NULL);
	getcwd(cwd, PATH_MAX);
	check_for_tilde(&cwd);
	pw = getpwuid(getuid());
	ft_putstr(GREEN);
	written += ft_putstr(pw->pw_name);
	ft_putstr(RED);
	written += ft_putstr("@");
	ft_putstr(BLUE);
	written += ft_putstr(cwd);
	ft_putstr(GREEN);
	written += ft_putstr("\n> ");
	ft_putstr(NORMAL);
	free(cwd);
	return (written);
}
