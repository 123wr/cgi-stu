CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= I_add.cgi I_del.cgi I_mod.cgi I_sel.cgi C_add.cgi C_del.cgi C_mod.cgi C_sel.cgi S_add.cgi S_del.cgi S_mod.cgi S_sel.cgi

all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./*.cgi

install:
	cp *.cgi /usr/lib/cgi-bin/sx/
