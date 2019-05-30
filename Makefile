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

bignum_dbg: $(SRCDIR)/Bignum.cpp
	$(CPP) -o $(BINDIR)/$@ $< $(DEF)
	(cd $(BINDIR);./bignum_dbg)

matrix_dbg: $(SRCDIR)/Matrix.cpp bignum
	$(CPP) -o $(BINDIR)/$@ $< $(DEF) $(BINDIR)/bignum.o
	(cd $(BINDIR);./matrix_dbg)

polish_dbg: $(SRCDIR)/Polish.cpp matrix bignum
	$(CPP) -o $(BINDIR)/$@ $< $(DEF) $(BINDIR)/matrix.o $(BINDIR)/bignum.o
	(cd $(BINDIR);./polish_dbg)

run:
	cd $(BINDIR);./main

clean:
	rm -f $(BINDIR)/*
