/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 21:38:05 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/20 13:21:34 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

//Ejecutamos env
bool	builtin_env(t_cmd *cmd, t_env *env, int *last_status)
{
	if (cmd->argv_expanded[1])
	{
		write(2, "env: too many arguments\n", 24);
		*last_status = 1;
		return (false);
	}
	while (env)
	{
		if (env->value)
		{
			write(1, env->key, ft_strlen(env->key));
			write(1, "=", 1);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	*last_status = 0;
	return (true);
}
