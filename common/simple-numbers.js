"use strict"

export const totalNumbers = 40000; // max = 40000

export let simpleNumbers;

if (!!localStorage.simpleNumbers?.length) {
    simpleNumbers = localStorage.simpleNumbers.split(',').map(el => parseInt(el));
} else {
    simpleNumbers = [2];
}

while (simpleNumbers.length < totalNumbers) {
    for (let i = simpleNumbers[simpleNumbers.length - 1] + 1; i > 0; ++i) {
        let simple = true;
        for (let j = 0; simpleNumbers[j] < i / 2 + 1; ++j) {
            if (i % simpleNumbers[j] === 0) {
                simple = false;
                break;
            }
        }

        if (simple) {
            simpleNumbers.push(i);
            localStorage.simpleNumbers = simpleNumbers.toString();
            break;
        }
    }
}