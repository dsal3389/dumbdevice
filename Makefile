

CC=gcc
C_FLAGS=-Wall -std=c11


build: conf.h
	$(CC) $(C_FLAGS) src/dumbdevice/*.c -o dumbdevice.bin

conf.h:
	cp -f src/dumbdevice/conf.def.h src/dumbdevice/$@

install: build conf.h
	cp -f dumbdevice.bin /usr/local/bin/dumbdevice
	echo "/usr/local/bin/dumbdevice" >> /etc/shells

clean:
	rm -f dumbdevice src/dumbdevice/conf.h
