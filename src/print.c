/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:28:06 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/15 20:29:14 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_putnbr_base(unsigned long long n, int base, int lowercase)
{
	char	*b;

	if (lowercase)
		b = "0123456789abcdef";
	else
		b = "0123456789ABCDEF";
	if (n > (unsigned long long)base - 1)
	{
		if (n / base)
			ft_putnbr_base(n / base, base, lowercase);
		ft_putchar(b[n % base]);
	}
	else
		ft_putchar(b[n]);
}

static void	ft_putstr_len(char *str, size_t len)
{
	if (ft_strlen(str) > len)
		write(1, str, len);
	else
		write(1, str, ft_strlen(str));
}

void	long_format_part_2(char *name,
			struct stat *buf, char *buff, char *full_path)
{
	if (S_ISCHR(buf->st_mode) || S_ISBLK(buf->st_mode))
	{
		if (buf->st_rdev != 0)
			ft_putstr("0x");
		ft_putnbr_base(buf->st_rdev, 16, 1);
	}
	else
		ft_putnbr(buf->st_size);
	ft_putstr("\t");
	ft_putstr_len(&ctime(&buf->st_mtime)[4], 12);
	ft_putstr(" ");
	ft_putstr(name);
	if (S_ISLNK(buf->st_mode))
	{
		readlink(full_path, buff, PATH_MAX);
		ft_putstr(" -> ");
		ft_putstr(buff);
	}
	free(buf);
	free(full_path);
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
	ft_putstr("\n");
	lstat(full_path, buf);
	print_file_permissions(buf->st_mode);
	ft_putstr(" ");
	ft_putnbr(buf->st_nlink);
	ft_putstr(" ");
	ft_putstr(user_name(buf->st_uid));
	ft_putstr("  ");
	ft_putstr(group_name(buf->st_gid));
	ft_putstr("  ");
	long_format_part_2(name, buf, buff, full_path);
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
