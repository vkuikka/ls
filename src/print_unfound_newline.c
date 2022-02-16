/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unfound_newline.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 01:48:21 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/16 19:12:16 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	unfound_newline_or_tab(int first)
{
	if (first == 2)
		ft_putstr("\n");
	if (!first || first == 2)
		ft_putstr("\n");
	else if (first == -1)
		ft_putstr("\t");
}

DIR	*arg_permission(char *str, int printed)
{
	struct stat	*buf;
	DIR			*d;

	buf = (struct stat *)ft_memalloc(sizeof(struct stat));
	if (!lstat(str, buf) && S_ISDIR(buf->st_mode) && !opendir(str))
	{
		if (printed)
			ft_putstr("\n\n");
		ft_putstr("ft_ls: ");
		ft_putstr(str);
		ft_putstr(": ");
		ft_putstr(strerror(errno));
	}
	free(buf);
	d = opendir(str);
	return (d);
}
