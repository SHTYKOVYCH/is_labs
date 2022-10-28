"use strict"

import {totalNumbers, simpleNumbers} from "../common/simple-numbers";
import {modPow, modMul} from "../common/cyclic-operators";

function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min) + min);
}

function getKeys() {
    // const q = simpleNumbers[getRandomInt(0, totalNumbers)];
    // const p = 2 * q + 1;

    const p = simpleNumbers[getRandomInt(0, totalNumbers)];

    const g = (() => {
        let g;

        do {
            g = getRandomInt(2, p - 1);
        } while (g === 1 && modPow(g, q, p) !== 1);

        return g;
    })();

    const x = getRandomInt(2, p - 1);

    const y = modPow(g, x, p);

    const k = getRandomInt(1, p - 2);

    return {publicKey: {p, g, y, k}, privateKey: {p, x}};
}

function encode(text, publicKey) {
    return text
        .split('')
        .map(el => {
            return modPow(publicKey.g, publicKey.k, publicKey.p)
                    .toString(16)
                    .padStart(8, '0')
                + modMul(el.charCodeAt(), modPow(publicKey.y, publicKey.k, publicKey.p), publicKey.p)
                    .toString(16)
                    .padStart(8, '0')
        })
        .join('');
}

function decode(text, privateKey) {
    return String
        .fromCharCode(...text
            .match(/.{1,16}/g)
            .map(el => {
                const subString = el.match(/.{1,8}/g);

                const r = parseInt(subString[0], 16);
                const e = parseInt(subString[1], 16);

                return modMul(e, modPow(r, privateKey.p - 1 - privateKey.x, privateKey.p), privateKey.p);
            }));
}

let keys;

do {
    keys = getKeys();
} while (decode(encode('abcdefghijklmnopqrstuvwxyz', keys.publicKey), keys.privateKey) !== 'abcdefghijklmnopqrstuvwxyz');

console.log(keys)

// document.querySelector("#openKey").innerHTML = `e: ${keys.publicKey.e.toString()}<br>module: ${keys.publicKey.module.toString()}`;
// document.querySelector("#privateKey").innerHTML = `d: ${keys.privateKey.d.toString()}<br>module: ${keys.privateKey.module.toString()}`;

document.querySelector("form").addEventListener('submit', (e) => {
    e.preventDefault();

    const formData = new FormData(e.target);

    const encript = formData.get('encript') == 'true';
    const text = formData.get('text');

    if (encript) {
        document.querySelector('#result').innerHTML = encode(text, keys.publicKey);
    } else {
        document.querySelector('#result').innerHTML = decode(text, keys.privateKey);
    }
});
