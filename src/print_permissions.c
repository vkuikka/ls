/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_permissions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 19:51:25 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/09 19:54:05 vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_file_type(unsigned short st_mode)
{
	if (S_ISLNK(st_mode))
		ft_printf("l");
	else if (S_ISDIR(st_mode))
		ft_printf("d");
	else
		ft_printf("-");
}

static void	print_file_permissions_part3(unsigned short st_mode)
{
	if (st_mode & S_IROTH)
		ft_printf("r");
	else
		ft_printf("-");
	if (st_mode & S_IWOTH)
		ft_printf("w");
	else
		ft_printf("-");
	if (st_mode & S_ISVTX)
	{
		if (st_mode & S_IXOTH)
			ft_printf("t");
		else
			ft_printf("T");
	}
	else
	{
		if (st_mode & S_IXOTH)
			ft_printf("x");
		else
			ft_printf("-");
	}
}

static void	print_file_permissions_part2(unsigned short st_mode)
{
	if (st_mode & S_IRGRP)
		ft_printf("r");
	else
		ft_printf("-");
	if (st_mode & S_IWGRP)
		ft_printf("w");
	else
		ft_printf("-");
	if (st_mode & S_ISGID)
	{
		if (st_mode & S_IXGRP)
			ft_printf("s");
		else
			ft_printf("S");
	}
	else
	{
		if (st_mode & S_IXGRP)
			ft_printf("x");
		else
			ft_printf("-");
	}
	print_file_permissions_part3(st_mode);
}

void	print_file_permissions(unsigned short st_mode)
{
	print_file_type(st_mode);
	if (st_mode & S_IRUSR)
		ft_printf("r");
	else
		ft_printf("-");
	if (st_mode & S_IWUSR)
		ft_printf("w");
	else
		ft_printf("-");
	if (st_mode & S_ISUID)
	{
		if (st_mode & S_IXUSR)
			ft_printf("s");
		else
			ft_printf("S");
	}
	else
	{
		if (st_mode & S_IXUSR)
			ft_printf("x");
		else
			ft_printf("-");
	}
	print_file_permissions_part2(st_mode);
}
