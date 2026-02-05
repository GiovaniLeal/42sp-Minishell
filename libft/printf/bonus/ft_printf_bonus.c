/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giodos-s <giodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:32:26 by giodos-s          #+#    #+#             */
/*   Updated: 2025/09/13 11:25:00 by giodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include "ft_printf.h"

/* *************************************************************** */
/*   Add a formatted node with debug                                 */
/*   - Parse format (flags, width, precision, specifier)             */
/*   - Generate formatted string                                     */
/*   - Create node and append to linked list                         */
/*   - Prints debug info to track string, length and memory address  */
/* *************************************************************** */
static void	ft_add_formatted_bonus(t_node **list_head,
			const char **format_ptr, va_list args)
{
	t_fmt	format_info;
	t_node	*new_node;
	char	*formatted_str;
	size_t	str_len;

	formatted_str = NULL;
	ft_bzero(&format_info, sizeof(t_fmt));
	ft_parse_format_bonus(format_ptr, &format_info, args);
	formatted_str = ft_dispatcher_bonus(&format_info, args);
	if (format_info.specifier == 'c' && formatted_str[0] == '\0')
		str_len = 1;
	else if (format_info.specifier == '%')
		str_len = 1;
	else
		str_len = ft_strlen(formatted_str);
	new_node = ft_node_create(formatted_str, str_len);
	if (new_node)
	{
		ft_list_append(list_head, new_node);
		free(formatted_str);
	}
}

/* *************************************************************** */
/*   Parse format string and build linked list                     */
/*   - Handles literal strings                                     */
/*   - Handles '%' specifiers and formatted output                 */
/* *************************************************************** */
static t_node	*ft_list_parser_bonus(const char *format, va_list args)
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
			ft_add_formatted_bonus(&list_head, &format, args);
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
/*   ft_printf_bonus                                               */
/*   - Parses format string with bonus features                    */
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
	list_head = ft_list_parser_bonus(format, args);
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
