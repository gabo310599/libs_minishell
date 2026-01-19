/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:21:58 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 10:47:16 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../minishell.h"

//Funciones principales del parser
t_pipeline	*parse_tokens(t_token *tokens);

//Funciones auxiliares
t_cmd		*cmd_new(void);
bool		cmd_add_arg(t_cmd *cmd, t_token *word);
t_redir		*redir_new(t_redir_type type, t_token *target);
bool		cmd_add_redir(t_cmd *cmd, t_redir *redir);
t_pipeline	*pipeline_new(void);
bool		pipeline_add_cmd(t_pipeline *p, t_cmd *cmd);
bool		is_redir(t_token_type type);
bool		finalize_cmd(t_pipeline *p, t_cmd **cmd);
bool		start_cmd_if_needed(t_cmd **cmd);

//Funciones handlers
bool		parse_word(t_pipeline *p, t_cmd **cmd, t_token *tok);
bool		parse_pipe(t_pipeline *p, t_cmd **cmd);
bool		parse_redir(t_cmd *cmd, t_token **tok);
bool		dispatch_token(t_pipeline *p, t_cmd **cmd, t_token **tok);

//Funciones para liberar memoria del parser
void		free_all(t_pipeline *p, t_cmd *cmd);
void		free_redirs(t_redir *r);
void		free_cmd(t_cmd *cmd);
void		free_pipeline(t_pipeline *p);

#endif