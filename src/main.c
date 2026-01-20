/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gojeda <gojeda@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:39:11 by gojeda            #+#    #+#             */
/*   Updated: 2026/01/20 15:43:13 by gojeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../lexer/includes/lexer.h"
#include "../parser/includes/parser.h"
#include "../expander/includes/expander.h"
#include "../executor/includes/executor.h"
#include "../env/includes/env.h"

//Función para ejecutar una línea
static void	process_line(char *line, t_shell *sh)
{
	t_lexer		*lx;
	t_pipeline	*p;

	lx = lexer_tokenize(line);
	if (!lx)
		return ;
	p = parse_tokens(lx->head);
	if (!p)
	{
		lexer_destroy(lx);
		return ;
	}
	if (!expand_pipeline(p, sh->env, sh->last_status))
	{
		free_pipeline(p);
		lexer_destroy(lx);
		return ;
	}
	setup_signals_parent();
	execute_pipeline(p, sh->env, &sh->last_status);
	setup_signals_interactive();
	free_pipeline(p);
	lexer_destroy(lx);
}

//Loop principal
int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_shell		sh;

	(void)argc;
	(void)argv;
	sh.env = env_init(envp);
	sh.last_status = 0;
	setup_signals_interactive();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*line)
			add_history(line);
		process_line(line, &sh);
		free(line);
	}
	cleanup_shell(&sh);
	return (sh.last_status);
}
