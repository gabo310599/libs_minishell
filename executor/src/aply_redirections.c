/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aply_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 19:50:22 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 20:18:10 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

//Abrimos el target de una redireccion
static int	open_redir_fd(t_redir *r)
{
	if (r->type == REDIR_IN)
		return (open(r->target->value, O_RDONLY));
	if (r->type == REDIR_OUT)
		return (open(r->target->value,
				O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (r->type == REDIR_APPEND)
		return (open(r->target->value,
				O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (-1);
}

//Hacemos dup de una redireccion
static void	dup_redir_fd(t_redir *r, int fd)
{
	if (r->type == REDIR_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
}

//Aplicamos una sola redireccion
static bool	apply_single_redir(t_redir *r)
{
	int	fd;

	if (r->type == REDIR_HEREDOC)
		return (true);
	fd = open_redir_fd(r);
	if (fd < 0)
		return (perror(r->target->value), false);
	dup_redir_fd(r, fd);
	close(fd);
	return (true);
}

//Aplicamos todas las redirecciones
bool	apply_redirections(t_redir *r)
{
	while (r)
	{
		if (!apply_single_redir(r))
			return (false);
		r = r->next;
	}
	return (true);
}
