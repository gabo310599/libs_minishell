/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:33:39 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/20 15:39:22 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

//Unica variable global para signals
extern int	g_signal;

// **************************************************************************
//TOKEN
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF,
	TOKEN_ERROR,
	TOKEN_UNKNOWN
}	t_token_type;

/* Cada segmento de una palabra: texto y si es expandible */
typedef struct s_segment
{
	char				*str;
	bool				expand;
	struct s_segment	*next;
}	t_segment;

/* 
Un token WORD contiene una lista de segmentos.
Otros tokens usan ->value para información opcional (por ejemplo, filename raw).
*/
typedef struct s_token
{
	t_token_type	type;
	t_segment		*segments;
	char			*value;
	struct s_token	*next;
}	t_token;

// **************************************************************************
//ENV

//Representa una variable de entorno: KEY=VALUE
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// **************************************************************************
//LEXER

/* Resultado del lexer: lista ligada de tokens */
typedef struct s_lexer
{
	t_token		*head;
	t_token		*tail;
	int			error;
	t_token		*current_word;
	t_segment	*current_seg;
	bool		current_expand;
}	t_lexer;

// **************************************************************************
//Parser
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
	char	**argv_expanded;
	t_redir	*redirs;
}	t_cmd;

//Estructura para el pipeline
typedef struct s_pipeline
{
	t_cmd	**cmds;
	int		count;
}	t_pipeline;

// **************************************************************************
//EXPANDER

//Redireccion expandida
typedef struct s_ex_redir
{
	t_redir_type		type;
	char				*filename;
	struct s_ex_redir	*next;
}	t_ex_redir;

//Comando expandido
typedef struct s_ex_cmd
{
	char		**argv;
	t_ex_redir	*redirs;
}	t_ex_cmd;

//Pipeline expandido
typedef struct s_ex_pipeline
{
	t_ex_cmd	**cmds;
	int			count;
}	t_ex_pipeline;

//Contexto de expansion
typedef struct s_expand_ctx
{
	t_env	*env;
	int		last_status;
}	t_expand_ctx;

// **************************************************************************
//EXECUTOR

typedef struct s_exec_base
{
	t_env	*env;
	int		*last_status;
}	t_exec_base;

typedef struct s_exec_ctx
{
	t_exec_base	*base;
	int			prev_fd;
	int			fd[2];
	bool		has_next;
}	t_exec_ctx;

// **************************************************************************
//MINISHELL
typedef struct s_shell
{
	t_env	*env;
	int		last_status;
}	t_shell;

// **************************************************************************
//Funciones

//Signals
void	setup_signals_interactive(void);
void	setup_signals_exec(void);
void	setup_signals_parent(void);

//Limpieza
void	cleanup_shell(t_shell *sh);

#endif