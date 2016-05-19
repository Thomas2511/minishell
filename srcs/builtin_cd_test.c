#include <sys/stat.h>
#include "minishell.h"
#include "libft.h"

static char			*next_directory(char **end, int depth, char relative)
{
	int				i;
	int				found;
	char			*to_free;

	i = 0;
	if (relative && (*end)[0] == '/' && (*end)[1])
	{
		to_free = *end;
		*end = ft_strjoin(".", *end);
		free(to_free);
		++i;
	}
	else if (!relative && (*end)[0] == '/' && !(*end)[1])
		++i;
	while ((*end)[i] && depth > 0)
	{
		if ((*end)[i] == '/')
			--depth;
		++i;
	}
	found = i;
	return (ft_strsub(*end, 0, found));
}

int					test_destination(char **end, int depth)
{
	struct stat		s;
	char			*next;
	int				val;

	val = 0;
	if (!end)
		return (1);
	next = next_directory(end, depth + 1, 0);
	if (access(next, F_OK) == -1)
	{
		free(next);
		next = next_directory(end, depth + 1, 1);
		if (access(next, F_OK) == -1)
			val = ft_putendl_fd("cd: no such file or directory", STD_ERR);
	}
	else if (stat(next, &s) != 0 || !(s.st_mode & S_IXUSR))
	{
		ft_putstr_fd("cd: permission denied: ", STD_ERR);
		val = ft_putendl_fd(*end, STD_ERR);
	}
	else if (!ft_strequ(*end, next))
		val = test_destination(end, depth + 1);
	free(next);
	return (val);
}
