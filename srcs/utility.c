#include <unistd.h>
#include "minishell.h"
#include "libft.h"

int				utility_count_to_spe(const t_list *alist)
{
	int			i;
	t_list		*tmp;

	i = 0;
	tmp = (t_list *)alist;
	while (tmp && !ft_strchr(SPECIAL_CHARACTERS, ((char *)tmp->content)[0]))
	{
		++i;
		tmp = tmp->next;
	}
	return (i);
}

int				utility_list_len(const t_env_list *alist)
{
	int			i;
	t_env_list	*tmp;

	i = 0;
	tmp = (t_env_list *)alist;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	return (i);
}

int				utility_join(char **str, char *str2, const char arg_to_delete)
{
	char		*new;

	if ((new = ft_strjoin(*str, str2)) == NULL)
		sh_error(0, NULL);
	free(*str);
	*str = new;
	if (arg_to_delete)
		ft_memdel((void **)&str2);
	return (0);
}

int				utility_list_clear(t_list **alist)
{
	t_list		*tmp;

	while (*alist)
	{
		tmp = *alist;
		*alist = (*alist)->next;
		free(tmp->content);
		free(tmp);
	}
	return (0);
}
