/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 09:55:17 by amansour          #+#    #+#             */
/*   Updated: 2019/07/25 10:27:27 by amansour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_hash.h"

static	void	init_sha224(t_sha256_context *context)
{
	context->state[0] = 0xc1059ed8;
	context->state[1] = 0x367cd507;
	context->state[2] = 0x3070dd17;
	context->state[3] = 0xf70e5939;
	context->state[4] = 0xffc00b31;
	context->state[5] = 0x68581511;
	context->state[6] = 0x64f98fa7;
	context->state[7] = 0xbefa4fa4;
}

void			sha224(char *msg, t_flags flags, char *filename, t_u64 len)
{
	t_sha256_context	c;
	t_u8				*new_msg;

	init_sha224(&c);
	if ((c.len = prepare_msg(msg, &new_msg, len)))
	{
		hash_sha_256(&c, &new_msg, len);
		free(new_msg);
		print_sha256(c, flags, filename, "SHA224");
	}
}
