#include "pipex.h"

void	free_other(char **strarr , size_t necesseary)
{
	size_t	i;

	i = 0;
	while (strarr[i])
	{
		if (i != necesseary)
		{
			free(strarr[i]);
			strarr[i] = NULL;
		}
		i++;
	}
	free(strarr);
	strarr = NULL;
}

char	*get_filepathes(char **env)
{
	size_t	i;

	i = 0;
	while (i < ft_strptrlen(env))
	{
		if (!ft_strncmp(env[i], PATH, 4))
		{
			// printf("PATH = %s\n", &env[i][5]);
			return (&env[i][5]);
		}
		i++;
	}
	return (NULL);
}

char *get_exactpath(char **split_pathes, char *cmd)
{
	char	*tmp_path;
	char	*tmp_path2;
	char	*path;
	size_t	i;

	i = 0;
	while (i < ft_strptrlen(split_pathes))
	{
		tmp_path = split_pathes[i];
		split_pathes[i] = ft_strjoin(split_pathes[i], (tmp_path2 = ft_strjoin("/", cmd)));
		free(tmp_path);
		free(tmp_path2);
		// printf("split_pathes[%zu] = %s\n", i, split_pathes[i]);
		i++;
	}
	while (i-- >= 0)
	{
		if (access(split_pathes[i], F_OK) == 0)
		{
			path = split_pathes[i];
			free_other(split_pathes, i);
			return (path);
		}
	}
	return (NULL);
}

char *get_filepath(char *cmd, char **env)
{
	char	*all_path;
	char	**split_pathes;
	char	*path;

	if ((all_path = get_filepathes(env)) == NULL)
		ft_error("Error: PATH not found\n", 1);
	split_pathes = ft_split(all_path, ':');
	if (split_pathes == NULL)
		ft_error(strerror(errno), 2);
	path = get_exactpath(split_pathes, cmd);
	return (path);
}

//この関数は
//1.コマンドのパスを取得
//2.パイプの両端を取得
//3.パイプの両端をdup2で標準入出力に割り当てる
//4.コマンドを実行
//5.パイプの両端を閉じる
//6.コマンドのパスをfree
//7.コマンドの引数をfree


int	main(int ac, char **av, char **env)
{
	int	fd;

	printf("exact_path = %s\n", get_filepath(av[2], env));
	return (0);
	if (ac != 5)
		ft_error("Error: wrong number of arguments\n", 1);
	if (access(av[1], R_OK) || access(av[3], W_OK))
		ft_error(strerror(errno), 2);
	if ((fd = open(av[1], O_RDONLY)) < 0)
		ft_error(strerror(errno), 2);
	if (dup2(fd, 1) < 0)
	{
		close(fd);
		ft_error(strerror(errno), 2);
	}
	execve(get_filepath(av[2], env), &av[2], NULL);
	return (0);
}

// usage of strerror
// printf("%s\n", strerror(errno));