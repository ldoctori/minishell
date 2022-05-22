/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoctori <hectkctk@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:02:09 by ldoctori          #+#    #+#             */
/*   Updated: 2022/05/22 09:36:28 by ldoctori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <linux/ioctl.h>
# include <curses.h>
# include <term.h>

int	g_last_exit_status;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_struct
{
	char			**split;
	char			*s;
	char			c;
	unsigned int	size;
}	t_struct;

typedef struct s_command
{
	char				**cmd_args;
	char				*infile;
	char				*outfile;
	int					append_out;
	char				*delimiter;
	int					*del_fd;
	char				**envp;
	t_env				*env;
	int					cmd_number;
	int					**fd;
	struct s_command	*next;
}	t_command;

/*-----------utils--------------*/
int				ft_strncmp(char *s1, char *s2, unsigned int n);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strjoin(char const *s1, char const *s2);
unsigned int	ft_strlen(const char *str);
char			*ft_strdup(char *src);
char			*ft_strldup(char *src, int n);
char			*ft_strchr(const char *s, int c);
char			**ft_split(char *s, char c);
void			ft_split_allocate(t_struct *ss);
void			len_ptr_increas(char **ptr, int *len, char some_c);
char			**free_all(t_struct *ss);
void			ft_putstr_fd(char *s, int fd);
char			*ft_itoa(int n);

/*-----------parser--------------*/
char			**set_token_arr(char *line);
int				get_args_num(char **token_arr);
t_command		*get_command(char **token_arr, int args_num,
					char **envp, t_env *env);
t_command		*get_command_list(char **token_arr, char **envp, t_env *env);
void			free_command_list(t_command *command);
void			free_env_list(t_env *env);
void			free_parser(char *line, char **token_arr, t_command *command);
t_env			*get_env_list(char **envp);
t_env			*get_env(char *envp);
void			set_new_env_list(t_command *cmd, int *exp_fd);
void			set_cmd_number(t_command *command);
void			set_cmd_args(t_command *command, char
					**token_arr, int i, int j);
int				**fd_allocate(int cmd_number);
char			**get_envp_arr(char **envp);
char			**updape_envp_arr(t_env *env, char **envp);
void			free_arr(char **arr);

/*-----------executor--------------*/
void			free_fd(int **fd, int fd_number);
void			del_fd_free(int *del_fd);
void			cmds_executer(t_command *command, char *envp[]);
void			fd_duplicate(int **fd, int i, t_command *command);
void			close_wait(int **fd, int **exit_status_fd,
					int *pid, int cmd_number);
void			exec_pid(t_command *command, int *exp_fd,
					int **exit_status_fd, int i);
char			*find_cmd_path(char **paths, t_command *command);
char			*find_file_path(char *file, char **envp);
int				open_file_fd(char *file, t_command *command, char c);
void			here_doc(t_command *command);
void			finish_exec(int **fd, int **exit_status_fd,
					int *pid, int cmd_number);
char			*get_path_env(char **envp);

/*-----------GNL--------------*/
char			*get_next_line(int fd);

/*-----------prompt--------------*/
char			*path_for_prompt(char **envp);
char			*cut_path(char *path);

/*-----------error_manager--------------*/
void			open_file_error(int in_fd, int out_fd, t_command *command);
void			pipe_error(int pipe);
void			cmd_error(char *cmd);
int				pid_error(int *pid, int i, int **fd, int cmd_number);

/*-----------builtins--------------*/
int				is_builtin(t_command *cmd, int *exp_fd);
void			exit_cmd(char *line, char **token_arr,
					char *prompt, t_command *command);
void			cd(t_command *command);
void			pwd(void);
void			env(t_env *env);
void			export(t_command *cmd, int *exp_fd);
void			export_print(t_env *env);
void			unset(t_command *cmd, int *exp_fd);
void			echo_cmd(t_command *cmd);

#endif
