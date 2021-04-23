# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hapryl <hapryl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/23 14:27:23 by hapryl            #+#    #+#              #
#    Updated: 2021/04/23 15:28:23 by hapryl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2
INCLUDES = -I./includes/*.h -I$(LFT_DIR)
FOLDER_SRCS = ./
FUNC =		commands/cd \
			commands/echo \
			commands/env \
			commands/exit \
			commands/export \
			commands/pwd \
			commands/unset \
			error/error \
			parser/command_execution \
			parser/command_search \
			parser/ft_parsing_ss \
			parser/parser_utils \
			parser/parser \
			parser/parsing_double_quotes \
			parser/parsing_redirects \
			parser/parsing_single_quotes \
			parser/parsing_space \
			parser/pipe \
			termcap/env \
			termcap/termcap \
			termcap/termcap2 \
			utils/dictionary \
			utils/dllst \
			main
SRC = $(addprefix $(FOLDER_SRCS), $(FUNC))
OBJ = $(SRC:=.o)
LXFLAGS = -ltermcap
LFT_DIR = ./libft/
LFTFLAGS = -L$(LFT_DIR) -lft

.PHONY: all clean fclean re norme lft

all: lft $(NAME)
	@echo "\033[32m[+] Make completed\033[0m"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(INCLUDES) $(LXFLAGS) $(LFTFLAGS) -lm -o $(NAME)

lft:
	@$(MAKE) -C $(LFT_DIR) --silent
	@$(MAKE) bonus -C $(LFT_DIR) --silent
	@echo  "\033[32m[+] Libft builded\033[0m"

$(OBJ): %.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) clean -C $(LFT_DIR) --silent
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) clean -C $(LX_DIR) --silent
	@$(MAKE) fclean -C $(LFT_DIR) --silent
	@rm -f $(NAME)
	@rm -f screenshot.bmp
	@rm -f libmlx.a

re: fclean all

norm: 
	@$(MAKE) norm -C $(LFT_DIR) --silent
	@norminette *.c *.h gnl/*.c gnl/*.h