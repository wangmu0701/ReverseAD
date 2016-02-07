reverseadroot='/Users/muwang/packages/reversead'
reverseadinclude=['-I' fullfile(reverseadroot,'include')]
reverseadlib=['-L' fullfile(reverseadroot, 'lib')]

%uncomment the following line if you're compiling with clang++
%comment it if using g++
cpplibs='-stdlib=libc++ '

reverseadcxxflags=['CXXFLAGS=' '-std=c++11 ' cpplibs '$CXXFLAGS']
reverseadldflags=['LDFLAGS=' cpplibs '$LDFLAGS']

%mex -v -largeArrayDims CXXFLAGS='-std=c++11 -stdlib=libc++ $CXXFLAGS' LDFLAGS='-stdlib=libc++ $LDFLAGS' -I/Users/muwang/packages/reversead/include jacobian.cpp -L/Users/muwang/packages/reversead/lib -lreversead

mex('-v', '-largeArrayDims', reverseadcxxflags, reverseadldflags, reverseadinclude, reverseadlib, 'jacobian.cpp','-lreversead')
mex('-v', '-largeArrayDims', reverseadcxxflags, reverseadldflags, reverseadinclude, reverseadlib, 'hessian.cpp','-lreversead')
