/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 19:20:51 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/11 19:20:51 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* ************************************************************************** */
/*  Dispatcher                                                                */
/* - Select and convert argument to string based on specifier                 */
/* ************************************************************************** */
static char	*ft_dispatcher(const char *format, va_list args)
{
	if (*format == 'c')
		return (ft_put_char_generic((char)va_arg(args, int)));
	else if (*format == '%')
		return (ft_put_char_generic('%'));
	else if (*format == 's')
		return (ft_put_str_generic(va_arg(args, char *), 1));
	else if (*format == 'd' || *format == 'i')
		return (ft_put_num(*format, va_arg(args, int)));
	else if (*format == 'u')
		return (ft_put_num(*format, va_arg(args, unsigned int)));
	else if (*format == 'x' || *format == 'X')
		return (ft_put_hex(*format, va_arg(args, unsigned int)));
	else if (*format == 'p')
		return (ft_put_ptr(va_arg(args, void *)));
	return (NULL);
}

/* *************************************************************** */
/*   Add a formatted node                                          */
/*   - Dispatch specifier                                          */
/*   - Create node and append to linked list                       */
/* *************************************************************** */
static void	ft_add_formatted(t_node **list_head,
			const char **format_ptr, va_list args)
{
	t_node	*new_node;
	char	*formatted_str;
	size_t	str_len;

	formatted_str = ft_dispatcher(*format_ptr, args);
	if (!formatted_str)
		return ;
	if (*format_ptr[0] == 'c' && formatted_str[0] == '\0')
		str_len = 1;
	else
		str_len = ft_strlen(formatted_str);
	new_node = ft_node_create(formatted_str, str_len);
	if (new_node)
		ft_list_append(list_head, new_node);
	free(formatted_str);
	(*format_ptr)++;
}

/* *************************************************************** */
/*   Parse format string and build linked list                     */
/*   - Handles literal strings                                     */
/*   - Handles '%' specifiers and formatted output                 */
/* *************************************************************** */
static t_node	*ft_list_parser(const char *format, va_list args)
{
	t_node		*list_head;
	const char	*segment_start;

	list_head = NULL;
	segment_start = format;
	while (*format)
	{
		if (*format == '%')
		{
			if (segment_start < format)
				ft_add_literal_node(&list_head, segment_start,
					format - segment_start);
			format++;
			ft_add_formatted(&list_head, &format, args);
			segment_start = format;
		}
		else
			format++;
	}
	if (segment_start < format)
		ft_add_literal_node(&list_head, segment_start, format - segment_start);
	return (list_head);
}

/* *************************************************************** */
/*   ft_printf                                                     */
/*   - Parses format string                                        */
/*   - Builds a linked list of nodes                               */
/*   - Writes final output to stdout                               */
/* *************************************************************** */
int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_node	*list_head;
	t_node	*current;
	int		total_len;

	if (!format)
		return (0);
	total_len = 0;
	va_start(args, format);
	list_head = ft_list_parser(format, args);
	va_end(args);
	current = list_head;
	while (current)
	{
		total_len += write(1, current->str_content, current->len);
		current = current->next;
	}
	ft_list_clear(&list_head);
	return (total_len);
}
