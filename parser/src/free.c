/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 02:38:42 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/16 08:26:14 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

//Liberamos todo
void	free_all(t_pipeline *p, t_cmd *cmd)
{
	if (cmd)
		free_cmd(cmd);
	free_pipeline(p);
}

//Liberamos las redirecciones
void	free_redirs(t_redir *r)
{
	t_redir	*tmp;

	while (r)
	{
		tmp = r->next;
		free(r);
		r = tmp;
	}
}

//Liberamos los comandos
void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free(cmd->argv);
	free_redirs(cmd->redirs);
	free(cmd);
}

//Liberamos los pipelines
void	free_pipeline(t_pipeline *p)
{
	int	i;

	if (!p)
		return ;
	i = 0;
	while (i < p->count)
	{
		free_cmd(p->cmds[i]);
		i++;
	}
	free(p->cmds);
	free(p);
}
