/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:01:35 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/10 14:53:22 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	recursion(t_flags flags, t_dirent **dirs, char *path, int depth)
{
	char	*tmp_path;
	int		i;

	i = 0;
	if (flags.R)
	{
		while (dirs[i])
		{
			if (dirs[i]->d_type == DT_DIR)
			{
				tmp_path = ft_strjoin(path, dirs[i]->d_name);
				ls_dir(tmp_path, flags, depth + 1);
			}
			i++;
		}
	}
	free(path);
	free(dirs);
}

static void	handle_flags(t_flags flags, t_dirent **dirs, char *path, int depth)
{
	int	i;

	if (flags.t)
	{
		sort_files_alphabetical(dirs, 0);
		sort_files_time(path, dirs, flags.r);
	}
	else
		sort_files_alphabetical(dirs, flags.r);
	blocks_total(dirs, flags, path);
	i = -1;
	while (dirs[++i])
	{
		if (flags.l)
		{
			long_format(path, dirs[i]->d_name);
			if (dirs[i + 1])
				ft_printf("\n");
		}
		else
		{
			depth_print(dirs[i]->d_name, depth);
			ft_printf("\t");
		}
	}
}

static t_dirent	**add_dir(t_dirent **names, t_dirent *new)
{
	t_dirent	**new_names;
	int			i;

	i = 0;
	while (names[i])
		i++;
	new_names = (t_dirent **)malloc(sizeof(t_dirent *) * (i + 2));
	i = 0;
	while (names[i])
	{
		new_names[i] = names[i];
		i++;
	}
	new_names[i] = new;
	new_names[i + 1] = NULL;
	free(names);
	return (new_names);
}

static t_dirent	**init_names(char **path, int depth)
{
	t_dirent	**names;
	char		*tmp_path;

	if (depth != 0)
	{
		ft_printf("\n\n");
		depth_print(*path, depth);
		ft_printf(":\n");
	}
	tmp_path = ft_strjoin(*path, "/");
	if (depth != 0)
		free(*path);
	*path = tmp_path;
	names = (t_dirent **)malloc(sizeof(t_dirent *) * 1);
	names[0] = NULL;
	return (names);
}

void	ls_dir(char *path, t_flags flags, int depth)
{
	DIR			*d;
	t_dirent	*tmp;
	t_dirent	**dirs;

	d = opendir(path);
	if (!d)
		return ;
	dirs = init_names(&path, depth);
	tmp = readdir(d);
	while (tmp != NULL)
	{
		if (tmp->d_name[0] == '.' && !flags.a)
		{
			tmp = readdir(d);
			continue ;
		}
		if (ft_strcmp(tmp->d_name, ".") == 0
			|| ft_strcmp(tmp->d_name, "..") == 0)
			tmp->d_type = DT_REG;
		dirs = add_dir(dirs, tmp);
		tmp = readdir(d);
	}
	handle_flags(flags, dirs, path, depth);
	recursion(flags, dirs, path, depth);
	closedir(d);
}
