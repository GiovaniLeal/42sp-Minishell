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

SRC_DIR     := src
INC_DIR     := includes

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

SRCS := $(addprefix $(SRC_DIR)/, $(SRC))
OBJS := $(SRCS:.c=.o)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)


clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[1;33m🧹 Objects removed.\033[0m"

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[1;31m🗑️  Binary removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re