/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:45:58 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/07 10:36:04 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../../libft/libft.h"
# include "../token.h"
# define NORMAL 0
# define IN_SQUOTE 1
# define IN_DQUOTE 2

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

/* CRUD */
t_lexer			*lexer_create(void);
t_segment		*segment_new(char *str, bool expand);
t_token			*token_new(t_token_type type);
void			token_add_segment(t_token *tok, t_segment *seg);
bool			lexer_add_token(t_lexer *lex, t_token *tok);

/* Funciones para liberar memoria*/
void			lexer_destroy(t_lexer *lex);

/* Operator utils */
int				is_operator_char(char c);
t_token_type	identify_operator(const char *s);
int				operator_length(const char *s);

/* State Machine */
t_lexer			*lexer_tokenize(const char *line);
void			handle_normal(t_lexer *lx, const char *line,
					size_t *i, int *state);
void			handle_in_squote(t_lexer *lx, const char *line,
					size_t *i, int *state);
void			handle_in_dquote(t_lexer *lx, const char *line,
					size_t *i, int *state);

/* Words and segments functions */
void			lexer_start_word(t_lexer *lx);
void			lexer_add_char(t_lexer *lx, char c);
void			lexer_end_segment(t_lexer *lx);
void			lexer_start_segment(t_lexer *lx, bool expand);
bool			lexer_end_word(t_lexer *lx);
#endif