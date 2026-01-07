/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_base.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:57:18 by gojeda            #+#    #+#             */
/*   Updated: 2025/05/30 21:54:29 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_calculate_base_len(char *base)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
}

int	ft_validate_base_errors(char *base, int len)
{
	int	i;
	int	j;

	if (len <= 1)
		return (0);
	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j]
				|| base[j] == '+' || base[j] == '-')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_putnbr_base(int nb, char *base)
{
	long	num;
	int		base_len;

	num = nb;
	base_len = ft_calculate_base_len(base);
	if (ft_validate_base_errors(base, base_len))
	{
		if (num < 0 && base_len != 16)
		{
			num = num * -1;
			write(1, "-", 1);
		}
		if (num < base_len)
			write(1, &base[num], 1);
		else
		{
			ft_putnbr_base(num / base_len, base);
			write(1, &base[num % base_len], 1);
		}
	}
}
