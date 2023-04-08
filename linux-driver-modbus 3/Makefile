
SRC_DIR = src/
BIN_DIR = bin/
EXT_SRC_DIR = apm-hardware-tool/src/

all: read search config getConfig configMenu 
	rm *.o

i2c:	i2c.o
	gcc -o $(BIN_DIR)i2c i2c.o

search: search.o lib.o modbus.o modbus-rtu.o modbus-tcp.o modbus-data.o
	gcc -o $(BIN_DIR)search search.o lib.o modbus.o modbus-rtu.o modbus-tcp.o modbus-data.o -lm

config: config.o lib.o modbus.o modbus-rtu.o modbus-tcp.o modbus-data.o
	gcc -o $(BIN_DIR)config config.o lib.o modbus.o modbus-rtu.o modbus-tcp.o modbus-data.o -lm

getConfig: getConfig.o lib.o modbus.o modbus-rtu.o modbus-tcp.o modbus-data.o
	gcc -o $(BIN_DIR)getConfig getConfig.o lib.o modbus.o modbus-rtu.o modbus-tcp.o modbus-data.o -lm

configMenu: configMenu.o lib.o modbus.o modbus-rtu.o modbus-tcp.o modbus-data.o
	gcc -o $(BIN_DIR)configMenu configMenu.o lib.o modbus.o modbus-rtu.o modbus-tcp.o modbus-data.o -lm

read: read.o lib.o modbus.o modbus-rtu.o modbus-tcp.o modbus-data.o
	gcc -o $(BIN_DIR)read read.o lib.o modbus.o modbus-rtu.o modbus-tcp.o modbus-data.o -lm

lib.o:	$(SRC_DIR)lib.c
	gcc -c $(SRC_DIR)lib.c

i2c.o:	$(EXT_SRC_DIR)i2c.c
	gcc -c $(EXT_SRC_DIR)i2c.c

modbus-data.o: $(SRC_DIR)modbus-data.c
	gcc -c $(SRC_DIR)modbus-data.c

modbus-tcp.o: $(SRC_DIR)modbus-tcp.c
	gcc -c $(SRC_DIR)modbus-tcp.c

modbus-rtu.o: $(SRC_DIR)modbus-rtu.c
	gcc -c $(SRC_DIR)modbus-rtu.c

modbus.o: $(SRC_DIR)modbus.c
	gcc -c $(SRC_DIR)modbus.c

search.o: $(SRC_DIR)search.c
	gcc -c $(SRC_DIR)search.c -lm

read.o: $(SRC_DIR)read.c
	gcc -c $(SRC_DIR)read.c -lm

config.o: $(SRC_DIR)config.c
	gcc -c $(SRC_DIR)config.c -lm

getConfig.o: $(SRC_DIR)getConfig.c
	gcc -c $(SRC_DIR)getConfig.c -lm

configMenu.o: $(SRC_DIR)configMenu.c
	gcc -c $(SRC_DIR)configMenu.c -lm
