/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:48:10 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 20:29:16 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

//Detectamos si es un builtin
bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	return (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

//Dispatcher del builtin
bool	execute_builtin(t_cmd *cmd, t_env **env, int *last_status)
{
	char	*name;

	name = cmd->argv[0];
	if (!ft_strcmp(name, "echo"))
		return (builtin_echo(cmd, last_status));
	if (!ft_strcmp(name, "pwd"))
		return (builtin_pwd(last_status));
	if (!ft_strcmp(name, "cd"))
		return (builtin_cd(cmd, env, last_status));
	if (!ft_strcmp(name, "export"))
		return (builtin_export(cmd, env, last_status));
	if (!ft_strcmp(name, "unset"))
		return (builtin_unset(cmd, env, last_status));
	if (!ft_strcmp(name, "env"))
		return (builtin_env(cmd, *env, last_status));
	if (!ft_strcmp(name, "exit"))
		return (builtin_exit(cmd, last_status));
	return (false);
}
