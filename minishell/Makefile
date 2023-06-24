NAME= minishell
CFLAGS= -Wall -Wextra -Werror -fsanitize=address -g3
CC= cc
ReadLine = -lreadline  -L /Users/oait-bad/Desktop/readline-8.2 -I/Users/oait-bad/Desktop/readline-8.2 -lcurses

SRC= minishell.c lexer/lexer.c lexer/check_tokens.c parser/expand.c parser/parser.c parser/parser_utils.c parser/handle_quotes.c libft/ft_strlen.c libft/ft_strdup.c libft/ft_substr.c libft/ft_strncmp.c \
		libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_split.c libft/ft_strchr.c libft/ft_strnstr.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putchar_fd.c \
		libft/ft_strtrim.c libft/ft_lstadd_back.c libft/ft_lstnew.c builtin/builtin_cd_pwd.c builtin/builtin_echo.c builtin/builtin_env.c builtin/builtin_export.c builtin/builtin_unset.c \
		builtin/builtin_utilis_2.c builtin/builtin_utilis.c get_next_line/get_next_line_utilis.c get_next_line/get_next_line.c execution/check_single_cmd.c execution/exec_single_cmd.c \
		execution/single_cmd.c execution/multi_pipe.c \


OBJ= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(ReadLine) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re