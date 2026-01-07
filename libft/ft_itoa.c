/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:28:44 by gojeda            #+#    #+#             */
/*   Updated: 2025/04/11 14:28:46 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_len_num(long n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
	{
		n = -n;
		count++;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str_num;
	size_t	size;
	long	nb;

	nb = n;
	size = count_len_num(nb);
	str_num = (char *) malloc((size + 1) * sizeof(char));
	if (!str_num)
		return (NULL);
	str_num[size] = '\0';
	if (nb == 0)
		str_num[0] = '0';
	else if (nb < 0)
	{
		nb = -nb;
		str_num[0] = '-';
	}
	while (nb > 0)
	{
		str_num[--size] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str_num);
}
