/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 11:12:12 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/19 11:24:55 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../minishell.h"

t_env	*env_new(const char *key, const char *value);
t_env	*env_init(char **envp);
char	*env_get(t_env *env, const char *key);
bool	env_set(t_env **env, const char *key, const char *value);
bool	env_unset(t_env **env, const char *key);
void	env_destroy(t_env *env);

#endif