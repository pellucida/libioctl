/*
// @(#) libioctl.c - intercept ioctl requests 
//
//	Here we edit the return values from the system call
//	alternatively we could alter the parameters before
//	the system call or even both.
*/
# define	_GNU_SOURCE
# include	<dlfcn.h>

# include	<sys/ioctl.h>

# include	<stdarg.h>
# include	<string.h>
# include	<stdlib.h>

static	int	(*real_ioctl)(int, unsigned long,...)	= 0;

static void	__attribute__((constructor)) hook_ioctl() {
	real_ioctl	= dlsym (RTLD_NEXT, "ioctl");	
}

extern	void	__attribute__((visibility("hidden")))
	redact_ioctl_call (int fd, unsigned long int request, ...);

int ioctl (int fd, unsigned long int request, ...) { 
	va_list	ap;
	va_start (ap, request);
	void*	arg	= va_arg (ap, void*);

	int	result 	= real_ioctl (fd, request, arg);

	redact_ioctl_call (fd, request, arg);

	va_end(ap);
	return result;
}
