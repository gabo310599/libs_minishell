/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:04:17 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/20 15:57:10 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

//Ejecutamos el comando en el hijo
void	exec_child_cmd(t_cmd *cmd, t_exec_ctx *ctx)
{
	if (is_builtin(cmd->argv_expanded[0]))
	{
		execute_builtin(cmd, &ctx->base->env, ctx->base->last_status);
		exit(*ctx->base->last_status);

	}
	execvp(cmd->argv_expanded[0], cmd->argv_expanded);
	perror(cmd->argv_expanded[0]);
	exit(127);
}

//Ejecutamos el pipe de hijo
void	exec_pipe_child(t_cmd *cmd, t_exec_ctx *ctx)
{
	setup_pipe_fds(ctx);
	close_pipe_fds(ctx);
	if (!apply_redirections(cmd->redirs))
		exit(1);
	exec_child_cmd(cmd, ctx);
}

void	restore_fds(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

// Ejecutamos builtin sin pipe (PADRE)
bool	execute_single_builtin(t_cmd *cmd, t_env **env, int *last_status)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = backup_fd(STDIN_FILENO);
	stdout_backup = backup_fd(STDOUT_FILENO);
	if (stdin_backup < 0 || stdout_backup < 0)
		return (perror("dup"), false);

	if (!apply_redirections(cmd->redirs))
	{
		restore_fd(stdin_backup, STDIN_FILENO);
		restore_fd(stdout_backup, STDOUT_FILENO);
		return (false);
	}
	execute_builtin(cmd, env, last_status);
	restore_fd(stdin_backup, STDIN_FILENO);
	restore_fd(stdout_backup, STDOUT_FILENO);
	return (true);
}
