"use strict"
import {totalNumbers, simpleNumbers} from "../common/simple-numbers";
import {modPow} from "../common/cyclic-operators";


function getRandomInt(max) {
    return Math.floor(Math.random() * max);
}


function getKeys() {
    const p = getRandomInt(totalNumbers);
    const q = (() => {
        let q;
        do {
            q = getRandomInt(totalNumbers);
        } while (q === p);
        return q;
    })();

    const simpleP = simpleNumbers[p];
    const simpleQ = simpleNumbers[q];

    const module = simpleP * simpleQ;

    const euler = (simpleP - 1) * (simpleQ - 1);

    const e = (() => {
        let e;
        let simple;
        do {
            e = getRandomInt(euler);

            simple = true;
            for (let i = 0; i < totalNumbers; ++i) {
                if (e % simpleNumbers[i] === 0 && euler % simpleNumbers[i] === 0) {
                    simple = false;
                    break
                }
            }
        } while (!simple)
        return e;
    })();

    const d = (() => {
        for (let i = 2; i < e; ++i) {
            if ((i * e) % euler === 1) {
                return i;
            }
        }
    })();

    return {publicKey: {e, module}, privateKey: {d, module}};
}

function encode(text, publicKey) {
    return text
        .split('')
        .map(el => modPow(el.charCodeAt(), publicKey.e, publicKey.module)
            .toString(16)
            .padStart(6, '0'))
        .join('');
}

function decode(text, privateKey) {
    return String
        .fromCharCode(...text
            .match(/.{1,6}/g)
            .map(el => modPow(parseInt(el, 16), privateKey.d, privateKey.module)));
}

let keys;

do {
    keys = getKeys();
} while (!keys.privateKey.d);

console.log(keys)

document.querySelector("#openKey").innerHTML = `e: ${keys.publicKey.e.toString()}<br>module: ${keys.publicKey.module.toString()}`;
document.querySelector("#privateKey").innerHTML = `d: ${keys.privateKey.d.toString()}<br>module: ${keys.privateKey.module.toString()}`;

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
