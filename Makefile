
CC = g++
CFLAGS = -Wall -ggdb -std=c++0x -I. -O3

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
            dsrp/usernotfoundexception.o \
            dsrp/srpclientauthenticator.o \
            dsrp/memorylookup.o

OBJ-OSSL =  ossl/osslsha1.o \
            ossl/osslsha256.o \
            ossl/osslsha512.o \
            ossl/osslrandom.o \
            ossl/osslmathimpl.o \
            ossl/osslconversion.o

OBJ-APPS =  apps/server_test.o \
            apps/client_test.o \
            apps/create_user.o \
            apps/benchmark.o

OBJ-MAC  =  mac/hmac.o \
            mac/macexception.o

LIBS-OSSL = -lssl

all: dsrp ossl apps mac

#build the object files for dsrp
dsrp: $(OBJ-DSRP)

#to build ossl we first need to have build dsrp
ossl: dsrp $(OBJ-OSSL)

#buil mac
mac: dsrp $(OBJ-MAC)

#build the apps
apps: dsrp ossl $(OBJ-APPS)
	$(CC) apps/server_test.o $(OBJ-DSRP) $(OBJ-OSSL) -o apps/server_test $(LIBS-OSSL)
	$(CC) apps/client_test.o $(OBJ-DSRP) $(OBJ-OSSL) -o apps/client_test $(LIBS-OSSL)
	$(CC) apps/create_user.o $(OBJ-DSRP) $(OBJ-OSSL) -o apps/create_user $(LIBS-OSSL)
	$(CC) apps/benchmark.o $(OBJ-DSRP) $(OBJ-OSSL) -o apps/benchmark $(LIBS-OSSL)

#tells how to make an *.o object file from an *.cpp file
%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean::
	rm -f *.o
	rm -f dsrp/*.o
	rm -f ossl/*.o
	rm -f apps/server_test
	rm -f apps/client_test
	rm -f apps/create_user
	rm -f apps/*.o
	rm -f mac/*.o
