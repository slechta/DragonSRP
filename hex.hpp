#ifndef DSRP_HEX_HPP
#define DSRP_HEX_HPP

unsigned char *hextobyte(const char *hexstring, int *lenout); // must be deallocated by free()
unsigned char *hexscan(int maxbyteslen, int *resultlen); // must be deallocated by free()
void print_hex(unsigned char *array, int len);
#endif
