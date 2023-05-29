#include "pipex.h"

void	input_process(char **av, char **env, int *pipefd)
{
	char	*exact_path;
	// char	buf;
	// int		ret;

	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	// while ((ret = read(pipefd[0], &buf, 1)) > 0)
	// {
	// 	if (ret < 0)
	// 		ft_error(strerror(errno), 2);
	// 	write(0, &buf, ret);
	// }
	exact_path = get_filepath(av[2], env);
	char	*argv[] = {exact_path, NULL};
	execve(exact_path, argv, NULL);
	printf("exact_path = %s\n", exact_path);
	exit (0);
}
