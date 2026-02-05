/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:02:07 by giodos-s          #+#    #+#             */
/*   Updated: 2025/11/08 20:30:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>

int			ft_isalpha(int c);
int			ft_isdigit( int digit);
int			ft_isalnum(int character);
int			ft_isascii(int character);
int			ft_isprint(int c);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_atoi(const char *str);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_itoa(int n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s, char const *set);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		**ft_split(char const *s, char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memchr( const void *s, int c, size_t n);
void		*ft_memset(void *buffer, int value, size_t size);
void		*ft_bzero(void *s, size_t n);
void		*ft_striteri(char *s, void (*f)(unsigned int, char*));
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
/* ************************************************************************** */
/*           	         BONUS PART				        */
/* ************************************************************************** */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list		*ft_lstnew_bonus(void *content);
t_list		*ft_lstlast_bonus(t_list *lst);
t_list		*ft_lstmap_bonus(t_list *lst,
				void *(*f)(void *), void (*del)(void *));
void		ft_lstadd_front_bonus(t_list **lst, t_list *new);
void		ft_lstadd_back_bonus(t_list **lst, t_list *new);
void		ft_lstdelone_bonus(t_list *lst, void (*del)(void*));
void		ft_lstclear_bonus(t_list **lst, void (*del)(void*));
void		ft_lstiter_bonus(t_list *lst, void (*f)(void *));
int			ft_lstsize_bonus(t_list *lst);

#endif