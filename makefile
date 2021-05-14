CC = gcc
ALL = odev

all: $(ALL)

clean:
	rm -f *.o core $(ALL)
odev: 
	$(CC) -g -I ./libfdr -o program ./main.c
