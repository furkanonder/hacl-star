/* MIT License
 *
 * Copyright (c) 2016-2022 INRIA, CMU and Microsoft Corporation
 * Copyright (c) 2022-2023 HACL* Contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include "internal/Hacl_Hash_SHA2.h"

#include "internal/Hacl_Krmllib.h"

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha256_init */

void Hacl_SHA2_Scalar32_sha256_init(uint32_t *hash)
{
  KRML_MAYBE_FOR8(i,
    0U,
    8U,
    1U,
    uint32_t *os = hash;
    uint32_t x = Hacl_Impl_SHA2_Generic_h256[i];
    os[i] = x;);
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha256_init */

/* SNIPPET_START: sha256_update */

static inline void sha256_update(uint8_t *b, uint32_t *hash)
{
  uint32_t hash_old[8U] = { 0U };
  uint32_t ws[16U] = { 0U };
  memcpy(hash_old, hash, 8U * sizeof (uint32_t));
  uint8_t *b10 = b;
  uint32_t u = load32_be(b10);
  ws[0U] = u;
  uint32_t u0 = load32_be(b10 + 4U);
  ws[1U] = u0;
  uint32_t u1 = load32_be(b10 + 8U);
  ws[2U] = u1;
  uint32_t u2 = load32_be(b10 + 12U);
  ws[3U] = u2;
  uint32_t u3 = load32_be(b10 + 16U);
  ws[4U] = u3;
  uint32_t u4 = load32_be(b10 + 20U);
  ws[5U] = u4;
  uint32_t u5 = load32_be(b10 + 24U);
  ws[6U] = u5;
  uint32_t u6 = load32_be(b10 + 28U);
  ws[7U] = u6;
  uint32_t u7 = load32_be(b10 + 32U);
  ws[8U] = u7;
  uint32_t u8 = load32_be(b10 + 36U);
  ws[9U] = u8;
  uint32_t u9 = load32_be(b10 + 40U);
  ws[10U] = u9;
  uint32_t u10 = load32_be(b10 + 44U);
  ws[11U] = u10;
  uint32_t u11 = load32_be(b10 + 48U);
  ws[12U] = u11;
  uint32_t u12 = load32_be(b10 + 52U);
  ws[13U] = u12;
  uint32_t u13 = load32_be(b10 + 56U);
  ws[14U] = u13;
  uint32_t u14 = load32_be(b10 + 60U);
  ws[15U] = u14;
  KRML_MAYBE_FOR4(i0,
    0U,
    4U,
    1U,
    KRML_MAYBE_FOR16(i,
      0U,
      16U,
      1U,
      uint32_t k_t = Hacl_Impl_SHA2_Generic_k224_256[16U * i0 + i];
      uint32_t ws_t = ws[i];
      uint32_t a0 = hash[0U];
      uint32_t b0 = hash[1U];
      uint32_t c0 = hash[2U];
      uint32_t d0 = hash[3U];
      uint32_t e0 = hash[4U];
      uint32_t f0 = hash[5U];
      uint32_t g0 = hash[6U];
      uint32_t h02 = hash[7U];
      uint32_t k_e_t = k_t;
      uint32_t
      t1 =
        h02
        + ((e0 << 26U | e0 >> 6U) ^ ((e0 << 21U | e0 >> 11U) ^ (e0 << 7U | e0 >> 25U)))
        + ((e0 & f0) ^ (~e0 & g0))
        + k_e_t
        + ws_t;
      uint32_t
      t2 =
        ((a0 << 30U | a0 >> 2U) ^ ((a0 << 19U | a0 >> 13U) ^ (a0 << 10U | a0 >> 22U)))
        + ((a0 & b0) ^ ((a0 & c0) ^ (b0 & c0)));
      uint32_t a1 = t1 + t2;
      uint32_t b1 = a0;
      uint32_t c1 = b0;
      uint32_t d1 = c0;
      uint32_t e1 = d0 + t1;
      uint32_t f1 = e0;
      uint32_t g1 = f0;
      uint32_t h12 = g0;
      hash[0U] = a1;
      hash[1U] = b1;
      hash[2U] = c1;
      hash[3U] = d1;
      hash[4U] = e1;
      hash[5U] = f1;
      hash[6U] = g1;
      hash[7U] = h12;);
    if (i0 < 3U)
    {
      KRML_MAYBE_FOR16(i,
        0U,
        16U,
        1U,
        uint32_t t16 = ws[i];
        uint32_t t15 = ws[(i + 1U) % 16U];
        uint32_t t7 = ws[(i + 9U) % 16U];
        uint32_t t2 = ws[(i + 14U) % 16U];
        uint32_t s1 = (t2 << 15U | t2 >> 17U) ^ ((t2 << 13U | t2 >> 19U) ^ t2 >> 10U);
        uint32_t s0 = (t15 << 25U | t15 >> 7U) ^ ((t15 << 14U | t15 >> 18U) ^ t15 >> 3U);
        ws[i] = s1 + t7 + s0 + t16;);
    });
  KRML_MAYBE_FOR8(i,
    0U,
    8U,
    1U,
    uint32_t *os = hash;
    uint32_t x = hash[i] + hash_old[i];
    os[i] = x;);
}

/* SNIPPET_END: sha256_update */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha256_update_nblocks */

void Hacl_SHA2_Scalar32_sha256_update_nblocks(uint32_t len, uint8_t *b, uint32_t *st)
{
  uint32_t blocks = len / 64U;
  for (uint32_t i = 0U; i < blocks; i++)
  {
    uint8_t *b0 = b;
    uint8_t *mb = b0 + i * 64U;
    sha256_update(mb, st);
  }
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha256_update_nblocks */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha256_update_last */

void
Hacl_SHA2_Scalar32_sha256_update_last(
  uint64_t totlen,
  uint32_t len,
  uint8_t *b,
  uint32_t *hash
)
{
  uint32_t blocks;
  if (len + 8U + 1U <= 64U)
  {
    blocks = 1U;
  }
  else
  {
    blocks = 2U;
  }
  uint32_t fin = blocks * 64U;
  uint8_t last[128U] = { 0U };
  uint8_t totlen_buf[8U] = { 0U };
  uint64_t total_len_bits = totlen << 3U;
  store64_be(totlen_buf, total_len_bits);
  uint8_t *b0 = b;
  memcpy(last, b0, len * sizeof (uint8_t));
  last[len] = 0x80U;
  memcpy(last + fin - 8U, totlen_buf, 8U * sizeof (uint8_t));
  uint8_t *last00 = last;
  uint8_t *last10 = last + 64U;
  uint8_t *l0 = last00;
  uint8_t *l1 = last10;
  uint8_t *lb0 = l0;
  uint8_t *lb1 = l1;
  uint8_t *last0 = lb0;
  uint8_t *last1 = lb1;
  sha256_update(last0, hash);
  if (blocks > 1U)
  {
    sha256_update(last1, hash);
    return;
  }
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha256_update_last */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha256_finish */

void Hacl_SHA2_Scalar32_sha256_finish(uint32_t *st, uint8_t *h)
{
  uint8_t hbuf[32U] = { 0U };
  KRML_MAYBE_FOR8(i, 0U, 8U, 1U, store32_be(hbuf + i * 4U, st[i]););
  memcpy(h, hbuf, 32U * sizeof (uint8_t));
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha256_finish */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha224_init */

void Hacl_SHA2_Scalar32_sha224_init(uint32_t *hash)
{
  KRML_MAYBE_FOR8(i,
    0U,
    8U,
    1U,
    uint32_t *os = hash;
    uint32_t x = Hacl_Impl_SHA2_Generic_h224[i];
    os[i] = x;);
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha224_init */

/* SNIPPET_START: sha224_update_nblocks */

static inline void sha224_update_nblocks(uint32_t len, uint8_t *b, uint32_t *st)
{
  Hacl_SHA2_Scalar32_sha256_update_nblocks(len, b, st);
}

/* SNIPPET_END: sha224_update_nblocks */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha224_update_last */

void
Hacl_SHA2_Scalar32_sha224_update_last(uint64_t totlen, uint32_t len, uint8_t *b, uint32_t *st)
{
  Hacl_SHA2_Scalar32_sha256_update_last(totlen, len, b, st);
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha224_update_last */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha224_finish */

void Hacl_SHA2_Scalar32_sha224_finish(uint32_t *st, uint8_t *h)
{
  uint8_t hbuf[32U] = { 0U };
  KRML_MAYBE_FOR8(i, 0U, 8U, 1U, store32_be(hbuf + i * 4U, st[i]););
  memcpy(h, hbuf, 28U * sizeof (uint8_t));
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha224_finish */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha512_init */

void Hacl_SHA2_Scalar32_sha512_init(uint64_t *hash)
{
  KRML_MAYBE_FOR8(i,
    0U,
    8U,
    1U,
    uint64_t *os = hash;
    uint64_t x = Hacl_Impl_SHA2_Generic_h512[i];
    os[i] = x;);
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha512_init */

/* SNIPPET_START: sha512_update */

static inline void sha512_update(uint8_t *b, uint64_t *hash)
{
  uint64_t hash_old[8U] = { 0U };
  uint64_t ws[16U] = { 0U };
  memcpy(hash_old, hash, 8U * sizeof (uint64_t));
  uint8_t *b10 = b;
  uint64_t u = load64_be(b10);
  ws[0U] = u;
  uint64_t u0 = load64_be(b10 + 8U);
  ws[1U] = u0;
  uint64_t u1 = load64_be(b10 + 16U);
  ws[2U] = u1;
  uint64_t u2 = load64_be(b10 + 24U);
  ws[3U] = u2;
  uint64_t u3 = load64_be(b10 + 32U);
  ws[4U] = u3;
  uint64_t u4 = load64_be(b10 + 40U);
  ws[5U] = u4;
  uint64_t u5 = load64_be(b10 + 48U);
  ws[6U] = u5;
  uint64_t u6 = load64_be(b10 + 56U);
  ws[7U] = u6;
  uint64_t u7 = load64_be(b10 + 64U);
  ws[8U] = u7;
  uint64_t u8 = load64_be(b10 + 72U);
  ws[9U] = u8;
  uint64_t u9 = load64_be(b10 + 80U);
  ws[10U] = u9;
  uint64_t u10 = load64_be(b10 + 88U);
  ws[11U] = u10;
  uint64_t u11 = load64_be(b10 + 96U);
  ws[12U] = u11;
  uint64_t u12 = load64_be(b10 + 104U);
  ws[13U] = u12;
  uint64_t u13 = load64_be(b10 + 112U);
  ws[14U] = u13;
  uint64_t u14 = load64_be(b10 + 120U);
  ws[15U] = u14;
  KRML_MAYBE_FOR5(i0,
    0U,
    5U,
    1U,
    KRML_MAYBE_FOR16(i,
      0U,
      16U,
      1U,
      uint64_t k_t = Hacl_Impl_SHA2_Generic_k384_512[16U * i0 + i];
      uint64_t ws_t = ws[i];
      uint64_t a0 = hash[0U];
      uint64_t b0 = hash[1U];
      uint64_t c0 = hash[2U];
      uint64_t d0 = hash[3U];
      uint64_t e0 = hash[4U];
      uint64_t f0 = hash[5U];
      uint64_t g0 = hash[6U];
      uint64_t h02 = hash[7U];
      uint64_t k_e_t = k_t;
      uint64_t
      t1 =
        h02
        + ((e0 << 50U | e0 >> 14U) ^ ((e0 << 46U | e0 >> 18U) ^ (e0 << 23U | e0 >> 41U)))
        + ((e0 & f0) ^ (~e0 & g0))
        + k_e_t
        + ws_t;
      uint64_t
      t2 =
        ((a0 << 36U | a0 >> 28U) ^ ((a0 << 30U | a0 >> 34U) ^ (a0 << 25U | a0 >> 39U)))
        + ((a0 & b0) ^ ((a0 & c0) ^ (b0 & c0)));
      uint64_t a1 = t1 + t2;
      uint64_t b1 = a0;
      uint64_t c1 = b0;
      uint64_t d1 = c0;
      uint64_t e1 = d0 + t1;
      uint64_t f1 = e0;
      uint64_t g1 = f0;
      uint64_t h12 = g0;
      hash[0U] = a1;
      hash[1U] = b1;
      hash[2U] = c1;
      hash[3U] = d1;
      hash[4U] = e1;
      hash[5U] = f1;
      hash[6U] = g1;
      hash[7U] = h12;);
    if (i0 < 4U)
    {
      KRML_MAYBE_FOR16(i,
        0U,
        16U,
        1U,
        uint64_t t16 = ws[i];
        uint64_t t15 = ws[(i + 1U) % 16U];
        uint64_t t7 = ws[(i + 9U) % 16U];
        uint64_t t2 = ws[(i + 14U) % 16U];
        uint64_t s1 = (t2 << 45U | t2 >> 19U) ^ ((t2 << 3U | t2 >> 61U) ^ t2 >> 6U);
        uint64_t s0 = (t15 << 63U | t15 >> 1U) ^ ((t15 << 56U | t15 >> 8U) ^ t15 >> 7U);
        ws[i] = s1 + t7 + s0 + t16;);
    });
  KRML_MAYBE_FOR8(i,
    0U,
    8U,
    1U,
    uint64_t *os = hash;
    uint64_t x = hash[i] + hash_old[i];
    os[i] = x;);
}

/* SNIPPET_END: sha512_update */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha512_update_nblocks */

void Hacl_SHA2_Scalar32_sha512_update_nblocks(uint32_t len, uint8_t *b, uint64_t *st)
{
  uint32_t blocks = len / 128U;
  for (uint32_t i = 0U; i < blocks; i++)
  {
    uint8_t *b0 = b;
    uint8_t *mb = b0 + i * 128U;
    sha512_update(mb, st);
  }
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha512_update_nblocks */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha512_update_last */

void
Hacl_SHA2_Scalar32_sha512_update_last(
  FStar_UInt128_uint128 totlen,
  uint32_t len,
  uint8_t *b,
  uint64_t *hash
)
{
  uint32_t blocks;
  if (len + 16U + 1U <= 128U)
  {
    blocks = 1U;
  }
  else
  {
    blocks = 2U;
  }
  uint32_t fin = blocks * 128U;
  uint8_t last[256U] = { 0U };
  uint8_t totlen_buf[16U] = { 0U };
  FStar_UInt128_uint128 total_len_bits = FStar_UInt128_shift_left(totlen, 3U);
  store128_be(totlen_buf, total_len_bits);
  uint8_t *b0 = b;
  memcpy(last, b0, len * sizeof (uint8_t));
  last[len] = 0x80U;
  memcpy(last + fin - 16U, totlen_buf, 16U * sizeof (uint8_t));
  uint8_t *last00 = last;
  uint8_t *last10 = last + 128U;
  uint8_t *l0 = last00;
  uint8_t *l1 = last10;
  uint8_t *lb0 = l0;
  uint8_t *lb1 = l1;
  uint8_t *last0 = lb0;
  uint8_t *last1 = lb1;
  sha512_update(last0, hash);
  if (blocks > 1U)
  {
    sha512_update(last1, hash);
    return;
  }
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha512_update_last */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha512_finish */

void Hacl_SHA2_Scalar32_sha512_finish(uint64_t *st, uint8_t *h)
{
  uint8_t hbuf[64U] = { 0U };
  KRML_MAYBE_FOR8(i, 0U, 8U, 1U, store64_be(hbuf + i * 8U, st[i]););
  memcpy(h, hbuf, 64U * sizeof (uint8_t));
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha512_finish */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha384_init */

void Hacl_SHA2_Scalar32_sha384_init(uint64_t *hash)
{
  KRML_MAYBE_FOR8(i,
    0U,
    8U,
    1U,
    uint64_t *os = hash;
    uint64_t x = Hacl_Impl_SHA2_Generic_h384[i];
    os[i] = x;);
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha384_init */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha384_update_nblocks */

void Hacl_SHA2_Scalar32_sha384_update_nblocks(uint32_t len, uint8_t *b, uint64_t *st)
{
  Hacl_SHA2_Scalar32_sha512_update_nblocks(len, b, st);
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha384_update_nblocks */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha384_update_last */

void
Hacl_SHA2_Scalar32_sha384_update_last(
  FStar_UInt128_uint128 totlen,
  uint32_t len,
  uint8_t *b,
  uint64_t *st
)
{
  Hacl_SHA2_Scalar32_sha512_update_last(totlen, len, b, st);
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha384_update_last */

/* SNIPPET_START: Hacl_SHA2_Scalar32_sha384_finish */

void Hacl_SHA2_Scalar32_sha384_finish(uint64_t *st, uint8_t *h)
{
  uint8_t hbuf[64U] = { 0U };
  KRML_MAYBE_FOR8(i, 0U, 8U, 1U, store64_be(hbuf + i * 8U, st[i]););
  memcpy(h, hbuf, 48U * sizeof (uint8_t));
}

/* SNIPPET_END: Hacl_SHA2_Scalar32_sha384_finish */

/* SNIPPET_START: Hacl_Streaming_SHA2_create_in_256 */

/**
Allocate initial state for the SHA2_256 hash. The state is to be freed by
calling `free_256`.
*/
Hacl_Streaming_MD_state_32 *Hacl_Streaming_SHA2_create_in_256(void)
{
  uint8_t *buf = (uint8_t *)KRML_HOST_CALLOC(64U, sizeof (uint8_t));
  uint32_t *block_state = (uint32_t *)KRML_HOST_CALLOC(8U, sizeof (uint32_t));
  Hacl_Streaming_MD_state_32
  s = { .block_state = block_state, .buf = buf, .total_len = (uint64_t)0U };
  Hacl_Streaming_MD_state_32
  *p = (Hacl_Streaming_MD_state_32 *)KRML_HOST_MALLOC(sizeof (Hacl_Streaming_MD_state_32));
  p[0U] = s;
  Hacl_SHA2_Scalar32_sha256_init(block_state);
  return p;
}

/* SNIPPET_END: Hacl_Streaming_SHA2_create_in_256 */

/* SNIPPET_START: Hacl_Streaming_SHA2_copy_256 */

/**
Copies the state passed as argument into a newly allocated state (deep copy).
The state is to be freed by calling `free_256`. Cloning the state this way is
useful, for instance, if your control-flow diverges and you need to feed
more (different) data into the hash in each branch.
*/
Hacl_Streaming_MD_state_32 *Hacl_Streaming_SHA2_copy_256(Hacl_Streaming_MD_state_32 *s0)
{
  Hacl_Streaming_MD_state_32 scrut = *s0;
  uint32_t *block_state0 = scrut.block_state;
  uint8_t *buf0 = scrut.buf;
  uint64_t total_len0 = scrut.total_len;
  uint8_t *buf = (uint8_t *)KRML_HOST_CALLOC(64U, sizeof (uint8_t));
  memcpy(buf, buf0, 64U * sizeof (uint8_t));
  uint32_t *block_state = (uint32_t *)KRML_HOST_CALLOC(8U, sizeof (uint32_t));
  memcpy(block_state, block_state0, 8U * sizeof (uint32_t));
  Hacl_Streaming_MD_state_32
  s = { .block_state = block_state, .buf = buf, .total_len = total_len0 };
  Hacl_Streaming_MD_state_32
  *p = (Hacl_Streaming_MD_state_32 *)KRML_HOST_MALLOC(sizeof (Hacl_Streaming_MD_state_32));
  p[0U] = s;
  return p;
}

/* SNIPPET_END: Hacl_Streaming_SHA2_copy_256 */

/* SNIPPET_START: Hacl_Streaming_SHA2_init_256 */

/**
Reset an existing state to the initial hash state with empty data.
*/
void Hacl_Streaming_SHA2_init_256(Hacl_Streaming_MD_state_32 *s)
{
  Hacl_Streaming_MD_state_32 scrut = *s;
  uint8_t *buf = scrut.buf;
  uint32_t *block_state = scrut.block_state;
  Hacl_SHA2_Scalar32_sha256_init(block_state);
  Hacl_Streaming_MD_state_32
  tmp = { .block_state = block_state, .buf = buf, .total_len = (uint64_t)0U };
  s[0U] = tmp;
}

/* SNIPPET_END: Hacl_Streaming_SHA2_init_256 */

/* SNIPPET_START: update_224_256 */

static inline Hacl_Streaming_Types_error_code
update_224_256(Hacl_Streaming_MD_state_32 *p, uint8_t *data, uint32_t len)
{
  Hacl_Streaming_MD_state_32 s = *p;
  uint64_t total_len = s.total_len;
  if ((uint64_t)len > 2305843009213693951ULL - total_len)
  {
    return Hacl_Streaming_Types_MaximumLengthExceeded;
  }
  uint32_t sz;
  if (total_len % (uint64_t)64U == 0ULL && total_len > 0ULL)
  {
    sz = 64U;
  }
  else
  {
    sz = (uint32_t)(total_len % (uint64_t)64U);
  }
  if (len <= 64U - sz)
  {
    Hacl_Streaming_MD_state_32 s1 = *p;
    uint32_t *block_state1 = s1.block_state;
    uint8_t *buf = s1.buf;
    uint64_t total_len1 = s1.total_len;
    uint32_t sz1;
    if (total_len1 % (uint64_t)64U == 0ULL && total_len1 > 0ULL)
    {
      sz1 = 64U;
    }
    else
    {
      sz1 = (uint32_t)(total_len1 % (uint64_t)64U);
    }
    uint8_t *buf2 = buf + sz1;
    memcpy(buf2, data, len * sizeof (uint8_t));
    uint64_t total_len2 = total_len1 + (uint64_t)len;
    *p
    =
      (
        (Hacl_Streaming_MD_state_32){
          .block_state = block_state1,
          .buf = buf,
          .total_len = total_len2
        }
      );
  }
  else if (sz == 0U)
  {
    Hacl_Streaming_MD_state_32 s1 = *p;
    uint32_t *block_state1 = s1.block_state;
    uint8_t *buf = s1.buf;
    uint64_t total_len1 = s1.total_len;
    uint32_t sz1;
    if (total_len1 % (uint64_t)64U == 0ULL && total_len1 > 0ULL)
    {
      sz1 = 64U;
    }
    else
    {
      sz1 = (uint32_t)(total_len1 % (uint64_t)64U);
    }
    if (!(sz1 == 0U))
    {
      Hacl_SHA2_Scalar32_sha256_update_nblocks(64U, buf, block_state1);
    }
    uint32_t ite;
    if ((uint64_t)len % (uint64_t)64U == 0ULL && (uint64_t)len > 0ULL)
    {
      ite = 64U;
    }
    else
    {
      ite = (uint32_t)((uint64_t)len % (uint64_t)64U);
    }
    uint32_t n_blocks = (len - ite) / 64U;
    uint32_t data1_len = n_blocks * 64U;
    uint32_t data2_len = len - data1_len;
    uint8_t *data1 = data;
    uint8_t *data2 = data + data1_len;
    Hacl_SHA2_Scalar32_sha256_update_nblocks(data1_len / 64U * 64U, data1, block_state1);
    uint8_t *dst = buf;
    memcpy(dst, data2, data2_len * sizeof (uint8_t));
    *p
    =
      (
        (Hacl_Streaming_MD_state_32){
          .block_state = block_state1,
          .buf = buf,
          .total_len = total_len1 + (uint64_t)len
        }
      );
  }
  else
  {
    uint32_t diff = 64U - sz;
    uint8_t *data1 = data;
    uint8_t *data2 = data + diff;
    Hacl_Streaming_MD_state_32 s1 = *p;
    uint32_t *block_state10 = s1.block_state;
    uint8_t *buf0 = s1.buf;
    uint64_t total_len10 = s1.total_len;
    uint32_t sz10;
    if (total_len10 % (uint64_t)64U == 0ULL && total_len10 > 0ULL)
    {
      sz10 = 64U;
    }
    else
    {
      sz10 = (uint32_t)(total_len10 % (uint64_t)64U);
    }
    uint8_t *buf2 = buf0 + sz10;
    memcpy(buf2, data1, diff * sizeof (uint8_t));
    uint64_t total_len2 = total_len10 + (uint64_t)diff;
    *p
    =
      (
        (Hacl_Streaming_MD_state_32){
          .block_state = block_state10,
          .buf = buf0,
          .total_len = total_len2
        }
      );
    Hacl_Streaming_MD_state_32 s10 = *p;
    uint32_t *block_state1 = s10.block_state;
    uint8_t *buf = s10.buf;
    uint64_t total_len1 = s10.total_len;
    uint32_t sz1;
    if (total_len1 % (uint64_t)64U == 0ULL && total_len1 > 0ULL)
    {
      sz1 = 64U;
    }
    else
    {
      sz1 = (uint32_t)(total_len1 % (uint64_t)64U);
    }
    if (!(sz1 == 0U))
    {
      Hacl_SHA2_Scalar32_sha256_update_nblocks(64U, buf, block_state1);
    }
    uint32_t ite;
    if ((uint64_t)(len - diff) % (uint64_t)64U == 0ULL && (uint64_t)(len - diff) > 0ULL)
    {
      ite = 64U;
    }
    else
    {
      ite = (uint32_t)((uint64_t)(len - diff) % (uint64_t)64U);
    }
    uint32_t n_blocks = (len - diff - ite) / 64U;
    uint32_t data1_len = n_blocks * 64U;
    uint32_t data2_len = len - diff - data1_len;
    uint8_t *data11 = data2;
    uint8_t *data21 = data2 + data1_len;
    Hacl_SHA2_Scalar32_sha256_update_nblocks(data1_len / 64U * 64U, data11, block_state1);
    uint8_t *dst = buf;
    memcpy(dst, data21, data2_len * sizeof (uint8_t));
    *p
    =
      (
        (Hacl_Streaming_MD_state_32){
          .block_state = block_state1,
          .buf = buf,
          .total_len = total_len1 + (uint64_t)(len - diff)
        }
      );
  }
  return Hacl_Streaming_Types_Success;
}

/* SNIPPET_END: update_224_256 */

/* SNIPPET_START: Hacl_Streaming_SHA2_update_256 */

/**
Feed an arbitrary amount of data into the hash. This function returns 0 for
success, or 1 if the combined length of all of the data passed to `update_256`
(since the last call to `init_256`) exceeds 2^61-1 bytes.

This function is identical to the update function for SHA2_224.
*/
Hacl_Streaming_Types_error_code
Hacl_Streaming_SHA2_update_256(
  Hacl_Streaming_MD_state_32 *p,
  uint8_t *input,
  uint32_t input_len
)
{
  return update_224_256(p, input, input_len);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_update_256 */

/* SNIPPET_START: Hacl_Streaming_SHA2_finish_256 */

/**
Write the resulting hash into `dst`, an array of 32 bytes. The state remains
valid after a call to `finish_256`, meaning the user may feed more data into
the hash via `update_256`. (The finish_256 function operates on an internal copy of
the state and therefore does not invalidate the client-held state `p`.)
*/
void Hacl_Streaming_SHA2_finish_256(Hacl_Streaming_MD_state_32 *p, uint8_t *dst)
{
  Hacl_Streaming_MD_state_32 scrut = *p;
  uint32_t *block_state = scrut.block_state;
  uint8_t *buf_ = scrut.buf;
  uint64_t total_len = scrut.total_len;
  uint32_t r;
  if (total_len % (uint64_t)64U == 0ULL && total_len > 0ULL)
  {
    r = 64U;
  }
  else
  {
    r = (uint32_t)(total_len % (uint64_t)64U);
  }
  uint8_t *buf_1 = buf_;
  uint32_t tmp_block_state[8U] = { 0U };
  memcpy(tmp_block_state, block_state, 8U * sizeof (uint32_t));
  uint32_t ite;
  if (r % 64U == 0U && r > 0U)
  {
    ite = 64U;
  }
  else
  {
    ite = r % 64U;
  }
  uint8_t *buf_last = buf_1 + r - ite;
  uint8_t *buf_multi = buf_1;
  Hacl_SHA2_Scalar32_sha256_update_nblocks(0U, buf_multi, tmp_block_state);
  uint64_t prev_len_last = total_len - (uint64_t)r;
  Hacl_SHA2_Scalar32_sha256_update_last(prev_len_last + (uint64_t)r,
    r,
    buf_last,
    tmp_block_state);
  Hacl_SHA2_Scalar32_sha256_finish(tmp_block_state, dst);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_finish_256 */

/* SNIPPET_START: Hacl_Streaming_SHA2_free_256 */

/**
Free a state allocated with `create_in_256`.

This function is identical to the free function for SHA2_224.
*/
void Hacl_Streaming_SHA2_free_256(Hacl_Streaming_MD_state_32 *s)
{
  Hacl_Streaming_MD_state_32 scrut = *s;
  uint8_t *buf = scrut.buf;
  uint32_t *block_state = scrut.block_state;
  KRML_HOST_FREE(block_state);
  KRML_HOST_FREE(buf);
  KRML_HOST_FREE(s);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_free_256 */

/* SNIPPET_START: Hacl_Streaming_SHA2_hash_256 */

/**
Hash `input`, of len `input_len`, into `dst`, an array of 32 bytes.
*/
void Hacl_Streaming_SHA2_hash_256(uint8_t *input, uint32_t input_len, uint8_t *dst)
{
  uint8_t *ib = input;
  uint8_t *rb = dst;
  uint32_t st[8U] = { 0U };
  Hacl_SHA2_Scalar32_sha256_init(st);
  uint32_t rem = input_len % 64U;
  uint64_t len_ = (uint64_t)input_len;
  Hacl_SHA2_Scalar32_sha256_update_nblocks(input_len, ib, st);
  uint32_t rem1 = input_len % 64U;
  uint8_t *b0 = ib;
  uint8_t *lb = b0 + input_len - rem1;
  Hacl_SHA2_Scalar32_sha256_update_last(len_, rem, lb, st);
  Hacl_SHA2_Scalar32_sha256_finish(st, rb);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_hash_256 */

/* SNIPPET_START: Hacl_Streaming_SHA2_create_in_224 */

Hacl_Streaming_MD_state_32 *Hacl_Streaming_SHA2_create_in_224(void)
{
  uint8_t *buf = (uint8_t *)KRML_HOST_CALLOC(64U, sizeof (uint8_t));
  uint32_t *block_state = (uint32_t *)KRML_HOST_CALLOC(8U, sizeof (uint32_t));
  Hacl_Streaming_MD_state_32
  s = { .block_state = block_state, .buf = buf, .total_len = (uint64_t)0U };
  Hacl_Streaming_MD_state_32
  *p = (Hacl_Streaming_MD_state_32 *)KRML_HOST_MALLOC(sizeof (Hacl_Streaming_MD_state_32));
  p[0U] = s;
  Hacl_SHA2_Scalar32_sha224_init(block_state);
  return p;
}

/* SNIPPET_END: Hacl_Streaming_SHA2_create_in_224 */

/* SNIPPET_START: Hacl_Streaming_SHA2_init_224 */

void Hacl_Streaming_SHA2_init_224(Hacl_Streaming_MD_state_32 *s)
{
  Hacl_Streaming_MD_state_32 scrut = *s;
  uint8_t *buf = scrut.buf;
  uint32_t *block_state = scrut.block_state;
  Hacl_SHA2_Scalar32_sha224_init(block_state);
  Hacl_Streaming_MD_state_32
  tmp = { .block_state = block_state, .buf = buf, .total_len = (uint64_t)0U };
  s[0U] = tmp;
}

/* SNIPPET_END: Hacl_Streaming_SHA2_init_224 */

/* SNIPPET_START: Hacl_Streaming_SHA2_update_224 */

Hacl_Streaming_Types_error_code
Hacl_Streaming_SHA2_update_224(
  Hacl_Streaming_MD_state_32 *p,
  uint8_t *input,
  uint32_t input_len
)
{
  return update_224_256(p, input, input_len);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_update_224 */

/* SNIPPET_START: Hacl_Streaming_SHA2_finish_224 */

/**
Write the resulting hash into `dst`, an array of 28 bytes. The state remains
valid after a call to `finish_224`, meaning the user may feed more data into
the hash via `update_224`.
*/
void Hacl_Streaming_SHA2_finish_224(Hacl_Streaming_MD_state_32 *p, uint8_t *dst)
{
  Hacl_Streaming_MD_state_32 scrut = *p;
  uint32_t *block_state = scrut.block_state;
  uint8_t *buf_ = scrut.buf;
  uint64_t total_len = scrut.total_len;
  uint32_t r;
  if (total_len % (uint64_t)64U == 0ULL && total_len > 0ULL)
  {
    r = 64U;
  }
  else
  {
    r = (uint32_t)(total_len % (uint64_t)64U);
  }
  uint8_t *buf_1 = buf_;
  uint32_t tmp_block_state[8U] = { 0U };
  memcpy(tmp_block_state, block_state, 8U * sizeof (uint32_t));
  uint32_t ite;
  if (r % 64U == 0U && r > 0U)
  {
    ite = 64U;
  }
  else
  {
    ite = r % 64U;
  }
  uint8_t *buf_last = buf_1 + r - ite;
  uint8_t *buf_multi = buf_1;
  sha224_update_nblocks(0U, buf_multi, tmp_block_state);
  uint64_t prev_len_last = total_len - (uint64_t)r;
  Hacl_SHA2_Scalar32_sha224_update_last(prev_len_last + (uint64_t)r,
    r,
    buf_last,
    tmp_block_state);
  Hacl_SHA2_Scalar32_sha224_finish(tmp_block_state, dst);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_finish_224 */

/* SNIPPET_START: Hacl_Streaming_SHA2_free_224 */

void Hacl_Streaming_SHA2_free_224(Hacl_Streaming_MD_state_32 *p)
{
  Hacl_Streaming_SHA2_free_256(p);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_free_224 */

/* SNIPPET_START: Hacl_Streaming_SHA2_hash_224 */

/**
Hash `input`, of len `input_len`, into `dst`, an array of 28 bytes.
*/
void Hacl_Streaming_SHA2_hash_224(uint8_t *input, uint32_t input_len, uint8_t *dst)
{
  uint8_t *ib = input;
  uint8_t *rb = dst;
  uint32_t st[8U] = { 0U };
  Hacl_SHA2_Scalar32_sha224_init(st);
  uint32_t rem = input_len % 64U;
  uint64_t len_ = (uint64_t)input_len;
  sha224_update_nblocks(input_len, ib, st);
  uint32_t rem1 = input_len % 64U;
  uint8_t *b0 = ib;
  uint8_t *lb = b0 + input_len - rem1;
  Hacl_SHA2_Scalar32_sha224_update_last(len_, rem, lb, st);
  Hacl_SHA2_Scalar32_sha224_finish(st, rb);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_hash_224 */

/* SNIPPET_START: Hacl_Streaming_SHA2_create_in_512 */

Hacl_Streaming_MD_state_64 *Hacl_Streaming_SHA2_create_in_512(void)
{
  uint8_t *buf = (uint8_t *)KRML_HOST_CALLOC(128U, sizeof (uint8_t));
  uint64_t *block_state = (uint64_t *)KRML_HOST_CALLOC(8U, sizeof (uint64_t));
  Hacl_Streaming_MD_state_64
  s = { .block_state = block_state, .buf = buf, .total_len = (uint64_t)0U };
  Hacl_Streaming_MD_state_64
  *p = (Hacl_Streaming_MD_state_64 *)KRML_HOST_MALLOC(sizeof (Hacl_Streaming_MD_state_64));
  p[0U] = s;
  Hacl_SHA2_Scalar32_sha512_init(block_state);
  return p;
}

/* SNIPPET_END: Hacl_Streaming_SHA2_create_in_512 */

/* SNIPPET_START: Hacl_Streaming_SHA2_copy_512 */

/**
Copies the state passed as argument into a newly allocated state (deep copy).
The state is to be freed by calling `free_512`. Cloning the state this way is
useful, for instance, if your control-flow diverges and you need to feed
more (different) data into the hash in each branch.
*/
Hacl_Streaming_MD_state_64 *Hacl_Streaming_SHA2_copy_512(Hacl_Streaming_MD_state_64 *s0)
{
  Hacl_Streaming_MD_state_64 scrut = *s0;
  uint64_t *block_state0 = scrut.block_state;
  uint8_t *buf0 = scrut.buf;
  uint64_t total_len0 = scrut.total_len;
  uint8_t *buf = (uint8_t *)KRML_HOST_CALLOC(128U, sizeof (uint8_t));
  memcpy(buf, buf0, 128U * sizeof (uint8_t));
  uint64_t *block_state = (uint64_t *)KRML_HOST_CALLOC(8U, sizeof (uint64_t));
  memcpy(block_state, block_state0, 8U * sizeof (uint64_t));
  Hacl_Streaming_MD_state_64
  s = { .block_state = block_state, .buf = buf, .total_len = total_len0 };
  Hacl_Streaming_MD_state_64
  *p = (Hacl_Streaming_MD_state_64 *)KRML_HOST_MALLOC(sizeof (Hacl_Streaming_MD_state_64));
  p[0U] = s;
  return p;
}

/* SNIPPET_END: Hacl_Streaming_SHA2_copy_512 */

/* SNIPPET_START: Hacl_Streaming_SHA2_init_512 */

void Hacl_Streaming_SHA2_init_512(Hacl_Streaming_MD_state_64 *s)
{
  Hacl_Streaming_MD_state_64 scrut = *s;
  uint8_t *buf = scrut.buf;
  uint64_t *block_state = scrut.block_state;
  Hacl_SHA2_Scalar32_sha512_init(block_state);
  Hacl_Streaming_MD_state_64
  tmp = { .block_state = block_state, .buf = buf, .total_len = (uint64_t)0U };
  s[0U] = tmp;
}

/* SNIPPET_END: Hacl_Streaming_SHA2_init_512 */

/* SNIPPET_START: update_384_512 */

static inline Hacl_Streaming_Types_error_code
update_384_512(Hacl_Streaming_MD_state_64 *p, uint8_t *data, uint32_t len)
{
  Hacl_Streaming_MD_state_64 s = *p;
  uint64_t total_len = s.total_len;
  if ((uint64_t)len > 18446744073709551615ULL - total_len)
  {
    return Hacl_Streaming_Types_MaximumLengthExceeded;
  }
  uint32_t sz;
  if (total_len % (uint64_t)128U == 0ULL && total_len > 0ULL)
  {
    sz = 128U;
  }
  else
  {
    sz = (uint32_t)(total_len % (uint64_t)128U);
  }
  if (len <= 128U - sz)
  {
    Hacl_Streaming_MD_state_64 s1 = *p;
    uint64_t *block_state1 = s1.block_state;
    uint8_t *buf = s1.buf;
    uint64_t total_len1 = s1.total_len;
    uint32_t sz1;
    if (total_len1 % (uint64_t)128U == 0ULL && total_len1 > 0ULL)
    {
      sz1 = 128U;
    }
    else
    {
      sz1 = (uint32_t)(total_len1 % (uint64_t)128U);
    }
    uint8_t *buf2 = buf + sz1;
    memcpy(buf2, data, len * sizeof (uint8_t));
    uint64_t total_len2 = total_len1 + (uint64_t)len;
    *p
    =
      (
        (Hacl_Streaming_MD_state_64){
          .block_state = block_state1,
          .buf = buf,
          .total_len = total_len2
        }
      );
  }
  else if (sz == 0U)
  {
    Hacl_Streaming_MD_state_64 s1 = *p;
    uint64_t *block_state1 = s1.block_state;
    uint8_t *buf = s1.buf;
    uint64_t total_len1 = s1.total_len;
    uint32_t sz1;
    if (total_len1 % (uint64_t)128U == 0ULL && total_len1 > 0ULL)
    {
      sz1 = 128U;
    }
    else
    {
      sz1 = (uint32_t)(total_len1 % (uint64_t)128U);
    }
    if (!(sz1 == 0U))
    {
      Hacl_SHA2_Scalar32_sha512_update_nblocks(128U, buf, block_state1);
    }
    uint32_t ite;
    if ((uint64_t)len % (uint64_t)128U == 0ULL && (uint64_t)len > 0ULL)
    {
      ite = 128U;
    }
    else
    {
      ite = (uint32_t)((uint64_t)len % (uint64_t)128U);
    }
    uint32_t n_blocks = (len - ite) / 128U;
    uint32_t data1_len = n_blocks * 128U;
    uint32_t data2_len = len - data1_len;
    uint8_t *data1 = data;
    uint8_t *data2 = data + data1_len;
    Hacl_SHA2_Scalar32_sha512_update_nblocks(data1_len / 128U * 128U, data1, block_state1);
    uint8_t *dst = buf;
    memcpy(dst, data2, data2_len * sizeof (uint8_t));
    *p
    =
      (
        (Hacl_Streaming_MD_state_64){
          .block_state = block_state1,
          .buf = buf,
          .total_len = total_len1 + (uint64_t)len
        }
      );
  }
  else
  {
    uint32_t diff = 128U - sz;
    uint8_t *data1 = data;
    uint8_t *data2 = data + diff;
    Hacl_Streaming_MD_state_64 s1 = *p;
    uint64_t *block_state10 = s1.block_state;
    uint8_t *buf0 = s1.buf;
    uint64_t total_len10 = s1.total_len;
    uint32_t sz10;
    if (total_len10 % (uint64_t)128U == 0ULL && total_len10 > 0ULL)
    {
      sz10 = 128U;
    }
    else
    {
      sz10 = (uint32_t)(total_len10 % (uint64_t)128U);
    }
    uint8_t *buf2 = buf0 + sz10;
    memcpy(buf2, data1, diff * sizeof (uint8_t));
    uint64_t total_len2 = total_len10 + (uint64_t)diff;
    *p
    =
      (
        (Hacl_Streaming_MD_state_64){
          .block_state = block_state10,
          .buf = buf0,
          .total_len = total_len2
        }
      );
    Hacl_Streaming_MD_state_64 s10 = *p;
    uint64_t *block_state1 = s10.block_state;
    uint8_t *buf = s10.buf;
    uint64_t total_len1 = s10.total_len;
    uint32_t sz1;
    if (total_len1 % (uint64_t)128U == 0ULL && total_len1 > 0ULL)
    {
      sz1 = 128U;
    }
    else
    {
      sz1 = (uint32_t)(total_len1 % (uint64_t)128U);
    }
    if (!(sz1 == 0U))
    {
      Hacl_SHA2_Scalar32_sha512_update_nblocks(128U, buf, block_state1);
    }
    uint32_t ite;
    if ((uint64_t)(len - diff) % (uint64_t)128U == 0ULL && (uint64_t)(len - diff) > 0ULL)
    {
      ite = 128U;
    }
    else
    {
      ite = (uint32_t)((uint64_t)(len - diff) % (uint64_t)128U);
    }
    uint32_t n_blocks = (len - diff - ite) / 128U;
    uint32_t data1_len = n_blocks * 128U;
    uint32_t data2_len = len - diff - data1_len;
    uint8_t *data11 = data2;
    uint8_t *data21 = data2 + data1_len;
    Hacl_SHA2_Scalar32_sha512_update_nblocks(data1_len / 128U * 128U, data11, block_state1);
    uint8_t *dst = buf;
    memcpy(dst, data21, data2_len * sizeof (uint8_t));
    *p
    =
      (
        (Hacl_Streaming_MD_state_64){
          .block_state = block_state1,
          .buf = buf,
          .total_len = total_len1 + (uint64_t)(len - diff)
        }
      );
  }
  return Hacl_Streaming_Types_Success;
}

/* SNIPPET_END: update_384_512 */

/* SNIPPET_START: Hacl_Streaming_SHA2_update_512 */

/**
Feed an arbitrary amount of data into the hash. This function returns 0 for
success, or 1 if the combined length of all of the data passed to `update_512`
(since the last call to `init_512`) exceeds 2^125-1 bytes.

This function is identical to the update function for SHA2_384.
*/
Hacl_Streaming_Types_error_code
Hacl_Streaming_SHA2_update_512(
  Hacl_Streaming_MD_state_64 *p,
  uint8_t *input,
  uint32_t input_len
)
{
  return update_384_512(p, input, input_len);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_update_512 */

/* SNIPPET_START: Hacl_Streaming_SHA2_finish_512 */

/**
Write the resulting hash into `dst`, an array of 64 bytes. The state remains
valid after a call to `finish_512`, meaning the user may feed more data into
the hash via `update_512`. (The finish_512 function operates on an internal copy of
the state and therefore does not invalidate the client-held state `p`.)
*/
void Hacl_Streaming_SHA2_finish_512(Hacl_Streaming_MD_state_64 *p, uint8_t *dst)
{
  Hacl_Streaming_MD_state_64 scrut = *p;
  uint64_t *block_state = scrut.block_state;
  uint8_t *buf_ = scrut.buf;
  uint64_t total_len = scrut.total_len;
  uint32_t r;
  if (total_len % (uint64_t)128U == 0ULL && total_len > 0ULL)
  {
    r = 128U;
  }
  else
  {
    r = (uint32_t)(total_len % (uint64_t)128U);
  }
  uint8_t *buf_1 = buf_;
  uint64_t tmp_block_state[8U] = { 0U };
  memcpy(tmp_block_state, block_state, 8U * sizeof (uint64_t));
  uint32_t ite;
  if (r % 128U == 0U && r > 0U)
  {
    ite = 128U;
  }
  else
  {
    ite = r % 128U;
  }
  uint8_t *buf_last = buf_1 + r - ite;
  uint8_t *buf_multi = buf_1;
  Hacl_SHA2_Scalar32_sha512_update_nblocks(0U, buf_multi, tmp_block_state);
  uint64_t prev_len_last = total_len - (uint64_t)r;
  Hacl_SHA2_Scalar32_sha512_update_last(FStar_UInt128_add(FStar_UInt128_uint64_to_uint128(prev_len_last),
      FStar_UInt128_uint64_to_uint128((uint64_t)r)),
    r,
    buf_last,
    tmp_block_state);
  Hacl_SHA2_Scalar32_sha512_finish(tmp_block_state, dst);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_finish_512 */

/* SNIPPET_START: Hacl_Streaming_SHA2_free_512 */

/**
Free a state allocated with `create_in_512`.

This function is identical to the free function for SHA2_384.
*/
void Hacl_Streaming_SHA2_free_512(Hacl_Streaming_MD_state_64 *s)
{
  Hacl_Streaming_MD_state_64 scrut = *s;
  uint8_t *buf = scrut.buf;
  uint64_t *block_state = scrut.block_state;
  KRML_HOST_FREE(block_state);
  KRML_HOST_FREE(buf);
  KRML_HOST_FREE(s);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_free_512 */

/* SNIPPET_START: Hacl_Streaming_SHA2_hash_512 */

/**
Hash `input`, of len `input_len`, into `dst`, an array of 64 bytes.
*/
void Hacl_Streaming_SHA2_hash_512(uint8_t *input, uint32_t input_len, uint8_t *dst)
{
  uint8_t *ib = input;
  uint8_t *rb = dst;
  uint64_t st[8U] = { 0U };
  Hacl_SHA2_Scalar32_sha512_init(st);
  uint32_t rem = input_len % 128U;
  FStar_UInt128_uint128 len_ = FStar_UInt128_uint64_to_uint128((uint64_t)input_len);
  Hacl_SHA2_Scalar32_sha512_update_nblocks(input_len, ib, st);
  uint32_t rem1 = input_len % 128U;
  uint8_t *b0 = ib;
  uint8_t *lb = b0 + input_len - rem1;
  Hacl_SHA2_Scalar32_sha512_update_last(len_, rem, lb, st);
  Hacl_SHA2_Scalar32_sha512_finish(st, rb);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_hash_512 */

/* SNIPPET_START: Hacl_Streaming_SHA2_create_in_384 */

Hacl_Streaming_MD_state_64 *Hacl_Streaming_SHA2_create_in_384(void)
{
  uint8_t *buf = (uint8_t *)KRML_HOST_CALLOC(128U, sizeof (uint8_t));
  uint64_t *block_state = (uint64_t *)KRML_HOST_CALLOC(8U, sizeof (uint64_t));
  Hacl_Streaming_MD_state_64
  s = { .block_state = block_state, .buf = buf, .total_len = (uint64_t)0U };
  Hacl_Streaming_MD_state_64
  *p = (Hacl_Streaming_MD_state_64 *)KRML_HOST_MALLOC(sizeof (Hacl_Streaming_MD_state_64));
  p[0U] = s;
  Hacl_SHA2_Scalar32_sha384_init(block_state);
  return p;
}

/* SNIPPET_END: Hacl_Streaming_SHA2_create_in_384 */

/* SNIPPET_START: Hacl_Streaming_SHA2_init_384 */

void Hacl_Streaming_SHA2_init_384(Hacl_Streaming_MD_state_64 *s)
{
  Hacl_Streaming_MD_state_64 scrut = *s;
  uint8_t *buf = scrut.buf;
  uint64_t *block_state = scrut.block_state;
  Hacl_SHA2_Scalar32_sha384_init(block_state);
  Hacl_Streaming_MD_state_64
  tmp = { .block_state = block_state, .buf = buf, .total_len = (uint64_t)0U };
  s[0U] = tmp;
}

/* SNIPPET_END: Hacl_Streaming_SHA2_init_384 */

/* SNIPPET_START: Hacl_Streaming_SHA2_update_384 */

Hacl_Streaming_Types_error_code
Hacl_Streaming_SHA2_update_384(
  Hacl_Streaming_MD_state_64 *p,
  uint8_t *input,
  uint32_t input_len
)
{
  return update_384_512(p, input, input_len);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_update_384 */

/* SNIPPET_START: Hacl_Streaming_SHA2_finish_384 */

/**
Write the resulting hash into `dst`, an array of 48 bytes. The state remains
valid after a call to `finish_384`, meaning the user may feed more data into
the hash via `update_384`.
*/
void Hacl_Streaming_SHA2_finish_384(Hacl_Streaming_MD_state_64 *p, uint8_t *dst)
{
  Hacl_Streaming_MD_state_64 scrut = *p;
  uint64_t *block_state = scrut.block_state;
  uint8_t *buf_ = scrut.buf;
  uint64_t total_len = scrut.total_len;
  uint32_t r;
  if (total_len % (uint64_t)128U == 0ULL && total_len > 0ULL)
  {
    r = 128U;
  }
  else
  {
    r = (uint32_t)(total_len % (uint64_t)128U);
  }
  uint8_t *buf_1 = buf_;
  uint64_t tmp_block_state[8U] = { 0U };
  memcpy(tmp_block_state, block_state, 8U * sizeof (uint64_t));
  uint32_t ite;
  if (r % 128U == 0U && r > 0U)
  {
    ite = 128U;
  }
  else
  {
    ite = r % 128U;
  }
  uint8_t *buf_last = buf_1 + r - ite;
  uint8_t *buf_multi = buf_1;
  Hacl_SHA2_Scalar32_sha384_update_nblocks(0U, buf_multi, tmp_block_state);
  uint64_t prev_len_last = total_len - (uint64_t)r;
  Hacl_SHA2_Scalar32_sha384_update_last(FStar_UInt128_add(FStar_UInt128_uint64_to_uint128(prev_len_last),
      FStar_UInt128_uint64_to_uint128((uint64_t)r)),
    r,
    buf_last,
    tmp_block_state);
  Hacl_SHA2_Scalar32_sha384_finish(tmp_block_state, dst);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_finish_384 */

/* SNIPPET_START: Hacl_Streaming_SHA2_free_384 */

void Hacl_Streaming_SHA2_free_384(Hacl_Streaming_MD_state_64 *p)
{
  Hacl_Streaming_SHA2_free_512(p);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_free_384 */

/* SNIPPET_START: Hacl_Streaming_SHA2_hash_384 */

/**
Hash `input`, of len `input_len`, into `dst`, an array of 48 bytes.
*/
void Hacl_Streaming_SHA2_hash_384(uint8_t *input, uint32_t input_len, uint8_t *dst)
{
  uint8_t *ib = input;
  uint8_t *rb = dst;
  uint64_t st[8U] = { 0U };
  Hacl_SHA2_Scalar32_sha384_init(st);
  uint32_t rem = input_len % 128U;
  FStar_UInt128_uint128 len_ = FStar_UInt128_uint64_to_uint128((uint64_t)input_len);
  Hacl_SHA2_Scalar32_sha384_update_nblocks(input_len, ib, st);
  uint32_t rem1 = input_len % 128U;
  uint8_t *b0 = ib;
  uint8_t *lb = b0 + input_len - rem1;
  Hacl_SHA2_Scalar32_sha384_update_last(len_, rem, lb, st);
  Hacl_SHA2_Scalar32_sha384_finish(st, rb);
}

/* SNIPPET_END: Hacl_Streaming_SHA2_hash_384 */

