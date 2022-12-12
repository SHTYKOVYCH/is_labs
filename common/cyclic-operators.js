"use strict"

export function modPow(a, b, module) {
    const numOfBits = Math.floor(Math.log2(b)) + 1;

    let tmpB = b;
    let bits = [];

    for (let i = 0; i < numOfBits; ++i) {
        bits.push(tmpB & 1);
        tmpB = tmpB >> 1;
    }

    let d = 1;

    for (let i = numOfBits; i > -1; --i) {
        d = (d * d) % module;

        if (bits[i]) {
            d = (d * a) % module;
        }
    }

    return d;
}

export function modMul(a, b, c) {
    let sum = 0;

    for (let i = 0; i < b; i++) {
        sum += a;

        if (sum >= c) {
            sum -= c;
        }
    }

    return sum;
}