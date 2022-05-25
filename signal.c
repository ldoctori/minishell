#include "minishell.h"

void	sigint_handler(int sig)
{
	if (g_last_exit.pid == 0)
	{
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit!\n", 1);
		else if (sig == SIGINT)
			ft_putstr_fd("\n", 1);
	}
	/*else
	{
		if (sig == SIGINT)
		{
			g_last_exit.exit_status = 1;
			ft_putstr_fd("\n", 2);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		//else if (sig == SIGQUIT)
		//{
		//	rl_on_new_line();
			//rl_on_new_line();
			//rl_redisplay();
		//}
	}*/
}
