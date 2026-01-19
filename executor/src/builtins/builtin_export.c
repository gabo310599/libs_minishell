/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:44:17 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 20:56:22 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

//Verificamos que la llave sea valida
static bool	is_valid_key(const char *s)
{
	int	i;

	if (!s || !ft_isalpha(s[0]) && s[0] != '_')
		return (false);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

//Separamos la llave de su valor
static void	split_key_value(char *arg, char **key, char **value)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (!eq)
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
	else
	{
		*key = ft_substr(arg, 0, eq - arg);
		*value = ft_strdup(eq + 1);
	}
}

//Imprimimos el env en orden
static void	print_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
}

//Exportamos una sola variable
static bool	export_one(char *arg, t_env **env)
{
	char	*key;
	char	*value;

	if (!is_valid_key(arg))
	{
		write(2, "minishell: export: `", 21);
		write(2, arg, ft_strlen(arg));
		write(2, "': not a valid identifier\n", 26);
		return (false);
	}
	split_key_value(arg, &key, &value);
	if (!key)
		return (false);
	env_set(env, key, value);
	free(key);
	free(value);
	return (true);
}

//Ejecutamos el export
bool	builtin_export(t_cmd *cmd, t_env **env, int *last_status)
{
	int		i;
	bool	ok;

	if (!cmd->argv[1])
	{
		print_export(*env);
		*last_status = 0;
		return (true);
	}
	i = 1;
	ok = true;
	while (cmd->argv[i])
	{
		if (!export_one(cmd->argv[i], env))
			ok = false;
		i++;
	}
	if (ok)
		*last_status = 0;
	else
		*last_status = 1;
	return (ok);
}
