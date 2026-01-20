/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 02:14:53 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/20 15:10:46 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

//Creamos un comano vacio
t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->redirs = NULL;
	cmd->argv_expanded = NULL;
	return (cmd);
}

//Agregamos WORD a un comando 
bool	cmd_add_arg(t_cmd *cmd, t_token *word)
{
	t_token	**new_argv;
	int		i;

	new_argv = malloc(sizeof(t_token *) * (cmd->argc + 2));
	if (!new_argv)
		return (false);
	i = 0;
	while (i < cmd->argc)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[cmd->argc] = word;
	new_argv[cmd->argc + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
	cmd->argc++;
	return (true);
}

//Agregamos una redireccion a un comando
bool	cmd_add_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*tmp;

	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return (true);
	}
	tmp = cmd->redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
	return (true);
}

//Agregamos comando al pipeline
bool	pipeline_add_cmd(t_pipeline *p, t_cmd *cmd)
{
	t_cmd	**new_cmds;
	int		i;

	new_cmds = malloc(sizeof(t_cmd *) * (p->count + 1));
	if (!new_cmds)
		return (false);
	i = 0;
	while (i < p->count)
	{
		new_cmds[i] = p->cmds[i];
		i++;
	}
	new_cmds[p->count] = cmd;
	free(p->cmds);
	p->cmds = new_cmds;
	p->count++;
	return (true);
}

//Finalizamos el comando actual
bool	finalize_cmd(t_pipeline *p, t_cmd **cmd)
{
	if (!*cmd)
		return (false);
	if (!pipeline_add_cmd(p, *cmd))
		return (false);
	*cmd = NULL;
	return (true);
}
