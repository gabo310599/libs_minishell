/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 21:22:49 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 21:26:01 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

//Comprobamos si el numero es valido
static bool	is_numeric(char *s)
{
	int	i;

	if (!s || !*s)
		return (false);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (false);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

//Convertimos a exit status (mod 256)
static int	exit_status_from_str(char *s)
{
	long	n;

	n = ft_atol(s);
	return ((unsigned char)n);
}

//Ejecutamos exit
bool	builtin_exit(t_cmd *cmd, int *last_status)
{
	write(2, "exit\n", 5);
	if (!cmd->argv[1])
		exit(*last_status);
	if (!is_numeric(cmd->argv[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
		write(2, ": numeric argument required\n", 28);
		exit(255);
	}
	if (cmd->argv[2])
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		*last_status = 1;
		return (false);
	}
	exit(exit_status_from_str(cmd->argv[1]));
}
