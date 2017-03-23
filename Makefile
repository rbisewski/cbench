# Version
VERSION = 17.3

# Includes
INCLUDES= -I. \
          -I/usr/include

# Libraries
LIBS= -L/usr/lib \
      -lm

# Flags
CFLAGS = -std=c99 \
         -O3 \
         -fopenmp \
         -fpic \
         -Wall \
         -Wextra \
         -Wpedantic \
         -Wno-missing-braces \
         -DVERSION=\"${VERSION}\"

# Compiler
CC = cc

# Headers
HDR = cbench.h \
      misc.h \
      vec.h \
      ray.h \
      sphere.h

# C sources
SRC = cbench.c \
      misc.c \
      vec.c \
      ray.c \
      sphere.c

# C objects
OBJ = ${SRC:.c=.o}


#
# Makefile options
#


# State the "phony" targets
.PHONY: all clean


all: cbench

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

cbench: ${OBJ}
	@echo ${CC} ${CFLAGS} ${INCLUDES} -o $@ ${LIBS} $^
	@${CC} ${CFLAGS} ${INCLUDES} -o $@ ${LIBS} $^

clean:
	@echo cleaning
	@rm -f cbench *.o output.ppm
