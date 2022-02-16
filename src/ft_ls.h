/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:18:28 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/16 19:24:24 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBS

	# include <sys/stat.h>	// lstat (file info)
	# include <dirent.h> 	// DIR
	# include <time.h>		// ctime() (time to string)
	# include <pwd.h>		// getpwuid (uid to string)
	# include <grp.h>		// getgrgid (uid to string)
	# include <limits.h>	// PATH_MAX
	# include <string.h>	// strerror
	# include <errno.h>		// errno

** FLAGS

	int		a;	// all files
	int		t;	// time sort
	int		r;	// reverse sort
	int		R;	// recursive
	int		l;	// long format
*/

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>

# include "../libft/includes/libft.h"
# include <sys/stat.h>
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <limits.h>
# include <string.h>
# include <errno.h>

typedef struct dirent	t_dirent;

typedef struct s_flags
{
	int		flags_present;
	int		a;
	int		t;
	int		r;
	int		rec;
	int		l;
}	t_flags;

typedef struct s_stats
{
	char	*d_name;
	char	*path;
	char	d_type;
	char	no_recursion;
}	t_stats;

/*
**	SORT
*/
void	sort_args_alphabetical(int argc, char **argv, int reverse);
void	sort_args_time(int argc, char **argv, int reverse);
void	sort_files_alphabetical(t_stats **files, int reverse);
void	sort_files_time(char *path, t_stats **files, int reverse);

/*
** UTILS
*/
void	swap_string(char **a, char **b);
void	push_string(char **str, int i, int j);
void	swap_stats(t_stats *a, t_stats *b);
void	push_stats(t_stats **files, int i, int j);
void	free_dirs(t_stats **names);
t_stats	**init_names(char **path, int depth);

/*
**	LS
*/
void	ls_dir(char *path, t_flags flags, int depth);

/*
**	NAMES
*/
char	*group_name(int gid);
char	*user_name(int uid);

/*
**	PRINT
*/
void	depth_print(char *str, int depth);
void	print_file_permissions(unsigned short st_mode);
void	long_format(char *path, char *name, int first);
void	blocks_total(t_stats **dirs, t_flags flags, char *path);
int		print_unfound(int argc, char **argv, t_flags flags);
void	print_filename_error(char *path);
void	unfound_newline_or_tab(int first);

void	free_dirs(t_stats **names);
DIR		*arg_permission(char *str, int printed);

#endif
