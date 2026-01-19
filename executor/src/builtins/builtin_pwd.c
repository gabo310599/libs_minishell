/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 21:27:47 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 21:29:29 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

//Ejecutamos pwd
bool	builtin_pwd(int *last_status)
{
	char	buf[4096];

	if (!getcwd(buf, sizeof(buf)))
	{
		perror("pwd");
		*last_status = 1;
		return (false);
	}
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	*last_status = 0;
	return (true);
}
