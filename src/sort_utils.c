/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:52:33 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/15 17:04:5 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap_string(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	push_string(char **str, int i, int j)
{
	char	*tmp;

	tmp = str[j];
	while (j > i && j > 0)
	{
		str[j] = str[j - 1];
		j--;
	}
	str[j] = tmp;
}

void	swap_stats(t_stats *a, t_stats *b)
{
	t_stats		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	push_stats(t_stats **files, int i, int j)
{
	t_stats	*tmp;

	tmp = files[j];
	while (j > i && j > 0)
	{
		files[j] = files[j - 1];
		j--;
	}
	files[j] = tmp;
}
