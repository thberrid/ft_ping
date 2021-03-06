/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:35:08 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/06 20:35:10 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ping.h>

void	ping(void)
{
	ping_print_intro(g_pingu.address_ip, g_pingu.addrinfo);
	ping_alarm(SIGALRM);
	while (1)
		g_pingu.previous_ping_status = ping_reception(
			g_pingu.sockfd,
			g_pingu.addrinfo,
			g_pingu.options
		);
	return ;
}
