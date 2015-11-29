
#PATH to your ipopt
IPOPTPATH = $(HOME)/packages/ipopt

# C++ Compiler command
CXX = /usr/local/bin/g++

# C++ Compiler options
#CXXFLAGS = -O3 --std=c++11 -pipe -DNDEBUG -Wparentheses -Wreturn-type -Wcast-qual -Wall -Wpointer-arith -Wwrite-strings -Wconversion -Wno-unknown-pragmas -Wno-long-long   -DIPOPT_BUILD

CXXFLAGS = -O3 --std=c++11 -m64
# additional C++ Compiler options for linking
CXXLINKFLAGS = 

#IPOPT include and linking path
#Mostly you could copy the following from the Ipopt/example/Cpp_example/Makefile
# Include directories (we use the CYGPATH_W variables to allow compilation with Windows compilers)
#INCL = `PKG_CONFIG_PATH=$(IPOPTPATH)/lib64/pkgconfig:$(IPOPTPATH)/lib/pkgconfig:$(IPOPTPATH)/share/pkgconfig: pkg-config --cflags ipopt` $(ADDINCFLAGS)
INCL = -I`$(CYGPATH_W) $(IPOPTPATH)/include/coin` -I$(IPOPTPATH)/include/coin/ThirdParty  $(ADDINCFLAGS)

# Linker flags
#LIBS = `PKG_CONFIG_PATH=$(IPOPTPATH)/lib64/pkgconfig:$(IPOPTPATH)/lib/pkgconfig:$(IPOPTPATH)/share/pkgconfig: pkg-config --libs ipopt`
#LIBS = -L$(IPOPTPATH)/lib -lipopt -L$(IPOPTPATH)/lib -lcoinhsl -L/usr/local/gfortran/lib/gcc/x86_64-apple-darwin13/4.9.0 -L/usr/local/gfortran/lib/gcc/x86_64-apple-darwin13/4.9.0/../../.. -lgfortran -lSystem -lquadmath -lm -llapack -lblas -ldl

LIBS = -L$(IPOPTPATH)/lib -lipopt -L$(IPOPTPATH)/lib -lcoinhsl -lgfortran -lSystem -lquadmath -lm -llapack -lblas -ldl
# The following is necessary under cygwin, if native compilers are used
CYGPATH_W = echo

all: $(EXE)

.SUFFIXES: .cpp .c .o .obj

$(EXE): $(OBJS)
	bla=;\
	for file in $(OBJS); do bla="$$bla `$(CYGPATH_W) $$file`"; done; \
	$(CXX) $(CXXLINKFLAGS) $(CXXFLAGS) -o $@ $$bla  $(LIBS) $(ADDLIBS)

clean:
	rm -rf $(EXE) $(OBJS);

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $@ $<


.cpp.obj:
	$(CXX) $(CXXFLAGS) $(INCL) -c -o $@ `$(CYGPATH_W) '$<'`



