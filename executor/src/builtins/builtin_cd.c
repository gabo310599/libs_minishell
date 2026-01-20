/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:29:58 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/20 13:20:35 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

//Obtenemos el destino de cd
static char	*cd_get_target(t_cmd *cmd, t_env *env)
{
	char	*target;

	if (!cmd->argv_expanded[1])
		return (env_get(env, "HOME"));
	if (!ft_strncmp(cmd->argv_expanded[1], "-", 2))
		return (env_get(env, "OLDPWD"));
	target = ft_strdup(cmd->argv_expanded[1]);
	return (target);
}

//Acrualizamos PWD y OLDPWD (4096 es el PATH_MAX)
static void	update_pwd(t_env **env, char *oldpwd)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
		env_set(env, "PWD", cwd);
	if (oldpwd)
		env_set(env, "OLDPWD", oldpwd);
}

//Mensaje de error de cd
static void	cd_error(char *path)
{
	write(2, "minishell: cd: ", 15);
	perror(path);
}

//Ejecutamos cd
bool	builtin_cd(t_cmd *cmd, t_env **env, int *last_status)
{
	char	*target;
	char	*oldpwd;

	oldpwd = env_get(*env, "PWD");
	target = cd_get_target(cmd, *env);
	if (!target)
		return (*last_status = 1, free(oldpwd), false);
	if (chdir(target) < 0)
	{
		cd_error(target);
		*last_status = 1;
		return (free(target), free(oldpwd), false);
	}
	update_pwd(env, oldpwd);
	*last_status = 0;
	free(target);
	free(oldpwd);
	return (true);
}
