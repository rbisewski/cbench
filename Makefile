# Version
VERSION = 17.3

# Includes
INCLUDES= -I. \
          -I/usr/include

# Libraries
LIBS= -L/usr/lib 

# Flags
CFLAGS = -std=c++98 \
         -O3 \
         -fopenmp \
         -fpic \
         -Wall \
         -Wextra \
         -Wpedantic \
         -Wno-missing-braces \
         -DVERSION=\"${VERSION}\"

# Compiler
CC = g++

# Headers
HDR = cbench.h \
      vec.h \
      ray.h \
      sphere.h

# C sources
SRC = cbench.c \
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
	@echo ${CC} ${CFLAGS} ${INCLUDES} ${LIBS} -o $@ $^
	@${CC} ${CFLAGS} ${INCLUDES} ${LIBS} -o $@ $^

clean:
	@echo cleaning
	@rm -f cbench *.o
