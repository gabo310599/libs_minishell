/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:59:26 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 21:01:52 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

//Validamos la llave
static bool	is_valid_unset_key(const char *s)
{
	int	i;

	if (!s || (!ft_isalpha(s[0]) && s[0] != '_'))
		return (false);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

//Unset de una sola variable
static bool	unset_one(char *arg, t_env **env)
{
	if (!is_valid_unset_key(arg))
	{
		write(2, "minishell: unset: `", 20);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		return (false);
	}
	env_unset(env, arg);
	return (true);
}

//Ejecutamos el unset
bool	builtin_unset(t_cmd *cmd, t_env **env, int *last_status)
{
	int		i;
	bool	ok;

	i = 1;
	ok = true;
	while (cmd->argv[i])
	{
		if (!unset_one(cmd->argv[i], env))
			ok = false;
		i++;
	}
	if (ok)
		*last_status = 0;
	else
		*last_status = 1;
	return (true);
}
