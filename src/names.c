/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 18:55:43 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/09 18:58:09 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*user_name(int uid)
{
	struct passwd	*pw;

	pw = getpwuid(uid);
	return (pw->pw_name);
}

char	*group_name(int gid)
{
	struct group	*gr;

	gr = getgrgid(gid);
	return (gr->gr_name);
}
