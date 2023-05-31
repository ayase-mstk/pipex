#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int		fd;
	int		pipefd[2];
	pid_t	pid1;
	// int		status;
	pid_t	pid2;

	if (ac != 5)
		ft_error("Error: wrong number of arguments\n", 1);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe(pipefd) == -1)
		ft_error(strerror(errno), 2);
	// input process
	if ((pid1 = fork()) == -1)
		ft_error(strerror(errno), 2);
	if (pid1 == 0)
	{
		input_process(av, env, fd, pipefd);
	}
	// output process
	if ((pid2 = fork()) == -1)
		ft_error(strerror(errno), 2);
	if (pid2 == 0)
		output_process(av, env, fd, pipefd);
	// 親プロセス
	close(fd);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);

	// if (access(av[1], R_OK) || access(av[3], W_OK))
	// 	ft_error(strerror(errno), 2);
	// if ((fd = open(av[1], O_RDONLY)) < 0)
	// 	ft_error(strerror(errno), 2);
	// return (0);
}

// usage of strerror
// printf("%s\n", strerror(errno));