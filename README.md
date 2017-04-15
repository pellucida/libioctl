# libioctl

### Intercept a Linux ioctl system call and edit its returned values.

Using the ELF run time loader (ld.so) to intercalate shared objects
before the system library (glibc) we can alter the values passed into
a system call (or any library function) and modify the values returned.
Ioctl(2) is no exception.

#### Note: Linux specific and uses GCC extensions.

The example provided (hwaddr.c) will alter the hardware address returned
for a specific interface when the SIOCGIFHWADDR networking ioctl is invoked.

The default interface (here eth0) and returned hardware (ethernet)
address (BA:DB:AD:C0:FF:EE) which are compiled in can be altered at
run time using environment variables REDACT_HWADDR, REDACT_INTERFACE

If using LD_PRELOAD is undesirable patchelf (https://nixos.org/patchelf.html)
to insert this shared library into the DT_NEEDED part of the ELF header of your
executable (or another shared object)

eg patchelf --add-needed '${ORIGIN}/../lib64/libioct.so.0' myprog
