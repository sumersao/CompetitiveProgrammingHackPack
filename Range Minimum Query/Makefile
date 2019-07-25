CXXFLAGS = --std=c++17 -Wall -Werror -Wpedantic -O3 -g
CXX = g++
ISPC=ispc
# note: requires AVX2 capable machine
ISPCFLAGS=-O3 --target=avx2-i32x16 --arch=x86-64

OBJECTS = SparseTableISPCRMQ.o FastestRMQ.o FischerHeunRMQ.o HybridRMQ.o PrecomputedRMQ.o SparseTableRMQ.o SegmentTreeRMQ.o sparse.o
HEADERS = SparseTableISPCRMQ.h FastestRMQ.h FischerHeunRMQ.h HybridRMQ.h PrecomputedRMQ.h SparseTableRMQ.h SegmentTreeRMQ.h RMQEntry.h Timer.h

#new
OBJDIR=objs
#PATH = /afs/.ir/users/a/d/adampah/cs149/ISPC/ispc-v1.9.2-linux

default: run-tests

$(OBJECTS): Makefile

run-tests: $(OBJECTS) RunTests.o Makefile
	#$(ISPC) $(ISPCFLAGS) sparse.ispc -o sparse.o -h sparse_ispc.h
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) RunTests.o

RunTests.o: $(HEADERS) RunTests.cpp Makefile

%.o: $(HEADERS) %.cpp %.h

clean:
	rm -f run-tests *.o *~

$(OBJDIR)/%_ispc.h $(OBJDIR)//%_ispc.o: %.ispc
		$(ISPC) $(ISPCFLAGS) $< -o $(OBJDIR)/$*_ispc.o -h $(OBJDIR)/$*_ispc.h
