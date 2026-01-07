/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:32:37 by gojeda            #+#    #+#             */
/*   Updated: 2025/05/30 21:54:16 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned long n)
{
	int		count;
	char	*base;

	base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count += ft_puthex(n / 16);
	count += ft_putchar(base[n % 16]);
	return (count);
}

int	ft_count_hex_digits(unsigned int n)
{
	int	count;

	count = 1;
	while (n >= 16)
	{
		n /= 16;
		count++;
	}
	return (count);
}

void	ft_putnbr_base_unsigned(unsigned int num, char *base)
{
	unsigned int	base_len;

	base_len = ft_calculate_base_len(base);
	if (ft_validate_base_errors(base, base_len))
	{
		if (num < base_len)
			write(1, &base[num], 1);
		else
		{
			ft_putnbr_base_unsigned(num / base_len, base);
			write(1, &base[num % base_len], 1);
		}
	}
}
