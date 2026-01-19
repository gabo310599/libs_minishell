#include <stdio.h>
#include "../../lexer/includes/lexer.h"
#include "../../parser/includes/parser.h"
#include "../../expander/includes/expander.h"
#include "../../env/includes/env.h"

/* ===================== PRINT HELPERS ===================== */

static void	print_argv(char **argv)
{
	int	i;

	if (!argv)
	{
		printf("    argv_expanded: (null)\n");
		return ;
	}
	i = 0;
	while (argv[i])
	{
		printf("      argv[%d]: \"%s\"\n", i, argv[i]);
		i++;
	}
}

static void	print_redirs(t_redir *r)
{
	while (r)
	{
		if (r->type == REDIR_IN)
			printf("      < ");
		else if (r->type == REDIR_OUT)
			printf("      > ");
		else if (r->type == REDIR_APPEND)
			printf("      >> ");
		else if (r->type == REDIR_HEREDOC)
			printf("      << ");
		printf("\"%s\"\n", r->target->value);
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
		printf("  CMD[%d]\n", i);
		print_argv(p->cmds[i]->argv_expanded);
		print_redirs(p->cmds[i]->redirs);
		i++;
	}
}

/* ===================== TEST RUNNER ===================== */

static void	run_test(char *input, t_env *env, int last_status)
{
	t_lexer		*lx;
	t_pipeline	*p;

	printf("================================\n");
	printf("INPUT: %s\n", input);
	printf("================================\n");

	lx = lexer_tokenize(input);
	if (!lx)
	{
		printf("Lexer error\n");
		return ;
	}
	p = parse_tokens(lx->head);
	if (!p)
	{
		printf("Parser error\n");
		lexer_destroy(lx);
		return ;
	}
	if (!expand_pipeline(p, env, last_status))
	{
		printf("Expander error\n");
		lexer_destroy(lx);
		free_pipeline(p);
		return ;
	}
	print_pipeline(p);
	lexer_destroy(lx);
	free_pipeline(p);
}

/* ===================== MAIN ===================== */

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;

	env = env_init(envp);
	env_set(&env, "FOO", "bar");
	env_set(&env, "EMPTY", "");
	env_set(&env, "FILE", "file.txt");

	run_test("echo hola", env, 0);
	run_test("echo $FOO", env, 0);
	run_test("echo '$FOO'", env, 0);
	run_test("echo \"$FOO\"", env, 0);
	run_test("echo \"a$FOO b\"", env, 0);
	run_test("echo a$FOO$FOO", env, 0);
	run_test("echo $NOEXIST", env, 0);
	run_test("echo $?\"", env, 42);
	run_test("cat < $FILE > \"$FILE\"", env, 0);
	run_test("cat << $FILE", env, 0);
	run_test("echo \"\" ''", env, 0);
	run_test("echo \"a\"\"b\"\"c\"", env, 0);
	run_test("echo hola | cat > $FILE", env, 0);

	env_destroy(env);
	return (0);
}
