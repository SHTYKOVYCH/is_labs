#include "gost_3411_2012_calc.h"

void
GOSTHashInit(TGOSTHashContext *CTX)
{
    memset(CTX, 0x00, sizeof(TGOSTHashContext));
    CTX->v_512[1] = 0x02;
}

static void
GOSTHashX(const uint8_t *a, const uint8_t *b, uint8_t *c)
{
    int i;
    for (i = 0; i < 64; i++)
        c[i] = a[i]^b[i];
}

static void
GOSTHashAdd512(const uint8_t *a, const uint8_t *b, uint8_t *c)
{
    int i;
    int internal = 0;
    for (i = 0; i < 64; i++)
    {
        internal = a[i] + b[i] + (internal >> 8);
        c[i] = internal & 0xff;
    }
}

static void
GOSTHashP(uint8_t *state)
{
    int i;
    vect internal;
    for (i = 63; i >= 0; i--)
        internal[i] = state[Tau[i]];
    memcpy(state, internal, BLOCK_SIZE);
}

static void
GOSTHashS(uint8_t *state)
{
    int i;
    for (i = 63; i >= 0; i--)
        state[i] = Pi[state[i]];
}

static void
GOSTHashL(uint8_t *state)
{
    uint64_t* internal_in = (uint64_t*)state;
    uint64_t internal_out[8];
    memset(internal_out, 0x00, BLOCK_SIZE);
    int i, j;
    for (i = 7; i >= 0; i--)
    {
        for (j = 63; j >= 0; j--)
            if ((internal_in[i] >> j) & 1)
                internal_out[i] ^= A[63 - j];
    }
    memcpy(state, internal_out, 64);
}

static void
GOSTHashGetKey(uint8_t *K, int i)
{
    GOSTHashX(K, C[i], K);
    GOSTHashS(K);
    GOSTHashP(K);
    GOSTHashL(K);
}

static void
GOSTHashE(uint8_t *K, const uint8_t *m, uint8_t *state)
{
    int i;
    GOSTHashX(m, K, state);
    for(i = 0; i < 12; i++)
    {
        GOSTHashS(state);
        GOSTHashP(state);
        GOSTHashL(state);
        GOSTHashGetKey(K, i);
        GOSTHashX(state, K, state);
    }
}

static void
GOSTHashG( uint8_t *h, uint8_t *N, const uint8_t *m)
{
    vect K, internal;
    GOSTHashX(N, h, K);

    GOSTHashS(K);
    GOSTHashP(K);
    GOSTHashL(K);

    GOSTHashE(K, m, internal);

    GOSTHashX(internal, h, internal);
    GOSTHashX(internal, m, h);
}

static void
GOSTHashPadding(TGOSTHashContext *CTX)
{
    vect internal;

    if (CTX->buf_size < BLOCK_SIZE)
    {
        memset(internal, 0x00, BLOCK_SIZE);
        memcpy(internal, CTX->buffer, CTX->buf_size);
        internal[CTX->buf_size] = 0x01;
        memcpy(CTX->buffer, internal, BLOCK_SIZE);
    }
}

static void
GOSTHashStage_2(TGOSTHashContext *CTX, const uint8_t *data)
{
    GOSTHashG(CTX->h, CTX->N, data);
    GOSTHashAdd512(CTX->N, CTX->v_512, CTX->N);
    GOSTHashAdd512(CTX->Sigma, data, CTX->Sigma);
}

static void
GOSTHashStage_3(TGOSTHashContext *CTX)
{
    vect internal;
    memset(internal, 0x00, BLOCK_SIZE);
    internal[1] = ((CTX->buf_size * 8) >> 8) & 0xff;
    internal[0] = (CTX->buf_size * 8) & 0xff;

    GOSTHashPadding(CTX);

    GOSTHashG(CTX->h, CTX->N, (const uint8_t*)&(CTX->buffer));

    GOSTHashAdd512(CTX->N, internal, CTX->N);
    GOSTHashAdd512(CTX->Sigma, CTX->buffer, CTX->Sigma);

    GOSTHashG(CTX->h, CTX->v_0, (const uint8_t*)&(CTX->N));
    GOSTHashG(CTX->h, CTX->v_0, (const uint8_t*)&(CTX->Sigma));

    memcpy(CTX->hash, CTX->h, BLOCK_SIZE);
}

void
GOSTHashUpdate(TGOSTHashContext *CTX, const uint8_t *data, size_t len)
{
    size_t chk_size;

    while((len > 63) && (CTX->buf_size) == 0)
    {
        GOSTHashStage_2(CTX, data);
        data += 64;
        len -= 64;
    }
    while (len)
    {
        chk_size = 64 - CTX->buf_size;
        if (chk_size > len)
            chk_size = len;
        memcpy(&CTX->buffer[CTX->buf_size], data, chk_size);
        CTX->buf_size += chk_size;
        len -= chk_size;
        data += chk_size;
        if (CTX->buf_size == 64)
        {
            GOSTHashStage_2(CTX, CTX->buffer);
            CTX->buf_size = 0;
        }
    }
}
void
GOSTHashFinal(TGOSTHashContext *CTX)
{
    GOSTHashStage_3(CTX);
    CTX->buf_size = 0;
}
