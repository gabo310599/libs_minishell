/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:37:55 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/20 15:45:52 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../env/includes/env.h"

void	cleanup_shell(t_shell *sh)
{
	if (!sh)
		return ;
	if (sh->env)
	{
		env_destroy(sh->env);
		sh->env = NULL;
	}
}

