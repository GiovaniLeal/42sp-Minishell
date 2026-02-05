/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:59:30 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/11 18:59:30 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/* --- LIBRARIES [ARGS - MALLOC - WRITE] --- */
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <libft.h>

/*************** BASE DEFINE ***************/
# define BASE_DEC      "0123456789"
# define BASE_HEX      "0123456789abcdef"
# define BASE_HEX_UPP  "0123456789ABCDEF"

/*************** NODE/LIST STRUCT ***************/
typedef struct s_node
{
	char			*str_content;
	size_t			len;
	struct s_node	*next;
}	t_node;

/*************** FT_PRINTF ***************/
int			ft_printf(const char *format, ...);

/*************** PUT FUNCTIONS ***************/
char		*ft_put_num(const char specifier, long long numb);
char		*ft_put_hex(const char specifier, unsigned int number);
char		*ft_put_ptr(void *ptr);
char		*ft_put_char_generic(char c);
char		*ft_put_str_generic(const char *str, int do_alloc);

/*************** LIST FUNCTIONS ***************/
void		ft_list_clear(t_node **head);
void		ft_list_append(t_node **head, t_node *node);
void		ft_add_literal_node(t_node **head, const char *start, size_t len);
t_node		*ft_node_create(const char *str, size_t len);

/*************** LIB UTILS ***************/

//char		*ft_strdup(const char *s);
char		*ft_itoa_base(long long value, const char *base);
char		*ft_utoa_base(unsigned long long value, const char *base);
void		*ft_memcpy(void *dest, const void *src, size_t n);
#endif