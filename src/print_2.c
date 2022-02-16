/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:43:51 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/16 13:36:03 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	blocks_total(t_stats **dirs, t_flags flags, char *path)
{
	struct stat	*buf;
	char		*full_path;
	int			i;
	int			total;

	if (!flags.l)
		return ;
	buf = (struct stat *)ft_memalloc(sizeof(struct stat));
	i = 0;
	total = 0;
	while (dirs[i])
	{
		full_path = ft_strjoin(path, dirs[i]->d_name);
		lstat(full_path, buf);
		total += buf->st_blocks;
		free(full_path);
		i++;
	}
	ft_putstr("total ");
	ft_putnbr(total);
	free(buf);
}

void	print_filename_error(char *path)
{
	struct stat	*buf;

	buf = (struct stat *)ft_memalloc(sizeof(struct stat));
	stat(path, buf);
	ft_putstr("\n\n");
	ft_putstr(path);
	ft_putstr(":\ntotal 0\n");
	ft_putstr("ft_ls: ");
	ft_putstr(path);
	ft_putstr(": ");
	ft_putstr(strerror(errno));
	free(buf);
}
