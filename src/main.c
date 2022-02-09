/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:16:20 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/10 01:09:13 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//	reads and saves present flags
static int	check_flags(int argc, char **argv, t_flags *flags)
{
	int		i;
	int		j;
	int		res;

	res = 1;
	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][0] == '-')
		{
			while (argv[i][j])
			{
				if (argv[i][j] == 'l')
					flags->l = 1;
				else if (argv[i][j] == 'R')
					flags->R = 1;
				else if (argv[i][j] == 'a')
					flags->a = 1;
				else if (argv[i][j] == 'r')
					flags->r = 1;
				else if (argv[i][j] == 't')
					flags->t = 1;
				j++;
			}
		}
		else
			res = 0;
		i++;
	}
	return (res);
}

void	ls_all(int argc, char **argv, t_flags flags)
{
	int		i;
	int		j;

	i = 1;
	while (i < argc)
	{
		ls_dir(argv[i], flags, 0);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_flags	flags;
	int		has_nonflag;

	ft_bzero(&flags, sizeof(t_flags));
	if (check_flags(argc, argv, &flags))
		ls_dir(".", flags, 0);
	else
		ls_all(argc, argv, flags);
	ft_putstr("\n");
	return(0);
}
