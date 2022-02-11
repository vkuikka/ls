/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:51:25 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/11 11:42:55 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_file_type(unsigned short st_mode)
{
	if (S_ISLNK(st_mode))
		ft_putstr("l");
	else if (S_ISDIR(st_mode))
		ft_putstr("d");
	else
		ft_putstr("-");
}

static void	print_file_permissions_part3(unsigned short st_mode)
{
	if (st_mode & S_IROTH)
		ft_putstr("r");
	else
		ft_putstr("-");
	if (st_mode & S_IWOTH)
		ft_putstr("w");
	else
		ft_putstr("-");
	if (st_mode & S_ISVTX)
	{
		if (st_mode & S_IXOTH)
			ft_putstr("t");
		else
			ft_putstr("T");
	}
	else
	{
		if (st_mode & S_IXOTH)
			ft_putstr("x");
		else
			ft_putstr("-");
	}
}

static void	print_file_permissions_part2(unsigned short st_mode)
{
	if (st_mode & S_IRGRP)
		ft_putstr("r");
	else
		ft_putstr("-");
	if (st_mode & S_IWGRP)
		ft_putstr("w");
	else
		ft_putstr("-");
	if (st_mode & S_ISGID)
	{
		if (st_mode & S_IXGRP)
			ft_putstr("s");
		else
			ft_putstr("S");
	}
	else
	{
		if (st_mode & S_IXGRP)
			ft_putstr("x");
		else
			ft_putstr("-");
	}
	print_file_permissions_part3(st_mode);
}

void	print_file_permissions(unsigned short st_mode)
{
	print_file_type(st_mode);
	if (st_mode & S_IRUSR)
		ft_putstr("r");
	else
		ft_putstr("-");
	if (st_mode & S_IWUSR)
		ft_putstr("w");
	else
		ft_putstr("-");
	if (st_mode & S_ISUID)
	{
		if (st_mode & S_IXUSR)
			ft_putstr("s");
		else
			ft_putstr("S");
	}
	else
	{
		if (st_mode & S_IXUSR)
			ft_putstr("x");
		else
			ft_putstr("-");
	}
	print_file_permissions_part2(st_mode);
}
