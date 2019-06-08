CPP=g++
DEF=-DDEBUG

BINDIR=./bin
SRCDIR=./src

all: fileutil matrix bignum polish main

main: $(SRCDIR)/Main.cpp
	$(CPP) -o $(BINDIR)/$@ $< $(BINDIR)/fileutil.o $(BINDIR)/bignum.o $(BINDIR)/matrix.o $(BINDIR)/polish.o

cmder: $(SRCDIR)/cmder.cpp fileutil matrix bignum polish
	$(CPP) -o $(BINDIR)/$@ $< $(BINDIR)/fileutil.o $(BINDIR)/bignum.o $(BINDIR)/matrix.o $(BINDIR)/polish.o

fileutil: $(SRCDIR)/FileUtil.cpp
	$(CPP) -c -o $(BINDIR)/$@.o $<

bignum: $(SRCDIR)/Bignum.cpp
	$(CPP) -c -o $(BINDIR)/$@.o $<

matrix: $(SRCDIR)/Matrix.cpp
	$(CPP) -c -o $(BINDIR)/$@.o $<

polish: $(SRCDIR)/Polish.cpp
	$(CPP) -c -o $(BINDIR)/$@.o $<

run:
	cd $(BINDIR);./main

clean:
	rm -f $(BINDIR)/*
