/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:40:17 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 21:37:29 by gojeda           ###   ########.fr       */
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