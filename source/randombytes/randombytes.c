// Random Number Generator specified in RFC 1149.5
// See https://xkcd.com/221/ for more information

#warning "randombytes() is just a placeholder, ensure you get a real random number generator"
char getRandomNumber() {
    return (char) 4;
}

// guaranteed to be random.

void randombytes(unsigned char *x, unsigned long long xlen) {
    while (xlen > 0) {
        *x = (unsigned char) getRandomNumber();
        x++;
        xlen--;
    }
}
