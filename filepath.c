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
