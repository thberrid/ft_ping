/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping_send.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:44:03 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/05 19:44:23 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

static void		ping_packet_update(struct icmp_packet *packet, int sequence)
{
	packet->header.un.echo.sequence = ft_htons(sequence);
	packet->header.checksum = 0;
	packet->header.checksum = checksum(packet, sizeof(struct icmp_packet));
}

void			ping_send(
					int sockfd,
					struct addrinfo *addrinfo,
					struct icmp_packet *packet, 
					int sequence
				)
{
	int		retrn;

	ping_packet_update(packet, sequence);
	retrn = sendto(
		sockfd,
		packet,
		sizeof(struct icmp_packet),
		0,
		addrinfo->ai_addr,
		addrinfo->ai_addrlen
	);
	if (retrn <= 0)
	{
		print_return_code(e_error_sendto);
		exit(e_error_sendto);
	}
	g_pingu.previous_ping_status = SEND;
	gettimeofday(&g_pingu.previous_ping_sendtime, NULL);
	return ;
}