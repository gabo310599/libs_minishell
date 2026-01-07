/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:21:58 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/07 10:54:00 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../../libft/libft.h"
# include "../../token.h"

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

//Estructura para las redirecciones
typedef struct s_redir
{
	t_redir_type	type;
	t_token			*target;
	struct s_redir	*next;
}	t_redir;

//Estructura para los comandos simples
typedef struct s_cmd
{
	t_token	**argv;
	int		argc;
	t_redir	*redirs;
}	t_cmd;

//Estructura para el pipeline
typedef struct s_pipeline
{
	t_cmd	**cmds;
	int		count;
}	t_pipeline;

#endif