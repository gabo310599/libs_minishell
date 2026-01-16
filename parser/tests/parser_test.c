#include "../../lexer/includes/lexer.h"
#include "../includes/parser.h"

/* ---------- utils de impresión ---------- */

static void	print_segments(t_segment *seg)
{
	while (seg)
	{
		printf("\"%s\"", seg->str);
		if (seg->expand)
			printf("($)");
		if (seg->next)
			printf(" + ");
		seg = seg->next;
	}
	printf("\n");
}

static void	print_token(t_token *tok)
{
	if (tok->type != TOKEN_WORD)
	{
		printf("TOKEN (%d)\n", tok->type);
		return ;
	}
	printf("WORD: ");
	print_segments(tok->segments);
}

static const char	*redir_type_str(t_redir_type type)
{
	if (type == REDIR_IN)
		return ("<");
	if (type == REDIR_OUT)
		return (">");
	if (type == REDIR_APPEND)
		return (">>");
	if (type == REDIR_HEREDOC)
		return ("<<");
	return ("?");
}

static void	print_cmd(t_cmd *cmd, int index)
{
	int		i;
	t_redir	*r;

	printf("  CMD[%d]\n", index);
	printf("    argv (%d):\n", cmd->argc);
	i = 0;
	while (i < cmd->argc)
	{
		printf("      [%d] ", i);
		print_token(cmd->argv[i]); // reutilizamos printer del lexer
		i++;
	}
	printf("    redirs:\n");
	r = cmd->redirs;
	while (r)
	{
		printf("      %s ", redir_type_str(r->type));
		print_token(r->target);
		r = r->next;
	}
}

static void	print_pipeline(t_pipeline *p)
{
	int	i;

	printf("PIPELINE (%d cmds)\n", p->count);
	i = 0;
	while (i < p->count)
	{
		print_cmd(p->cmds[i], i);
		i++;
	}
}

/* ---------- tests ---------- */

static void	run_test(const char *input)
{
	t_lexer		*lx;
	t_token		*tokens;
	t_pipeline	*p;

	printf("================================\n");
	printf("INPUT: %s\n", input);
	printf("================================\n");

	lx = lexer_tokenize(input);
	if (!lx)
	{
		printf("Lexer error\n\n");
		return ;
	}
	tokens = lx->head;
	p = parse_tokens(tokens);
	if (!p)
	{
		printf("Parser error\n\n");
		lexer_destroy(lx);
		return ;
	}
	print_pipeline(p);
	free_pipeline(p);
	lexer_destroy(lx);
	printf("\n");
}


int	main(void)
{
	run_test("ls -la");
	run_test("echo hola | wc");
	run_test("cat < infile > outfile");
	run_test("cat << EOF | grep hello");
	run_test("echo 'a b' | cat > file.txt");
	run_test("ls | | wc");        // error
	run_test("| ls");             // error
	run_test("ls |");             // error
	run_test("ls >");             // error
	run_test("ls > | wc");        // error
	return (0);
}
