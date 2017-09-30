#ifndef NUMBERS_H
#define NUMBERS_H

template<class I>
bool isPrime(I x) {
    if (x < 2)
        return false;
    for (I i = 2; i * i <= x; i++)
        if (!(x % i))
            return false;
    return true;
}

#endif
