module Hacl.Streaming.Lemmas

module S = FStar.Seq

open Spec.UpdateMulti
open FStar.Mul

let uint8 = Lib.IntTypes.uint8

#set-options "--fuel 0 --ifuel 0"
let update_full #a
  (block_length:pos)
  (update: a -> (s:S.seq uint8 { S.length s = block_length }) -> a)
  (update_last: a -> (s:S.seq uint8 { S.length s < block_length }) -> a)
  (acc: a)
  (input: S.seq uint8)
=
  let n_blocks = S.length input / block_length in
  let blocks, rest = S.split input (n_blocks * block_length) in
  assert (S.length rest = S.length input % block_length);
  Math.Lemmas.multiple_modulo_lemma n_blocks block_length;
  assert (S.length blocks % block_length = 0);
  assert (S.length rest < block_length);
  update_last (mk_update_multi block_length update acc blocks) rest

#set-options "--max_fuel 0 --max_ifuel 0"
val update_multi_is_repeat_blocks:
  #a:Type0 ->
  block_length:pos { block_length < pow2 32 } ->
  update: (a -> s:S.seq uint8 { S.length s = block_length } -> a) ->
  update_last: (a -> s:S.seq uint8 { S.length s < block_length } -> a) ->
  acc:a ->
  input:S.seq uint8 ->
  Lemma
    (ensures (
      let repeat_f = fun (input: S.seq uint8 { S.length input = block_length }) (acc: a) -> update acc input in
      let repeat_l = fun (l: Lib.IntTypes.size_nat { l == S.length input % block_length })
        (s: Lib.Sequence.lseq uint8 l) (acc: a) ->
        update_last acc s
      in

      Lib.Sequence.repeat_blocks #uint8 block_length input repeat_f repeat_l acc ==
      update_full block_length update update_last acc input))
    (decreases (S.length input))
