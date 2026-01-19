/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 10:37:39 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 13:57:49 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../../minishell.h"
# include "../../env/includes/env.h"

//Expandir segmentos
char	*expand_env_var(const char *s, size_t *i, t_env *env);
char	*expand_dollar(const char *s, size_t *i, t_env *env, int last_status);
char	*expand_segment(t_segment *seg, t_env *env, int last_status);

//Expandir token
char	*expand_token(t_token *tok, t_env *env, int last_status);
char	**expand_cmd(t_cmd *cmd, t_env *env, int last_status);

//Expandir redirecciones
bool	expand_redirs(t_redir *redirs, t_expand_ctx *ctx);

//Expandir pipeline
bool	expand_pipeline(t_pipeline *p, t_env *env, int last_status);

//Utils
void	free_argv(char **argv);
char	*token_to_literal(t_token *tok);

#endif