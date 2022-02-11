/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuikka <vkuikka@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:18:28 by vkuikka           #+#    #+#             */
/*   Updated: 2022/02/11 11:49:04 by vkuikka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdio.h>
# include "../libftprintf/printf.h"
# include "../libftprintf/libft/includes/libft.h"

// # include <sys/ioctl.h>
// # include <sys/xattr.h>
// # include <sys/types.h>

# include <sys/stat.h>	// lstat (file info)
# include <dirent.h> 	// DIR
# include <time.h>		// ctime() (time to string)
# include <pwd.h>		// getpwuid (uid to string)
# include <grp.h>		// getgrgid (uid to string)
# include <limits.h>	// PATH_MAX

typedef struct dirent	t_dirent;

typedef struct s_flags
{
	int		flags_present;
	int		a;	// all files
	int		t;	// time sort
	int		r;	// reverse sort
	int		R;	// recursive
	int		l;	// long format
}	t_flags;

/*
**	SORT
*/
void	sort_args_alphabetical(int argc, char **argv);
void	sort_files_alphabetical(t_dirent **files, int reverse);
void	sort_files_time(char *path, t_dirent **files, int reverse);

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
void	long_format(char *path, char *name);
void	blocks_total(t_dirent **dirs, t_flags flags, char *path);
void	print_unfound(int argc, char **argv, t_flags flags);

#endif
