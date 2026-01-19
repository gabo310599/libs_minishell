/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 21:15:41 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 21:20:54 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

//Detectamos si esta la opcion -n
static bool	is_n_flag(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] != 'n')
		return (false);
	i = 1;
	while (s[i] == 'n')
		i++;
	return (s[i] == '\0');
}

//Imprimimos los argumentos
static void	print_echo_args(char **argv, int start)
{
	int	i;

	i = start;
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
}

//Ejecutamos echo
bool	builtin_echo(t_cmd *cmd, int *last_status)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	while (cmd->argv[i] && is_n_flag(cmd->argv[i]))
	{
		newline = false;
		i++;
	}
	print_echo_args(cmd->argv, i);
	if (newline)
		write(1, "\n", 1);
	*last_status = 0;
	return (true);
}
