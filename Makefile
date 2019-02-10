CFLAGS=-std=c11 -Wall -Wextra -pedantic -g
FICHEIROS=verifica.c verifica.h ancora.c ancora.h openFile.c openFile.h cgi.h estado.c estado.h exemplo.c Makefile
EXECUTAVEL=GandaGalo

install: $(EXECUTAVEL)
	sudo cp $(EXECUTAVEL) /usr/lib/cgi-bin
	touch install

$(EXECUTAVEL): exemplo.o estado.o openFile.o ancora.o verifica.o
	cc -o $(EXECUTAVEL) exemplo.o estado.o openFile.o ancora.o verifica.o

imagens:
	sudo mkdir -p /var/www/html/images
	sudo cp *.png /var/www/html/images

tabuleiro:
	sudo cp tabuleiro.txt /usr/lib/cgi-bin
	
save:
	sudo chmod -R a+rwx /usr/local/games/GandaGalo/
	sudo chmod -R a+rwx /usr/local/games/GandaGalo/stack/

GandaGalo.zip: $(FICHEIROS)
	zip -9 GandaGalo.zip $(FICHEIROS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o $(EXECUTAVEL) Doxyfile latex html install

estado.o: estado.c estado.h
exemplo.o: ancora.h openFile.h exemplo.c cgi.h estado.h
openFile.o: openFile.c openFile.h
ancora.o: ancora.c ancora.h
verifica.o: verifica.c verifica.h