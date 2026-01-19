#include <stdio.h>
#include "../includes/env.h"

static void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*val;

	(void)argc;
	(void)argv;

	printf("== init ==\n");
	env = env_init(envp);
	print_env(env);

	printf("\n== get ==\n");
	val = env_get(env, "HOME");
	printf("HOME=%s\n", val);
	free(val);

	val = env_get(env, "NOEXIST");
	printf("NOEXIST='%s'\n", val);
	free(val);

	printf("\n== set ==\n");
	env_set(&env, "FOO", "bar");
	env_set(&env, "HOME", "/tmp");
	print_env(env);

	printf("\n== unset ==\n");
	env_unset(&env, "FOO");
	env_unset(&env, "NOEXIST");
	print_env(env);

	env_destroy(env);
	return (0);
}
