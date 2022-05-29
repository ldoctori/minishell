#include "minishell.h"

void	sig_int_handler(int sig)
{
    struct termios old_term, new_term;
    char *cursor;
    char *esc_sequence;

	new_term = old_term;
	if (g_last_exit.flag == -1)
	{
		printf("\n");
		printf("%s",g_last_exit.prompt);
	}
	else if (g_last_exit.flag == 0)
	{
		printf("\n");
		exit(EXIT_SUCCESS);
	}
	else if (g_last_exit.flag > 0)
	{
		printf("\n");
		int i = 0;
		while (g_last_exit.pid[i])
		{
			kill(g_last_exit.pid[i], SIGKILL);
			g_last_exit.exit_status = 130;
			i++;
		}
	}
}