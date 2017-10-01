#ifndef NUMBERS_H
#define NUMBERS_H

template<class I>
bool isPrime(I x) {
    if (x == 2) return true;
    if (x < 2 || (x & 1) == 0) return false;

    for (I i = 3; i * i <= x; i+=2) //TODO: i <= sqrt(x) - should be faster
        if (x % i == 0)
            return false;
    return true;
}

int countBits(int i) {
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

#endif
