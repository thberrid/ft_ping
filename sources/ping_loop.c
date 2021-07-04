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
	
	retrn = ping_prepare(&packet, &sockfd, &addrinfo, options);
	if (retrn != e_error_none)
		return (retrn);
	ping_print_intro(addrinfo, options);
	index = 1;
	while (index <= options->count || options->count < 1)
	{
		ft_printf(":: 0\n");
		ping_packet_update(&packet, index);
		ft_printf(":: 1\n");
		retrn = sendto(sockfd, &packet, sizeof(struct icmp_packet), 0, addrinfo->ai_addr, addrinfo->ai_addrlen);
		ft_printf(":: 2\n");
		if (retrn < 1)
			return (e_error_sendto);
		retrn = ping_reception(sockfd, addrinfo, options);
		if (retrn != e_error_none)
			return (retrn);
		index += 1;
	}
	return (e_error_none);
}
