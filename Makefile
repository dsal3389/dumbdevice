

CC=gcc
C_FLAGS=-Wall -std=c11
INSTALL_PATH=/usr/local/bin/dumbdevice
OUT_BIN=dumbdevice.bin


build: conf.h
	$(CC) $(C_FLAGS) src/dumbdevice/*.c -o $(OUT_BIN)

conf.h:
	cp -f src/dumbdevice/conf.def.h src/dumbdevice/$@

install: build conf.h
	cp -f $(OUT_BIN) $(INSTALL_PATH)/$(OUT_BIN)
	echo $(INSTALL_PATH)/$(OUT_BIN) >> /etc/shells

clean:
	rm -f dumbdevice src/dumbdevice/conf.h
