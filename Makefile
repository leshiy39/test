#
# Makefile.  Generated from Makefile.in by configure.
#

sourcefiles = $(srcdir)/socketcand.c $(srcdir)/statistics.c $(srcdir)/beacon.c \
             $(srcdir)/state_bcm.c $(srcdir)/state_raw.c $(srcdir)/state_control.c
executable = socketcand
sourcefiles_cl = $(srcdir)/socketcandcl.c
executable_cl = socketcandcl
srcdir = .
prefix = /usr/local
exec_prefix = ${prefix}
datarootdir = ${prefix}/share
bindir = ${exec_prefix}/bin
mandir = ${datarootdir}/man
sysconfdir = ${prefix}/etc
CFLAGS =  -Wall -Wno-parentheses -DPF_CAN=29 -DAF_CAN=PF_CAN
LIBS = -lpthread -lconfig 
init_script = yes
rc_script = no
CC = gcc
LDFLAGS = 
DEFS = -DHAVE_CONFIG_H
CPPFLAGS = 
sysroot = 

all: socketcand socketcandcl

socketcand: $(sourcefiles)
	$(CC) $(CFLAGS) $(DEFS) $(CPPFLAGS) $(LDFLAGS) -I . -o $(executable) $(sourcefiles) $(LIBS)

socketcandcl: $(sourcefiles_cl)
	$(CC) $(CFLAGS) $(DEFS) $(CPPFLAGS) $(LDFLAGS) -I . -o $(executable_cl) $(sourcefiles_cl)

clean:
	rm -f $(executable) $(executable_cl) *.o

distclean:
	rm -f $(executable) $(executable_cl) *.o *~ Makefile config.h

install: socketcand
	mkdir -p $(DESTDIR)$(sysroot)$(bindir)
	cp $(srcdir)/socketcand $(DESTDIR)$(sysroot)$(bindir)/
	cp $(srcdir)/socketcandcl $(DESTDIR)$(sysroot)$(bindir)/
	mkdir -p $(DESTDIR)$(sysroot)$(mandir)
	cp $(srcdir)/socketcand.1 $(DESTDIR)$(sysroot)$(mandir)/
	mkdir -p $(DESTDIR)$(sysroot)/etc/
	install -m 0644 $(srcdir)/etc/socketcand.conf $(DESTDIR)$(sysroot)/etc/
	if [ $(init_script) = yes ]; then mkdir -p $(DESTDIR)$(sysroot)/etc/init.d; install --mode=755 $(srcdir)/init.d/socketcand $(DESTDIR)$(sysroot)/etc/init.d/socketcand; fi
	if [ $(rc_script) = yes ]; then install --mode=755 $(srcdir)/rc.d/socketcand $(DESTDIR)$(sysroot)/etc/rc.d/socketcand; fi
