/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:28:06 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/11 11:57:35 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	no_such(char *str)
{
	ft_putstr("ft_ls: ");
	ft_putstr(str);
	ft_putstr(": No such file or directory\n");
	str[0] = '\0';
}

void	print_unfound(int argc, char **argv, t_flags flags)
{
	struct stat	*buf;
	DIR		*d;
	int		i;

	i = flags.flags_present;
	sort_args_alphabetical(argc - (i + 1), &argv[i + 1]);
	buf = (struct stat *)malloc(sizeof(struct stat));
	while (++i < argc)
	{
		d = opendir(argv[i]);
		if (!lstat(argv[i], buf) && !S_ISDIR(buf->st_mode))
		{
			if (flags.l)
				long_format("./", argv[i]);
			else
				ft_putstr(argv[i]);
			ft_putstr("\n\n");
			argv[i][0] = '\0';
		}
		else if (!d)
			no_such(argv[i]);
		if (d)
			closedir(d);
	}
	free(buf);
}

void	blocks_total(t_dirent **dirs, t_flags flags, char *path)
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
	ft_putstr("\n");
	free(buf);
}

void	long_format(char *path, char *name)
{
	struct stat	*buf;
	char		*full_path;
	char		buff[PATH_MAX];

	full_path = ft_strjoin(path, name);
	buf = (struct stat *)malloc(sizeof(struct stat));
	if (!buf)
	{
		free(full_path);
		return ;
	}
	lstat(full_path, buf);
	print_file_permissions(buf->st_mode);
	ft_printf("%4hu ", buf->st_nlink);
	ft_printf("%s  %s", user_name(buf->st_uid), group_name(buf->st_gid));
	ft_printf("%6lld ", buf->st_size);
	ft_putstr_len(&ctime(&buf->st_mtime)[4], 12);
	ft_printf(" %s", name);
	if (S_ISLNK(buf->st_mode))
	{
		readlink(full_path, buff, PATH_MAX);
		ft_printf(" -> %s", buff);
	}
	free(buf);
	free(full_path);
}

void	depth_print(char *str, int depth)
{
	if (depth == 1)
		ft_putstr("\033[1;34m");
	if (depth == 2)
		ft_putstr("\033[1;32m");
	if (depth == 3)
		ft_putstr("\033[1;36m");
	if (depth == 4)
		ft_putstr("\033[1;31m");
	if (depth == 5)
		ft_putstr("\033[1;35m");
	if (depth == 6)
		ft_putstr("\033[1;33m");
	ft_putstr(str);
	ft_putstr("\033[0m");
}
