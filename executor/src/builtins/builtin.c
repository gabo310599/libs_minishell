/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:48:10 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/20 13:18:05 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

//Detectamos si es un builtin
bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp(cmd, "echo", 5))
		return (true);
	if (!ft_strncmp(cmd, "cd", 3))
		return (true);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (true);
	if (!ft_strncmp(cmd, "export", 7))
		return (true);
	if (!ft_strncmp(cmd, "unset", 6))
		return (true);
	if (!ft_strncmp(cmd, "env", 4))
		return (true);
	if (!ft_strncmp(cmd, "exit", 5))
		return (true);
	return (false);
}

//Dispatcher del builtin
bool	execute_builtin(t_cmd *cmd, t_env **env, int *last_status)
{
	char	*name;

	name = cmd->argv_expanded[0];
	if (!name)
		return (false);
	if (!ft_strncmp(name, "echo", 5))
		return (builtin_echo(cmd, last_status));
	if (!ft_strncmp(name, "pwd", 4))
		return (builtin_pwd(last_status));
	if (!ft_strncmp(name, "cd", 3))
		return (builtin_cd(cmd, env, last_status));
	if (!ft_strncmp(name, "export", 7))
		return (builtin_export(cmd, env, last_status));
	if (!ft_strncmp(name, "unset", 6))
		return (builtin_unset(cmd, env, last_status));
	if (!ft_strncmp(name, "env", 4))
		return (builtin_env(cmd, *env, last_status));
	if (!ft_strncmp(name, "exit", 5))
		return (builtin_exit(cmd, last_status));
	return (false);
}
