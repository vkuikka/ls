/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:01:35 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/10 01:21:30 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

static t_dirent	**init_names(void)
{
	t_dirent	**names;

	names = (t_dirent **)malloc(sizeof(t_dirent *) * 1);
	names[0] = NULL;
	return (names);
}

// __builtin_dump_struct(dir, &printf);
void	ls_dir(char *path, t_flags flags, int depth)
{
	DIR			*d;
	t_dirent	*tmp;
	t_dirent	**dirs;

	if (depth != 0)
	{
		ft_printf("\n\n");
		depth_print(path, depth);
		ft_printf(":\n");
	}
	d = opendir(path);
	if (!d)
		return ;
	dirs = init_names();
	path = ft_strjoin(path, "/");
	while ((tmp = readdir(d)) != NULL)
	{
		if (tmp->d_name[0] == '.' && !flags.a)
			continue;
		if (ft_strcmp(tmp->d_name, ".") == 0 || ft_strcmp(tmp->d_name, "..") == 0)
			tmp->d_type = DT_REG;
		dirs = add_dir(dirs, tmp);
	}
	if (flags.t)
	{
		sort_files_alphabetical(dirs, 0);
		sort_files_time(path, dirs, flags.r);
	}
	else
		sort_files_alphabetical(dirs, flags.r);
	if (flags.l)
		blocks_total(dirs, flags, path);
	for (int i = 0; dirs[i]; i++)
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
	for (int i = 0; dirs[i]; i++)
		if (dirs[i]->d_type == DT_DIR && flags.R)
			ls_dir(ft_strjoin(path, dirs[i]->d_name), flags, depth + 1);
	closedir(d);
}
