CC = g++
CFLAGS = -Wall -ggdb
LIBS = -lssl
BIN = dsrp
OBJ = main.o srpclient.o srpserver.o

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

clean::
	rm *.o
	rm $(BIN)
