#include <readline/readline.h>
#include <unistd.h>
#include <fcntl.h>

#include "../includes/expander.h"

char	*expand_string(const char *str, t_env *env, int last_status)
{
	t_segment	seg;

	if (!str)
		return (ft_strdup(""));
	seg.str = (char *)str;
	seg.expand = true;
	seg.next = NULL;
	return (expand_segment(&seg, env, last_status));
}

int	create_heredoc_pipe(char *delimiter, t_expand_ctx *ctx)
{
	int		pipefd[2];
	char	*line;
	char	*expanded;

	if (pipe(pipefd) < 0)
		return (-1);
	
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_string(line, ctx->env, ctx->last_status);
		ft_putendl_fd(expanded, pipefd[1]);
		free(expanded);
		free(line);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}
