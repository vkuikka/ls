/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 23:43:51 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/15 20:54:00 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	no_such(char *str)
{
	ft_putstr("ft_ls: ");
	ft_putstr(str);
	ft_putstr(": No such file or directory\n");
	str[0] = '\0';
}

static void	unfound(char **argv, t_flags flags, int i)
{
	if (flags.l)
		long_format("./", argv[i]);
	else
		ft_putstr(argv[i]);
	ft_putstr("\n\n");
	argv[i][0] = '\0';
}

void	print_unfound(int argc, char **argv, t_flags flags)
{
	struct stat	*buf;
	DIR			*d;
	int			i;

	i = flags.flags_present;
	sort_args_alphabetical(argc - (i + 1), &argv[i + 1], flags.r);
	if (flags.t)
		sort_args_time(argc - (i + 1), &argv[i + 1], flags.r);
	buf = (struct stat *)malloc(sizeof(struct stat));
	while (++i < argc)
	{
		d = opendir(argv[i]);
		if (!lstat(argv[i], buf) && !S_ISDIR(buf->st_mode))
			unfound(argv, flags, i);
		else if (!d)
			no_such(argv[i]);
		if (d)
			closedir(d);
	}
	free(buf);
}

void	blocks_total(t_stats **dirs, t_flags flags, char *path)
{
	struct stat	*buf;
	char		*full_path;
	int			i;
	int			total;

	if (!flags.l)
		return ;
	buf = (struct stat *)malloc(sizeof(struct stat));
	if (!buf)
		return ;
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

	buf = (struct stat *)malloc(sizeof(struct stat));
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
