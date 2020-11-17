/* MIT License
 *
 * Copyright (c) 2016-2020 INRIA, CMU and Microsoft Corporation
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


#ifndef __Hacl_Bignum_H
#define __Hacl_Bignum_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "evercrypt_targetconfig.h"
#include "lib_intrinsics.h"
#include "libintvector.h"
#include "kremlin/internal/types.h"
#include "kremlin/lowstar_endianness.h"
#include <string.h>
#include "kremlin/internal/target.h"


#include "Hacl_Kremlib.h"

/* SNIPPET_START: Hacl_Bignum_Convert_bn_from_bytes_be_uint64 */

static inline void
Hacl_Bignum_Convert_bn_from_bytes_be_uint64(uint32_t len, uint8_t *b, uint64_t *res)
{
  uint32_t bnLen = (len - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U;
  uint32_t tmpLen = (uint32_t)8U * bnLen;
  KRML_CHECK_SIZE(sizeof (uint8_t), tmpLen);
  uint8_t tmp[tmpLen];
  memset(tmp, 0U, tmpLen * sizeof (uint8_t));
  memcpy(tmp + tmpLen - len, b, len * sizeof (uint8_t));
  for (uint32_t i = (uint32_t)0U; i < bnLen; i++)
  {
    uint64_t *os = res;
    uint64_t u = load64_be(tmp + (bnLen - i - (uint32_t)1U) * (uint32_t)8U);
    uint64_t x = u;
    os[i] = x;
  }
}

/* SNIPPET_END: Hacl_Bignum_Convert_bn_from_bytes_be_uint64 */

/* SNIPPET_START: Hacl_Bignum_Convert_bn_to_bytes_be_uint64 */

static inline void
Hacl_Bignum_Convert_bn_to_bytes_be_uint64(uint32_t len, uint64_t *b, uint8_t *res)
{
  uint32_t bnLen = (len - (uint32_t)1U) / (uint32_t)8U + (uint32_t)1U;
  uint32_t tmpLen = (uint32_t)8U * bnLen;
  KRML_CHECK_SIZE(sizeof (uint8_t), tmpLen);
  uint8_t tmp[tmpLen];
  memset(tmp, 0U, tmpLen * sizeof (uint8_t));
  uint32_t numb = (uint32_t)8U;
  for (uint32_t i = (uint32_t)0U; i < bnLen; i++)
  {
    store64_be(tmp + i * numb, b[bnLen - i - (uint32_t)1U]);
  }
  memcpy(res, tmp + tmpLen - len, len * sizeof (uint8_t));
}

/* SNIPPET_END: Hacl_Bignum_Convert_bn_to_bytes_be_uint64 */

/* SNIPPET_START: Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64 */

static inline void
Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(
  uint32_t aLen,
  uint64_t *a,
  uint64_t *b,
  uint64_t *tmp,
  uint64_t *res
)
{
  if (aLen < (uint32_t)32U || aLen % (uint32_t)2U == (uint32_t)1U)
  {
    uint32_t resLen = aLen + aLen;
    memset(res, 0U, resLen * sizeof (uint64_t));
    for (uint32_t i0 = (uint32_t)0U; i0 < aLen; i0++)
    {
      uint64_t uu____0 = b[i0];
      uint64_t *res_ = res + i0;
      uint64_t c = (uint64_t)0U;
      uint32_t k = aLen / (uint32_t)4U * (uint32_t)4U;
      for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
      {
        uint64_t uu____1 = a[(uint32_t)4U * i];
        uint64_t uu____2 = c;
        uint64_t *uu____3 = res_ + (uint32_t)4U * i;
        FStar_UInt128_uint128 uu____4 = FStar_UInt128_uint64_to_uint128(uu____3[0U]);
        FStar_UInt128_uint128
        res1 =
          FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____1, uu____0),
              FStar_UInt128_uint64_to_uint128(uu____2)),
            uu____4);
        uu____3[0U] = FStar_UInt128_uint128_to_uint64(res1);
        c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res1, (uint32_t)64U));
        uint64_t uu____5 = a[(uint32_t)4U * i + (uint32_t)1U];
        uint64_t uu____6 = c;
        uint64_t *uu____7 = res_ + (uint32_t)4U * i + (uint32_t)1U;
        FStar_UInt128_uint128 uu____8 = FStar_UInt128_uint64_to_uint128(uu____7[0U]);
        FStar_UInt128_uint128
        res10 =
          FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____5, uu____0),
              FStar_UInt128_uint64_to_uint128(uu____6)),
            uu____8);
        uu____7[0U] = FStar_UInt128_uint128_to_uint64(res10);
        c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res10, (uint32_t)64U));
        uint64_t uu____9 = a[(uint32_t)4U * i + (uint32_t)2U];
        uint64_t uu____10 = c;
        uint64_t *uu____11 = res_ + (uint32_t)4U * i + (uint32_t)2U;
        FStar_UInt128_uint128 uu____12 = FStar_UInt128_uint64_to_uint128(uu____11[0U]);
        FStar_UInt128_uint128
        res11 =
          FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____9, uu____0),
              FStar_UInt128_uint64_to_uint128(uu____10)),
            uu____12);
        uu____11[0U] = FStar_UInt128_uint128_to_uint64(res11);
        c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res11, (uint32_t)64U));
        uint64_t uu____13 = a[(uint32_t)4U * i + (uint32_t)3U];
        uint64_t uu____14 = c;
        uint64_t *uu____15 = res_ + (uint32_t)4U * i + (uint32_t)3U;
        FStar_UInt128_uint128 uu____16 = FStar_UInt128_uint64_to_uint128(uu____15[0U]);
        FStar_UInt128_uint128
        res12 =
          FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____13, uu____0),
              FStar_UInt128_uint64_to_uint128(uu____14)),
            uu____16);
        uu____15[0U] = FStar_UInt128_uint128_to_uint64(res12);
        c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res12, (uint32_t)64U));
      }
      for (uint32_t i = k; i < aLen; i++)
      {
        uint64_t uu____17 = a[i];
        uint64_t uu____18 = c;
        uint64_t *uu____19 = res_ + i;
        FStar_UInt128_uint128 uu____20 = FStar_UInt128_uint64_to_uint128(uu____19[0U]);
        FStar_UInt128_uint128
        res1 =
          FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____17, uu____0),
              FStar_UInt128_uint64_to_uint128(uu____18)),
            uu____20);
        uu____19[0U] = FStar_UInt128_uint128_to_uint64(res1);
        c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res1, (uint32_t)64U));
      }
      uint64_t r = c;
      res[aLen + i0] = r;
    }
    return;
  }
  uint32_t len2 = aLen / (uint32_t)2U;
  uint64_t *a0 = a;
  uint64_t *a1 = a + len2;
  uint64_t *b0 = b;
  uint64_t *b1 = b + len2;
  uint64_t *t0 = tmp;
  uint64_t *t1 = tmp + len2;
  uint64_t *tmp_ = tmp + aLen;
  uint64_t c0 = (uint64_t)0U;
  uint32_t k0 = len2 / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k0 / (uint32_t)4U; i++)
  {
    uint64_t t11 = a0[(uint32_t)4U * i];
    uint64_t t20 = a1[(uint32_t)4U * i];
    c0 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c0, t11, t20, tmp_ + (uint32_t)4U * i);
    uint64_t t110 = a0[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = a1[(uint32_t)4U * i + (uint32_t)1U];
    c0 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c0,
        t110,
        t21,
        tmp_ + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t111 = a0[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = a1[(uint32_t)4U * i + (uint32_t)2U];
    c0 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c0,
        t111,
        t22,
        tmp_ + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t112 = a0[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = a1[(uint32_t)4U * i + (uint32_t)3U];
    c0 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c0,
        t112,
        t2,
        tmp_ + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k0; i < len2; i++)
  {
    uint64_t t11 = a0[i];
    uint64_t t2 = a1[i];
    c0 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c0, t11, t2, tmp_ + i);
  }
  uint64_t c00 = c0;
  uint64_t c1 = (uint64_t)0U;
  uint32_t k1 = len2 / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k1 / (uint32_t)4U; i++)
  {
    uint64_t t11 = a1[(uint32_t)4U * i];
    uint64_t t20 = a0[(uint32_t)4U * i];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t11, t20, t0 + (uint32_t)4U * i);
    uint64_t t110 = a1[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = a0[(uint32_t)4U * i + (uint32_t)1U];
    c1 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c1,
        t110,
        t21,
        t0 + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t111 = a1[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = a0[(uint32_t)4U * i + (uint32_t)2U];
    c1 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c1,
        t111,
        t22,
        t0 + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t112 = a1[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = a0[(uint32_t)4U * i + (uint32_t)3U];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t112, t2, t0 + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k1; i < len2; i++)
  {
    uint64_t t11 = a1[i];
    uint64_t t2 = a0[i];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t11, t2, t0 + i);
  }
  uint64_t c10 = c1;
  for (uint32_t i = (uint32_t)0U; i < len2; i++)
  {
    uint64_t *os = t0;
    uint64_t x = (((uint64_t)0U - c00) & t0[i]) | (~((uint64_t)0U - c00) & tmp_[i]);
    os[i] = x;
  }
  uint64_t c01 = c00;
  uint64_t c2 = (uint64_t)0U;
  uint32_t k2 = len2 / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k2 / (uint32_t)4U; i++)
  {
    uint64_t t11 = b0[(uint32_t)4U * i];
    uint64_t t20 = b1[(uint32_t)4U * i];
    c2 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c2, t11, t20, tmp_ + (uint32_t)4U * i);
    uint64_t t110 = b0[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = b1[(uint32_t)4U * i + (uint32_t)1U];
    c2 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c2,
        t110,
        t21,
        tmp_ + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t111 = b0[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = b1[(uint32_t)4U * i + (uint32_t)2U];
    c2 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c2,
        t111,
        t22,
        tmp_ + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t112 = b0[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = b1[(uint32_t)4U * i + (uint32_t)3U];
    c2 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c2,
        t112,
        t2,
        tmp_ + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k2; i < len2; i++)
  {
    uint64_t t11 = b0[i];
    uint64_t t2 = b1[i];
    c2 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c2, t11, t2, tmp_ + i);
  }
  uint64_t c010 = c2;
  uint64_t c3 = (uint64_t)0U;
  uint32_t k3 = len2 / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k3 / (uint32_t)4U; i++)
  {
    uint64_t t11 = b1[(uint32_t)4U * i];
    uint64_t t20 = b0[(uint32_t)4U * i];
    c3 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c3, t11, t20, t1 + (uint32_t)4U * i);
    uint64_t t110 = b1[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = b0[(uint32_t)4U * i + (uint32_t)1U];
    c3 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c3,
        t110,
        t21,
        t1 + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t111 = b1[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = b0[(uint32_t)4U * i + (uint32_t)2U];
    c3 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c3,
        t111,
        t22,
        t1 + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t112 = b1[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = b0[(uint32_t)4U * i + (uint32_t)3U];
    c3 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c3, t112, t2, t1 + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k3; i < len2; i++)
  {
    uint64_t t11 = b1[i];
    uint64_t t2 = b0[i];
    c3 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c3, t11, t2, t1 + i);
  }
  uint64_t c11 = c3;
  for (uint32_t i = (uint32_t)0U; i < len2; i++)
  {
    uint64_t *os = t1;
    uint64_t x = (((uint64_t)0U - c010) & t1[i]) | (~((uint64_t)0U - c010) & tmp_[i]);
    os[i] = x;
  }
  uint64_t c12 = c010;
  uint64_t *t23 = tmp + aLen;
  uint64_t *tmp1 = tmp + aLen + aLen;
  Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(len2, t0, t1, tmp1, t23);
  uint64_t *r01 = res;
  uint64_t *r23 = res + aLen;
  Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(len2, a0, b0, tmp1, r01);
  Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(len2, a1, b1, tmp1, r23);
  uint64_t *r011 = res;
  uint64_t *r231 = res + aLen;
  uint64_t *t01 = tmp;
  uint64_t *t231 = tmp + aLen;
  uint64_t *t45 = tmp + (uint32_t)2U * aLen;
  uint64_t *t67 = tmp + (uint32_t)3U * aLen;
  uint64_t c4 = (uint64_t)0U;
  uint32_t k4 = aLen / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k4 / (uint32_t)4U; i++)
  {
    uint64_t t11 = r011[(uint32_t)4U * i];
    uint64_t t20 = r231[(uint32_t)4U * i];
    c4 = Lib_IntTypes_Intrinsics_add_carry_u64(c4, t11, t20, t01 + (uint32_t)4U * i);
    uint64_t t110 = r011[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = r231[(uint32_t)4U * i + (uint32_t)1U];
    c4 =
      Lib_IntTypes_Intrinsics_add_carry_u64(c4,
        t110,
        t21,
        t01 + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t111 = r011[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = r231[(uint32_t)4U * i + (uint32_t)2U];
    c4 =
      Lib_IntTypes_Intrinsics_add_carry_u64(c4,
        t111,
        t22,
        t01 + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t112 = r011[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = r231[(uint32_t)4U * i + (uint32_t)3U];
    c4 = Lib_IntTypes_Intrinsics_add_carry_u64(c4, t112, t2, t01 + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k4; i < aLen; i++)
  {
    uint64_t t11 = r011[i];
    uint64_t t2 = r231[i];
    c4 = Lib_IntTypes_Intrinsics_add_carry_u64(c4, t11, t2, t01 + i);
  }
  uint64_t c20 = c4;
  uint64_t c_sign = c01 ^ c12;
  uint64_t c5 = (uint64_t)0U;
  uint32_t k5 = aLen / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k5 / (uint32_t)4U; i++)
  {
    uint64_t t11 = t01[(uint32_t)4U * i];
    uint64_t t20 = t231[(uint32_t)4U * i];
    c5 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c5, t11, t20, t67 + (uint32_t)4U * i);
    uint64_t t110 = t01[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = t231[(uint32_t)4U * i + (uint32_t)1U];
    c5 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c5,
        t110,
        t21,
        t67 + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t111 = t01[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = t231[(uint32_t)4U * i + (uint32_t)2U];
    c5 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c5,
        t111,
        t22,
        t67 + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t112 = t01[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = t231[(uint32_t)4U * i + (uint32_t)3U];
    c5 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c5,
        t112,
        t2,
        t67 + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k5; i < aLen; i++)
  {
    uint64_t t11 = t01[i];
    uint64_t t2 = t231[i];
    c5 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c5, t11, t2, t67 + i);
  }
  uint64_t c30 = c5;
  uint64_t c31 = c20 - c30;
  uint64_t c6 = (uint64_t)0U;
  uint32_t k6 = aLen / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k6 / (uint32_t)4U; i++)
  {
    uint64_t t11 = t01[(uint32_t)4U * i];
    uint64_t t20 = t231[(uint32_t)4U * i];
    c6 = Lib_IntTypes_Intrinsics_add_carry_u64(c6, t11, t20, t45 + (uint32_t)4U * i);
    uint64_t t110 = t01[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = t231[(uint32_t)4U * i + (uint32_t)1U];
    c6 =
      Lib_IntTypes_Intrinsics_add_carry_u64(c6,
        t110,
        t21,
        t45 + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t111 = t01[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = t231[(uint32_t)4U * i + (uint32_t)2U];
    c6 =
      Lib_IntTypes_Intrinsics_add_carry_u64(c6,
        t111,
        t22,
        t45 + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t112 = t01[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = t231[(uint32_t)4U * i + (uint32_t)3U];
    c6 = Lib_IntTypes_Intrinsics_add_carry_u64(c6, t112, t2, t45 + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k6; i < aLen; i++)
  {
    uint64_t t11 = t01[i];
    uint64_t t2 = t231[i];
    c6 = Lib_IntTypes_Intrinsics_add_carry_u64(c6, t11, t2, t45 + i);
  }
  uint64_t c40 = c6;
  uint64_t c41 = c20 + c40;
  uint64_t mask = (uint64_t)0U - c_sign;
  for (uint32_t i = (uint32_t)0U; i < aLen; i++)
  {
    uint64_t *os = t45;
    uint64_t x = (mask & t45[i]) | (~mask & t67[i]);
    os[i] = x;
  }
  uint64_t c50 = (mask & c41) | (~mask & c31);
  uint32_t aLen2 = aLen / (uint32_t)2U;
  uint64_t *r0 = res + aLen2;
  uint64_t c7 = (uint64_t)0U;
  uint32_t k7 = aLen / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k7 / (uint32_t)4U; i++)
  {
    uint64_t t11 = r0[(uint32_t)4U * i];
    uint64_t t20 = t45[(uint32_t)4U * i];
    c7 = Lib_IntTypes_Intrinsics_add_carry_u64(c7, t11, t20, r0 + (uint32_t)4U * i);
    uint64_t t110 = r0[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = t45[(uint32_t)4U * i + (uint32_t)1U];
    c7 = Lib_IntTypes_Intrinsics_add_carry_u64(c7, t110, t21, r0 + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t111 = r0[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = t45[(uint32_t)4U * i + (uint32_t)2U];
    c7 = Lib_IntTypes_Intrinsics_add_carry_u64(c7, t111, t22, r0 + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t112 = r0[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = t45[(uint32_t)4U * i + (uint32_t)3U];
    c7 = Lib_IntTypes_Intrinsics_add_carry_u64(c7, t112, t2, r0 + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k7; i < aLen; i++)
  {
    uint64_t t11 = r0[i];
    uint64_t t2 = t45[i];
    c7 = Lib_IntTypes_Intrinsics_add_carry_u64(c7, t11, t2, r0 + i);
  }
  uint64_t r10 = c7;
  uint64_t c60 = r10;
  uint64_t c70 = c50 + c60;
  uint64_t c71 = c70;
  uint64_t *r = res + aLen + aLen2;
  uint64_t *a01 = r;
  uint64_t *res0 = r;
  uint64_t c8 = (uint64_t)0U;
  uint32_t k8 = (uint32_t)0U;
  for (uint32_t i = (uint32_t)0U; i < k8 / (uint32_t)4U; i++)
  {
    uint64_t t11 = a01[(uint32_t)4U * i];
    uint64_t t20 = (&c71)[(uint32_t)4U * i];
    c8 = Lib_IntTypes_Intrinsics_add_carry_u64(c8, t11, t20, res0 + (uint32_t)4U * i);
    uint64_t t110 = a01[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = (&c71)[(uint32_t)4U * i + (uint32_t)1U];
    c8 =
      Lib_IntTypes_Intrinsics_add_carry_u64(c8,
        t110,
        t21,
        res0 + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t111 = a01[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = (&c71)[(uint32_t)4U * i + (uint32_t)2U];
    c8 =
      Lib_IntTypes_Intrinsics_add_carry_u64(c8,
        t111,
        t22,
        res0 + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t112 = a01[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = (&c71)[(uint32_t)4U * i + (uint32_t)3U];
    c8 =
      Lib_IntTypes_Intrinsics_add_carry_u64(c8,
        t112,
        t2,
        res0 + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k8; i < (uint32_t)1U; i++)
  {
    uint64_t t11 = a01[i];
    uint64_t t2 = (&c71)[i];
    c8 = Lib_IntTypes_Intrinsics_add_carry_u64(c8, t11, t2, res0 + i);
  }
  uint64_t c011 = c8;
  uint64_t r1;
  if ((uint32_t)1U < aLen + aLen - (aLen + aLen2))
  {
    uint32_t rLen = aLen + aLen - (aLen + aLen2) - (uint32_t)1U;
    uint64_t *a11 = r + (uint32_t)1U;
    uint64_t *res1 = r + (uint32_t)1U;
    uint64_t c = c011;
    uint32_t k = rLen / (uint32_t)4U * (uint32_t)4U;
    for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
    {
      uint64_t t11 = a11[(uint32_t)4U * i];
      c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t11, (uint64_t)0U, res1 + (uint32_t)4U * i);
      uint64_t t110 = a11[(uint32_t)4U * i + (uint32_t)1U];
      c =
        Lib_IntTypes_Intrinsics_add_carry_u64(c,
          t110,
          (uint64_t)0U,
          res1 + (uint32_t)4U * i + (uint32_t)1U);
      uint64_t t111 = a11[(uint32_t)4U * i + (uint32_t)2U];
      c =
        Lib_IntTypes_Intrinsics_add_carry_u64(c,
          t111,
          (uint64_t)0U,
          res1 + (uint32_t)4U * i + (uint32_t)2U);
      uint64_t t112 = a11[(uint32_t)4U * i + (uint32_t)3U];
      c =
        Lib_IntTypes_Intrinsics_add_carry_u64(c,
          t112,
          (uint64_t)0U,
          res1 + (uint32_t)4U * i + (uint32_t)3U);
    }
    for (uint32_t i = k; i < rLen; i++)
    {
      uint64_t t11 = a11[i];
      c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t11, (uint64_t)0U, res1 + i);
    }
    uint64_t c110 = c;
    r1 = c110;
  }
  else
  {
    r1 = c011;
  }
  uint64_t c80 = r1;
  uint64_t c = c80;
  uint64_t c9 = c;
}

/* SNIPPET_END: Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64 */

/* SNIPPET_START: Hacl_Bignum_Karatsuba_bn_karatsuba_sqr_uint64 */

static inline void
Hacl_Bignum_Karatsuba_bn_karatsuba_sqr_uint64(
  uint32_t aLen,
  uint64_t *a,
  uint64_t *tmp,
  uint64_t *res
)
{
  if (aLen < (uint32_t)32U || aLen % (uint32_t)2U == (uint32_t)1U)
  {
    uint32_t resLen = aLen + aLen;
    memset(res, 0U, resLen * sizeof (uint64_t));
    for (uint32_t i0 = (uint32_t)0U; i0 < aLen; i0++)
    {
      uint64_t *uu____0 = a;
      uint64_t uu____1 = a[i0];
      uint64_t *res_ = res + i0;
      uint64_t c = (uint64_t)0U;
      uint32_t k = i0 / (uint32_t)4U * (uint32_t)4U;
      for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
      {
        uint64_t uu____2 = uu____0[(uint32_t)4U * i];
        uint64_t uu____3 = c;
        uint64_t *uu____4 = res_ + (uint32_t)4U * i;
        FStar_UInt128_uint128 uu____5 = FStar_UInt128_uint64_to_uint128(uu____4[0U]);
        FStar_UInt128_uint128
        res1 =
          FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____2, uu____1),
              FStar_UInt128_uint64_to_uint128(uu____3)),
            uu____5);
        uu____4[0U] = FStar_UInt128_uint128_to_uint64(res1);
        c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res1, (uint32_t)64U));
        uint64_t uu____6 = uu____0[(uint32_t)4U * i + (uint32_t)1U];
        uint64_t uu____7 = c;
        uint64_t *uu____8 = res_ + (uint32_t)4U * i + (uint32_t)1U;
        FStar_UInt128_uint128 uu____9 = FStar_UInt128_uint64_to_uint128(uu____8[0U]);
        FStar_UInt128_uint128
        res10 =
          FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____6, uu____1),
              FStar_UInt128_uint64_to_uint128(uu____7)),
            uu____9);
        uu____8[0U] = FStar_UInt128_uint128_to_uint64(res10);
        c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res10, (uint32_t)64U));
        uint64_t uu____10 = uu____0[(uint32_t)4U * i + (uint32_t)2U];
        uint64_t uu____11 = c;
        uint64_t *uu____12 = res_ + (uint32_t)4U * i + (uint32_t)2U;
        FStar_UInt128_uint128 uu____13 = FStar_UInt128_uint64_to_uint128(uu____12[0U]);
        FStar_UInt128_uint128
        res11 =
          FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____10, uu____1),
              FStar_UInt128_uint64_to_uint128(uu____11)),
            uu____13);
        uu____12[0U] = FStar_UInt128_uint128_to_uint64(res11);
        c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res11, (uint32_t)64U));
        uint64_t uu____14 = uu____0[(uint32_t)4U * i + (uint32_t)3U];
        uint64_t uu____15 = c;
        uint64_t *uu____16 = res_ + (uint32_t)4U * i + (uint32_t)3U;
        FStar_UInt128_uint128 uu____17 = FStar_UInt128_uint64_to_uint128(uu____16[0U]);
        FStar_UInt128_uint128
        res12 =
          FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____14, uu____1),
              FStar_UInt128_uint64_to_uint128(uu____15)),
            uu____17);
        uu____16[0U] = FStar_UInt128_uint128_to_uint64(res12);
        c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res12, (uint32_t)64U));
      }
      for (uint32_t i = k; i < i0; i++)
      {
        uint64_t uu____18 = uu____0[i];
        uint64_t uu____19 = c;
        uint64_t *uu____20 = res_ + i;
        FStar_UInt128_uint128 uu____21 = FStar_UInt128_uint64_to_uint128(uu____20[0U]);
        FStar_UInt128_uint128
        res1 =
          FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____18, uu____1),
              FStar_UInt128_uint64_to_uint128(uu____19)),
            uu____21);
        uu____20[0U] = FStar_UInt128_uint128_to_uint64(res1);
        c = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res1, (uint32_t)64U));
      }
      uint64_t r = c;
      res[i0 + i0] = r;
    }
    uint64_t c0 = (uint64_t)0U;
    uint32_t k0 = resLen / (uint32_t)4U * (uint32_t)4U;
    for (uint32_t i = (uint32_t)0U; i < k0 / (uint32_t)4U; i++)
    {
      uint64_t t1 = res[(uint32_t)4U * i];
      uint64_t t20 = res[(uint32_t)4U * i];
      c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t1, t20, res + (uint32_t)4U * i);
      uint64_t t10 = res[(uint32_t)4U * i + (uint32_t)1U];
      uint64_t t21 = res[(uint32_t)4U * i + (uint32_t)1U];
      c0 =
        Lib_IntTypes_Intrinsics_add_carry_u64(c0,
          t10,
          t21,
          res + (uint32_t)4U * i + (uint32_t)1U);
      uint64_t t11 = res[(uint32_t)4U * i + (uint32_t)2U];
      uint64_t t22 = res[(uint32_t)4U * i + (uint32_t)2U];
      c0 =
        Lib_IntTypes_Intrinsics_add_carry_u64(c0,
          t11,
          t22,
          res + (uint32_t)4U * i + (uint32_t)2U);
      uint64_t t12 = res[(uint32_t)4U * i + (uint32_t)3U];
      uint64_t t2 = res[(uint32_t)4U * i + (uint32_t)3U];
      c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t12, t2, res + (uint32_t)4U * i + (uint32_t)3U);
    }
    for (uint32_t i = k0; i < resLen; i++)
    {
      uint64_t t1 = res[i];
      uint64_t t2 = res[i];
      c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t1, t2, res + i);
    }
    uint64_t uu____22 = c0;
    KRML_CHECK_SIZE(sizeof (uint64_t), resLen);
    uint64_t tmp1[resLen];
    memset(tmp1, 0U, resLen * sizeof (uint64_t));
    for (uint32_t i = (uint32_t)0U; i < aLen; i++)
    {
      FStar_UInt128_uint128 res1 = FStar_UInt128_mul_wide(a[i], a[i]);
      uint64_t hi = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res1, (uint32_t)64U));
      uint64_t lo = FStar_UInt128_uint128_to_uint64(res1);
      tmp1[(uint32_t)2U * i] = lo;
      tmp1[(uint32_t)2U * i + (uint32_t)1U] = hi;
    }
    uint64_t c = (uint64_t)0U;
    uint32_t k = resLen / (uint32_t)4U * (uint32_t)4U;
    for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
    {
      uint64_t t1 = res[(uint32_t)4U * i];
      uint64_t t20 = tmp1[(uint32_t)4U * i];
      c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t1, t20, res + (uint32_t)4U * i);
      uint64_t t10 = res[(uint32_t)4U * i + (uint32_t)1U];
      uint64_t t21 = tmp1[(uint32_t)4U * i + (uint32_t)1U];
      c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t10, t21, res + (uint32_t)4U * i + (uint32_t)1U);
      uint64_t t11 = res[(uint32_t)4U * i + (uint32_t)2U];
      uint64_t t22 = tmp1[(uint32_t)4U * i + (uint32_t)2U];
      c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t11, t22, res + (uint32_t)4U * i + (uint32_t)2U);
      uint64_t t12 = res[(uint32_t)4U * i + (uint32_t)3U];
      uint64_t t2 = tmp1[(uint32_t)4U * i + (uint32_t)3U];
      c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t12, t2, res + (uint32_t)4U * i + (uint32_t)3U);
    }
    for (uint32_t i = k; i < resLen; i++)
    {
      uint64_t t1 = res[i];
      uint64_t t2 = tmp1[i];
      c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t1, t2, res + i);
    }
    uint64_t uu____23 = c;
    return;
  }
  uint32_t len2 = aLen / (uint32_t)2U;
  uint64_t *a0 = a;
  uint64_t *a1 = a + len2;
  uint64_t *t0 = tmp;
  uint64_t *tmp_ = tmp + aLen;
  uint64_t c0 = (uint64_t)0U;
  uint32_t k0 = len2 / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k0 / (uint32_t)4U; i++)
  {
    uint64_t t1 = a0[(uint32_t)4U * i];
    uint64_t t20 = a1[(uint32_t)4U * i];
    c0 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c0, t1, t20, tmp_ + (uint32_t)4U * i);
    uint64_t t10 = a0[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = a1[(uint32_t)4U * i + (uint32_t)1U];
    c0 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c0,
        t10,
        t21,
        tmp_ + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = a0[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = a1[(uint32_t)4U * i + (uint32_t)2U];
    c0 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c0,
        t11,
        t22,
        tmp_ + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = a0[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = a1[(uint32_t)4U * i + (uint32_t)3U];
    c0 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c0,
        t12,
        t2,
        tmp_ + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k0; i < len2; i++)
  {
    uint64_t t1 = a0[i];
    uint64_t t2 = a1[i];
    c0 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c0, t1, t2, tmp_ + i);
  }
  uint64_t c00 = c0;
  uint64_t c1 = (uint64_t)0U;
  uint32_t k1 = len2 / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k1 / (uint32_t)4U; i++)
  {
    uint64_t t1 = a1[(uint32_t)4U * i];
    uint64_t t20 = a0[(uint32_t)4U * i];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t1, t20, t0 + (uint32_t)4U * i);
    uint64_t t10 = a1[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = a0[(uint32_t)4U * i + (uint32_t)1U];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t10, t21, t0 + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = a1[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = a0[(uint32_t)4U * i + (uint32_t)2U];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t11, t22, t0 + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = a1[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = a0[(uint32_t)4U * i + (uint32_t)3U];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t12, t2, t0 + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k1; i < len2; i++)
  {
    uint64_t t1 = a1[i];
    uint64_t t2 = a0[i];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t1, t2, t0 + i);
  }
  uint64_t c10 = c1;
  for (uint32_t i = (uint32_t)0U; i < len2; i++)
  {
    uint64_t *os = t0;
    uint64_t x = (((uint64_t)0U - c00) & t0[i]) | (~((uint64_t)0U - c00) & tmp_[i]);
    os[i] = x;
  }
  uint64_t c01 = c00;
  uint64_t *t23 = tmp + aLen;
  uint64_t *tmp1 = tmp + aLen + aLen;
  Hacl_Bignum_Karatsuba_bn_karatsuba_sqr_uint64(len2, t0, tmp1, t23);
  uint64_t *r01 = res;
  uint64_t *r23 = res + aLen;
  Hacl_Bignum_Karatsuba_bn_karatsuba_sqr_uint64(len2, a0, tmp1, r01);
  Hacl_Bignum_Karatsuba_bn_karatsuba_sqr_uint64(len2, a1, tmp1, r23);
  uint64_t *r011 = res;
  uint64_t *r231 = res + aLen;
  uint64_t *t01 = tmp;
  uint64_t *t231 = tmp + aLen;
  uint64_t *t45 = tmp + (uint32_t)2U * aLen;
  uint64_t c2 = (uint64_t)0U;
  uint32_t k2 = aLen / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k2 / (uint32_t)4U; i++)
  {
    uint64_t t1 = r011[(uint32_t)4U * i];
    uint64_t t20 = r231[(uint32_t)4U * i];
    c2 = Lib_IntTypes_Intrinsics_add_carry_u64(c2, t1, t20, t01 + (uint32_t)4U * i);
    uint64_t t10 = r011[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = r231[(uint32_t)4U * i + (uint32_t)1U];
    c2 = Lib_IntTypes_Intrinsics_add_carry_u64(c2, t10, t21, t01 + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = r011[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = r231[(uint32_t)4U * i + (uint32_t)2U];
    c2 = Lib_IntTypes_Intrinsics_add_carry_u64(c2, t11, t22, t01 + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = r011[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = r231[(uint32_t)4U * i + (uint32_t)3U];
    c2 = Lib_IntTypes_Intrinsics_add_carry_u64(c2, t12, t2, t01 + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k2; i < aLen; i++)
  {
    uint64_t t1 = r011[i];
    uint64_t t2 = r231[i];
    c2 = Lib_IntTypes_Intrinsics_add_carry_u64(c2, t1, t2, t01 + i);
  }
  uint64_t c20 = c2;
  uint64_t c3 = (uint64_t)0U;
  uint32_t k3 = aLen / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k3 / (uint32_t)4U; i++)
  {
    uint64_t t1 = t01[(uint32_t)4U * i];
    uint64_t t20 = t231[(uint32_t)4U * i];
    c3 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c3, t1, t20, t45 + (uint32_t)4U * i);
    uint64_t t10 = t01[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = t231[(uint32_t)4U * i + (uint32_t)1U];
    c3 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c3,
        t10,
        t21,
        t45 + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = t01[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = t231[(uint32_t)4U * i + (uint32_t)2U];
    c3 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c3,
        t11,
        t22,
        t45 + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = t01[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = t231[(uint32_t)4U * i + (uint32_t)3U];
    c3 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c3, t12, t2, t45 + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k3; i < aLen; i++)
  {
    uint64_t t1 = t01[i];
    uint64_t t2 = t231[i];
    c3 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c3, t1, t2, t45 + i);
  }
  uint64_t c30 = c3;
  uint64_t c5 = c20 - c30;
  uint32_t aLen2 = aLen / (uint32_t)2U;
  uint64_t *r0 = res + aLen2;
  uint64_t c4 = (uint64_t)0U;
  uint32_t k4 = aLen / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k4 / (uint32_t)4U; i++)
  {
    uint64_t t1 = r0[(uint32_t)4U * i];
    uint64_t t20 = t45[(uint32_t)4U * i];
    c4 = Lib_IntTypes_Intrinsics_add_carry_u64(c4, t1, t20, r0 + (uint32_t)4U * i);
    uint64_t t10 = r0[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = t45[(uint32_t)4U * i + (uint32_t)1U];
    c4 = Lib_IntTypes_Intrinsics_add_carry_u64(c4, t10, t21, r0 + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = r0[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = t45[(uint32_t)4U * i + (uint32_t)2U];
    c4 = Lib_IntTypes_Intrinsics_add_carry_u64(c4, t11, t22, r0 + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = r0[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = t45[(uint32_t)4U * i + (uint32_t)3U];
    c4 = Lib_IntTypes_Intrinsics_add_carry_u64(c4, t12, t2, r0 + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k4; i < aLen; i++)
  {
    uint64_t t1 = r0[i];
    uint64_t t2 = t45[i];
    c4 = Lib_IntTypes_Intrinsics_add_carry_u64(c4, t1, t2, r0 + i);
  }
  uint64_t r10 = c4;
  uint64_t c6 = r10;
  uint64_t c7 = c5 + c6;
  uint64_t c71 = c7;
  uint64_t *r = res + aLen + aLen2;
  uint64_t *a01 = r;
  uint64_t *res0 = r;
  uint64_t c8 = (uint64_t)0U;
  uint32_t k5 = (uint32_t)0U;
  for (uint32_t i = (uint32_t)0U; i < k5 / (uint32_t)4U; i++)
  {
    uint64_t t1 = a01[(uint32_t)4U * i];
    uint64_t t20 = (&c71)[(uint32_t)4U * i];
    c8 = Lib_IntTypes_Intrinsics_add_carry_u64(c8, t1, t20, res0 + (uint32_t)4U * i);
    uint64_t t10 = a01[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = (&c71)[(uint32_t)4U * i + (uint32_t)1U];
    c8 =
      Lib_IntTypes_Intrinsics_add_carry_u64(c8,
        t10,
        t21,
        res0 + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = a01[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = (&c71)[(uint32_t)4U * i + (uint32_t)2U];
    c8 =
      Lib_IntTypes_Intrinsics_add_carry_u64(c8,
        t11,
        t22,
        res0 + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = a01[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = (&c71)[(uint32_t)4U * i + (uint32_t)3U];
    c8 = Lib_IntTypes_Intrinsics_add_carry_u64(c8, t12, t2, res0 + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k5; i < (uint32_t)1U; i++)
  {
    uint64_t t1 = a01[i];
    uint64_t t2 = (&c71)[i];
    c8 = Lib_IntTypes_Intrinsics_add_carry_u64(c8, t1, t2, res0 + i);
  }
  uint64_t c010 = c8;
  uint64_t r1;
  if ((uint32_t)1U < aLen + aLen - (aLen + aLen2))
  {
    uint32_t rLen = aLen + aLen - (aLen + aLen2) - (uint32_t)1U;
    uint64_t *a11 = r + (uint32_t)1U;
    uint64_t *res1 = r + (uint32_t)1U;
    uint64_t c = c010;
    uint32_t k = rLen / (uint32_t)4U * (uint32_t)4U;
    for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
    {
      uint64_t t1 = a11[(uint32_t)4U * i];
      c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t1, (uint64_t)0U, res1 + (uint32_t)4U * i);
      uint64_t t10 = a11[(uint32_t)4U * i + (uint32_t)1U];
      c =
        Lib_IntTypes_Intrinsics_add_carry_u64(c,
          t10,
          (uint64_t)0U,
          res1 + (uint32_t)4U * i + (uint32_t)1U);
      uint64_t t11 = a11[(uint32_t)4U * i + (uint32_t)2U];
      c =
        Lib_IntTypes_Intrinsics_add_carry_u64(c,
          t11,
          (uint64_t)0U,
          res1 + (uint32_t)4U * i + (uint32_t)2U);
      uint64_t t12 = a11[(uint32_t)4U * i + (uint32_t)3U];
      c =
        Lib_IntTypes_Intrinsics_add_carry_u64(c,
          t12,
          (uint64_t)0U,
          res1 + (uint32_t)4U * i + (uint32_t)3U);
    }
    for (uint32_t i = k; i < rLen; i++)
    {
      uint64_t t1 = a11[i];
      c = Lib_IntTypes_Intrinsics_add_carry_u64(c, t1, (uint64_t)0U, res1 + i);
    }
    uint64_t c11 = c;
    r1 = c11;
  }
  else
  {
    r1 = c010;
  }
  uint64_t c80 = r1;
  uint64_t c = c80;
  uint64_t c9 = c;
}

/* SNIPPET_END: Hacl_Bignum_Karatsuba_bn_karatsuba_sqr_uint64 */

/* SNIPPET_START: Hacl_Bignum_bn_add_mod_n_u64 */

static inline void
Hacl_Bignum_bn_add_mod_n_u64(
  uint32_t len1,
  uint64_t *n,
  uint64_t *a,
  uint64_t *b,
  uint64_t *res
)
{
  uint64_t c0 = (uint64_t)0U;
  uint32_t k0 = len1 / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k0 / (uint32_t)4U; i++)
  {
    uint64_t t1 = a[(uint32_t)4U * i];
    uint64_t t20 = b[(uint32_t)4U * i];
    c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t1, t20, res + (uint32_t)4U * i);
    uint64_t t10 = a[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = b[(uint32_t)4U * i + (uint32_t)1U];
    c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t10, t21, res + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = a[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = b[(uint32_t)4U * i + (uint32_t)2U];
    c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t11, t22, res + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = a[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = b[(uint32_t)4U * i + (uint32_t)3U];
    c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t12, t2, res + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k0; i < len1; i++)
  {
    uint64_t t1 = a[i];
    uint64_t t2 = b[i];
    c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, t1, t2, res + i);
  }
  uint64_t c00 = c0;
  KRML_CHECK_SIZE(sizeof (uint64_t), len1);
  uint64_t tmp[len1];
  memset(tmp, 0U, len1 * sizeof (uint64_t));
  uint64_t c = (uint64_t)0U;
  uint32_t k = len1 / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
  {
    uint64_t t1 = res[(uint32_t)4U * i];
    uint64_t t20 = n[(uint32_t)4U * i];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t1, t20, tmp + (uint32_t)4U * i);
    uint64_t t10 = res[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = n[(uint32_t)4U * i + (uint32_t)1U];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t10, t21, tmp + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = res[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = n[(uint32_t)4U * i + (uint32_t)2U];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t11, t22, tmp + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = res[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = n[(uint32_t)4U * i + (uint32_t)3U];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t12, t2, tmp + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k; i < len1; i++)
  {
    uint64_t t1 = res[i];
    uint64_t t2 = n[i];
    c = Lib_IntTypes_Intrinsics_sub_borrow_u64(c, t1, t2, tmp + i);
  }
  uint64_t c1 = c;
  uint64_t c2 = c00 - c1;
  for (uint32_t i = (uint32_t)0U; i < len1; i++)
  {
    uint64_t *os = res;
    uint64_t x = (c2 & res[i]) | (~c2 & tmp[i]);
    os[i] = x;
  }
}

/* SNIPPET_END: Hacl_Bignum_bn_add_mod_n_u64 */

/* SNIPPET_START: Hacl_Bignum_ModInvLimb_mod_inv_uint64 */

static inline uint64_t Hacl_Bignum_ModInvLimb_mod_inv_uint64(uint64_t n0)
{
  uint64_t alpha = (uint64_t)9223372036854775808U;
  uint64_t beta = n0;
  uint64_t ub = (uint64_t)0U;
  uint64_t vb = (uint64_t)0U;
  ub = (uint64_t)1U;
  vb = (uint64_t)0U;
  for (uint32_t i = (uint32_t)0U; i < (uint32_t)64U; i++)
  {
    uint64_t us = ub;
    uint64_t vs = vb;
    uint64_t u_is_odd = (uint64_t)0U - (us & (uint64_t)1U);
    uint64_t beta_if_u_is_odd = beta & u_is_odd;
    ub = ((us ^ beta_if_u_is_odd) >> (uint32_t)1U) + (us & beta_if_u_is_odd);
    uint64_t alpha_if_u_is_odd = alpha & u_is_odd;
    vb = (vs >> (uint32_t)1U) + alpha_if_u_is_odd;
  }
  return vb;
}

/* SNIPPET_END: Hacl_Bignum_ModInvLimb_mod_inv_uint64 */

/* SNIPPET_START: Hacl_Bignum_Montgomery_bn_precomp_r2_mod_n_u64 */

static inline void
Hacl_Bignum_Montgomery_bn_precomp_r2_mod_n_u64(
  uint32_t len,
  uint32_t nBits,
  uint64_t *n,
  uint64_t *res
)
{
  memset(res, 0U, len * sizeof (uint64_t));
  uint32_t i = nBits / (uint32_t)64U;
  uint32_t j = nBits % (uint32_t)64U;
  res[i] = res[i] | (uint64_t)1U << j;
  for (uint32_t i0 = (uint32_t)0U; i0 < (uint32_t)128U * len - nBits; i0++)
  {
    Hacl_Bignum_bn_add_mod_n_u64(len, n, res, res, res);
  }
}

/* SNIPPET_END: Hacl_Bignum_Montgomery_bn_precomp_r2_mod_n_u64 */

/* SNIPPET_START: Hacl_Bignum_Montgomery_bn_mont_reduction_u64 */

static inline void
Hacl_Bignum_Montgomery_bn_mont_reduction_u64(
  uint32_t len,
  uint64_t *n,
  uint64_t nInv,
  uint64_t *c,
  uint64_t *res
)
{
  uint64_t c0 = (uint64_t)0U;
  for (uint32_t i0 = (uint32_t)0U; i0 < len; i0++)
  {
    uint64_t qj = nInv * c[i0];
    uint64_t *res_ = c + i0;
    uint64_t c1 = (uint64_t)0U;
    uint32_t k = len / (uint32_t)4U * (uint32_t)4U;
    for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
    {
      uint64_t uu____0 = n[(uint32_t)4U * i];
      uint64_t uu____1 = c1;
      uint64_t *uu____2 = res_ + (uint32_t)4U * i;
      FStar_UInt128_uint128 uu____3 = FStar_UInt128_uint64_to_uint128(uu____2[0U]);
      FStar_UInt128_uint128
      res1 =
        FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____0, qj),
            FStar_UInt128_uint64_to_uint128(uu____1)),
          uu____3);
      uu____2[0U] = FStar_UInt128_uint128_to_uint64(res1);
      c1 = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res1, (uint32_t)64U));
      uint64_t uu____4 = n[(uint32_t)4U * i + (uint32_t)1U];
      uint64_t uu____5 = c1;
      uint64_t *uu____6 = res_ + (uint32_t)4U * i + (uint32_t)1U;
      FStar_UInt128_uint128 uu____7 = FStar_UInt128_uint64_to_uint128(uu____6[0U]);
      FStar_UInt128_uint128
      res10 =
        FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____4, qj),
            FStar_UInt128_uint64_to_uint128(uu____5)),
          uu____7);
      uu____6[0U] = FStar_UInt128_uint128_to_uint64(res10);
      c1 = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res10, (uint32_t)64U));
      uint64_t uu____8 = n[(uint32_t)4U * i + (uint32_t)2U];
      uint64_t uu____9 = c1;
      uint64_t *uu____10 = res_ + (uint32_t)4U * i + (uint32_t)2U;
      FStar_UInt128_uint128 uu____11 = FStar_UInt128_uint64_to_uint128(uu____10[0U]);
      FStar_UInt128_uint128
      res11 =
        FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____8, qj),
            FStar_UInt128_uint64_to_uint128(uu____9)),
          uu____11);
      uu____10[0U] = FStar_UInt128_uint128_to_uint64(res11);
      c1 = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res11, (uint32_t)64U));
      uint64_t uu____12 = n[(uint32_t)4U * i + (uint32_t)3U];
      uint64_t uu____13 = c1;
      uint64_t *uu____14 = res_ + (uint32_t)4U * i + (uint32_t)3U;
      FStar_UInt128_uint128 uu____15 = FStar_UInt128_uint64_to_uint128(uu____14[0U]);
      FStar_UInt128_uint128
      res12 =
        FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____12, qj),
            FStar_UInt128_uint64_to_uint128(uu____13)),
          uu____15);
      uu____14[0U] = FStar_UInt128_uint128_to_uint64(res12);
      c1 = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res12, (uint32_t)64U));
    }
    for (uint32_t i = k; i < len; i++)
    {
      uint64_t uu____16 = n[i];
      uint64_t uu____17 = c1;
      uint64_t *uu____18 = res_ + i;
      FStar_UInt128_uint128 uu____19 = FStar_UInt128_uint64_to_uint128(uu____18[0U]);
      FStar_UInt128_uint128
      res1 =
        FStar_UInt128_add(FStar_UInt128_add(FStar_UInt128_mul_wide(uu____16, qj),
            FStar_UInt128_uint64_to_uint128(uu____17)),
          uu____19);
      uu____18[0U] = FStar_UInt128_uint128_to_uint64(res1);
      c1 = FStar_UInt128_uint128_to_uint64(FStar_UInt128_shift_right(res1, (uint32_t)64U));
    }
    uint64_t r = c1;
    uint64_t c10 = r;
    c0 = Lib_IntTypes_Intrinsics_add_carry_u64(c0, c10, c[len + i0], c + len + i0);
  }
  memcpy(res, c + len, (len + len - len) * sizeof (uint64_t));
  uint64_t uu____20 = c0;
  KRML_CHECK_SIZE(sizeof (uint64_t), len);
  uint64_t tmp[len];
  memset(tmp, 0U, len * sizeof (uint64_t));
  uint64_t c1 = (uint64_t)0U;
  uint32_t k = len / (uint32_t)4U * (uint32_t)4U;
  for (uint32_t i = (uint32_t)0U; i < k / (uint32_t)4U; i++)
  {
    uint64_t t1 = res[(uint32_t)4U * i];
    uint64_t t20 = n[(uint32_t)4U * i];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t1, t20, tmp + (uint32_t)4U * i);
    uint64_t t10 = res[(uint32_t)4U * i + (uint32_t)1U];
    uint64_t t21 = n[(uint32_t)4U * i + (uint32_t)1U];
    c1 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c1,
        t10,
        t21,
        tmp + (uint32_t)4U * i + (uint32_t)1U);
    uint64_t t11 = res[(uint32_t)4U * i + (uint32_t)2U];
    uint64_t t22 = n[(uint32_t)4U * i + (uint32_t)2U];
    c1 =
      Lib_IntTypes_Intrinsics_sub_borrow_u64(c1,
        t11,
        t22,
        tmp + (uint32_t)4U * i + (uint32_t)2U);
    uint64_t t12 = res[(uint32_t)4U * i + (uint32_t)3U];
    uint64_t t2 = n[(uint32_t)4U * i + (uint32_t)3U];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t12, t2, tmp + (uint32_t)4U * i + (uint32_t)3U);
  }
  for (uint32_t i = k; i < len; i++)
  {
    uint64_t t1 = res[i];
    uint64_t t2 = n[i];
    c1 = Lib_IntTypes_Intrinsics_sub_borrow_u64(c1, t1, t2, tmp + i);
  }
  uint64_t c10 = c1;
  uint64_t c2 = uu____20 - c10;
  for (uint32_t i = (uint32_t)0U; i < len; i++)
  {
    uint64_t *os = res;
    uint64_t x = (c2 & res[i]) | (~c2 & tmp[i]);
    os[i] = x;
  }
}

/* SNIPPET_END: Hacl_Bignum_Montgomery_bn_mont_reduction_u64 */

/* SNIPPET_START: Hacl_Bignum_Exponentiation_bn_mod_exp_precompr2_u64 */

static inline void
Hacl_Bignum_Exponentiation_bn_mod_exp_precompr2_u64(
  uint32_t len,
  uint64_t *n,
  uint64_t *a,
  uint32_t bBits,
  uint64_t *b,
  uint64_t *r2,
  uint64_t *res
)
{
  KRML_CHECK_SIZE(sizeof (uint64_t), len);
  uint64_t acc[len];
  memset(acc, 0U, len * sizeof (uint64_t));
  memset(acc, 0U, len * sizeof (uint64_t));
  acc[0U] = (uint64_t)1U;
  uint64_t nInv = Hacl_Bignum_ModInvLimb_mod_inv_uint64(n[0U]);
  KRML_CHECK_SIZE(sizeof (uint64_t), len);
  uint64_t aM[len];
  memset(aM, 0U, len * sizeof (uint64_t));
  KRML_CHECK_SIZE(sizeof (uint64_t), len);
  uint64_t accM[len];
  memset(accM, 0U, len * sizeof (uint64_t));
  KRML_CHECK_SIZE(sizeof (uint64_t), len + len);
  uint64_t c[len + len];
  memset(c, 0U, (len + len) * sizeof (uint64_t));
  KRML_CHECK_SIZE(sizeof (uint64_t), (uint32_t)4U * len);
  uint64_t tmp0[(uint32_t)4U * len];
  memset(tmp0, 0U, (uint32_t)4U * len * sizeof (uint64_t));
  Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(len, a, r2, tmp0, c);
  Hacl_Bignum_Montgomery_bn_mont_reduction_u64(len, n, nInv, c, aM);
  KRML_CHECK_SIZE(sizeof (uint64_t), len + len);
  uint64_t c0[len + len];
  memset(c0, 0U, (len + len) * sizeof (uint64_t));
  KRML_CHECK_SIZE(sizeof (uint64_t), (uint32_t)4U * len);
  uint64_t tmp1[(uint32_t)4U * len];
  memset(tmp1, 0U, (uint32_t)4U * len * sizeof (uint64_t));
  Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(len, acc, r2, tmp1, c0);
  Hacl_Bignum_Montgomery_bn_mont_reduction_u64(len, n, nInv, c0, accM);
  for (uint32_t i = (uint32_t)0U; i < bBits; i++)
  {
    uint32_t i1 = i / (uint32_t)64U;
    uint32_t j = i % (uint32_t)64U;
    uint64_t tmp2 = b[i1];
    uint64_t get_bit = tmp2 >> j & (uint64_t)1U;
    if (!(get_bit == (uint64_t)0U))
    {
      KRML_CHECK_SIZE(sizeof (uint64_t), len + len);
      uint64_t c1[len + len];
      memset(c1, 0U, (len + len) * sizeof (uint64_t));
      KRML_CHECK_SIZE(sizeof (uint64_t), (uint32_t)4U * len);
      uint64_t tmp[(uint32_t)4U * len];
      memset(tmp, 0U, (uint32_t)4U * len * sizeof (uint64_t));
      Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(len, aM, accM, tmp, c1);
      Hacl_Bignum_Montgomery_bn_mont_reduction_u64(len, n, nInv, c1, accM);
    }
    KRML_CHECK_SIZE(sizeof (uint64_t), len + len);
    uint64_t c1[len + len];
    memset(c1, 0U, (len + len) * sizeof (uint64_t));
    KRML_CHECK_SIZE(sizeof (uint64_t), (uint32_t)4U * len);
    uint64_t tmp[(uint32_t)4U * len];
    memset(tmp, 0U, (uint32_t)4U * len * sizeof (uint64_t));
    Hacl_Bignum_Karatsuba_bn_karatsuba_sqr_uint64(len, aM, tmp, c1);
    Hacl_Bignum_Montgomery_bn_mont_reduction_u64(len, n, nInv, c1, aM);
  }
  KRML_CHECK_SIZE(sizeof (uint64_t), len + len);
  uint64_t tmp[len + len];
  memset(tmp, 0U, (len + len) * sizeof (uint64_t));
  memcpy(tmp, accM, len * sizeof (uint64_t));
  Hacl_Bignum_Montgomery_bn_mont_reduction_u64(len, n, nInv, tmp, res);
}

/* SNIPPET_END: Hacl_Bignum_Exponentiation_bn_mod_exp_precompr2_u64 */

/* SNIPPET_START: Hacl_Bignum_Exponentiation_bn_mod_exp_mont_ladder_precompr2_u64 */

static inline void
Hacl_Bignum_Exponentiation_bn_mod_exp_mont_ladder_precompr2_u64(
  uint32_t len,
  uint64_t *n,
  uint64_t *a,
  uint32_t bBits,
  uint64_t *b,
  uint64_t *r2,
  uint64_t *res
)
{
  KRML_CHECK_SIZE(sizeof (uint64_t), len);
  uint64_t one[len];
  memset(one, 0U, len * sizeof (uint64_t));
  memset(one, 0U, len * sizeof (uint64_t));
  one[0U] = (uint64_t)1U;
  uint64_t nInv = Hacl_Bignum_ModInvLimb_mod_inv_uint64(n[0U]);
  KRML_CHECK_SIZE(sizeof (uint64_t), len);
  uint64_t rM0[len];
  memset(rM0, 0U, len * sizeof (uint64_t));
  KRML_CHECK_SIZE(sizeof (uint64_t), len);
  uint64_t rM1[len];
  memset(rM1, 0U, len * sizeof (uint64_t));
  uint64_t sw = (uint64_t)0U;
  KRML_CHECK_SIZE(sizeof (uint64_t), len + len);
  uint64_t c[len + len];
  memset(c, 0U, (len + len) * sizeof (uint64_t));
  KRML_CHECK_SIZE(sizeof (uint64_t), (uint32_t)4U * len);
  uint64_t tmp0[(uint32_t)4U * len];
  memset(tmp0, 0U, (uint32_t)4U * len * sizeof (uint64_t));
  Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(len, one, r2, tmp0, c);
  Hacl_Bignum_Montgomery_bn_mont_reduction_u64(len, n, nInv, c, rM0);
  KRML_CHECK_SIZE(sizeof (uint64_t), len + len);
  uint64_t c0[len + len];
  memset(c0, 0U, (len + len) * sizeof (uint64_t));
  KRML_CHECK_SIZE(sizeof (uint64_t), (uint32_t)4U * len);
  uint64_t tmp1[(uint32_t)4U * len];
  memset(tmp1, 0U, (uint32_t)4U * len * sizeof (uint64_t));
  Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(len, a, r2, tmp1, c0);
  Hacl_Bignum_Montgomery_bn_mont_reduction_u64(len, n, nInv, c0, rM1);
  for (uint32_t i0 = (uint32_t)0U; i0 < bBits; i0++)
  {
    uint32_t i1 = (bBits - i0 - (uint32_t)1U) / (uint32_t)64U;
    uint32_t j = (bBits - i0 - (uint32_t)1U) % (uint32_t)64U;
    uint64_t tmp2 = b[i1];
    uint64_t bit = tmp2 >> j & (uint64_t)1U;
    uint64_t sw1 = bit ^ sw;
    for (uint32_t i = (uint32_t)0U; i < len; i++)
    {
      uint64_t dummy = ((uint64_t)0U - sw1) & (rM0[i] ^ rM1[i]);
      rM0[i] = rM0[i] ^ dummy;
      rM1[i] = rM1[i] ^ dummy;
    }
    KRML_CHECK_SIZE(sizeof (uint64_t), len + len);
    uint64_t c1[len + len];
    memset(c1, 0U, (len + len) * sizeof (uint64_t));
    KRML_CHECK_SIZE(sizeof (uint64_t), (uint32_t)4U * len);
    uint64_t tmp3[(uint32_t)4U * len];
    memset(tmp3, 0U, (uint32_t)4U * len * sizeof (uint64_t));
    Hacl_Bignum_Karatsuba_bn_karatsuba_mul_uint64(len, rM1, rM0, tmp3, c1);
    Hacl_Bignum_Montgomery_bn_mont_reduction_u64(len, n, nInv, c1, rM1);
    KRML_CHECK_SIZE(sizeof (uint64_t), len + len);
    uint64_t c2[len + len];
    memset(c2, 0U, (len + len) * sizeof (uint64_t));
    KRML_CHECK_SIZE(sizeof (uint64_t), (uint32_t)4U * len);
    uint64_t tmp[(uint32_t)4U * len];
    memset(tmp, 0U, (uint32_t)4U * len * sizeof (uint64_t));
    Hacl_Bignum_Karatsuba_bn_karatsuba_sqr_uint64(len, rM0, tmp, c2);
    Hacl_Bignum_Montgomery_bn_mont_reduction_u64(len, n, nInv, c2, rM0);
    sw = bit;
  }
  uint64_t uu____0 = sw;
  for (uint32_t i = (uint32_t)0U; i < len; i++)
  {
    uint64_t dummy = ((uint64_t)0U - uu____0) & (rM0[i] ^ rM1[i]);
    rM0[i] = rM0[i] ^ dummy;
    rM1[i] = rM1[i] ^ dummy;
  }
  KRML_CHECK_SIZE(sizeof (uint64_t), len + len);
  uint64_t tmp[len + len];
  memset(tmp, 0U, (len + len) * sizeof (uint64_t));
  memcpy(tmp, rM0, len * sizeof (uint64_t));
  Hacl_Bignum_Montgomery_bn_mont_reduction_u64(len, n, nInv, tmp, res);
}

/* SNIPPET_END: Hacl_Bignum_Exponentiation_bn_mod_exp_mont_ladder_precompr2_u64 */

#if defined(__cplusplus)
}
#endif

#define __Hacl_Bignum_H_DEFINED
#endif
