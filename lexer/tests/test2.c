#include "../includes/lexer.h"
#include <stdio.h>

static const char *token_type_str(t_token_type type)
{
	if (type == TOKEN_WORD) return "WORD";
	if (type == TOKEN_PIPE) return "PIPE";
	if (type == TOKEN_REDIR_IN) return "REDIR_IN";
	if (type == TOKEN_REDIR_OUT) return "REDIR_OUT";
	if (type == TOKEN_HEREDOC) return "HEREDOC";
	if (type == TOKEN_APPEND) return "APPEND";
	if (type == TOKEN_EOF) return "EOF";
	if (type == TOKEN_ERROR) return "ERROR";
	return "UNKNOWN";
}

static void	print_tokens(t_lexer *lx)
{
	t_token		*tok;
	t_segment	*seg;
	int			i = 0;
	int			j;

	tok = lx->head;
	while (tok)
	{
		printf("token[%d]: %s\n", i, token_type_str(tok->type));
		if (tok->type == TOKEN_WORD)
		{
			seg = tok->segments;
			j = 0;
			while (seg)
			{
				printf("      segment[%d]: \"%s\" (expand=%d)\n",
					j, seg->str, seg->expand);
				seg = seg->next;
				j++;
			}
		}
		tok = tok->next;
		i++;
	}
}

static void	run_test(const char *input)
{
	t_lexer	*lx;

	printf("================================\n");
	printf("INPUT: %s\n", input);
	printf("================================\n");

	lx = lexer_tokenize(input);
	if (!lx)
	{
		printf("LEXER ERROR\n\n");
		return ;
	}
	print_tokens(lx);
	lexer_destroy(lx);
	printf("\n");
}

int	main(void)
{
	/* Palabras simples */
	run_test("hola");
	run_test("hola mundo");
	run_test("ls -la");

	/* Comillas simples y dobles */
	run_test("'hola'");
	run_test("\"hola\"");
	run_test("'hola mundo'");
	run_test("\"hola mundo\"");

	/* Combinación de segmentos */
	run_test("hola\"mundo\"");
	run_test("\"hola\"mundo");
	run_test("'hola'mundo");
	run_test("'hola''mundo'");
	run_test("\"hola\"\"mundo\"");
	run_test("'hola'\"mundo\"");

	/* Segmentos vacíos */
	run_test("\"\"");
	run_test("''");
	run_test("\"\"test");
	run_test("test\"\"");
	run_test("''test");
	run_test("test''");
	run_test("echo '' \"\" ''\"\"");

	/* Operadores */
	run_test("ls|wc");
	run_test("ls | wc");
	run_test("cat < infile");
	run_test("cat > outfile");
	run_test("cat >> outfile");
	run_test("cat << EOF");

	/* Casos realistas */
	run_test("echo 'a b' | cat > file.txt");
	run_test("ls -la | grep \"Jan\" > output.txt");
	run_test("cmd \"arg1\"arg2 'arg3'arg4");

	return (0);
}
