
NAME=libioctl
SONAME=$(NAME).so.0

OBJ=ioctl.o hwaddr.o
# Noticed when LD_PRELOADED executables complain about 'dlsym' missing
LIBES=-ldl

CFLAGS=-fPIC
LDFLAGS=--shared -Wl,-soname=$(SONAME) $(LIBES)
.c.o:
	$(CC) -c $(CFLAGS) $<

$(SONAME):	$(OBJ)
	$(CC) -o $(SONAME) $(LDFLAGS) $(OBJ)

clean:
	rm -f *.o *.so *.so.?


