/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:51:43 by gojeda            #+#    #+#             */
/*   Updated: 2025/05/30 21:53:53 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_validate_format(char c)
{
	return (c && (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
			|| c == 'u' || c == 'x' || c == 'X' || c == '%'));
}

static int	ft_control_hex(char c, va_list args)
{
	unsigned int	num;

	num = va_arg(args, unsigned int);
	if (c == 'x')
		ft_putnbr_base_unsigned(num, "0123456789abcdef");
	else
		ft_putnbr_base_unsigned(num, "0123456789ABCDEF");
	return (ft_count_hex_digits(num));
}

static int	ft_control_format(char c, va_list args)
{
	int	num;

	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
	{
		num = va_arg(args, int);
		ft_putnbr_base(num, "0123456789");
		return (ft_count_digits(num));
	}
	else if (c == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int)));
	else if (c == 'X' || c == 'x')
		return (ft_control_hex(c, args));
	else if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && ft_validate_format(format[i + 1]))
			count += ft_control_format(format[++i], args);
		else if (format[i] == '%')
			return (-1);
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
