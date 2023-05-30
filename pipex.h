#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>
# include "libft/libft.h"
# include "libftprintf/ft_printf.h"

# define PATH "PATH="

// typedef struct s_pipex
// {
// 	char	**cmd;
// 	char	**env;
// 	char	*infile;
// 	char	*outfile;
// 	int		pipefd[2];
// 	int		fd_in;
// 	int		fd_out;
// 	int		pid;
// 	int		status;
// }				t_pipex;

int		ft_error(char *str, int fd);
char	*get_filepath(char *cmd, char **env);
char	*get_exactpath(char **split_pathes, char *cmd);
char	*get_filepathes(char **env);
void	free_other(char **strarr , size_t necesseary);
char	**make_argv(char **av, int	check, char	*exact_path);
void	input_process(char **av, char **env, int *pipefd);
void	output_process(char **av, char **env, int *pipefd);

#endif