/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:33:39 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/07 10:35:26 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdbool.h>
# include <stddef.h>

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

#endif
