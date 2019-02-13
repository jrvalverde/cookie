#	Makefile for cookie programs and database.
#
#	Where the database file will be installed
LIBDIR=/u/sysadmin/txomsy/lib

#	Where to install the standalone cookie program
BINDIR=/usr/local/bin

#	http daemon root directory
HTTPDIR=/usr/local/etc/httpd

#	CGI-bin directory as seen by the http daemon
CGIBASEDIR=/cgi-bin

#	The real, physical, absolute pathname to the cgi-bin directory
CGIDIR=$(HTTPDIR)$(CGIBASEDIR)

#	Where html documents are stored.
HTDOCDIR=/usr/local/etc/httpd/htdocs

#	Where the gif backgrounds will be as seen by the http daemon
GIFBASEDIR=/images/txomsy/backgrounds

#	The absolute pathname of the gif directory for backgrounds
GIFDIR=$(HTDOCDIR)$(GIFBASEDIR)

CC=cc
CFLAGS= -O
LDFLAGS= -lm

all: cookie-cgi cook


cookie-cgi: cookie-cgi.c rnd.o
	sed -e 's|/usr/local/lib|$(LIBDIR)|g;s|/gifs|$(GIFBASEDIR)|g' cookie-cgi.c > tmp.c
	$(CC) $(CFLAGS) -o cookie-cgi tmp.c rnd.o $(LDFLAGS)
	rm tmp.c

cook: cook.c rnd.o
	sed -e 's|/usr/local/lib|$(LIBDIR)|g' cook.c > tmp.c
	$(CC) $(CFLAGS) -o cook cook.c rnd.o $(LDFLAGS)
	rm tmp.c

rnd.o: rnd.c
	$(CC) $(CFLAGS) -c rnd.c

installbin: cook cookie-cgi
	mv cookie-cgi $(CGIDIR)/.
	mv cook $(BINDIR)/.

install: cook cookie-cgi
	mv cookie-cgi $(CGIDIR)/.
	mv cook $(BINDIR)/.
	cp cookie.file $(LIBDIR)/.
	cp greytileback.gif $(GIFDIR)/.
	cp fernback.gif $(GIFDIR)/.
	cp bullback.gif $(GIFDIR)/.
	cp bambooback.gif $(GIFDIR)/.
	cp marbleback.gif $(GIFDIR)/.
	cp budhaback.gif $(GIFDIR)/.
	cp branchback.gif $(GIFDIR)/.
	cp sunriverback.gif $(GIFDIR)/.
	cp lotusback.gif $(GIFDIR)/.
	cp sback.gif $(GIFDIR)/.
	cp marble2back.gif $(GIFDIR)/.
	cp tileback.gif $(GIFDIR)/.
	cp tile2back.gif $(GIFDIR)/.
	cp jr.gif $(GIFDIR)/.

clean:
	rm -f core *.o cook cookie-cgi

uninstall:
	rm $(CGIDIR)/cookie-cgi
	rm $(BINDIR)/cook
	rm $(LIBDIR)/cookie.file
	rm $(GIFDIR)/jr.gif
	rm $(GIFDIR)/greytileback.gif
	rm $(GIFDIR)/fernback.gif
	rm $(GIFDIR)/bullback.gif
	rm $(GIFDIR)/bambooback.gif
	rm $(GIFDIR)/marbleback.gif
	rm $(GIFDIR)/budhaback.gif
	rm $(GIFDIR)/branchback.gif
	rm $(GIFDIR)/sunriverback.gif
	rm $(GIFDIR)/lotusback.gif
	rm $(GIFDIR)/sback.gif
	rm $(GIFDIR)/marble2back.gif
	rm $(GIFDIR)/tileback.gif
	rm $(GIFDIR)/tile2back.gif
