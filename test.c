# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>

char *cmd1[] = {"/bin/cat", "test2.c", NULL};
char *cmd2[] = {"/usr/bin/head", "-n", "10", NULL};
char *cmd3[] = {"/usr/bin/grep", "char", NULL};
char **cmds[] = {cmd1, cmd2, cmd3};

void	recursive_pipe(int cmd_n, int filefd, int i)
{
	pid_t	pid;
	int		pipefd[2];

	if (i == cmd_n - 1)
	{
		execve(cmds[0][0], cmds[0], NULL);
	}
	else{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			recursive_pipe(cmd_n, filefd, i + 1);
		}
		else
		{
			if (i == 0)
				dup2(filefd, STDOUT_FILENO);
			close(filefd);
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			execve(cmds[cmd_n-i-1][0], cmds[cmd_n-i-1], NULL);
		}
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		cmd_n;
	int		filefd;

	cmd_n = 3;
	filefd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
		recursive_pipe(cmd_n, filefd, 0);
	else
		wait(NULL);
	return (0);
}