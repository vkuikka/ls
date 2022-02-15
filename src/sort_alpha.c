/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_alpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 20:30:17 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/15 20:31:09 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_args_alphabetical(int argc, char **argv, int reverse)
{
	struct stat	*buf[2];
	int			i;
	int			j;

	i = 0;
	while (i < argc)
	{
		j = 0;
		while (j < argc)
		{
			if (!reverse && ft_strcmp(argv[i], argv[j]) < 0)
				swap_string(&argv[i], &argv[j]);
			if (reverse && ft_strcmp(argv[i], argv[j]) > 0)
				swap_string(&argv[i], &argv[j]);
			j++;
		}
		i++;
	}
}

void	sort_files_alphabetical(t_stats **files, int reverse)
{
	int		i;
	int		j;

	i = 0;
	while (files[i])
	{
		j = i;
		while (files[j])
		{
			if (i != j)
			{
				if ((!reverse ^ (j < i))
					&& ft_strcmp(files[i]->d_name, files[j]->d_name) > 0)
					swap_stats(files[i], files[j]);
				else if ((reverse ^ (j < i))
					&& ft_strcmp(files[i]->d_name, files[j]->d_name) < 0)
					swap_stats(files[i], files[j]);
			}
			j++;
		}
		i++;
	}
}
