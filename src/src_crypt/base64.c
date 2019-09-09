/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 13:58:46 by amansour          #+#    #+#             */
/*   Updated: 2019/09/02 08:52:02 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "../libft/inc/libft.h"

static void		read_args(t_flags *f, int argc, char **argv)
{
	int i;

	init_flags(f);
	i = 1;
	while (++i < argc)
	{
		if ((!(ft_strcmp(argv[i], "-i")) || !(ft_strcmp(argv[i], "-o"))) && \
				!argv[i + 1])
			usage_base64();
		else if (!(ft_strcmp(argv[i], "-i")))
			f->in = argv[++i];
		else if (!(ft_strcmp(argv[i], "-o")))
			f->out = argv[++i];
		else if (!(ft_strcmp(argv[i], "-e")))
			f->encrypt = 1;
		else if (!(ft_strcmp(argv[i], "-d")))
			f->decrypt = 1;
	}
}

void			base64(int argc, char **av)
{
	t_flags		flags;
	uint64_t	l;
	char		*msg;

	read_args(&flags, argc, av);
	if (flags.in && (flags.fd_in = open(flags.in, O_RDONLY)) == -1)
	{
		file_error("base64", flags.in);
		return ;
	}
	if (flags.out && (flags.fd_out = \
				open(flags.out, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	{
		file_error("base64", flags.in);
		return ;
	}
	l = read_stdin(flags.fd_in, &msg);
	flags.decrypt ? base64_decode(msg, l, flags.fd_out) : \
		base64_encode(msg, l, flags.fd_out);
	free(msg);
}