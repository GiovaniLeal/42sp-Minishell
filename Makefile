# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/05 17:36:48 by giodos-s          #+#    #+#              #
#    Updated: 2026/02/05 17:36:48 by giodos-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME        := minishell
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -O3

INC_DIR     := includes
LEXER_DIR   := lexer
PARSING_DIR := parsing
EXECUTION_DIR := execution
REDIRS_DIR := redirs
ENVIRONMENT_DIR := environment
EXPANDER_DIR := expander
BUILTINS_DIR := builtins
UTILS_DIR := utils

# **************************************************************************** #
#                                   LIBFT                                      #
# **************************************************************************** #
LIBFT_DIR   := libft
LIBFT_INC   := $(LIBFT_DIR)/includes
LIBFT       := $(LIBFT_DIR)/libft.a
INCLUDES    := -I$(INC_DIR) -I$(LIBFT_INC)

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #
SRC :=  main.c \
	signals.c \
	$(LEXER_DIR)/lexer.c \
	$(LEXER_DIR)/lexer_list.c \
	$(LEXER_DIR)/lexer_utils.c \
	$(LEXER_DIR)/lexer_tester.c \
	$(PARSING_DIR)/parsing.c \
	$(PARSING_DIR)/parsing_utils.c \
	$(PARSING_DIR)/parsing_free.c \
	$(PARSING_DIR)/parsing_tester.c \
	$(EXECUTION_DIR)/exec_ast.c \
	$(EXECUTION_DIR)/exec_pipes.c \
	$(EXECUTION_DIR)/exec.c \
	$(EXECUTION_DIR)/path.c \
	$(REDIRS_DIR)/redir.c \
	$(UTILS_DIR)/free.c \
	$(ENVIRONMENT_DIR)/environment.c \
	$(ENVIRONMENT_DIR)/environment_utils.c \
	$(BUILTINS_DIR)/builtins.c \
	$(BUILTINS_DIR)/exit.c \
	$(BUILTINS_DIR)/echo.c \
	$(BUILTINS_DIR)/pwd.c \
	$(BUILTINS_DIR)/cd.c \
	$(BUILTINS_DIR)/env.c \
	$(BUILTINS_DIR)/export.c \
	$(BUILTINS_DIR)/export_display.c \
	$(UTILS_DIR)/ft_atol_safe.c \
	$(UTILS_DIR)/error.c \
 	$(EXPANDER_DIR)/expand.c \
 	$(EXPANDER_DIR)/expand_utils.c

OBJS := $(SRC:.c=.o)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #
all: banner $(NAME)

banner:
	@printf "\033[1;34m////////////////////////////////////////////////////////////\n"; \
	printf "//                                                        //\n"; \
	printf "//   __  __ ___ _   _ ___ ____  _   _ _____ _     _       //\n"; \
	printf "//  |  \\/  |_ _| \\ | |_ _/ ___|| | | | ____| |   | |      //\n"; \
	printf "//  | |\\/| || ||  \\| || |\\___ \\| |_| |  _| | |   | |      //\n"; \
	printf "//  | |  | || || |\\  || | ___) |  _  | |___| |___| |___   //\n"; \
	printf "//  |_|  |_|___|_| \\_|___|____/|_| |_|_____|_____|_____|  //\n"; \
	printf "//                                                        //\n"; \
	printf "////////////////////////////////////////////////////////////\n"; \
	printf "\033[0m\n"

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lncurses -o $(NAME)
	@echo "\033[1;32m✅ minishell created successfully!\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

val:
	@valgrind -q\
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--track-fds=yes \
		--trace-children=yes \
		--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
		--suppressions=./valgrind.supp \
		./$(NAME)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "\033[1;33mObjects removed.\033[0m"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "\033[1;31mBinary removed.\033[0m"

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=readline.sup ./minishell

.PHONY: all clean fclean re banner