NAME = minishell

CC = gcc

FLAGS = -Wall -Wextra -Werror 

PARSER = free_all.c get_command.c get_env.c get_envp_arr.c set_cmd_args.c \
			some_main_checks.c

UTILS = ft_strncmp.c ft_strcmp.c ft_split.c ft_split_helper.c ft_strjoin.c ft_strlen.c \
		 ft_strdup.c ft_strldup.c ft_strchr.c ft_putstr_fd.c ft_itoa.c

EXECUTOR = exec.c exec_helpers.c exec_free.c fd_duplicate.c open_file.c here_doc.c \
			close_wait.c

PROMPT = path_for_prompt.c

GNL = get_next_line.c

ERRORS_MANAGER = errors_manager.c

BUILTINS = is_builtin.c exit_cmd.c cd.c pwd.c env.c export.c export_print.c unset.c echo.c

SIGNALS = signal.c

SOURCE = main.c \
		$(addprefix parser/, $(PARSER)) \
		$(addprefix executer/, $(EXECUTOR)) \
		$(addprefix utils/, $(UTILS)) \
		$(addprefix prompt/, $(PROMPT)) \
		$(addprefix gnl/, $(GNL)) \
		$(addprefix errors_manager/, $(ERRORS_MANAGER)) \
		$(addprefix builtins/, $(BUILTINS)) \
		$(SIGNALS)

OBJECT = $(SOURCE:.c=.o)

HEADER = minishell.h

all: $(NAME)

$(NAME): $(OBJECT) $(HEADER)
	$(CC) $(FLAGS) $(OBJECT) -lreadline -lcurses -o $(NAME)

%.o:%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)

re: fclean all
