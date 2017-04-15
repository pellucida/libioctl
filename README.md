# libioctl

### Intercept a Linux ioctl system call and edit its returned values.

Using the ELF run time loader (ld.so) to intercalate shared objects
before the system library (glibc) we can alter the values passed into
a system call (or any library function) and modify the values returned.
Ioctl(2) is no exception.

#### Note: Linux specific and uses GCC extensions.

The example provided (hwaddr.c) will alter the hardware address returned
for a specific interface when the SIOCGIFHWADDR networking ioctl is invoked.

The default interface (eth0) and returned hardware
address (BA:DB:AD:C0:FF:EE) that have been compiled in can also be altered at
run time using environment variables REDACT_HWADDR, REDACT_INTERFACE

If using LD_PRELOAD is undesirable patchelf 
(https://nixos.org/patchelf.html)
to insert this shared library into the DT_NEEDED part of the ELF header of your
executable (or another shared object)

eg 
````
# Assume myprog is in $INSTDIR/bin and libioctl.so.1 is in $INSTDIR/lib64
patchelf --add-needed '${ORIGIN}/../lib64/libioctl.so.0' myprog
````
### LICENSE
Creative Commons CC0
(http://creativecommons.org/publicdomain/zero/1.0/legalcode)

### AUTHOR
[mailto:toves@sdf.lonestar.org](James Sainsbury)
