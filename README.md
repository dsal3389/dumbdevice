# dumbdevice

this is a dumb shell written in C and mimic a device, the code style is like suckless style, the config for commands 
and shell behaviour is at the file `conf.def.h`


## build from source
```sh
git@github.com:dsal3389/dumbdevice.git && \
    cd dumbdevice && make build
```
you will see new binary called dumbdevice.bin

## install from source
this will build the binary and upload it to the configured `INSTALL_PATH` in the Makefile,
it will also add the path to the /etc/shells
```sh
git@github.com:dsal3389/dumbdevice.git && \
    cd dumbdevice && sudo make install
```

## about
the code is simple, if you need to emulate a device on the network, you can create a new user on your linux machine 
that uses the configured dumbdevice shell

## many shells / configurations
all your configurations are in the `src/dumbdevice/conf.def.h`, you can have many config files that each one is a different shell,
and then all you need to do, is to replace you `conf.def.h` file with the desired shell and compile


## todo
 * add throtteling
