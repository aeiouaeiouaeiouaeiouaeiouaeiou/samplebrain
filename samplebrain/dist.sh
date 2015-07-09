# clean up
make distclean
# build src/config.h from configure.ac
autoheader
# build configure
autoconf configure.ac > configure
./configure 'CXX=g++-4.7' 'CXXFLAGS=-O3'
