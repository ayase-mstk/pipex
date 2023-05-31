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

void	input_process(char **av, char **env, int *filefd, int *pipefd)
{
	char	*exact_path;

	dup2(filefd[1], STDOUT_FILENO);
	close(filefd[0]);
	close(filefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	// exact_path = get_filepath(av[3], env);
	printf("av[3] = %s\n", av[3]);
	printf("env = %s\n", env[0]);
	exact_path = "/bin/wc";
	char	*argv[] = {"/bin/wc", "-l", NULL};
	execve(exact_path, argv, NULL);
	// waitpid(output_pid, NULL, 0);
	exit (0);
}
