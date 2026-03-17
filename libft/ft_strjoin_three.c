/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 20:57:48 by gojeda            #+#    #+#             */
/*   Updated: 2026/03/17 20:59:28 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len3;
	size_t	total_len;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	total_len = len1 + len2 + len3 + 1;
	result = malloc(total_len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, total_len);
	ft_strlcat(result, s2, total_len);
	ft_strlcat(result, s3, total_len);
	return (result);
}
