/*
// @(#) hwaddr.c - rewrite the hardware address
//
//	If the ioctl is SIOCGIFHWADDR (get interface hardware address)
//	and specifies the interface we are interested in edit the returned
//	address with our desired hardware address
*/
# include	<sys/ioctl.h>
# include	<net/if.h>
# include	<netinet/ether.h>

# include	<stdarg.h>
# include	<string.h>
# include	<stdlib.h>

# define	ENV_DESIRED_HW		"REDACT_HWADDR"
# define	ENV_DESIRED_INTERFACE	"REDACT_INTERFACE"

# define	DEFAULT_ETHER		"BA:DB:AD:C0:FF:EE"
# define	DEFAULT_INTERFACE	"eth0"

enum	{ ETH_STR_SIZE	= sizeof("01:02:03:04:05:06"), };

static	char	desired_ether_str[ETH_STR_SIZE]	= DEFAULT_ETHER;
static	char	desired_interface[IF_NAMESIZE]	= DEFAULT_INTERFACE;

static	struct	ether_addr	desired_ether;


static void	__attribute__((constructor)) setup_ether_address() {
	char*	eaddr	= getenv (ENV_DESIRED_HW);
	char*	intf	= getenv (ENV_DESIRED_INTERFACE);
	if (eaddr) {
		strncpy (desired_ether_str, eaddr, sizeof(desired_ether_str));
	}
	ether_aton_r (desired_ether_str, &desired_ether);

	if (intf) {
		strncpy (desired_interface, intf, sizeof (desired_interface));
	}
}

void __attribute__((visibility("hidden")))
		redact_ioctl_call (int fd, unsigned long int request, ...) { 

	va_list	ap;
	va_start (ap, request);
	struct	ifreq*	ifrq	= va_arg (ap, struct ifreq*);
	if (request == SIOCGIFHWADDR) {
		if (strncmp (ifrq->ifr_name, desired_interface,
			sizeof(desired_interface))==0) {

			memcpy (ifrq->ifr_hwaddr.sa_data,
				desired_ether.ether_addr_octet, ETH_ALEN);
		}
	}
	va_end(ap);
}
