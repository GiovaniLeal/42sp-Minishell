/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:15:52 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/11 19:15:52 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include "ft_printf.h"

/* -------------------- FLAGS BITMASK -------------------- */
# define FLAG_MINUS  1
# define FLAG_PLUS   2
# define FLAG_SPACE  4
# define FLAG_HASH   8
# define FLAG_ZERO   16

/* -------------------- FORMAT STRUCT -------------------- */
typedef struct s_fmt
{
	int		flags;
	int		width;
	int		precision;
	int		precision_specified;
	char	specifier;
}	t_fmt;

/* -------------------- PRINTF BONUS -------------------- */
int		ft_printf(const char *format, ...);
char	*ft_dispatcher_bonus(t_fmt *fmt, va_list args);
void	ft_parse_format_bonus(const char **format_ptr,
			t_fmt *f, va_list args);

/* -------------------- APPLY FORMAT -------------------- */
char	*ft_apply_width_bonus(char *orig_str, t_fmt *fmt);
char	*ft_apply_precision_num(char *num_str, t_fmt *fmt);
char	*ft_apply_precision_ptr(char *ptr_str, t_fmt *fmt);
char	*ft_apply_precision_str(char *str, t_fmt *fmt);
char	*ft_apply_flags_bonus(char *str, t_fmt *fmt);

/* -------------------- UTILS -------------------- */
char	*ft_put_str_printf(const char *str);
char	*ft_put_char_printf(char c, int is_percent);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin_free(char *s1, const char *s2);
void	*ft_memset(void *b, int c, size_t len);

#endif
