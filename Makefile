
CC = g++
CFLAGS = -Wall -ggdb -std=c++0x -I./dsrp

OBJ-DSRP =  dsrp/conversionexception.o \
            dsrp/conversion.o \
            dsrp/srpclient.o \
            dsrp/user.o \
            dsrp/ng.o \
            dsrp/dsrpexception.o \
            dsrp/lookupinterface.o \
            dsrp/hashinterface.o \
            dsrp/mathinterface.o \
            dsrp/randominterface.o \
            dsrp/srpverificator.o \
            dsrp/srpserver.o \
            dsrp/usernotfoundexception.o

OBJ-OSSL =  ossl/osslsha256.o \
            ossl/osslrandom.o \
            ossl/osslmathimpl.o \
            ossl/osslconversion.o

OBJ-TEST =  main.o
BIN-TEST =  test

LIBS-OSSL = -lssl

all: dsrp ossl test

#build the object files for dsrp
dsrp: $(OBJ-DSRP)

#to build ossl we first need to have build dsrp
ossl: dsrp $(OBJ-OSSL)

#build the test
test: dsrp ossl $(OBJ-TEST)
	$(CC) $(OBJ-TEST) $(OBJ-DSRP) $(OBJ-OSSL) -o $(BIN-TEST) $(LIBS-OSSL)

#tells how to make an *.o object file from an *.cpp file
%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

#$(BIN): $(OBJ)
#	$(CC) $^ -o $@ $(LIBS)

clean::
	rm -f *.o
	rm -f dsrp/*.o
	rm -f ossl/*.o
#	rm -f $(BIN)
