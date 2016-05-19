#include <signal.h>
#include "minishell.h"
#include "libft.h"

int				signals_sigint(void)
{
	ft_putendl("");
	display_prompt();
	return (0);
}

int				signals_sigtstp(void)
{
	return (0);
}

int				signals_sigquit(void)
{
	return (0);
}

int				signals_sigcont(void)
{
	display_prompt();
	return (0);
}

void			signals_modification(int sig)
{
	int 		(*f_ptr[NUMBER_OF_SIGNALS])(void);

	f_ptr[SIGINT] = signals_sigint;
	f_ptr[SIGTSTP] = signals_sigtstp;
	f_ptr[SIGQUIT] = signals_sigquit;
	f_ptr[SIGCONT] = signals_sigcont;
	if (sig <= NUMBER_OF_SIGNALS)
		(f_ptr[sig])();
}
