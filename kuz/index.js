Uint8Array.prototype.toString = function () {
    return Array.from(this).map(el => (el & 0xff).toString(16).padStart(2, 0)).join('')
}

const BLOCK_SIZE = 16; // длина блока

// таблица прямого нелинейного преобразования
let Pi = new Uint8Array([
    252, 238, 221, 17, 207, 110, 49, 22, 251, 196, 250, 218, 35, 197, 4, 77, 233, 119, 240, 219, 147,
    46, 153, 186, 23, 54, 241, 187, 20, 205, 95, 193, 249, 24, 101, 90, 226, 92, 239, 33, 129, 28, 60, 66,
    139, 1, 142, 79, 5, 132, 2, 174, 227, 106, 143, 160, 6, 11,237, 152, 127, 212, 211,31,235, 52, 44, 81,
    234, 200, 72, 171,242, 42, 104, 162, 253, 58, 206, 204, 181, 112, 14, 86, 8, 12, 118, 18, 191, 114, 19,
    71, 156, 183, 93, 135, 21,161, 150, 41, 16, 123, 154, 199, 243, 145, 120, 111, 157, 158, 178, 177, 50,
    117, 25, 61,255, 53, 138, 126, 109, 84, 198, 128, 195, 189, 13, 87, 223, 245, 36, 169, 62, 168, 67,
    201,215, 121,214, 246, 124, 34, 185, 3, 224, 15, 236, 222, 122, 148, 176, 188, 220, 232, 40, 80, 78,
    51, 10, 74, 167, 151, 96, 115, 30, 0, 98, 68, 26, 184, 56, 130, 100, 159, 38, 65, 173, 69, 70, 146, 39,
    94, 85, 47, 140, 163, 165, 125, 105, 213, 149, 59, 7, 88, 179, 64, 134, 172, 29, 247, 48, 55, 107, 228,
    136, 217, 231, 137, 225, 27, 131,73, 76, 63, 248, 254, 141,83, 170, 144, 202, 216, 133, 97, 32, 113,
    103, 164, 45, 43, 9, 91,203, 155, 37, 208, 190, 229, 108, 82, 89, 166, 116, 210, 230, 244, 180, 192,
    209, 102, 175, 194, 57, 75, 99, 182
]);

// таблица обратного нелинейного преобразования
let reverse_Pi = new Uint8Array([
    0xA5, 0x2D, 0x32, 0x8F, 0x0E, 0x30, 0x38, 0xC0,
    0x54, 0xE6, 0x9E, 0x39, 0x55, 0x7E, 0x52, 0x91,
    0x64, 0x03, 0x57, 0x5A, 0x1C, 0x60, 0x07, 0x18,
    0x21, 0x72, 0xA8, 0xD1, 0x29, 0xC6, 0xA4, 0x3F,
    0xE0, 0x27, 0x8D, 0x0C, 0x82, 0xEA, 0xAE, 0xB4,
    0x9A, 0x63, 0x49, 0xE5, 0x42, 0xE4, 0x15, 0xB7,
    0xC8, 0x06, 0x70, 0x9D, 0x41, 0x75, 0x19, 0xC9,
    0xAA, 0xFC, 0x4D, 0xBF, 0x2A, 0x73, 0x84, 0xD5,
    0xC3, 0xAF, 0x2B, 0x86, 0xA7, 0xB1, 0xB2, 0x5B,
    0x46, 0xD3, 0x9F, 0xFD, 0xD4, 0x0F, 0x9C, 0x2F,
    0x9B, 0x43, 0xEF, 0xD9, 0x79, 0xB6, 0x53, 0x7F,
    0xC1, 0xF0, 0x23, 0xE7, 0x25, 0x5E, 0xB5, 0x1E,
    0xA2, 0xDF, 0xA6, 0xFE, 0xAC, 0x22, 0xF9, 0xE2,
    0x4A, 0xBC, 0x35, 0xCA, 0xEE, 0x78, 0x05, 0x6B,
    0x51, 0xE1, 0x59, 0xA3, 0xF2, 0x71, 0x56, 0x11,
    0x6A, 0x89, 0x94, 0x65, 0x8C, 0xBB, 0x77, 0x3C,
    0x7B, 0x28, 0xAB, 0xD2, 0x31, 0xDE, 0xC4, 0x5F,
    0xCC, 0xCF, 0x76, 0x2C, 0xB8, 0xD8, 0x2E, 0x36,
    0xDB, 0x69, 0xB3, 0x14, 0x95, 0xBE, 0x62, 0xA1,
    0x3B, 0x16, 0x66, 0xE9, 0x5C, 0x6C, 0x6D, 0xAD,
    0x37, 0x61, 0x4B, 0xB9, 0xE3, 0xBA, 0xF1, 0xA0,
    0x85, 0x83, 0xDA, 0x47, 0xC5, 0xB0, 0x33, 0xFA,
    0x96, 0x6F, 0x6E, 0xC2, 0xF6, 0x50, 0xFF, 0x5D,
    0xA9, 0x8E, 0x17, 0x1B, 0x97, 0x7D, 0xEC, 0x58,
    0xF7, 0x1F, 0xFB, 0x7C, 0x09, 0x0D, 0x7A, 0x67,
    0x45, 0x87, 0xDC, 0xE8, 0x4F, 0x1D, 0x4E, 0x04,
    0xEB, 0xF8, 0xF3, 0x3E, 0x3D, 0xBD, 0x8A, 0x88,
    0xDD, 0xCD, 0x0B, 0x13, 0x98, 0x02, 0x93, 0x80,
    0x90, 0xD0, 0x24, 0x34, 0xCB, 0xED, 0xF4, 0xCE,
    0x99, 0x10, 0x44, 0x40, 0x92, 0x3A, 0x01, 0x26,
    0x12, 0x1A, 0x48, 0x68, 0xF5, 0x81, 0x8B, 0xC7,
    0xD6, 0x20, 0x0A, 0x08, 0x00, 0x4C, 0xD7, 0x74
]);

// вектор линейного преобразования
let l_vec = new Uint8Array([
    1, 148, 32, 133, 16, 194, 192, 1,
    251, 1, 192, 194, 16, 133, 32, 148
]);

// массив для хранения констант
let iter_C = Array.from(new Array(32).keys()).map(() => new Uint8Array(BLOCK_SIZE));
// массив для хранения ключей
let iter_key = Array.from(new Array(10).keys()).map(() => new Uint8Array(64));

// функция X
function GOST_Kuz_X(a, b) {
    let c = new Uint8Array(BLOCK_SIZE);
    for (let i = 0; i < BLOCK_SIZE; i++)
        c[i] = (a[i] ^ b[i]);
    return c;
}

// Функция S
function GOST_Kuz_S(in_data) {
    let out_data = new Uint8Array(in_data.length);
    for (let i = 0; i < BLOCK_SIZE; i++) {
        out_data[i] = Pi[in_data[i]];
    }
    return out_data;
}

// умножение в поле Галуа
function GOST_Kuz_GF_mul(a, b) {
    let c = 0;
    let hi_bit;
    for (let i = 0; i < 8; i++) {
        if (b & 1)
            c ^= a;
        hi_bit = a & 0x80;
        a = a << 1;
        if (hi_bit)
            a = a ^ 0xc3; //полином  x^8+x^7+x^6+x+1
        b >>= 1;
    }
    return c;
}

// функция R сдвигает данные и реализует уравнение, представленное для расчета L-функции
function GOST_Kuz_R(state) {
    let a_15 = 0;
    let internal = new Uint8Array(BLOCK_SIZE);
    for (let i = 1; i < BLOCK_SIZE; i++) {
        internal[i] = state[i - 1];
        a_15 ^= GOST_Kuz_GF_mul(state[i - 1], l_vec[i]);
    }
    a_15 ^= GOST_Kuz_GF_mul(state[15], l_vec[0]);
    internal[0] = a_15;
    return internal;
}

function GOST_Kuz_reverse_R(state) {
    let a_0 = 0;
    let internal = new Uint8Array(16);
    for (let i = 0; i < 15; i++) {
        internal[i] = state[i + 1];
        a_0 ^= GOST_Kuz_GF_mul(state[i + 1], l_vec[15 - i]);
    }
    a_0 ^= GOST_Kuz_GF_mul(state[0], l_vec[0]);
    internal[15] = a_0;
    return internal;
}

function GOST_Kuz_L(in_data) {
    let internal = new Uint8Array(in_data);

    for (let i = 0; i < 16; i++) {
        internal = GOST_Kuz_R(internal);
    }

    return internal;
}

// функция S^(-1)
function GOST_Kuz_reverse_S(in_data) {
    let out_data = new Uint8Array(in_data.length);
    for (let i = 0; i < BLOCK_SIZE; i++) {
        out_data[i] = reverse_Pi[in_data[i]];
    }
    return out_data;
}

function GOST_Kuz_reverse_L(in_data) {
    let internal = new Uint8Array(in_data);
    for (let i = 0; i < 16; i++)
        internal = GOST_Kuz_reverse_R(internal);
    return internal;
}

// функция расчета констант
function GOST_Kuz_Get_C() {
    let iter_num = Array.from(new Array(32).keys()).map(() => new Uint8Array(BLOCK_SIZE));
    for (let i = 0; i < 32; i++) {
        for (let j = 0; j < BLOCK_SIZE; j++)
            iter_num[i][j] = 0;
        iter_num[i][15] = (i + 1);
    }
    for (let i = 0; i < 32; i++) {
        iter_C[i] = GOST_Kuz_L(iter_num[i]);
    }
}

// функция, выполняющая преобразования ячейки Фейстеля
function GOST_Kuz_F(in_key_1, in_key_2, iter_const) {
    let internal;
    let out_key_2 = in_key_1;
    internal = GOST_Kuz_X(in_key_1, iter_const);
    internal = GOST_Kuz_S(internal);
    internal = GOST_Kuz_L(internal);
    let out_key_1 = GOST_Kuz_X(internal, in_key_2);
    let key = (new Array(2)).map(() => []);
    key[0] = out_key_1;
    key[1] = out_key_2;
    return key;
}

// функция расчета раундовых ключей
function GOST_Kuz_Expand_Key(key_1, key_2) {
    let iter12 = Array.from(new Array(2).keys()).map(() => new Uint8Array());
    let iter34 = Array.from(new Array(2).keys()).map(() => new Uint8Array());

    GOST_Kuz_Get_C();
    iter_key[0] = new Uint8Array(key_1);
    iter_key[1] = new Uint8Array(key_2);
    iter12[0] = new Uint8Array(key_1);
    iter12[1] = new Uint8Array(key_2);
    for (let i = 0; i < 4; i++) {
        iter34 = GOST_Kuz_F(iter12[0], iter12[1], iter_C[8 * i]);
        iter12 = GOST_Kuz_F(iter34[0], iter34[1], iter_C[1 + 8 * i]);
        iter34 = GOST_Kuz_F(iter12[0], iter12[1], iter_C[2 + 8 * i]);
        iter12 = GOST_Kuz_F(iter34[0], iter34[1], iter_C[3 + 8 * i]);
        iter34 = GOST_Kuz_F(iter12[0], iter12[1], iter_C[4 + 8 * i]);
        iter12 = GOST_Kuz_F(iter34[0], iter34[1], iter_C[5 + 8 * i]);
        iter34 = GOST_Kuz_F(iter12[0], iter12[1], iter_C[6 + 8 * i]);
        iter12 = GOST_Kuz_F(iter34[0], iter34[1], iter_C[7 + 8 * i]);

        iter_key[2 * i + 2] = iter12[0];
        iter_key[2 * i + 3] = iter12[1];
    }
}

// функция шифрования блока
function GOST_Kuz_Encript(blk) {
    let out_blk = blk;
    for (let i = 0; i < 9; i++) {
        out_blk = GOST_Kuz_X(iter_key[i], out_blk);
        out_blk = GOST_Kuz_S(out_blk);
        out_blk = GOST_Kuz_L(out_blk);
    }
    out_blk = GOST_Kuz_X(out_blk, iter_key[9]);
    return out_blk;
}

//функция расшифрования блока
function GOST_Kuz_Decript(blk) {
    let out_blk = new Uint8Array(blk);

    for (let i = 9; i > 0; i--) {
        out_blk = GOST_Kuz_X(iter_key[i], out_blk);
        out_blk = GOST_Kuz_reverse_L(out_blk);
        out_blk = GOST_Kuz_reverse_S(out_blk);
    }

    out_blk = GOST_Kuz_X(iter_key[0], out_blk);

    return out_blk;
}

const encoder = new TextEncoder();
const decoder = new TextDecoder();

let key_1 =
    [
        0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00, 0xff, 0xee,
        0xdd, 0xcc, 0xbb, 0xaa, 0x99, 0x88
    ];

let key_2 =
    [
        0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01,
        0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe
    ];

let t = new Uint8Array('8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef'.match(/.{1,2}/g).map(el => parseInt(el, 16)));
key_1 = t.slice(0, 16);
key_2 = t.slice(16);
let blk = new Uint8Array("1122334455667700ffeeddccbbaa9988".match(/.{1,2}/g).map(el => parseInt(el, 16)));
blk = new Uint8Array(encoder.encode('Кадыров'), 0, BLOCK_SIZE);


GOST_Kuz_Expand_Key(key_1, key_2);
console.log('Constants: ', iter_C.map(el => el.toString()))
console.log('Keys: ', iter_key.map(el => el.toString()))
console.log("original: ", blk.toString());
let encriptBlok = GOST_Kuz_Encript(blk);
console.log("encripted:", encriptBlok.toString());
let decriptBlok = GOST_Kuz_Decript(encriptBlok);
console.log("decripted: ", decoder.decode(decriptBlok));