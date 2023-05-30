#include "pipex.h"

void	output_process(char **av, char **env, int *pipefd)
{
	char	*exact_path;

	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exact_path = get_filepath(av[3], env);
	char	*argv[] = {"/bin/wc", "-l", NULL};
	execve("/bin/wc", argv, NULL);
	exit (0);
}
