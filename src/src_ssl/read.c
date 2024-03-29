/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 10:01:18 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 10:01:32 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void		read_process(char **buf, int i, char **str)
{
	char *temp;

	temp = *str;
	*str = ft_strjoin_s(temp, *buf, i);
	temp ? free(temp) : 0;
	*buf ? free(*buf) : 0;
	*buf = ft_strnew(BUF);
}

t_u64			read_function(int fd, char **str)
{
	char	*buf;
	char	ch;
	t_u64	i;
	char	*temp;

	*str = NULL;
	buf = ft_strnew(BUF);
	i = 0;
	while (read(fd, &ch, 1) > 0)
	{
		if ((i % BUF) == 0 && i > 0)
			read_process(&buf, i, str);
		buf[i % BUF] = ch;
		++i;
	}
	if (*str)
		temp = ft_strjoin_s(*str, buf, i);
	else
		temp = ft_strndup(buf, (int)i);
	buf ? free(buf) : 0;
	*str ? free(*str) : 0;
	*str = temp;
	return (i);
}
