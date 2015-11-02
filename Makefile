.PHONY: all test deps clean

all:
	cd build; cmake ${CMAKE_ARGS} -DCMAKE_INSTALL_PREFIX=$(CURDIR) ..; make all

test: all
	cd tests/build; cmake ${CMAKE_ARGS} ..; make
	./tests/build/unit ${TEST_ARGS}

deps:
	cd deps; cmake ${CMAKE_ARGS} .; make

clean:
	rm -f build/*.*
	rm -f build/Makefile
	rm -f -r build/CMake*
	rm -f lib/*.*
	rm -f tests/build/*.*
	rm -f tests/build/Makefile
	rm -f -r tests/build/CMake*
	rm -f deps/CMakeCache.txt
	rm -f deps/cmake_install.cmake
	rm -f deps/Makefile
	rm -f -r deps/CMakeFiles
	rm -f -r deps/curl/include
	rm -f -r deps/curl/lib
	rm -f -r deps/curl/src
	rm -f -r deps/curl/tmp
	rm -f -r deps/gtest/include
	rm -f -r deps/gtest/lib
	rm -f -r deps/gtest/src
	rm -f -r deps/gtest/tmp
	rm -f -r deps/iconv/include
	rm -f -r deps/iconv/lib
	rm -f -r deps/iconv/src
	rm -f -r deps/iconv/tmp
	rm -f -r deps/yajl/include
	rm -f -r deps/yajl/lib
	rm -f -r deps/yajl/src
	rm -f -r deps/yajl/tmp
