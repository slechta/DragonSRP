
#ifndef _EDEFINES_H
#define _EDEFINES_H

//#define E_DATASIZE 100000

//#define E_MAX_PAYLOAD_SIZE 65536

// Pozor na to: musi byt vysoky nebo infinite
#define E_SELECTEX_TIMEOUT 100000

//"illegal port number or port is busy.\n"
#define E_ERROR_INVALIDPORT -7
#define E_ERROR_BINDFAILED -8
#define E_ERROR_LISTENFAILED -9

// Connections
#define E_MAX_PENDING_CONNECTIONS 10

#ifdef WIN32
	#define E_LENTYPE	WORD
	#define E_SEQTYPE	DWORD
#else
	#define E_LENTYPE   uint16_t
	#define E_SEQTYPE	uint32_t
#endif 

#endif
