#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int main() {

	int	pipefd[2];
	char	path[] = "/bin/echo";
	pid_t	input_pid;

	pipe(pipefd);
	input_pid = fork();
	if (input_pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		write(STDOUT_FILENO, "hello\n", 6);		
		exit (0);
	}
	// 親プロセス
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	char	*argv[] = {"/bin/echo", NULL};
	execve(path, argv, NULL);
	// waitpid(input_pid, NULL, 0);
    return 0;
}
