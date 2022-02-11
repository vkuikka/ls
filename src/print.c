/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:28:06 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/10 17:42:02 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_unfound(int argc, char **argv, t_flags flags)
{
	struct stat	*buf;
	DIR		*d;
	int		i;

	i = 1 + flags.flags_present;
	sort_args_alphabetical(argc - i, &argv[i]);
	buf = (struct stat *)malloc(sizeof(struct stat));
	while (i < argc)
	{
		d = opendir(argv[i]);
		if (!lstat(argv[i], buf) && !S_ISDIR(buf->st_mode))
		{
			ft_printf("%s\n", argv[i]);
			argv[i][0] = '\0';
		}
		else if (!d)
		{
			ft_printf("ft_ls: %s: No such file or directory\n", argv[i]);
			argv[i][0] = '\0';
		}
		if (d)
			closedir(d);
		i++;
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
	ft_printf("total %d\n", total);
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
	print_time(ctime(&buf->st_mtime));
	ft_printf(" %s", name);
	if (S_ISLNK(buf->st_mode))
	{
		readlink(full_path, buff, PATH_MAX);
		ft_printf(" -> %s", buff);
	}
	free(buf);
	free(full_path);
}

void	print_time(char *str)
{
	str[16] = '\0';
	ft_putstr(&str[4]);
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
