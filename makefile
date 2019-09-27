CC = arm-linux-gcc 
SRC = $(wildcard ./src/*.c)
IFLAGS = -I ./include
LFLAGS = -L ./lib
bin/main:$(SRC)
	$(CC) $^ -o $@  $(IFLAGS) -lpthread
clean:
	$(RM) main

