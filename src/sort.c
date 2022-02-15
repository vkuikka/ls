/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:52:33 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/15 14:05:46 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap_stats(t_stats **a, t_stats **b)
{
	t_stats	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	swap_string(char **a, char **b)
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
				swap_string(&argv[i], &argv[j]);
			j++;
		}
		i++;
	}
}

void	sort_files_alphabetical(t_stats **files, int reverse)
{
	int		i;
	int		j;

	i = 0;
	while (files[i])
	{
		j = 0;
		while (files[j])
		{
			if (i != j)
			{
				if (!reverse
					&& ft_strcmp(files[i]->d_name, files[j]->d_name) < 0)
					swap_stats(&files[i], &files[j]);
				if (reverse
					&& ft_strcmp(files[i]->d_name, files[j]->d_name) > 0)
					swap_stats(&files[i], &files[j]);
			}
			j++;
		}
		i++;
	}
}

static void	set_buffers(struct stat *buf[2], t_stats **files,
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

static void	set_times(struct stat *buf[2], int t[2])
{
	t[0] = buf[0]->st_mtimespec.tv_sec;
	t[1] = buf[1]->st_mtimespec.tv_sec;
	if (t[0] == t[1])
	{
		t[0] = buf[0]->st_mtimespec.tv_nsec;
		t[1] = buf[1]->st_mtimespec.tv_nsec;
	}
}

void	sort_files_time(char *path, t_stats **files, int reverse)
{
	struct stat	*buf[2];
	int			mod_time[2];
	int			i[2];

	buf[0] = (struct stat *)malloc(sizeof(struct stat));
	buf[1] = (struct stat *)malloc(sizeof(struct stat));
	if (!buf[0] || !buf[1])
		return ;
	i[0] = -1;
	while (files[++i[0]])
	{
		i[1] = -1;
		while (files[++i[1]])
		{ if (i[0] != i[1])
			{
				set_buffers(buf, files, i, path);
				set_times(buf, mod_time);
				if (reverse && mod_time[0] < mod_time[1])
					swap_stats(&files[i[0]], &files[i[1]]);
				if (!reverse && mod_time[0] > mod_time[1])
					swap_stats(&files[i[0]], &files[i[1]]);
			}
		}
	}
	free(buf[0]);
	free(buf[1]);
}
