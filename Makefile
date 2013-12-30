#root directory for src and bin
SRC_ROOT=./usr/share/src
BIN_ROOT=./usr/bin
MAN_ROOT=./usr/share/man/man1
all:o-copy o-encrypt o-hide o-notice o-prime
o-copy:
	gcc $(SRC_ROOT)/o-copy/o-copy.c -o $(BIN_ROOT)/o-copy
	gcc $(SRC_ROOT)/o-copy/o-cut.c -o $(BIN_ROOT)/o-cut
	gcc $(SRC_ROOT)/o-copy/o-paste.c -o $(BIN_ROOT)/o-paste
o-encrypt:
	g++ $(SRC_ROOT)/o-encrypt/o-encrypt.cpp -o $(BIN_ROOT)/o-encrypt
o-hide:
	gcc $(SRC_ROOT)/o-hide/o-hide.c -o $(BIN_ROOT)/o-hide
o-notice:
	gcc $(SRC_ROOT)/o-notice/o-notice.c -o $(BIN_ROOT)/o-notice
o-prime:
	gcc $(SRC_ROOT)/o-prime/o-prime.c -o $(BIN_ROOT)/o-prime -lm
clean:
	rm -rf ./osac-pack.deb
	rm -rf ./usr/bin/*
install:
	cp $(BIN_ROOT)/* /usr/bin/
	cp $(MAN_ROOT)/* /usr/share/man/man1/
uninstall:
	rm /usr/bin/o-prime
	rm /usr/bin/o-notice
	rm /usr/bin/o-hide
	rm /usr/bin/o-encrypt
	rm /usr/bin/o-copy
	rm /usr/bin/o-cut
	rm /usr/bin/o-paste
	rm /$(MAN_ROOT)/o-*
	rm /$(MAN_ROOT)/obunt*
	rm /$(MAN_ROOT)/osac*
deb:
	make
	mkdir ./osac-pack
	cp -r ./DEBIAN ./osac-pack/
	cp -r ./usr ./osac-pack/
	dpkg -b ./osac-pack/
	rm -rf ./osac-pack/
