# libioctl

## Intercept a Linux ioctl system call and edit its returned values.

Note: Linux specific and uses GCC extensions.

The example (hwaddr.c) will alter the returned hardware address returned
for a specific interface for the SIOCGIFHWADDR networking ioctl.
The default interface (here eth0) and returned hardware (ethernet)
address (BA:DB:AD:C0:FF:EE) which are compiled in can be altered at
run time using environment variables REDACT_HWADDR, REDACT_INTERFACE

If using LD_PRELOAD is undesirable use patchelf (https://nixos.org/patchelf.html) to insert this 
library into the DT_NEEDED part of the ELF header of your executable
(or another shared object)

eg patchelf --add-needed '${ORIGIN}/../lib64/libioct.so.0' myprog
