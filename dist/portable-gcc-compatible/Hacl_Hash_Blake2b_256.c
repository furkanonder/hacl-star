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


#include "Hacl_Hash_Blake2b_256.h"

#include "internal/Hacl_Impl_Blake2_Constants.h"
#include "internal/Hacl_Hash_Blake2.h"
#include "lib_memzero0.h"

/* SNIPPET_START: blake2b_update_block */

static inline void
blake2b_update_block(
  Lib_IntVector_Intrinsics_vec256 *wv,
  Lib_IntVector_Intrinsics_vec256 *hash,
  bool flag,
  FStar_UInt128_uint128 totlen,
  uint8_t *d
)
{
  uint64_t m_w[16U] = { 0U };
  KRML_MAYBE_FOR16(i,
    0U,
    16U,
    1U,
    uint64_t *os = m_w;
    uint8_t *bj = d + i * 8U;
    uint64_t u = load64_le(bj);
    uint64_t r = u;
    uint64_t x = r;
    os[i] = x;);
  Lib_IntVector_Intrinsics_vec256 mask = Lib_IntVector_Intrinsics_vec256_zero;
  uint64_t wv_14;
  if (flag)
  {
    wv_14 = 0xFFFFFFFFFFFFFFFFULL;
  }
  else
  {
    wv_14 = 0ULL;
  }
  uint64_t wv_15 = 0ULL;
  mask =
    Lib_IntVector_Intrinsics_vec256_load64s(FStar_UInt128_uint128_to_uint64(totlen),
      FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(totlen, 64U)),
      wv_14,
      wv_15);
  memcpy(wv, hash, 4U * sizeof (Lib_IntVector_Intrinsics_vec256));
  Lib_IntVector_Intrinsics_vec256 *wv3 = wv + 3U;
  wv3[0U] = Lib_IntVector_Intrinsics_vec256_xor(wv3[0U], mask);
  KRML_MAYBE_FOR12(i,
    0U,
    12U,
    1U,
    uint32_t start_idx = i % 10U * 16U;
    KRML_PRE_ALIGN(32) Lib_IntVector_Intrinsics_vec256 m_st[4U] KRML_POST_ALIGN(32) = { 0U };
    Lib_IntVector_Intrinsics_vec256 *r0 = m_st;
    Lib_IntVector_Intrinsics_vec256 *r1 = m_st + 1U;
    Lib_IntVector_Intrinsics_vec256 *r20 = m_st + 2U;
    Lib_IntVector_Intrinsics_vec256 *r30 = m_st + 3U;
    uint32_t s0 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 0U];
    uint32_t s1 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 1U];
    uint32_t s2 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 2U];
    uint32_t s3 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 3U];
    uint32_t s4 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 4U];
    uint32_t s5 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 5U];
    uint32_t s6 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 6U];
    uint32_t s7 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 7U];
    uint32_t s8 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 8U];
    uint32_t s9 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 9U];
    uint32_t s10 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 10U];
    uint32_t s11 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 11U];
    uint32_t s12 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 12U];
    uint32_t s13 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 13U];
    uint32_t s14 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 14U];
    uint32_t s15 = Hacl_Impl_Blake2_Constants_sigmaTable[start_idx + 15U];
    r0[0U] = Lib_IntVector_Intrinsics_vec256_load64s(m_w[s0], m_w[s2], m_w[s4], m_w[s6]);
    r1[0U] = Lib_IntVector_Intrinsics_vec256_load64s(m_w[s1], m_w[s3], m_w[s5], m_w[s7]);
    r20[0U] = Lib_IntVector_Intrinsics_vec256_load64s(m_w[s8], m_w[s10], m_w[s12], m_w[s14]);
    r30[0U] = Lib_IntVector_Intrinsics_vec256_load64s(m_w[s9], m_w[s11], m_w[s13], m_w[s15]);
    Lib_IntVector_Intrinsics_vec256 *x = m_st;
    Lib_IntVector_Intrinsics_vec256 *y = m_st + 1U;
    Lib_IntVector_Intrinsics_vec256 *z = m_st + 2U;
    Lib_IntVector_Intrinsics_vec256 *w = m_st + 3U;
    uint32_t a = 0U;
    uint32_t b0 = 1U;
    uint32_t c0 = 2U;
    uint32_t d10 = 3U;
    Lib_IntVector_Intrinsics_vec256 *wv_a0 = wv + a * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b0 = wv + b0 * 1U;
    wv_a0[0U] = Lib_IntVector_Intrinsics_vec256_add64(wv_a0[0U], wv_b0[0U]);
    wv_a0[0U] = Lib_IntVector_Intrinsics_vec256_add64(wv_a0[0U], x[0U]);
    Lib_IntVector_Intrinsics_vec256 *wv_a1 = wv + d10 * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b1 = wv + a * 1U;
    wv_a1[0U] = Lib_IntVector_Intrinsics_vec256_xor(wv_a1[0U], wv_b1[0U]);
    wv_a1[0U] = Lib_IntVector_Intrinsics_vec256_rotate_right64(wv_a1[0U], 32U);
    Lib_IntVector_Intrinsics_vec256 *wv_a2 = wv + c0 * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b2 = wv + d10 * 1U;
    wv_a2[0U] = Lib_IntVector_Intrinsics_vec256_add64(wv_a2[0U], wv_b2[0U]);
    Lib_IntVector_Intrinsics_vec256 *wv_a3 = wv + b0 * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b3 = wv + c0 * 1U;
    wv_a3[0U] = Lib_IntVector_Intrinsics_vec256_xor(wv_a3[0U], wv_b3[0U]);
    wv_a3[0U] = Lib_IntVector_Intrinsics_vec256_rotate_right64(wv_a3[0U], 24U);
    Lib_IntVector_Intrinsics_vec256 *wv_a4 = wv + a * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b4 = wv + b0 * 1U;
    wv_a4[0U] = Lib_IntVector_Intrinsics_vec256_add64(wv_a4[0U], wv_b4[0U]);
    wv_a4[0U] = Lib_IntVector_Intrinsics_vec256_add64(wv_a4[0U], y[0U]);
    Lib_IntVector_Intrinsics_vec256 *wv_a5 = wv + d10 * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b5 = wv + a * 1U;
    wv_a5[0U] = Lib_IntVector_Intrinsics_vec256_xor(wv_a5[0U], wv_b5[0U]);
    wv_a5[0U] = Lib_IntVector_Intrinsics_vec256_rotate_right64(wv_a5[0U], 16U);
    Lib_IntVector_Intrinsics_vec256 *wv_a6 = wv + c0 * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b6 = wv + d10 * 1U;
    wv_a6[0U] = Lib_IntVector_Intrinsics_vec256_add64(wv_a6[0U], wv_b6[0U]);
    Lib_IntVector_Intrinsics_vec256 *wv_a7 = wv + b0 * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b7 = wv + c0 * 1U;
    wv_a7[0U] = Lib_IntVector_Intrinsics_vec256_xor(wv_a7[0U], wv_b7[0U]);
    wv_a7[0U] = Lib_IntVector_Intrinsics_vec256_rotate_right64(wv_a7[0U], 63U);
    Lib_IntVector_Intrinsics_vec256 *r10 = wv + 1U;
    Lib_IntVector_Intrinsics_vec256 *r21 = wv + 2U;
    Lib_IntVector_Intrinsics_vec256 *r31 = wv + 3U;
    Lib_IntVector_Intrinsics_vec256 v00 = r10[0U];
    Lib_IntVector_Intrinsics_vec256
    v1 = Lib_IntVector_Intrinsics_vec256_rotate_right_lanes64(v00, 1U);
    r10[0U] = v1;
    Lib_IntVector_Intrinsics_vec256 v01 = r21[0U];
    Lib_IntVector_Intrinsics_vec256
    v10 = Lib_IntVector_Intrinsics_vec256_rotate_right_lanes64(v01, 2U);
    r21[0U] = v10;
    Lib_IntVector_Intrinsics_vec256 v02 = r31[0U];
    Lib_IntVector_Intrinsics_vec256
    v11 = Lib_IntVector_Intrinsics_vec256_rotate_right_lanes64(v02, 3U);
    r31[0U] = v11;
    uint32_t a0 = 0U;
    uint32_t b = 1U;
    uint32_t c = 2U;
    uint32_t d1 = 3U;
    Lib_IntVector_Intrinsics_vec256 *wv_a = wv + a0 * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b8 = wv + b * 1U;
    wv_a[0U] = Lib_IntVector_Intrinsics_vec256_add64(wv_a[0U], wv_b8[0U]);
    wv_a[0U] = Lib_IntVector_Intrinsics_vec256_add64(wv_a[0U], z[0U]);
    Lib_IntVector_Intrinsics_vec256 *wv_a8 = wv + d1 * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b9 = wv + a0 * 1U;
    wv_a8[0U] = Lib_IntVector_Intrinsics_vec256_xor(wv_a8[0U], wv_b9[0U]);
    wv_a8[0U] = Lib_IntVector_Intrinsics_vec256_rotate_right64(wv_a8[0U], 32U);
    Lib_IntVector_Intrinsics_vec256 *wv_a9 = wv + c * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b10 = wv + d1 * 1U;
    wv_a9[0U] = Lib_IntVector_Intrinsics_vec256_add64(wv_a9[0U], wv_b10[0U]);
    Lib_IntVector_Intrinsics_vec256 *wv_a10 = wv + b * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b11 = wv + c * 1U;
    wv_a10[0U] = Lib_IntVector_Intrinsics_vec256_xor(wv_a10[0U], wv_b11[0U]);
    wv_a10[0U] = Lib_IntVector_Intrinsics_vec256_rotate_right64(wv_a10[0U], 24U);
    Lib_IntVector_Intrinsics_vec256 *wv_a11 = wv + a0 * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b12 = wv + b * 1U;
    wv_a11[0U] = Lib_IntVector_Intrinsics_vec256_add64(wv_a11[0U], wv_b12[0U]);
    wv_a11[0U] = Lib_IntVector_Intrinsics_vec256_add64(wv_a11[0U], w[0U]);
    Lib_IntVector_Intrinsics_vec256 *wv_a12 = wv + d1 * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b13 = wv + a0 * 1U;
    wv_a12[0U] = Lib_IntVector_Intrinsics_vec256_xor(wv_a12[0U], wv_b13[0U]);
    wv_a12[0U] = Lib_IntVector_Intrinsics_vec256_rotate_right64(wv_a12[0U], 16U);
    Lib_IntVector_Intrinsics_vec256 *wv_a13 = wv + c * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b14 = wv + d1 * 1U;
    wv_a13[0U] = Lib_IntVector_Intrinsics_vec256_add64(wv_a13[0U], wv_b14[0U]);
    Lib_IntVector_Intrinsics_vec256 *wv_a14 = wv + b * 1U;
    Lib_IntVector_Intrinsics_vec256 *wv_b = wv + c * 1U;
    wv_a14[0U] = Lib_IntVector_Intrinsics_vec256_xor(wv_a14[0U], wv_b[0U]);
    wv_a14[0U] = Lib_IntVector_Intrinsics_vec256_rotate_right64(wv_a14[0U], 63U);
    Lib_IntVector_Intrinsics_vec256 *r11 = wv + 1U;
    Lib_IntVector_Intrinsics_vec256 *r2 = wv + 2U;
    Lib_IntVector_Intrinsics_vec256 *r3 = wv + 3U;
    Lib_IntVector_Intrinsics_vec256 v0 = r11[0U];
    Lib_IntVector_Intrinsics_vec256
    v12 = Lib_IntVector_Intrinsics_vec256_rotate_right_lanes64(v0, 3U);
    r11[0U] = v12;
    Lib_IntVector_Intrinsics_vec256 v03 = r2[0U];
    Lib_IntVector_Intrinsics_vec256
    v13 = Lib_IntVector_Intrinsics_vec256_rotate_right_lanes64(v03, 2U);
    r2[0U] = v13;
    Lib_IntVector_Intrinsics_vec256 v04 = r3[0U];
    Lib_IntVector_Intrinsics_vec256
    v14 = Lib_IntVector_Intrinsics_vec256_rotate_right_lanes64(v04, 1U);
    r3[0U] = v14;);
  Lib_IntVector_Intrinsics_vec256 *s0 = hash;
  Lib_IntVector_Intrinsics_vec256 *s1 = hash + 1U;
  Lib_IntVector_Intrinsics_vec256 *r0 = wv;
  Lib_IntVector_Intrinsics_vec256 *r1 = wv + 1U;
  Lib_IntVector_Intrinsics_vec256 *r2 = wv + 2U;
  Lib_IntVector_Intrinsics_vec256 *r3 = wv + 3U;
  s0[0U] = Lib_IntVector_Intrinsics_vec256_xor(s0[0U], r0[0U]);
  s0[0U] = Lib_IntVector_Intrinsics_vec256_xor(s0[0U], r2[0U]);
  s1[0U] = Lib_IntVector_Intrinsics_vec256_xor(s1[0U], r1[0U]);
  s1[0U] = Lib_IntVector_Intrinsics_vec256_xor(s1[0U], r3[0U]);
}

/* SNIPPET_END: blake2b_update_block */

/* SNIPPET_START: Hacl_Blake2b_256_blake2b_init */

void
Hacl_Blake2b_256_blake2b_init(Lib_IntVector_Intrinsics_vec256 *hash, uint32_t kk, uint32_t nn)
{
  Lib_IntVector_Intrinsics_vec256 *r0 = hash;
  Lib_IntVector_Intrinsics_vec256 *r1 = hash + 1U;
  Lib_IntVector_Intrinsics_vec256 *r2 = hash + 2U;
  Lib_IntVector_Intrinsics_vec256 *r3 = hash + 3U;
  uint64_t iv0 = Hacl_Impl_Blake2_Constants_ivTable_B[0U];
  uint64_t iv1 = Hacl_Impl_Blake2_Constants_ivTable_B[1U];
  uint64_t iv2 = Hacl_Impl_Blake2_Constants_ivTable_B[2U];
  uint64_t iv3 = Hacl_Impl_Blake2_Constants_ivTable_B[3U];
  uint64_t iv4 = Hacl_Impl_Blake2_Constants_ivTable_B[4U];
  uint64_t iv5 = Hacl_Impl_Blake2_Constants_ivTable_B[5U];
  uint64_t iv6 = Hacl_Impl_Blake2_Constants_ivTable_B[6U];
  uint64_t iv7 = Hacl_Impl_Blake2_Constants_ivTable_B[7U];
  r2[0U] = Lib_IntVector_Intrinsics_vec256_load64s(iv0, iv1, iv2, iv3);
  r3[0U] = Lib_IntVector_Intrinsics_vec256_load64s(iv4, iv5, iv6, iv7);
  uint64_t kk_shift_8 = (uint64_t)kk << 8U;
  uint64_t iv0_ = iv0 ^ (0x01010000ULL ^ (kk_shift_8 ^ (uint64_t)nn));
  r0[0U] = Lib_IntVector_Intrinsics_vec256_load64s(iv0_, iv1, iv2, iv3);
  r1[0U] = Lib_IntVector_Intrinsics_vec256_load64s(iv4, iv5, iv6, iv7);
}

/* SNIPPET_END: Hacl_Blake2b_256_blake2b_init */

/* SNIPPET_START: Hacl_Blake2b_256_blake2b_update_key */

void
Hacl_Blake2b_256_blake2b_update_key(
  Lib_IntVector_Intrinsics_vec256 *wv,
  Lib_IntVector_Intrinsics_vec256 *hash,
  uint32_t kk,
  uint8_t *k,
  uint32_t ll
)
{
  FStar_UInt128_uint128 lb = FStar_UInt128_uint64_to_uint128((uint64_t)128U);
  uint8_t b[128U] = { 0U };
  memcpy(b, k, kk * sizeof (uint8_t));
  if (ll == 0U)
  {
    blake2b_update_block(wv, hash, true, lb, b);
  }
  else
  {
    blake2b_update_block(wv, hash, false, lb, b);
  }
  Lib_Memzero0_memzero(b, 128U, uint8_t);
}

/* SNIPPET_END: Hacl_Blake2b_256_blake2b_update_key */

/* SNIPPET_START: Hacl_Blake2b_256_blake2b_update_multi */

void
Hacl_Blake2b_256_blake2b_update_multi(
  uint32_t len,
  Lib_IntVector_Intrinsics_vec256 *wv,
  Lib_IntVector_Intrinsics_vec256 *hash,
  FStar_UInt128_uint128 prev,
  uint8_t *blocks,
  uint32_t nb
)
{
  KRML_MAYBE_UNUSED_VAR(len);
  for (uint32_t i = 0U; i < nb; i++)
  {
    FStar_UInt128_uint128
    totlen =
      FStar_UInt128_add_mod(prev,
        FStar_UInt128_uint64_to_uint128((uint64_t)((i + 1U) * 128U)));
    uint8_t *b = blocks + i * 128U;
    blake2b_update_block(wv, hash, false, totlen, b);
  }
}

/* SNIPPET_END: Hacl_Blake2b_256_blake2b_update_multi */

/* SNIPPET_START: Hacl_Blake2b_256_blake2b_update_last */

void
Hacl_Blake2b_256_blake2b_update_last(
  uint32_t len,
  Lib_IntVector_Intrinsics_vec256 *wv,
  Lib_IntVector_Intrinsics_vec256 *hash,
  FStar_UInt128_uint128 prev,
  uint32_t rem,
  uint8_t *d
)
{
  uint8_t b[128U] = { 0U };
  uint8_t *last = d + len - rem;
  memcpy(b, last, rem * sizeof (uint8_t));
  FStar_UInt128_uint128
  totlen = FStar_UInt128_add_mod(prev, FStar_UInt128_uint64_to_uint128((uint64_t)len));
  blake2b_update_block(wv, hash, true, totlen, b);
  Lib_Memzero0_memzero(b, 128U, uint8_t);
}

/* SNIPPET_END: Hacl_Blake2b_256_blake2b_update_last */

/* SNIPPET_START: blake2b_update_blocks */

static inline void
blake2b_update_blocks(
  uint32_t len,
  Lib_IntVector_Intrinsics_vec256 *wv,
  Lib_IntVector_Intrinsics_vec256 *hash,
  FStar_UInt128_uint128 prev,
  uint8_t *blocks
)
{
  uint32_t nb0 = len / 128U;
  uint32_t rem0 = len % 128U;
  K___uint32_t_uint32_t scrut;
  if (rem0 == 0U && nb0 > 0U)
  {
    uint32_t nb_ = nb0 - 1U;
    uint32_t rem_ = 128U;
    scrut = ((K___uint32_t_uint32_t){ .fst = nb_, .snd = rem_ });
  }
  else
  {
    scrut = ((K___uint32_t_uint32_t){ .fst = nb0, .snd = rem0 });
  }
  uint32_t nb = scrut.fst;
  uint32_t rem = scrut.snd;
  Hacl_Blake2b_256_blake2b_update_multi(len, wv, hash, prev, blocks, nb);
  Hacl_Blake2b_256_blake2b_update_last(len, wv, hash, prev, rem, blocks);
}

/* SNIPPET_END: blake2b_update_blocks */

/* SNIPPET_START: blake2b_update */

static inline void
blake2b_update(
  Lib_IntVector_Intrinsics_vec256 *wv,
  Lib_IntVector_Intrinsics_vec256 *hash,
  uint32_t kk,
  uint8_t *k,
  uint32_t ll,
  uint8_t *d
)
{
  FStar_UInt128_uint128 lb = FStar_UInt128_uint64_to_uint128((uint64_t)128U);
  if (kk > 0U)
  {
    Hacl_Blake2b_256_blake2b_update_key(wv, hash, kk, k, ll);
    if (!(ll == 0U))
    {
      blake2b_update_blocks(ll, wv, hash, lb, d);
      return;
    }
    return;
  }
  blake2b_update_blocks(ll, wv, hash, FStar_UInt128_uint64_to_uint128((uint64_t)0U), d);
}

/* SNIPPET_END: blake2b_update */

/* SNIPPET_START: Hacl_Blake2b_256_blake2b_finish */

void
Hacl_Blake2b_256_blake2b_finish(
  uint32_t nn,
  uint8_t *output,
  Lib_IntVector_Intrinsics_vec256 *hash
)
{
  uint8_t b[64U] = { 0U };
  uint8_t *first = b;
  uint8_t *second = b + 32U;
  Lib_IntVector_Intrinsics_vec256 *row0 = hash;
  Lib_IntVector_Intrinsics_vec256 *row1 = hash + 1U;
  Lib_IntVector_Intrinsics_vec256_store64_le(first, row0[0U]);
  Lib_IntVector_Intrinsics_vec256_store64_le(second, row1[0U]);
  uint8_t *final = b;
  memcpy(output, final, nn * sizeof (uint8_t));
  Lib_Memzero0_memzero(b, 64U, uint8_t);
}

/* SNIPPET_END: Hacl_Blake2b_256_blake2b_finish */

/* SNIPPET_START: Hacl_Blake2b_256_blake2b */

/**
Write the BLAKE2b digest of message `d` using key `k` into `output`.

@param nn Length of the to-be-generated digest with 1 <= `nn` <= 64.
@param output Pointer to `nn` bytes of memory where the digest is written to.
@param ll Length of the input message.
@param d Pointer to `ll` bytes of memory where the input message is read from.
@param kk Length of the key. Can be 0.
@param k Pointer to `kk` bytes of memory where the key is read from.
*/
void
Hacl_Blake2b_256_blake2b(
  uint32_t nn,
  uint8_t *output,
  uint32_t ll,
  uint8_t *d,
  uint32_t kk,
  uint8_t *k
)
{
  KRML_PRE_ALIGN(32) Lib_IntVector_Intrinsics_vec256 b[4U] KRML_POST_ALIGN(32) = { 0U };
  KRML_PRE_ALIGN(32) Lib_IntVector_Intrinsics_vec256 b1[4U] KRML_POST_ALIGN(32) = { 0U };
  Hacl_Blake2b_256_blake2b_init(b, kk, nn);
  blake2b_update(b1, b, kk, k, ll, d);
  Hacl_Blake2b_256_blake2b_finish(nn, output, b);
  Lib_Memzero0_memzero(b1, 4U, Lib_IntVector_Intrinsics_vec256);
  Lib_Memzero0_memzero(b, 4U, Lib_IntVector_Intrinsics_vec256);
}

/* SNIPPET_END: Hacl_Blake2b_256_blake2b */

/* SNIPPET_START: Hacl_Blake2b_256_load_state256b_from_state32 */

void
Hacl_Blake2b_256_load_state256b_from_state32(
  Lib_IntVector_Intrinsics_vec256 *st,
  uint64_t *st32
)
{
  Lib_IntVector_Intrinsics_vec256 *r0 = st;
  Lib_IntVector_Intrinsics_vec256 *r1 = st + 1U;
  Lib_IntVector_Intrinsics_vec256 *r2 = st + 2U;
  Lib_IntVector_Intrinsics_vec256 *r3 = st + 3U;
  uint64_t *b0 = st32;
  uint64_t *b1 = st32 + 4U;
  uint64_t *b2 = st32 + 8U;
  uint64_t *b3 = st32 + 12U;
  r0[0U] = Lib_IntVector_Intrinsics_vec256_load64s(b0[0U], b0[1U], b0[2U], b0[3U]);
  r1[0U] = Lib_IntVector_Intrinsics_vec256_load64s(b1[0U], b1[1U], b1[2U], b1[3U]);
  r2[0U] = Lib_IntVector_Intrinsics_vec256_load64s(b2[0U], b2[1U], b2[2U], b2[3U]);
  r3[0U] = Lib_IntVector_Intrinsics_vec256_load64s(b3[0U], b3[1U], b3[2U], b3[3U]);
}

/* SNIPPET_END: Hacl_Blake2b_256_load_state256b_from_state32 */

/* SNIPPET_START: Hacl_Blake2b_256_store_state256b_to_state32 */

void
Hacl_Blake2b_256_store_state256b_to_state32(
  uint64_t *st32,
  Lib_IntVector_Intrinsics_vec256 *st
)
{
  Lib_IntVector_Intrinsics_vec256 *r0 = st;
  Lib_IntVector_Intrinsics_vec256 *r1 = st + 1U;
  Lib_IntVector_Intrinsics_vec256 *r2 = st + 2U;
  Lib_IntVector_Intrinsics_vec256 *r3 = st + 3U;
  uint64_t *b0 = st32;
  uint64_t *b1 = st32 + 4U;
  uint64_t *b2 = st32 + 8U;
  uint64_t *b3 = st32 + 12U;
  uint8_t b8[32U] = { 0U };
  Lib_IntVector_Intrinsics_vec256_store64_le(b8, r0[0U]);
  KRML_MAYBE_FOR4(i,
    0U,
    4U,
    1U,
    uint64_t *os = b0;
    uint8_t *bj = b8 + i * 8U;
    uint64_t u = load64_le(bj);
    uint64_t r = u;
    uint64_t x = r;
    os[i] = x;);
  uint8_t b80[32U] = { 0U };
  Lib_IntVector_Intrinsics_vec256_store64_le(b80, r1[0U]);
  KRML_MAYBE_FOR4(i,
    0U,
    4U,
    1U,
    uint64_t *os = b1;
    uint8_t *bj = b80 + i * 8U;
    uint64_t u = load64_le(bj);
    uint64_t r = u;
    uint64_t x = r;
    os[i] = x;);
  uint8_t b81[32U] = { 0U };
  Lib_IntVector_Intrinsics_vec256_store64_le(b81, r2[0U]);
  KRML_MAYBE_FOR4(i,
    0U,
    4U,
    1U,
    uint64_t *os = b2;
    uint8_t *bj = b81 + i * 8U;
    uint64_t u = load64_le(bj);
    uint64_t r = u;
    uint64_t x = r;
    os[i] = x;);
  uint8_t b82[32U] = { 0U };
  Lib_IntVector_Intrinsics_vec256_store64_le(b82, r3[0U]);
  KRML_MAYBE_FOR4(i,
    0U,
    4U,
    1U,
    uint64_t *os = b3;
    uint8_t *bj = b82 + i * 8U;
    uint64_t u = load64_le(bj);
    uint64_t r = u;
    uint64_t x = r;
    os[i] = x;);
}

/* SNIPPET_END: Hacl_Blake2b_256_store_state256b_to_state32 */

/* SNIPPET_START: Hacl_Blake2b_256_blake2b_malloc */

Lib_IntVector_Intrinsics_vec256 *Hacl_Blake2b_256_blake2b_malloc(void)
{
  Lib_IntVector_Intrinsics_vec256
  *buf =
    (Lib_IntVector_Intrinsics_vec256 *)KRML_ALIGNED_MALLOC(32,
      sizeof (Lib_IntVector_Intrinsics_vec256) * 4U);
  memset(buf, 0U, 4U * sizeof (Lib_IntVector_Intrinsics_vec256));
  return buf;
}

/* SNIPPET_END: Hacl_Blake2b_256_blake2b_malloc */

