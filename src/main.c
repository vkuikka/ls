/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:16:20 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/16 19:22:30 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	flags_if(char *str, t_flags *flags)
{
	int		j;

	j = 0;
	while (str[j])
	{
		if (str[j] == 'l')
			flags->l = 1;
		else if (str[j] == 'R')
			flags->R = 1;
		else if (str[j] == 'a')
			flags->a = 1;
		else if (str[j] == 'r')
			flags->r = 1;
		else if (str[j] == 't')
			flags->t = 1;
		else if (str[j] != '-')
		{
			ft_putstr("ft_ls: invalid option: -- ");
			ft_putchar(str[j]);
			ft_putstr("\nusage: ft_ls [-lRart] [file ...]\n");
			exit(1);
		}
		j++;
	}
}

//	reads and saves present flags
static int	check_flags(int argc, char **argv, t_flags *flags)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-')
			return (1);
		else
		{
			if (ft_strlen(argv[i]) < 2)
				return (1);
			flags->flags_present++;
		}
		flags_if(argv[i], flags);
		i++;
	}
	return (0);
}

void	print_name(int *printed, char *name)
{
	if (*printed)
		ft_putstr("\n");
	*printed = 1;
	ft_putstr(name);
	ft_putstr(":\n");
}

void	ls_all(int argc, char **argv, t_flags flags)
{
	int		i;
	DIR		*d;
	int		printed;
	int		first;

	if (argc <= 1 + flags.flags_present)
		ls_dir(".", flags, 0);
	else
		printed = print_unfound(argc, argv, flags);
	i = 1 + flags.flags_present;
	first = 1;
	while (i < argc)
	{
		d = arg_permission(argv[i], printed);
		if (!d && ++i)
			continue ;
		if (printed == -1 || first == 0)
			ft_putstr("\n");
		if (argc - flags.flags_present > 2 && argv[i][0])
			print_name(&printed, argv[i]);
		closedir(d);
		first = 0;
		ls_dir(argv[i], flags, -1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_flags	flags;

	ft_bzero(&flags, sizeof(t_flags));
	check_flags(argc, argv, &flags);
	ls_all(argc, argv, flags);
	ft_putstr("\n");
	return (0);
}
