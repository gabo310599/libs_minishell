/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:40:17 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/20 15:48:04 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../../minishell.h"
# include "../../env/includes/env.h"

//Executor
bool	execute_pipeline(t_pipeline *p, t_env *env, int *last_status);
bool	apply_redirections(t_redir *r);
bool	execute_simple_cmd(t_cmd *cmd, t_env *env, int *last_status);
int		backup_fd(int fd);
void	restore_fd(int backup, int target);

//Pipelines
bool	execute_single_builtin(t_cmd *cmd, t_env **env, int *last_status);
bool	execute_no_pipe(t_pipeline *p, t_env *env, int *last_status);
bool	create_pipe_if_needed(int i, int count, int fd[2]);
void	setup_pipe_fds(t_exec_ctx *ctx);
void	close_pipe_fds(t_exec_ctx *ctx);
void	exec_child_cmd(t_cmd *cmd, t_exec_ctx *ctx);
void	exec_pipe_child(t_cmd *cmd, t_exec_ctx *ctx);

//Builtins
bool	is_builtin(char *cmd);
bool	execute_builtin(t_cmd *cmd, t_env **env, int *last_status);
bool	builtin_cd(t_cmd *cmd, t_env **env, int *last_status);
bool	builtin_export(t_cmd *cmd, t_env **env, int *last_status);
bool	builtin_unset(t_cmd *cmd, t_env **env, int *last_status);
bool	builtin_echo(t_cmd *cmd, int *last_status);
bool	builtin_exit(t_cmd *cmd, int *last_status);
bool	builtin_pwd(int *last_status);
bool	builtin_env(t_cmd *cmd, t_env *env, int *last_status);

#endif