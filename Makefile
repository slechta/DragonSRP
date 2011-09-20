CC = g++
CFLAGS = -Wall -ggdb
LIBS = -lssl
BIN = dsrp
OBJ = main.o srpclient.o user.o osslhelp.o osslsha256.o memorylookup.o osslrandom.o ng.o hex.o dsrpexception.o

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

clean::
	rm -f *.o
	rm -f $(BIN)
