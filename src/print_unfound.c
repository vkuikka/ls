/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unfound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:24:11 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/15 21:24:51by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	no_such(char *str)
{
	ft_putstr("ft_ls: ");
	ft_putstr(str);
	ft_putstr(": ");
	ft_putstr(strerror(errno));
	str[0] = '\0';
}

static void	unfound(char **argv, t_flags flags, int i)
{
	if (flags.l)
		long_format("./", argv[i]);
	else
		ft_putstr(argv[i]);
	argv[i][0] = '\0';
}

// static void	unfound_files(int argc, char **argv, t_flags flags)
// {
// }

int	print_unfound(int argc, char **argv, t_flags flags)
{
	struct stat	*buf;
	DIR			*d;
	int			i;
	int			first;

	i = flags.flags_present;
	sort_args_alphabetical(argc - (i + 1), &argv[i + 1], flags.r);
	if (flags.t)
		sort_args_time(argc - (i + 1), &argv[i + 1], flags.r);
	buf = (struct stat *)malloc(sizeof(struct stat));
	if (!buf)
		return (0);
	first = 1;
	while (++i < argc)
	{
		d = opendir(argv[i]);
		if (!d && lstat(argv[i], buf))
		{
			if (!first)
				printf("\n");
			first = 0;
			no_such(argv[i]);
		}
		if (d)
			closedir(d);
	}
	i = flags.flags_present;
	if (flags.l)
		first = 1;
	while (++i < argc)
	{
		d = opendir(argv[i]);
		if (!lstat(argv[i], buf) && !S_ISDIR(buf->st_mode))
		{
			if (!first)
				printf("\n");
			else if (first == -1)
				ft_putstr("\t");
			first = -1;
			unfound(argv, flags, i);
		}
		if (d)
			closedir(d);
	}
	free(buf);
	if (first == 0)
		return (1);
	else if (first == -1)
		return (-1);
	return (0);
}
