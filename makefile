INCLUDE = -I ./libfdr
CC = gcc
ALL = kripto
LIBS =  libfdr/libfdr.a
all: $(ALL)

clean:
	rm -f *.o core $(ALL)
cleanall:
	rm -f *.o core $(ALL) ./ornek_metin ./encripted ./decripted ./.kilit ./*txt
kripto: 
	$(CC) -g $(INCLUDE) -o kripto ./main.c $(LIBS)
run:
	$(CC) -g $(INCLUDE) -o kripto ./main.c $(LIBS)
	./kripto -e ornek_metin encripted
	./kripto -d encripted decripted
