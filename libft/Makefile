# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/11 15:22:53 by giodos-s          #+#    #+#              #
#    Updated: 2025/11/08 20:33:13 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#                                   LIBFT                                      #
# **************************************************************************** #

NAME        = libft.a
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
INCLUDES    = -I includes
AR          = ar -rcs
RM          = rm -f

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

PART1 = part1/ft_atoi.c \
	part1/ft_bzero.c \
	part1/ft_calloc.c \
	part1/ft_isalnum.c \
	part1/ft_isalpha.c \
	part1/ft_isascii.c \
	part1/ft_isdigit.c \
	part1/ft_isprint.c \
	part1/ft_itoa.c \
	part1/ft_memchr.c \
	part1/ft_memcmp.c \
	part1/ft_memcpy.c \
	part1/ft_memmove.c \
	part1/ft_strdup.c 

PART2 = part2/ft_memset.c \
	part2/ft_putchar_fd.c \
	part2/ft_putendl_fd.c \
	part2/ft_putnbr_fd.c \
	part2/ft_putstr_fd.c \
	part2/ft_split.c \
	part2/ft_striteri.c \
	part2/ft_strjoin.c \
	part2/ft_strlcat.c \
	part2/ft_strlcpy.c \
	part2/ft_strlen.c \
	part2/ft_strmapi.c \
	part2/ft_strncmp.c \
	part2/ft_strnstr.c \
	part2/ft_strchr.c \
	part2/ft_strrchr.c \
	part2/ft_strtrim.c \
	part2/ft_substr.c \
	part2/ft_tolower.c \
	part2/ft_toupper.c

PRINTF = printf/src/ft_libft_utils.c \
	printf/src/ft_list_utils.c \
	printf/src/ft_node_utils.c \
	printf/src/ft_numb_utils.c \
	printf/src/ft_printf.c

PRINTF_BONUS = printf/bonus/ft_apply_flags_bonus.c \
	printf/bonus/ft_apply_precision_bonus.c \
	printf/bonus/ft_apply_width_bonus.c \
	printf/bonus/ft_dispatcher_bonus.c \
	printf/bonus/ft_parse_format_bonus.c \
	printf/bonus/ft_printf_bonus.c \
	printf/bonus/ft_put_str_bonus.c \
	printf/bonus/ft_utils_bonus.c

LIBFT_BONUS_SRC = bonus/ft_lstnew_bonus.c \
	bonus/ft_lstadd_front_bonus.c \
	bonus/ft_lstsize_bonus.c \
	bonus/ft_lstlast_bonus.c \
	bonus/ft_lstadd_back_bonus.c \
	bonus/ft_lstdelone_bonus.c \
	bonus/ft_lstclear_bonus.c \
	bonus/ft_lstiter_bonus.c \
	bonus/ft_lstmap_bonus.c

# **************************************************************************** #
#                                   OBJECTS                                    #
# **************************************************************************** #

OBJS            = $(PART1:.c=.o) $(PART2:.c=.o) $(PRINTF:.c=.o)
BONUS_OBJS      = $(LIBFT_BONUS_SRC:.c=.o) $(PRINTF_BONUS:.c=.o)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "\033[1;32m✅ libft.a created successfully!\033[0m"

bonus: $(OBJS) $(BONUS_OBJS)
	@$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "\033[1;36m✨ libft.a bonus compiled!\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@echo "\033[1;33m🧹 Object files removed.\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[1;31m🗑️  libft.a removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re bonus

