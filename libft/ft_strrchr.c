/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:09:23 by gojeda            #+#    #+#             */
/*   Updated: 2025/04/09 16:09:24 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if ((unsigned char) c == '\0')
		return ((char *) s + s_len);
	s += s_len;
	while (s_len--)
	{
		s--;
		if (*s == (unsigned char) c)
			return ((char *) s);
	}
	return (NULL);
}
