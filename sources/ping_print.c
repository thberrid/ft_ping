/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 20:20:29 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/03 20:20:31 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void			ping_print(struct icmp_packet *packet, t_options *options)
{
	(void)options;
	ft_printf("%d bytes from %s: icmp_seq=%d\n", sizeof(struct icmp_packet), packet->header.un.echo.sequence);
	return ;
}
