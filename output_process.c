#include "pipex.h"

void	output_process(char **av, char **env, int *filefd, int *pipefd)
{
	char	*exact_path;

	dup2(filefd[0], STDIN_FILENO);
	close(filefd[0]);
	close(filefd[1]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exact_path = get_filepath(av[2], env);
	execve(exact_path, make_argv(av, 2, exact_path), NULL);
	exit (0);
}
