CC = gcc
CCFLAGS = 

SOURCES = 

build: $(shell pwd)/*.c
	for file in "$^ " ; do \
		${CC} ${CCFLAGS} $${file} -o ../rootfs/bin/$$(basename "$${file%.*}"); \
	done