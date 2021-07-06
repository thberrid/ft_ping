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

static void		ping_packet_update(struct icmp_packet *packet)
{
	int		sequence;

	sequence = ft_htons(packet->header.un.echo.sequence);
	packet->header.un.echo.sequence = ft_htons(sequence + 1);
	packet->header.checksum = 0;
	packet->header.checksum = checksum(packet, sizeof(struct icmp_packet));
}

void			ping_send(int signum)
{
	int		retrn;

	if (signum != SIGALRM)
		return ;
	ping_packet_update(&g_pingu.sendpacket);
	retrn = sendto(g_pingu.sockfd, &g_pingu.sendpacket, sizeof(struct icmp_packet), 0, g_pingu.addrinfo->ai_addr, g_pingu.addrinfo->ai_addrlen);
	if (retrn)
	{
		retrn = ping_reception(g_pingu.sockfd, g_pingu.addrinfo, g_pingu.options);
		if (retrn != e_error_none)
		{
			print_return_code(e_error_sendto);
			exit(e_error_sendto);
		}
		return ;
	}
	print_return_code(e_error_sendto);
	exit(e_error_sendto);
}