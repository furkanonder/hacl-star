module Spec.Box.Test

open FStar.Mul
open Lib.IntTypes
open Lib.RawIntTypes
open Lib.Sequence
open Lib.ByteSequence

open Spec.Box

#set-options "--z3rlimit 50 --fuel 0 --ifuel 0"

let plain : lbytes 72 =
  let l = List.Tot.map u8_from_UInt8 [
    0x00uy; 0x01uy; 0x02uy; 0x03uy; 0x04uy; 0x05uy; 0x06uy; 0x07uy;
    0x08uy; 0x09uy; 0x10uy; 0x11uy; 0x12uy; 0x13uy; 0x14uy; 0x15uy;
    0x16uy; 0x17uy; 0x18uy; 0x19uy; 0x20uy; 0x21uy; 0x22uy; 0x23uy;
    0x00uy; 0x01uy; 0x02uy; 0x03uy; 0x04uy; 0x05uy; 0x06uy; 0x07uy;
    0x08uy; 0x09uy; 0x10uy; 0x11uy; 0x12uy; 0x13uy; 0x14uy; 0x15uy;
    0x16uy; 0x17uy; 0x18uy; 0x19uy; 0x20uy; 0x21uy; 0x22uy; 0x23uy;
    0x00uy; 0x01uy; 0x02uy; 0x03uy; 0x04uy; 0x05uy; 0x06uy; 0x07uy;
    0x08uy; 0x09uy; 0x10uy; 0x11uy; 0x12uy; 0x13uy; 0x14uy; 0x15uy;
    0x16uy; 0x17uy; 0x18uy; 0x19uy; 0x20uy; 0x21uy; 0x22uy; 0x23uy
  ] in
  assert_norm (List.Tot.length l == 72);
  of_list l


let nonce : lbytes 24 =
  let l = List.Tot.map u8_from_UInt8 [
    0x00uy; 0x01uy; 0x02uy; 0x03uy; 0x04uy; 0x05uy; 0x06uy; 0x07uy;
    0x08uy; 0x09uy; 0x10uy; 0x11uy; 0x12uy; 0x13uy; 0x14uy; 0x15uy;
    0x16uy; 0x17uy; 0x18uy; 0x19uy; 0x20uy; 0x21uy; 0x22uy; 0x23uy
  ] in
  assert_norm (List.Tot.length l == 24);
  of_list l


let key : lbytes 32 =
  let l = List.Tot.map u8_from_UInt8 [
    0x85uy; 0xd6uy; 0xbeuy; 0x78uy; 0x57uy; 0x55uy; 0x6duy; 0x33uy;
    0x7fuy; 0x44uy; 0x52uy; 0xfeuy; 0x42uy; 0xd5uy; 0x06uy; 0xa8uy;
    0x01uy; 0x03uy; 0x80uy; 0x8auy; 0xfbuy; 0x0duy; 0xb2uy; 0xfduy;
    0x4auy; 0xbfuy; 0xf6uy; 0xafuy; 0x41uy; 0x49uy; 0xf5uy; 0x1buy
  ] in
  assert_norm (List.Tot.length l == 32);
  of_list l


let sk1 : lbytes 32 =
  let l = List.Tot.map u8_from_UInt8 [
    0x85uy; 0xd6uy; 0xbeuy; 0x78uy; 0x57uy; 0x55uy; 0x6duy; 0x33uy;
    0x7fuy; 0x44uy; 0x52uy; 0xfeuy; 0x42uy; 0xd5uy; 0x06uy; 0xa8uy;
    0x01uy; 0x03uy; 0x80uy; 0x8auy; 0xfbuy; 0x0duy; 0xb2uy; 0xfduy;
    0x4auy; 0xbfuy; 0xf6uy; 0xafuy; 0x41uy; 0x49uy; 0xf5uy; 0x1buy
  ] in
  assert_norm (List.Tot.length l == 32);
  of_list l


let sk2 : lbytes 32 =
  let l = List.Tot.map u8_from_UInt8 [
    0x85uy; 0xd6uy; 0xbeuy; 0x78uy; 0x57uy; 0x55uy; 0x6duy; 0x33uy;
    0x7fuy; 0x44uy; 0x52uy; 0xfeuy; 0x42uy; 0xd5uy; 0x06uy; 0xa8uy;
    0x01uy; 0x03uy; 0x80uy; 0x8auy; 0xfbuy; 0x0duy; 0xb2uy; 0xfduy;
    0x4auy; 0xbfuy; 0xf6uy; 0xafuy; 0x41uy; 0x49uy; 0xf5uy; 0x1cuy
  ] in
  assert_norm (List.Tot.length l == 32);
  of_list l


let test () =
  let pk1 : lbytes 32 = Spec.Curve25519.secret_to_public sk1 in
  let pk2 : lbytes 32 = Spec.Curve25519.secret_to_public sk2 in
  let mac_cipher = box_detached sk1 pk2 nonce plain in
  let (mac, cipher) =
    match mac_cipher with | Some p -> p | None -> (create 16 (u8 0), create 72 (u8 0)) in

  let dec = box_open_detached pk1 sk2 nonce mac cipher in
  let dec_p = match dec with | Some p -> p | None -> create 72 (u8 0) in
  let result_decryption =
    for_all2 (fun a b -> uint_to_nat #U8 a = uint_to_nat #U8 b) dec_p plain in

  if result_decryption
  then begin IO.print_string "\nCryptoBox: Success!\n"; true end
  else begin IO.print_string "\nCryptoBox: Failure :("; false end
