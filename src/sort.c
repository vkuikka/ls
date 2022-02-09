/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:52:33 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/10 00:53:23 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	sort_files_time(char *path, t_dirent **files, int reverse)
{
	struct stat	*buf;
	struct stat	*buf2;
	char		*full_path;
	int			i;
	int			j;

	buf = (struct stat *)malloc(sizeof(struct stat));
	buf2 = (struct stat *)malloc(sizeof(struct stat));
	if (!buf || !buf2)
		return ;
	i = 0;
	while (files[i])
	{
		j = 0;
		while (files[j])
		{
			full_path = ft_strjoin(path, files[i]->d_name);
			lstat(full_path, buf);
			full_path = ft_strjoin(path, files[j]->d_name);
			lstat(full_path, buf2);
			if (reverse && buf->st_mtime < buf2->st_mtime)
				ft_swap((int *)&files[i], (int *)&files[j]);
			if (!reverse && buf->st_mtime > buf2->st_mtime)
				ft_swap((int *)&files[i], (int *)&files[j]);
			free(full_path);
			j++;
		}
		i++;
	}
	free(buf);
	free(buf2);
}
