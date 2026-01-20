/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:47:04 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/20 15:47:36 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

int	backup_fd(int fd)
{
	return (dup(fd));
}

void	restore_fd(int backup, int target)
{
	dup2(backup, target);
	close(backup);
}
