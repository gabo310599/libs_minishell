/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 20:26:42 by gojeda            #+#    #+#             */
/*   Updated: 2026/03/17 20:49:03 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executor.h"

char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*full;
	char	*tmp;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = ft_split(env_get(env, "PATH"), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (free_str_array(paths), full);
		free(full);
		i++;
	}
	free_str_array(paths);
	return (NULL);
}

char	**env_to_envp(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		envp[i++] = ft_strjoin_three(tmp->key, "=", tmp->value);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
