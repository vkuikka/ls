/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_dir_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:42:12 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/15 23:17:19 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	free_dirs(t_stats **names)
{
	int	i;

	i = -1;
	while (names[++i])
	{
		free(names[i]->d_name);
		free(names[i]);
	}
	free(names);
}

t_stats	**init_names(char **path, int depth)
{
	t_stats		**names;
	char		*tmp_path;

	if (depth > 0)
	{
		ft_putstr("\n\n");
		depth_print(*path, depth);
		ft_putstr(":");
	}
	tmp_path = ft_strjoin(*path, "/");
	if (depth > 0)
		free(*path);
	*path = tmp_path;
	names = (t_stats **)malloc(sizeof(t_stats *) * 1);
	names[0] = NULL;
	return (names);
}
