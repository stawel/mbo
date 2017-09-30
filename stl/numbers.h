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

#endif
