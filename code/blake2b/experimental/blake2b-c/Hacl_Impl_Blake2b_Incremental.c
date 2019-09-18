/* 
  This file was generated by KreMLin <https://github.com/FStarLang/kremlin>
  KreMLin invocation: /opt/kremlin/krml -skip-compilation -no-prefix Hacl.Test.Blake2b.Incremental -no-prefix Hacl.Blake2b -bundle Lib.* -bundle Spec.* -bundle C=C.Endianness -library C,FStar -drop LowStar,Spec,Prims,Lib,C.Loops.*,C -add-include "c/Lib_PrintBuffer.h" -tmpdir blake2b-c .output/prims.krml .output/FStar_Pervasives_Native.krml .output/FStar_Pervasives.krml .output/FStar_Preorder.krml .output/FStar_Calc.krml .output/FStar_Squash.krml .output/FStar_Classical.krml .output/FStar_StrongExcludedMiddle.krml .output/FStar_FunctionalExtensionality.krml .output/FStar_List_Tot_Base.krml .output/FStar_List_Tot_Properties.krml .output/FStar_List_Tot.krml .output/FStar_Seq_Base.krml .output/FStar_Seq_Properties.krml .output/FStar_Seq.krml .output/FStar_Mul.krml .output/FStar_Math_Lib.krml .output/FStar_Math_Lemmas.krml .output/FStar_BitVector.krml .output/FStar_UInt.krml .output/FStar_UInt32.krml .output/FStar_Int.krml .output/FStar_Int16.krml .output/FStar_Reflection_Types.krml .output/FStar_Reflection_Data.krml .output/FStar_Order.krml .output/FStar_Reflection_Basic.krml .output/FStar_Ghost.krml .output/FStar_ErasedLogic.krml .output/FStar_UInt64.krml .output/FStar_Exn.krml .output/FStar_Set.krml .output/FStar_Monotonic_Witnessed.krml .output/FStar_PropositionalExtensionality.krml .output/FStar_PredicateExtensionality.krml .output/FStar_TSet.krml .output/FStar_Monotonic_Heap.krml .output/FStar_Heap.krml .output/FStar_ST.krml .output/FStar_All.krml .output/Lib_LoopCombinators.krml .output/FStar_UInt8.krml .output/FStar_Int64.krml .output/FStar_Int63.krml .output/FStar_Int32.krml .output/FStar_Int8.krml .output/FStar_UInt63.krml .output/FStar_UInt16.krml .output/FStar_Int_Cast.krml .output/FStar_UInt128.krml .output/FStar_Int_Cast_Full.krml .output/FStar_Int128.krml .output/Lib_IntTypes.krml .output/Lib_RawIntTypes.krml .output/Lib_Sequence.krml .output/Lib_ByteSequence.krml .output/Spec_Blake2.krml .output/Spec_Blake2_Incremental.krml .output/FStar_Map.krml .output/FStar_Monotonic_HyperHeap.krml .output/FStar_Monotonic_HyperStack.krml .output/FStar_HyperStack.krml .output/FStar_HyperStack_ST.krml .output/FStar_Universe.krml .output/FStar_GSet.krml .output/FStar_ModifiesGen.krml .output/FStar_Range.krml .output/FStar_Tactics_Types.krml .output/FStar_Tactics_Result.krml .output/FStar_Tactics_Effect.krml .output/FStar_Tactics_Util.krml .output/FStar_Reflection_Const.krml .output/FStar_Char.krml .output/FStar_List.krml .output/FStar_String.krml .output/FStar_Reflection_Derived.krml .output/FStar_Tactics_Builtins.krml .output/FStar_Reflection_Formula.krml .output/FStar_Reflection_Derived_Lemmas.krml .output/FStar_Reflection.krml .output/FStar_Tactics_Derived.krml .output/FStar_Tactics_Logic.krml .output/FStar_Tactics.krml .output/FStar_BigOps.krml .output/LowStar_Monotonic_Buffer.krml .output/LowStar_Buffer.krml .output/LowStar_BufferOps.krml .output/FStar_HyperStack_All.krml .output/FStar_Kremlin_Endianness.krml .output/C_Endianness.krml .output/C.krml .output/Spec_Loops.krml .output/C_Loops.krml .output/Lib_Loops.krml .output/LowStar_ImmutableBuffer.krml .output/Lib_Buffer.krml .output/Lib_ByteBuffer.krml .output/Hacl_Impl_Blake2b.krml .output/Hacl_Impl_Blake2b_Incremental.krml .output/Lib_PrintBuffer.krml .output/LowStar_Modifies.krml .output/C_String.krml .output/Hacl_Blake2b.krml .output/Hacl_Test_Blake2b_Incremental.krml
  F* version: 8d4580e6
  KreMLin version: fec2dd6f
 */

#include "Hacl_Impl_Blake2b_Incremental.h"

uint64_t
*Hacl_Impl_Blake2b_Incremental___proj__Mkstate_r__item__hash(
  Hacl_Impl_Blake2b_Incremental_state_r projectee
)
{
  return projectee.hash;
}

uint32_t
*Hacl_Impl_Blake2b_Incremental___proj__Mkstate_r__item__n(
  Hacl_Impl_Blake2b_Incremental_state_r projectee
)
{
  return projectee.n;
}

uint32_t
*Hacl_Impl_Blake2b_Incremental___proj__Mkstate_r__item__pl(
  Hacl_Impl_Blake2b_Incremental_state_r projectee
)
{
  return projectee.pl;
}

uint8_t
*Hacl_Impl_Blake2b_Incremental___proj__Mkstate_r__item__block(
  Hacl_Impl_Blake2b_Incremental_state_r projectee
)
{
  return projectee.block;
}

void
Hacl_Impl_Blake2b_Incremental_blake2b_incremental_init(
  Hacl_Impl_Blake2b_Incremental_state_r state,
  uint32_t kk,
  uint8_t *k,
  uint32_t nn
)
{
  KRML_CHECK_SIZE(sizeof (uint8_t), (uint32_t)16U * (uint32_t)8U);
  uint8_t b[(uint32_t)16U * (uint32_t)8U];
  memset(b, 0U, (uint32_t)16U * (uint32_t)8U * sizeof b[0U]);
  for (uint32_t i = (uint32_t)0U; i < (uint32_t)8U; i = i + (uint32_t)1U)
  {
    uint64_t *os = state.hash;
    uint64_t x = Hacl_Impl_Blake2b_const_iv[i];
    os[i] = x;
  }
  uint64_t s0 = state.hash[0U];
  uint64_t kk_shift_8 = (uint64_t)kk << (uint32_t)8U;
  uint64_t s0_ = s0 ^ (uint64_t)0x01010000U ^ kk_shift_8 ^ (uint64_t)nn;
  state.hash[0U] = s0_;
  if (!(kk == (uint32_t)0U))
  {
    memcpy(b, k, kk * sizeof k[0U]);
    uint64_t prev64 = (uint64_t)((uint32_t)16U * (uint32_t)8U);
    Hacl_Impl_Blake2b_blake2b_update_block(state.hash, FStar_UInt128_uint64_to_uint128(prev64), b);
  }
  memset(b, 0U, (uint32_t)16U * (uint32_t)8U * sizeof b[0U]);
  uint32_t n1;
  if (kk == (uint32_t)0U)
    n1 = (uint32_t)0U;
  else
    n1 = (uint32_t)1U;
  state.n[0U] = n1;
}

bool
Hacl_Impl_Blake2b_Incremental_blake2b_incremental_update(
  Hacl_Impl_Blake2b_Incremental_state_r state,
  uint32_t ll,
  uint8_t *input
)
{
  uint32_t nll = ll / ((uint32_t)16U * (uint32_t)8U);
  uint32_t n1 = state.n[0U];
  if (ll == (uint32_t)0U || !(n1 + nll + (uint32_t)2U <= (uint32_t)4294967295U))
    return false;
  else
  {
    uint32_t pl = state.pl[0U];
    uint32_t rb = (uint32_t)16U * (uint32_t)8U - pl;
    uint32_t ll0;
    if (ll < rb)
      ll0 = ll;
    else
      ll0 = rb;
    uint8_t *partial = input;
    memcpy(state.block + pl, partial, ll0 * sizeof partial[0U]);
    uint32_t pl1 = state.pl[0U];
    if (ll <= rb)
      state.pl[0U] = pl1 + ll0;
    else
    {
      uint32_t n1 = state.n[0U];
      uint64_t n640 = (uint64_t)n1;
      uint64_t size_block640 = (uint64_t)((uint32_t)16U * (uint32_t)8U);
      uint64_t prev64 = (n640 + (uint64_t)1U) * size_block640;
      FStar_UInt128_uint128 tlen = FStar_UInt128_uint64_to_uint128(prev64);
      Hacl_Impl_Blake2b_blake2b_update_block(state.hash, tlen, state.block);
      state.n[0U] = n1 + (uint32_t)1U;
      state.pl[0U] = (uint32_t)0U;
      uint32_t n10 = state.n[0U];
      uint32_t n11 = (ll - ll0) / ((uint32_t)16U * (uint32_t)8U);
      uint8_t *input1 = input + ll0;
      for (uint32_t i = (uint32_t)0U; i < n11; i = i + (uint32_t)1U)
      {
        uint8_t *block = input1 + i * (uint32_t)16U * (uint32_t)8U;
        uint64_t n64 = (uint64_t)state.n[0U];
        uint64_t i641 = (uint64_t)i;
        uint64_t size_block64 = (uint64_t)((uint32_t)16U * (uint32_t)8U);
        FStar_UInt128_uint128
        prev = FStar_UInt128_uint64_to_uint128(n64 * size_block64 + i641 * size_block64);
        Hacl_Impl_Blake2b_blake2b_update_block(state.hash, prev, block);
      }
      state.n[0U] = n10 + n11;
      uint32_t ll2 = (ll - ll0) % ((uint32_t)16U * (uint32_t)8U);
      uint8_t *input2 = input + ll - ll2;
      memcpy(state.block, input2, ll2 * sizeof input2[0U]);
      state.pl[0U] = ll2;
    }
    return true;
  }
}

void
Hacl_Impl_Blake2b_Incremental_blake2b_incremental_finish(
  uint32_t nn,
  uint8_t *output,
  Hacl_Impl_Blake2b_Incremental_state_r state
)
{
  uint32_t pl = state.pl[0U];
  uint8_t *last1 = state.block;
  uint32_t n1 = state.n[0U];
  uint64_t n64 = (uint64_t)n1;
  uint64_t size_block64 = (uint64_t)((uint32_t)16U * (uint32_t)8U);
  uint64_t pl64 = (uint64_t)pl;
  FStar_UInt128_uint128 prev = FStar_UInt128_uint64_to_uint128(n64 * size_block64 + pl64);
  Hacl_Impl_Blake2b_blake2b_update_last(state.hash, prev, pl, last1);
  Hacl_Impl_Blake2b_blake2b_finish(nn, output, state.hash);
}

