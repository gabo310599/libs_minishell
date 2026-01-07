/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:47:32 by gojeda            #+#    #+#             */
/*   Updated: 2025/11/30 15:47:36 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

// Identificamos si estamos en uno de los operadores
int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

// Identificamos en cual operador estamos
t_token_type	identify_operator(const char *s)
{
	if (s[0] == '|')
		return (TOKEN_PIPE);
	if (s[0] == '<')
	{
		if (s[1] == '<')
			return (TOKEN_HEREDOC);
		return (TOKEN_REDIR_IN);
	}
	if (s[0] == '>')
	{
		if (s[1] == '>')
			return (TOKEN_APPEND);
		return (TOKEN_REDIR_OUT);
	}
	return (TOKEN_UNKNOWN);
}

// Vemos la longitud del operador
int	operator_length(const char *s)
{
	if ((s[0] == '<' && s[1] == '<')
		|| (s[0] == '>' && s[1] == '>'))
		return (2);
	return (1);
}
