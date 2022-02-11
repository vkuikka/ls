/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:52:33 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/10 17:42:36 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_swap_string(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_args_alphabetical(int argc, char **argv)
{
	int		i;
	int		j;

	i = 0;
	while (i < argc)
	{
		j = 0;
		while (j < argc)
		{
			if (ft_strcmp(argv[i], argv[j]) < 0)
				ft_swap_string(&argv[i], &argv[j]);
			j++;
		}
		i++;
	}
}

void	sort_files_alphabetical(t_dirent **files, int reverse)
{
	int		i;
	int		j;

	i = 0;
	while (files[i])
	{
		j = 0;
		while (files[j])
		{
			if (reverse && ft_strcmp(files[i]->d_name, files[j]->d_name) > 0)
				ft_swap((int *)&files[i], (int *)&files[j]);
			if (!reverse && ft_strcmp(files[i]->d_name, files[j]->d_name) < 0)
				ft_swap((int *)&files[i], (int *)&files[j]);
			j++;
		}
		i++;
	}
}

static void	set_buffers(struct stat *buf[2], t_dirent **files,
						int i[2], char *path)
{
	char		*full_path;

	full_path = ft_strjoin(path, files[i[0]]->d_name);
	lstat(full_path, buf[0]);
	free(full_path);
	full_path = ft_strjoin(path, files[i[1]]->d_name);
	lstat(full_path, buf[1]);
	free(full_path);
}

void	sort_files_time(char *path, t_dirent **files, int reverse)
{
	struct stat	*buf[2];
	int			i[2];

	buf[0] = (struct stat *)malloc(sizeof(struct stat));
	buf[1] = (struct stat *)malloc(sizeof(struct stat));
	if (!buf[0] || !buf[1])
		return ;
	i[0] = 0;
	while (files[i[0]])
	{
		i[1] = 0;
		while (files[i[1]])
		{
			set_buffers(buf, files, i, path);
			if (reverse && buf[0]->st_mtime < buf[1]->st_mtime)
				ft_swap((int *)&files[i[0]], (int *)&files[i[1]]);
			if (!reverse && buf[0]->st_mtime > buf[1]->st_mtime)
				ft_swap((int *)&files[i[0]], (int *)&files[i[1]]);
			i[1]++;
		}
		i[0]++;
	}
	free(buf[0]);
	free(buf[1]);
}
