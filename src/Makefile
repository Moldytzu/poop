CC = gcc
CCFLAGS = -O2 -Wno-unused-result

SOURCES = 

build: $(shell pwd)/*.c
	for file in $(shell pwd)/*.c ; do \
		${CC} ${CCFLAGS} $${file} -o ../rootfs/bin/$$(basename "$${file%.*}"); \
	done