/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:01:35 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/15 13:45:51by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	recursion(t_flags flags, t_stats **dirs, char *path, int depth)
{
	char		*tmp_path;
	int			i;
	struct stat	*buf;

	if (flags.R)
	{
		buf = (struct stat *)malloc(sizeof(struct stat));
		i = 0;
		while (dirs[i])
		{
			tmp_path = ft_strjoin(path, dirs[i]->d_name);
			lstat(tmp_path, buf);
			free(tmp_path);
			if ((dirs[i]->d_type == DT_DIR || S_ISDIR(buf->st_mode)) && !dirs[i]->no_recursion)
			{
				tmp_path = ft_strjoin(path, dirs[i]->d_name);
				ls_dir(tmp_path, flags, depth + 1);
			}
			i++;
		}
		free(buf);
	}
	free(path);
}

static void	handle_flags(t_flags flags, t_stats **dirs, char *path, int depth)
{
	int	i;

	sort_files_alphabetical(dirs, flags.r);
	if (flags.t)
		sort_files_time(path, dirs, flags.r);
	blocks_total(dirs, flags, path);
	i = -1;
	while (dirs[++i])
	{
		if (flags.l)
			long_format(path, dirs[i]->d_name);
		else
		{
			depth_print(dirs[i]->d_name, depth);
			ft_putstr("\t");
		}
	}
}

void	free_dirs(t_stats **names)
{
	int	i;

	i = -1;
	while (names[++i])
	{
		free(names[i]->d_name);
		free(names[i]);
	}
	free(names);
}

static t_stats	**add_dir(t_stats **names, char *n_name, char n_type, char n_r)
{
	t_stats		**new_names;
	int			i;

	i = 0;
	while (names[i])
		i++;
	new_names = (t_stats **)malloc(sizeof(t_stats *) * (i + 2));
	i = -1;
	while (names[++i])
	{
		new_names[i] = (t_stats *)malloc(sizeof(t_stats));
		new_names[i]->d_name = ft_strdup(names[i]->d_name);
		new_names[i]->d_type = names[i]->d_type;
		new_names[i]->no_recursion = names[i]->no_recursion;
	}
	new_names[i] = (t_stats *)malloc(sizeof(t_stats));
	new_names[i]->d_name = ft_strdup(n_name);
	new_names[i]->d_type = n_type;
	new_names[i]->no_recursion = n_r;
	new_names[i + 1] = NULL;
	free_dirs(names);
	return (new_names);
}

static t_stats	**init_names(char **path, int depth)
{
	t_stats		**names;
	char		*tmp_path;

	if (depth != 0)
	{
		ft_putstr("\n\n");
		depth_print(*path, depth);
		ft_putstr(":\n");
	}
	tmp_path = ft_strjoin(*path, "/");
	if (depth != 0)
		free(*path);
	*path = tmp_path;
	names = (t_stats **)malloc(sizeof(t_stats *) * 1);
	names[0] = NULL;
	return (names);
}

void	ls_dir(char *path, t_flags flags, int depth)
{
	DIR			*d;
	t_dirent	*tmp;
	t_stats		**dirs;

	d = opendir(path);
	if (!d)
	{
		print_filename_error(path);
		return ;
	}
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
			dirs = add_dir(dirs, tmp->d_name, DT_REG, 1);
		else
			dirs = add_dir(dirs, tmp->d_name, tmp->d_type, 0);
		tmp = readdir(d);
	}
	handle_flags(flags, dirs, path, depth);
	recursion(flags, dirs, path, depth);
	closedir(d);
	free(tmp);
	free_dirs(dirs);
}
