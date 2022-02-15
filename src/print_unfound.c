/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unfound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 21:24:11 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/16 01:49:32 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	result_value(int res, struct stat *buf)
{
	free(buf);
	if (res == 0)
		return (1);
	else if (res == -1)
		return (-1);
	return (0);
}

static void	unfound(char **argv, t_flags flags, int i, int first)
{
	if (flags.l)
	{
		if (first > 0)
			long_format("./", argv[i], 0);
		else
			long_format("./", argv[i], 1);
	}
	else
		ft_putstr(argv[i]);
	argv[i][0] = '\0';
}

static int	no_such_files(int argc, char **argv,
						t_flags flags, struct stat *buf)
{
	DIR		*d;
	int		first;
	int		i;

	first = 1;
	i = flags.flags_present;
	while (++i < argc)
	{
		d = opendir(argv[i]);
		if (!d && lstat(argv[i], buf))
		{
			if (!first)
				ft_putstr("\n");
			first = 0;
			ft_putstr("ft_ls: ");
			ft_putstr(argv[i]);
			ft_putstr(": ");
			ft_putstr(strerror(errno));
			argv[i][0] = '\0';
		}
		if (d)
			closedir(d);
	}
	return (first);
}

static int	unfound_init(int argc, char **argv,
						t_flags flags, struct stat **buf)
{
	int		f;

	f = flags.flags_present + 1;
	sort_args_alphabetical(argc - f, &argv[f], flags.r);
	if (flags.t)
		sort_args_time(argc - f, &argv[f], flags.r);
	*buf = (struct stat *)malloc(sizeof(struct stat));
	if (!*buf)
		return (0);
	return (1);
}

int	print_unfound(int argc, char **argv, t_flags flags)
{
	struct stat	*buf;
	DIR			*d;
	int			i;
	int			first;

	if (!unfound_init(argc, argv, flags, &buf))
		return (0);
	first = no_such_files(argc, argv, flags, buf);
	if (flags.l && !first)
		first = 2;
	i = flags.flags_present;
	while (++i < argc)
	{
		d = opendir(argv[i]);
		if (!lstat(argv[i], buf) && !S_ISDIR(buf->st_mode))
		{
			unfound_newline_or_tab(first);
			unfound(argv, flags, i, first);
			first = -1;
		}
		if (d)
			closedir(d);
	}
	return (result_value(first, buf));
}
