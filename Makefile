NAME	=	minishell
CC		=	cc
CFLAGS	=	-Werror -Wextra -Wall
LIBFT	=	./libft/libft.a

SRCS	=	minishell.c													\
			./utils/execution/exec.c									\
			./utils/parsing/custom_split.c								\
			./utils/parsing/arr_utils.c									\
			./utils/parsing/parsing.c									\
			./utils/parsing/quotes.c									\
			./utils/parsing/check_errors.c								\
			./utils/parsing/redirections.c								\
			./utils/parsing/overwrite_env.c								\
			./utils/execution/exec.c									\
			./utils/execution/execute_cmd.c								\
			./utils/execution/handle_redirection.c						\
			./utils/execution/get_path_cmd.c 							\
			./utils/execution/ft_pathjoin.c								\
			./utils/execution/builtins/check_builtins.c					\
			./utils/execution/builtins/echo.c							\
			./utils/execution/builtins/pwd.c							\
			./utils/execution/builtins/cd.c								\
			./utils/execution/handle_out_in_of_pipe.c					\
			./utils/execution/create_env.c 								\
			./utils/execution/builtins/env.c							\
			./utils/execution/builtins/export.c							\
			./utils/execution/builtins/unset.c							\
			./utils/execution/compare.c									\
			./utils/execution/env_struct_to_array.c						\
			./utils/parsing/replace_dollar/replace.c					\
			./utils/execution/heredoc.c									\
			./utils/execution/insert_delete_line_from_array2d.c			\
			./utils/execution/GetNextLine/get_next_line_utils.c			\
			./utils/execution/GetNextLine/get_next_line.c				\
			./utils/parsing/fix_redirection.c							\
			./utils/execution/execute_cmd_utils.c						\
			./utils/parsing/exit.c										\
			./utils/execution/builtins/export_utils.c					\
			./utils/execution/handle_redirection_utils.c				\
			./utils/execution/replace_dollar_sign_heredoc.c				\
			./utils/execution/builtins/exit.c							\
			./utils/parsing/replace_dollar/replace.utils.c				\

OBJS	=	$(SRCS:.c=.o)

$(NAME): $(OBJS)
	@printf "\033[1;36m Compiling \033[0m LIBFT \033[1;36m√\033[0m\n"
	@$(MAKE) -s bonus -C ./libft
	@$(CC) $(CFLAGS) $(LIBFT) -L$(shell brew --prefix readline)/lib -lreadline $^ -o $(NAME)
	@$(MAKE) -s clean -C ./libft
	@printf "\n\033[1;36m ───────────── Done ──────────── \033[0m\n\n"

%.o: %.c minishell.h
	@$(CC) $(CFLAGS) -c -I$(shell brew --prefix readline)/include $< -o $@
	@printf "\033[1;36m Compiling \033[0m $< \033[1;36m√\033[0m\n"

all: $(NAME)

clean:
	@$(MAKE) -s clean -C ./libft
	@rm -rf $(OBJS)

fclean: clean
	@$(MAKE) -s fclean -C ./libft
	@rm -rf $(NAME)

re: fclean all