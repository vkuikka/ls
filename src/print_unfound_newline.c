/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unfound_newline.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 01:48:21 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/16 02:07:17 by vkuikka          ###   ########.fr       */
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
