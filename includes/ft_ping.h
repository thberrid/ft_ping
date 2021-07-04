/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <thberrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 11:24:00 by thberrid          #+#    #+#             */
/*   Updated: 2021/07/01 11:24:03 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <libft.h>
# include <ft_ping_errors.h>
# include <sys/types.h> 
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>

# define HELP_STRING		"Usage: ft_ping [-v] [-c count] destination"

/*
	iovlen = sizeof ip header (20)	+
					icmp hedr (8)	+
					ping data (56)
*/
# define IOVLEN  			84
# define ICMP_DATA_LEN		56

# define ICMP_TYPE_ECHO_REQUEST	8
# define ICMP_CODE_ECHO_REPLY	0

struct icmp_packet {
	struct icmphdr	header;
	char			data[ICMP_DATA_LEN];
};

/*
struct icmphdr
{
	u_int8_t	type;
	u_int8_t	code;
	u_int16_t	checksum;
	union
	{
		struct
		{
			u_int16_t	id;
			u_int16_t	sequence;
		} echo;                        
		u_int32_t gateway;      
		struct
		{
			u_int16_t __unused;
			u_int16_t mtu;
		} frag;                        
	} un;
};
*/

typedef struct	s_options
{
	char		help_required;
	char		verbose_required;
	int			count;
	int			ttl;
	char		*address;
}				t_options;

int				ping_loop(t_options *options);

int 			ping_prepare(struct icmp_packet *packet, int *sockfd, struct addrinfo **addrinfo, t_options *options);
void 			ping_packet_update(struct icmp_packet *packet, int index);
unsigned short	checksum(void *data, int len);
int				ping_reception(int sockfd, struct addrinfo *addrinfo, t_options *options);

void 			ping_print_intro(struct addrinfo *addrinfo, t_options *options);
void			ping_print_loop(struct ip *ipheader, t_options *options);

#endif
