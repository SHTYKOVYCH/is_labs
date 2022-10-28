const readline = require("readline");
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

const alphabet1 = 'абвгдежзиклмнопрстуфхцчшщъыьэюя';
const alphabet2 = 'абвгдежзийклмнопрстуфхцчшщъыьэюя';
const alphabet3 = 'абвгдеёжзиклмнопрстуфхцчшщъыьэюя';
const alphabet4 = 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя';

const alphabets = {
    '0': alphabet1,
    '1': alphabet2,
    '2': alphabet3,
    '3': alphabet4
}

let userInput = {
    alphabet: undefined,
    input: undefined
}

function getAlphabet() {
    rl.question("Выберете алфавит:\n0 - без ё и й\n1 - без ё\n2 - без й\n3 - полный алфавит\nВыбор:", (choise) => {

    });
}

function encode() {

}

rl.question("Зашифровать(0) или расшифровать(не 0)?: ", (choise) => {
    if (choise == '0') {

    } else {

    }

    rl.close();
});

rl.on('close', function () {
    console.log('\nBYE BYE !!!');
    process.exit(0);
});