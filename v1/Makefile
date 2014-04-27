# Makefile

TARGET = test

SRCS += $(wildcard *.c)
OBJS = $(foreach src, $(SRCS), $(basename $(src)).o )

CC = gcc
CFLAGS += -pipe -Wall -g3


################################################################
.PHONY : all clean
all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -$(CFLAGS) -o $@ $(OBJS)

clean :
	@rm -f $(TARGET) *.o

################################################################
.SUFFIXES : .cc
.cc.o :
	$(CC) $(CFLAGS) -c -o $@ $<
