
CC = gcc
CCC = g++
ASM = yasm

CCFLAGS = -Wall -I.
CCCFLAGS = -Wall -ggdb -std=c++0x -I. -O3

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

OBJ-OSSL =  ossl/osslmd5.o \
            ossl/osslsha1.o \
            ossl/osslsha256.o \
            ossl/osslsha512.o \
            ossl/osslrandom.o \
            ossl/osslmathimpl.o \
            ossl/osslconversion.o

OBJ-AES =   aes/aeskey.o \
            aes/aes_modes.o \
            aes/aestab.o

AES-NNN =   aes/aescrypt.o

AES-ASM =   aes/aes.o

OBJ-MAC  =  mac/hmac.o \
            mac/macexception.o

LIBS-OSSL = -lssl

all: dsrp ossl apps mac

#build the object files for dsrp
dsrp: $(OBJ-DSRP)

#to build ossl we first need to have build dsrp
ossl: dsrp $(OBJ-OSSL)

#build mac
mac: dsrp $(OBJ-MAC)

#compile the assebler part object file
aes-asm-x86:
	$(ASM) -f elf32 -o $(AES-ASM) aes/aes_x86.asm

aes-asm-amd64:
	$(ASM) -f elf64 -o $(AES-ASM) aes/aes_amd64.asm

#compile aes object files
aes: $(OBJ-AES) $(OBJ-NNN) aes-asm-amd64

# APPLICATION SECTION

#build the apps
app:  apps-srp apps-hmac

app-srp: app-srp-server-test app-srp-client-test app-srp-create-user app-srp-benchmark

app-hmac: app-hmac-testvector

app-aes: app-aes-rfx3686

app-srp-server-test: dsrp ossl apps/server_test.o
	$(CCC) apps/server_test.o $(OBJ-DSRP) $(OBJ-OSSL) -o apps/server_test $(LIBS-OSSL)
	
app-srp-client-test: dsrp ossl apps/client_test.o
	$(CCC) apps/client_test.o $(OBJ-DSRP) $(OBJ-OSSL) -o apps/client_test $(LIBS-OSSL)
	
app-srp-create-user: dsrp ossl apps/create_user.o
	$(CCC) apps/create_user.o $(OBJ-DSRP) $(OBJ-OSSL) -o apps/create_user $(LIBS-OSSL)
	
app-srp-benchmark: dsrp ossl apps/benchmark.o
	$(CCC) apps/benchmark.o $(OBJ-DSRP) $(OBJ-OSSL) -o apps/benchmark $(LIBS-OSSL)
	
app-hmac-testvector: dsrp ossl mac apps/hmac_md5_testvector.o
	$(CCC) apps/hmac_md5_testvector.o $(OBJ-DSRP) $(OBJ-MAC) $(OBJ-OSSL) -o apps/hmac_md5_testvector $(LIBS-OSSL)

app-aes-rfx3686: aes aes/rfc3686.o
	$(CCC) aes/rfc3686.o $(OBJ-AES) $(AES-ASM) -o aes/rfc3686
	
#tells how to make an *.o object file from an *.c file
%.o: %.c
	$(CC) -c $(CCFLAGS) $< -o $@

#tells how to make an *.o object file from an *.cpp file
%.o: %.cpp
	$(CCC) -c $(CCCFLAGS) $< -o $@
	
	
clean::
	rm -f *.o
	rm -f dsrp/*.o
	rm -f ossl/*.o
	rm -f apps/server_test
	rm -f apps/client_test
	rm -f apps/create_user
	rm -f apps/benchmark
	rm -f apps/hmac_md5_testvector
	rm -f apps/*.o
	rm -f mac/*.o
	rm -f aes/*.o
	rm -f aes/rfc3686

