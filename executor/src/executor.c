/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:44:27 by gojeda            #+#    #+#             */
/*   Updated: 2026/03/17 20:25:18 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

//Ejecutamos al hijo
static void	exec_child(t_cmd *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	setup_signals_exec();
	if (!apply_redirections(cmd->redirs))
		exit(1);
	path = get_cmd_path(cmd->argv_expanded[0], env);
	if (!path)
	{
		perror(cmd->argv_expanded[0]);
		exit(127);
	}
	envp = env_to_envp(env);
	execve(path, cmd->argv_expanded, envp);
	perror(cmd->argv_expanded[0]);
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
