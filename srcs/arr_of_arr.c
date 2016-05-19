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
