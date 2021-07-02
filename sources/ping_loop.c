/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 15:16:00 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/02 15:16:02 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

int			ping_loop(t_options *options)
{
	int					retrn;
	int					index;
	int					sockfd;
	struct addrinfo 	*addrinfo;
	struct icmp_packet	packet;
	
	retrn = ping_packet_prepare(&sockfd, &addrinfo, options);
	if (retrn != e_error_none)
		return (retrn);
	index = 0;
	while (index < options->count || options->count < 1)
	{
		ping_packet_update();
			// -> packet.header.un.echo.sequence = index;
			// -> packet->header.checksum = checksum(packet, sizeof(struct icmp_packet));
		retrn = sendto(sockfd, &packet, addrinfo->ai_addr, sizeof(struct sockaddr_in));
		index += 1;
	}
	return (e_error_none);
}
