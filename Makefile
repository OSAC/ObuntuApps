#root directory for src and bin
SRC_ROOT=./osac-pack/usr/share/doc
BIN_ROOT=./osac-pack/usr/bin
MAN_ROOT=usr/share/man/man1
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

deb: o-prime o-notice o-hide o-encrypt o-copy
	dpkg-deb -b osac-pack osac-pack.deb
install:
	cp $(BIN_ROOT)/* /usr/bin/
	cp ./osac-pack/$(MAN_ROOT)/* /$(MAN_ROOT)/
clean:
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
