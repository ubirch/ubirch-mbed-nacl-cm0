/**
 * This is a simple template for use with Calliope mini.
 *
 * @copyright (c) Calliope gGmbH.
 * @author Andreas Schuler(andreas@schulerdev.de)
 *
 * Licensed under the Apache License 2.0
 */

void init_print();
void print(const char *text);
void printbyte(unsigned char b);
void printbytes(const char *text, unsigned char* bytes, int cnt);
void itoa16(char value, char *text);
unsigned char nibble(char val);
void printnum(const char* text, int val);
void fail(const char* text);
void print_stack(const char *primitive, const unsigned int bytes, unsigned int stack);

