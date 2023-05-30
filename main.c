#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	int	pipefd[2];
	pid_t	input_pid;
	int		status;
	// pid_t	pid_output;

	// printf("exact_path = %s\n", get_filepath(av[2], env));
	if (pipe(pipefd) == -1)
		ft_error(strerror(errno), 2);
	if ((input_pid = fork()) == -1)
		ft_error(strerror(errno), 2);
	if (input_pid == 0)
		input_process(av, env, pipefd);
	// 親プロセス
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	// char *cmd[] = {"/bin/ls", "-l", NULL};
	// execve("/bin/ls", cmd, NULL);
	write(STDOUT_FILENO, av[1], ft_strlen(av[1]));
	if (wait(&status) == -1)
		ft_error(strerror(errno), 2);
	return (0);

	if (ac != 5)
		ft_error("Error: wrong number of arguments\n", 1);
	// if (access(av[1], R_OK) || access(av[3], W_OK))
	// 	ft_error(strerror(errno), 2);
	// if ((fd = open(av[1], O_RDONLY)) < 0)
	// 	ft_error(strerror(errno), 2);
	return (0);
}

// usage of strerror
// printf("%s\n", strerror(errno));