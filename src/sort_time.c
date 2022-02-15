/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:30:14 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/15 20:36:39 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	free_buf(struct stat *buf[2])
{
	free(buf[0]);
	free(buf[1]);
}

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
	free_buf(buf);
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
	i = -1;
	while (++i < argc)
	{
		j = i;
		while (++j < argc)
		{
			lstat(argv[i], buf[0]);
			lstat(argv[j], buf[1]);
			set_times(buf, mod_time);
			if (!reverse && mod_time[0] < mod_time[1])
				push_string(argv, i, j);
			if (reverse && mod_time[0] > mod_time[1])
				push_string(argv, i, j);
		}
	}
	free_buf(buf);
}
