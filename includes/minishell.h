
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define PATH_MAX 1024
# define BUFF_SIZE 1024
# define NUMBER_OF_SIGNALS 32
# define NUMBER_OF_BUILTINS 5
# define ERROR_FUNCTIONS 2
# define STD_IN 0
# define STD_OUT 1
# define STD_ERR 2
# define ARB_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

# define NORMAL "\x1B[0m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"

# define SPECIAL_CHARACTERS ";"
# define SEPARATION_CHARACTERS " \t"

typedef struct			s_env_list
{
	struct s_env_list	*next;
	char				*key;
	char				*value;
}						t_env_list;

/*
** environment.c
*/
int						env_duplicate(t_env_list **sh_env, const char **env);
int						env_rebuild(t_env_list **sh_env);
char					*env_get(const t_env_list *sh_env, const char *key);
int						env_insert(t_env_list **sh_env, const char *key,
		const char *value);

/*
** arr_of_arr.c
*/
int						arr_of_arr_count(const char **arr_of_arr);
int						arr_of_arr_free(char ***arr);

/*
** env_list.c
*/
t_env_list				*env_list_new(const char *key, const char *value);
int						env_list_push(t_env_list **sh_env, t_env_list *new);
int						env_list_del_if(t_env_list **sh_env, const char *value);
int						env_list_free(t_env_list **sh_env);

/*
** env_list_copy.c
*/
int						env_list_copy(t_env_list **copy, t_env_list **original);

/*
** sh_error.c
*/
int						sh_error(const int error_code, const char **command);

/*
** commands.c
*/
int						command_handler(char **cmd, t_env_list **sh_env);

/*
** lexer.c
*/
int						lexer(char **cmd, t_list **tokens);

/*
** builtin.c
*/
int						builtin_check(const char **command,
		t_env_list **sh_env, t_list **tokens);
int						builtin_display_env(t_env_list **sh_env);

/*
** builtin_env.c
*/
int						builtin_env(const char **command,
		t_env_list **sh_env, t_list **tokens);
int						builtin_env_execution(const char **env_command,
		t_env_list **copy, char verbose, int index);

/*
** builtin_env_parse.c
*/
int						builtin_env_parse(const char **env_command,
		t_env_list **copy);

/*
** builtin_cd.c
*/
int						builtin_cd(const char **env_command,
		t_env_list **copy, t_list **tokens);

/*
** builtin_cd_test.c
*/
int						test_destination(char **end, int depth);

/*
** display.c
*/
int						display_prompt(void);

/*
** utility.c
*/
int						utility_count_to_spe(const t_list *alist);
int						utility_list_len(const t_env_list *alist);
int						utility_join(char **str, char *str2,
		const char arg_to_delete);
int						utility_list_clear(t_list **alist);

/*
** execution.c
*/
int						execution(char **command, char **env);

/*
** signals.c
*/
void					signals_modification(int sig);

#endif
