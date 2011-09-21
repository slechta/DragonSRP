CC = g++
CFLAGS = -Wall -ggdb
LIBS = -lssl
BIN = dsrp
OBJ = osslconversion.o conversion.o main.o srpclient.o user.o osslsha256.o memorylookup.o osslrandom.o ng.o dsrpexception.o lookupinterface.o hashinterface.o mathinterface.o randominterface.o osslmathimpl.o srpverificator.o srpserver.o usernotfoundexception.o conversionexception.o

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BIN): $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

clean::
	rm -f *.o
	rm -f $(BIN)
