// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <utility>  // make_pair, pair

#include "Collatz.h"

// ------------
// collatz_read
// ------------

std::pair<int, int> collatz_read (std::istream& r) {
    int i;
    r >> i;
    if (!r)
        return std::make_pair(0, 0);
    int j;
    r >> j;
    return std::make_pair(i, j);}





/*
int ccache [1000000] = { 0 }; //zero-initialized cache

// ----------------------
// recursive cycle length
// ----------------------

int rcl (long val) {
    int countit = 1;
    for (; val >= 1000000; countit++) {
        if (val % 2 == 0)
            val /= 2;
        else {
            val = val + (val >> 1) + 1;
            countit++;
        }
    }

    if (ccache[val] == 0) {
        if (val % 2 == 0)           //even
            ccache[val] = (countit + rcl(val/2));
        else {                      //odd
            ccache[val] = (countit + rcl((3 * val) + 1));
        }
    }
    return ccache[val];
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);

    if (j < i) {
        int temp = i;
        i = j;
        j = temp;
    }

    ccache[1] = 1;
    ccache[0] = 0;
    //ORIGINAL CACHE-LESS SOLUTION
    // int max_length = 0;
    // int count = 1;
    // for (int n = i; n <= j; n++) {
    //     count = 1;
    //     for (int t = n; t > 1; count++) {
    //         if (t % 2 == 0)
    //             t /= 2;
    //         else
    //             t = (3 * t) + 1; 
    //     }
    //     if (count > max_length)
    //         max_length = count;
    // }

    creating cache algorithm
    int count = 0;
    int max_length = 0;
    for (int val = i; val <= j; val++) {
        count = rcl((long) val);
        if (count > max_length)
            max_length = count;
    }
    
    assert(max_length > 0);
    return max_length;
}
 */






// ------------
// collatz_eval
// ------------

int cache [1000000] = { 0 };

int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);

    if (j < i) {
        int temp = i;
        i = j;
        j = temp;
    }
    
    cache[0] = 0;
    cache[1] = 1;

    long max = 0;
    long count = 0;
    for (long t = i; t <= j; t++) {
        count = 0;
        if (cache[t] != 0)
            count = cache[t];

        else {  //t is not in the cache
            long t2 = t;
            while (t > 1) {
                if (t % 2 == 0) {
                    t /= 2;
                    count++;
                }
                else {
                    t = t + (t >> 1) + 1;
                    count += 2;
                }

                if (t < 1000000 && cache[t] != 0) {
                    count += cache[t];
                    break;
                }
            }
            t = t2;
            cache[t] = count;
        }

        if (count > max)
            max = count;
    }
    
    assert(max > 0);
    return max;
}

// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    while (true) {
        const std::pair<int, int> p = collatz_read(r);
        if (p == std::make_pair(0, 0))
            return;
        const int v = collatz_eval(p.first, p.second);
        collatz_print(w, p.first, p.second, v);}}
