/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:44:27 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 20:21:10 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

//Ejecutamos al hijo
static void	exec_child(t_cmd *cmd, t_env *env)
{
	(void)env;
	if (!apply_redirections(cmd->redirs))
		exit(1);
	execvp(cmd->argv[0], cmd->argv);
	perror(cmd->argv[0]);
	exit(127);
}

//Esperamos al hijo y despues guardamos su estado
static void	wait_child(pid_t pid, int *last_status)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*last_status = 128 + WTERMSIG(status);
}

//Ejecutamos un comando simple
bool	execute_simple_cmd(t_cmd *cmd, t_env *env, int *last_status)
{
	pid_t	pid;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (false);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), false);
	if (pid == 0)
		exec_child(cmd, env);
	wait_child(pid, last_status);
	return (true);
}
