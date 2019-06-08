CPP=g++
DEF=-DDEBUG

BINDIR=../bin
SRCDIR=../src
TESTDIR=.

all: fileutil matrix bignum polish main

fileutil: $(SRCDIR)/FileUtil.cpp
	$(CPP) -c -o $(BINDIR)/$@.o $<

bignum: $(SRCDIR)/Bignum.cpp
	$(CPP) -c -o $(BINDIR)/$@.o $<

matrix: $(SRCDIR)/Matrix.cpp
	$(CPP) -c -o $(BINDIR)/$@.o $<

polish: $(SRCDIR)/Polish.cpp
	$(CPP) -c -o $(BINDIR)/$@.o $<

bignum_dbg: $(TESTDIR)/testbignum.cpp bignum
	$(CPP) -o $(BINDIR)/$@ $< $(DEF) $(BINDIR)/bignum.o
	(cd $(BINDIR);./bignum_dbg)

matrix_dbg: $(TESTDIR)/testmatrix.cpp bignum matrix
	$(CPP) -o $(BINDIR)/$@ $< $(DEF) $(BINDIR)/matrix.o $(BINDIR)/bignum.o
	(cd $(BINDIR);./matrix_dbg)

polish_dbg: $(TESTDIR)/testpolish.cpp matrix bignum polish
	$(CPP) -o $(BINDIR)/$@ $< $(DEF) $(BINDIR)/matrix.o $(BINDIR)/bignum.o $(BINDIR)/polish.o
	(cd $(BINDIR);./polish_dbg)

clean:
	rm -f $(BINDIR)/*
