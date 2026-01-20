/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:08:35 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/20 14:08:29 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

//Ejecutamos sin pipe
bool	execute_no_pipe(t_pipeline *p, t_env *env, int *last_status)
{
	t_cmd	*cmd;

	cmd = p->cmds[0];
	if (is_builtin(cmd->argv_expanded[0]))
		return (execute_single_builtin(cmd, &env, last_status));
	return (execute_simple_cmd(cmd, env, last_status));
}

//Creamos pipe si hace falta
bool	create_pipe_if_needed(int i, int count, int fd[2])
{
	if (i < count - 1)
	{
		if (pipe(fd) < 0)
			return (perror("pipe"), false);
	}
	return (true);
}

//Redirecciones de entrada y salida
void	setup_pipe_fds(t_exec_ctx *ctx)
{
	if (ctx->prev_fd != -1)
		dup2(ctx->prev_fd, STDIN_FILENO);
	if (ctx->has_next)
		dup2(ctx->fd[1], STDOUT_FILENO);
}

//Cerramos descriptores
void	close_pipe_fds(t_exec_ctx *ctx)
{
	if (ctx->prev_fd != -1)
		close(ctx->prev_fd);
	if (ctx->has_next)
	{
		close(ctx->fd[0]);
		close(ctx->fd[1]);
	}
}
