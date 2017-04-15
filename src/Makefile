
NAME=libioctl
SONAME=$(NAME).so.0

OBJ=ioctl.o hwaddr.o

CFLAGS=-fPIC
LDFLAGS=--shared -Wl,-soname=$(SONAME)
.c.o:
	$(CC) -c $(CFLAGS) $<

$(SONAME):	$(OBJ)
	$(CC) -o $(SONAME) $(LDFLAGS) $(OBJ)

clean:
	rm -f *.o *.so *.so.?


