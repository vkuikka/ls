/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:16:20 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/11 11:40:13 by vkuikka          ###   ########.fr       */
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
		if (argv[i][0] != '-')
			return (i < argc);
		else
			flags->flags_present++;
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
		i++;
	}
	return (0);
}

void	ls_all(int argc, char **argv, t_flags flags)
{
	int		i;
	DIR		*d;

	if (argc <= 1 + flags.flags_present)
	{
		ls_dir(".", flags, 0);
		return ;
	}
	print_unfound(argc, argv, flags);
	i = 1 + flags.flags_present;
	while (i < argc)
	{
		if (argc - flags.flags_present > 2)
			ft_printf("%s:\n", argv[i]);
		d = opendir(argv[i]);
		if (!d)
		{
			i++;
			continue ;
		}
		closedir(d);
		ls_dir(argv[i], flags, 0);
		i++;
		if (i < argc)
			ft_putstr("\n\n");
	}
}

int	main(int argc, char **argv)
{
	t_flags	flags;

	ft_bzero(&flags, sizeof(t_flags));
	check_flags(argc, argv, &flags);
	ls_all(argc, argv, flags);
	ft_putstr("\n");
	return(0);
}
