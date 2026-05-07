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
CFLAGS      := -Wall -Wextra -Werror -g3
INC_DIR     := includes
LEXER_DIR   := lexer
PARSING_DIR := parsing
EXECUTION_DIR := execution
REDIRS_DIR := redirs
ENVIRONMENT_DIR := environment
EXPANDER_DIR := expander
BUILTINS_DIR := builtins
UTILS_DIR := utils
SRC_DIR := src

# **************************************************************************** #
#                                   LIBFT                                      #
# **************************************************************************** #
LIBFT_DIR   := libft
LIBFT_INC   := $(LIBFT_DIR)/includes
LIBFT       := $(LIBFT_DIR)/libft.a
INCLUDES    := -I$(INC_DIR) -I$(LIBFT_INC)
SRC         := $(SRC_DIR)

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #
SRC :=  main.c \
	signals.c \
	$(SRC)/$(LEXER_DIR)/lexer.c \
	$(SRC)/$(LEXER_DIR)/lexer_list.c \
	$(SRC)/$(LEXER_DIR)/lexer_utils.c \
	$(SRC)/$(PARSING_DIR)/parsing.c \
	$(SRC)/$(PARSING_DIR)/parsing_utils.c \
	$(SRC)/$(PARSING_DIR)/parsing_free.c \
	$(SRC)/$(EXECUTION_DIR)/exec_ast.c \
	$(SRC)/$(EXECUTION_DIR)/exec_pipes.c \
	$(SRC)/$(EXECUTION_DIR)/exec.c \
	$(SRC)/$(EXECUTION_DIR)/path.c \
	$(SRC)/$(REDIRS_DIR)/redir.c \
	$(SRC)/$(REDIRS_DIR)/heredoc_utils.c \
	$(SRC)/$(REDIRS_DIR)/heredoc.c \
	$(SRC)/$(UTILS_DIR)/free.c \
	$(SRC)/$(ENVIRONMENT_DIR)/environment.c \
	$(SRC)/$(ENVIRONMENT_DIR)/environment_utils.c \
	$(SRC)/$(BUILTINS_DIR)/builtins.c \
	$(SRC)/$(BUILTINS_DIR)/exit.c \
	$(SRC)/$(BUILTINS_DIR)/echo.c \
	$(SRC)/$(BUILTINS_DIR)/pwd.c \
	$(SRC)/$(BUILTINS_DIR)/cd.c \
	$(SRC)/$(BUILTINS_DIR)/env.c \
	$(SRC)/$(BUILTINS_DIR)/export.c \
	$(SRC)/$(BUILTINS_DIR)/export_display.c \
	$(SRC)/$(BUILTINS_DIR)/unset.c \
	$(SRC)/$(UTILS_DIR)/ft_atol_safe.c \
	$(SRC)/$(UTILS_DIR)/error.c \
	$(SRC)/$(EXPANDER_DIR)/expand_utils.c \
 	$(SRC)/$(EXPANDER_DIR)/expand.c \
 	

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
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=readline/readline.sup ./minishell
.PHONY: all clean fclean re banner