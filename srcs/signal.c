#include "../include/minishell.h"

void	ft_ctrlc(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_redisplay();
}

void	ft_ctrld(int sig)
{
	write(1, "\nhello", 6);
	(void)sig;
	// exit(0);
}
