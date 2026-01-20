/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:52:38 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/20 12:03:34 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

//Inicializamos el contexto de ejecución
static void	init_exec_ctx(
	t_exec_ctx *ctx,
	t_exec_base *base,
	int prev_fd,
	bool has_next
)
{
	ctx->base = base;
	ctx->prev_fd = prev_fd;
	ctx->has_next = has_next;
}

// Fork + ejecución del hijo
static bool	fork_and_exec(t_cmd *cmd, t_exec_ctx *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), false);
	if (pid == 0)
	{
		setup_signals_exec();
		exec_pipe_child(cmd, ctx);
	}
	return (true);
}

// Limpieza del padre tras fork
static void	parent_after_fork(t_exec_ctx *ctx, int *prev_fd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (ctx->has_next)
	{
		close(ctx->fd[1]);
		*prev_fd = ctx->fd[0];
	}
	else
		*prev_fd = -1;
}

// Esperamos a todos los hijos
static void	wait_all_children(int *last_status)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			*last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*last_status = 128 + WTERMSIG(status);
	}
}


//Funcion principal
bool	execute_pipeline(t_pipeline *p, t_env *env, int *last_status)
{
	int			i;
	int			prev_fd;
	t_exec_ctx	ctx;
	t_exec_base	base;

	if (!p || p->count == 0)
		return (false);
	if (p->count == 1)
		return (execute_no_pipe(p, env, last_status));
	base.env = env;
	base.last_status = last_status;
	prev_fd = -1;
	i = 0;
	while (i < p->count)
	{
		if (!create_pipe_if_needed(i, p->count, ctx.fd))
			return (false);
		init_exec_ctx(&ctx, &base, prev_fd, i < p->count - 1);
		if (!fork_and_exec(p->cmds[i], &ctx))
			return (false);
		parent_after_fork(&ctx, &prev_fd);
		i++;
	}
	wait_all_children(last_status);
	return (true);
}
