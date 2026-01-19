/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:17:42 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 11:52:40 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/env.h"

//Creamos nodo y lo agregamos a la lista
static bool	env_add_from_str(t_env **env, const char *str)
{
	t_env	*new;
	char	*eq;
	char	*key;

	eq = ft_strchr(str, '=');
	if (!eq)
		return (true);
	key = ft_substr(str, 0, eq - str);
	if (!key)
		return (false);
	new = env_new(key, eq + 1);
	free(key);
	if (!new)
		return (false);
	new->next = *env;
	*env = new;
	return (true);
}

//Iniciamos un env
t_env	*env_init(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		if (!env_add_from_str(&env, envp[i]))
			return (env_destroy(env), NULL);
		i++;
	}
	return (env);
}

//Creamos una variable de entorno nuevo
t_env	*env_new(const char *key, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	if (!node->key || !node->value)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}
