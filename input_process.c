#include "pipex.h"

bool	check_option(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '-')
			return (true);
		i++;
	}
	return (false);
}

char	**make_argv(char **av, int	check, char	*exact_path)
{
	char	**argv;
	int		size;
	int		i;

	if (check_option(av[check]))
		size = 4;
	else
		size = 3;
	argv = malloc(sizeof(char *) * size);
	i = 0;
	argv[i++] = ft_strdup(exact_path);
	if (size == 4)
		argv[i++] = ft_strdup(ft_strrchr(av[check], '-'));
	argv[i++] = ft_strdup(av[check - 1]);
	argv[i] = NULL;
	return (argv);
}

void	input_process(char **av, char **env, int *pipefd)
{
	char	*exact_path;

	dup2(pipefd[0], STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exact_path = get_filepath(av[2], env);
	execve(exact_path, make_argv(av, 2, exact_path), NULL);
	printf("exact_path = %s\n", exact_path);
	exit (0);
}
