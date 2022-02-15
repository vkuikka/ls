/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:52:33 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/15 17:04:5 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	set_times(struct stat *buf[2], long t[2])
{
	t[0] = buf[0]->st_mtimespec.tv_sec;
	t[1] = buf[1]->st_mtimespec.tv_sec;
	if (t[0] == t[1]
		&& buf[0]->st_mtimespec.tv_nsec && buf[1]->st_mtimespec.tv_nsec)
	{
		t[0] = buf[0]->st_mtimespec.tv_nsec;
		t[1] = buf[1]->st_mtimespec.tv_nsec;
	}
}

static void	swap_stats(t_stats *a, t_stats *b)
{
	t_stats		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	swap_string(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	push_string(char **str, int i, int j)
{
	char	*tmp;

	tmp = str[j];
	while (j > i && j > 0)
	{
		str[j] = str[j - 1];
		j--;
	}
	str[j] = tmp;
}

void	sort_args_time(int argc, char **argv, int reverse)
{
	struct stat	*buf[2];
	long		mod_time[2];
	int			i;
	int			j;

	buf[0] = (struct stat *)malloc(sizeof(struct stat));
	buf[1] = (struct stat *)malloc(sizeof(struct stat));
	if (!buf[0] || !buf[1])
		return ;
	i = 0;
	while (i < argc)
	{
		j = i;
		while (j < argc)
		{
			lstat(argv[i], buf[0]);
			lstat(argv[j], buf[1]);
			set_times(buf, mod_time);
			if (!reverse && mod_time[0] < mod_time[1])
				push_string(argv, i, j);
			if (reverse && mod_time[0] > mod_time[1])
				push_string(argv, i, j);
			j++;
		}
		i++;
	}
	free(buf[0]);
	free(buf[1]);
}

void	sort_args_alphabetical(int argc, char **argv, int reverse)
{
	struct stat	*buf[2];
	int			i;
	int			j;

	i = 0;
	while (i < argc)
	{
		j = 0;
		while (j < argc)
		{
			if (!reverse && ft_strcmp(argv[i], argv[j]) < 0)
				swap_string(&argv[i], &argv[j]);
			if (reverse && ft_strcmp(argv[i], argv[j]) > 0)
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
		j = i;
		while (files[j])
		{
			if (i != j)
			{
				if ((!reverse ^ (j < i))
					&& ft_strcmp(files[i]->d_name, files[j]->d_name) > 0)
					swap_stats(files[i], files[j]);
				else if ((reverse ^ (j < i))
					&& ft_strcmp(files[i]->d_name, files[j]->d_name) < 0)
					swap_stats(files[i], files[j]);
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

static void	push_stats(t_stats **files, int i, int j)
{
	t_stats	*tmp;

	tmp = files[j];
	while (j > i && j > 0)
	{
		files[j] = files[j - 1];
		j--;
	}
	files[j] = tmp;
}

void	sort_files_time(char *path, t_stats **files, int reverse)
{
	struct stat	*buf[2];
	long		mod_time[2];
	int			i[2];

	buf[0] = (struct stat *)malloc(sizeof(struct stat));
	buf[1] = (struct stat *)malloc(sizeof(struct stat));
	if (!buf[0] || !buf[1])
		return ;
	i[0] = -1;
	while (files[++i[0]])
	{
		i[1] = i[0];
		while (files[++i[1]])
		{
			set_buffers(buf, files, i, path);
			set_times(buf, mod_time);
			if (reverse && mod_time[0] > mod_time[1])
				push_stats(files, i[0], i[1]);
			if (!reverse && mod_time[0] < mod_time[1])
				push_stats(files, i[0], i[1]);
		}
	}
	free(buf[0]);
	free(buf[1]);
}
