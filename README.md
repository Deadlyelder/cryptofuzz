# Cryptofuzz - Differential cryptography fuzzing

## Operation

For each library that implements cryptographic functions, you use a module.

Each iteration, Cryptofuzz instructs each module to perform the same cryptographic operation.

For example, it can tell every loaded module to create a SHA256 hash of the string ```abcdef```.

The module returns the computed hash back to Cryptofuzz. Cryptofuzz then compares the result of every module, and if there is any mismatch, it crashes.

Comparing the results for the same cryptographic operation across different modules is what comprises the ***differential testing*** component of Cryptofuzz.

Every module is given the freedom to compute the result in any which way it likes.

For example, one way to compute the SHA256 hash of ```abcdef``` can be to pass ```abcdef``` in one go. Another way can be to pass ```abc```, then pass ```def```, and then compute the final hash.

If asserting equal results across multiple modules is ***differential testing***, then comparing multiple results generated by the same module using different internal computation methods could be called ***self-differential testing***.

## Implementing a new module

To implement a new module:

- Create a directory in ```modules/```
- Create a class in the ```cryptofuzz::module``` namespace that inherits from ```cryptofuzz::module::Module```.
- From the constructor of your class, call the base class with a ```std::string``` argument that describes your module. E.g.:

```cpp
FooBarTLS::FooBarTLS(void) :
    Module("FooBarTLS") {
   ...
   ...
}
```
- Perform any library initialization in your constructor, and any de-initialization in your destructor.
- Override any amount of pure virtual methods declared in ```include/cryptofuzz/module.h```. Let's say you want to implement a [message digest](https://en.wikipedia.org/wiki/Cryptographic_hash_function) operation, then implement:

```cpp
std::optional<component::Digest> FooBarTLS::OpDigest(operation::Digest& op) {
   ...
   ...
}
```

- If you cannot comply with the request described in ```op```, return ```std::nullopt``` (or ```return {};```).
- The ```op``` parameter of every ```cryptofuzz::module::Module``` method that can be overrided implements a ```modifier``` member, that contains 0 or more bytes. The method can optionally use this data to deterministically decide which internal operation to use.

```cpp
std::optional<component::Digest> FooBarTLS::OpDigest(operation::Digest& op) {
   if ( op.digestType == ID("Cryptofuzz/Digest/SHA256") ) {
      if ( !op.modifier.empty() && op.modifier[0] == 0 ) {
         return calc_SHA256_method_1(...);
      } else {
         return calc_SHA256_method_2(...);
      }
   }
   ...
   ...
}
```

## Compiling

### OpenSSL

```sh
./config --debug enable-md2 enable-rc5 <instrumentation/sanitizer flags>
```

## Analyzing crashes

(TODO)

## Tests

Individual tests to validate cryptographic operations reside in ```tests.cpp```.

It currently contains one test, that accurately identifies [OpenSSL CVE-2019-1543](https://www.openssl.org/news/secadv/20190306.txt) (overlong IV in a ChaCha20-Poly1305 operation).

If you have more tests, please add them!

## Hall of Fame

- OpenSSL: [ARIA GCM ciphers memory leak after EVP_CTRL_AEAD_SET_IVLEN](https://github.com/openssl/openssl/issues/8567)
- OpenSSL: [HMAC with SHAKE128 via EVP interface crashes on EVP_DigestSignUpdate](https://github.com/openssl/openssl/issues/8563)
- OpenSSL: [BLAKE2b_Update can pass NULL to memcpy (undefined behavior)](https://github.com/openssl/openssl/issues/8576)
- LibreSSL: [EVP_aes_128_cbc_hmac_sha1, EVP_aes_256_cbc_hmac_sha1 decrypt OOB read/crash/invalid result](https://cvsweb.openbsd.org/cgi-bin/cvsweb/src/lib/libcrypto/evp/e_aes_cbc_hmac_sha1.c?rev=1.15&content-type=text/x-cvsweb-markup)
- OpenSSL: [CHACHA20_POLY1305 different results for chunked/non-chunked updating](https://github.com/openssl/openssl/issues/8675)
- OpenSSL: [OpenSSL 1.0.2: BIO_read + *_WRAP ciphers copy to uninitialized pointer](https://github.com/openssl/openssl/issues/8688)
- BoringSSL: [AEAD AES GCM SIV NULL pointer dereference/OOB read](https://boringssl-review.googlesource.com/c/boringssl/+/35545)
- LibreSSL: [BIO_read can report more bytes written than buffer can hold](https://cvsweb.openbsd.org/src/lib/libcrypto/bio/bio_lib.c?rev=1.29&content-type=text/x-cvsweb-markup)
- LibreSSL: [Use-after-free/bad free after EVP_CIPHER_CTX_copy](https://cvsweb.openbsd.org/src/lib/libcrypto/evp/evp_enc.c?rev=1.41&content-type=text/x-cvsweb-markup)
- BoringSSL: [Use-after-free/bad free after EVP_CIPHER_CTX_copy](https://boringssl.googlesource.com/boringssl/+/65dc45cb57c7c6900a0657f6ee5c00fce9d366f5)
- LibreSSL: [GOST HMAC uses and outputs uninitialized memory](https://cvsweb.openbsd.org/src/lib/libcrypto/evp/digest.c?rev=1.31&content-type=text/x-cvsweb-markup)
- OpenSSL: [Overlong tag buffer leaves memory uninitialized in CCM mode](https://github.com/openssl/openssl/pull/8810)
- OpenSSL: [Buffer write overflow when passing large RC5 key](https://github.com/openssl/openssl/pull/8834)
- OpenSSL: [Hang after particular sequence of operations](https://github.com/openssl/openssl/issues/8827)
- LibreSSL: [Overlong tag buffer leaves memory uninitialized in CCM mode](https://cvsweb.openbsd.org/src/lib/libcrypto/modes/ccm128.c?rev=1.5&content-type=text/x-cvsweb-markup)
- LibreSSL: AES GCM context copy crash (TBA)
- LibreSSL: Streebog wrong output (TBA)
- OpenSSL: [EVP_EncryptUpdate, EVP_EncryptFinal_ex branching on uninitialized memory](https://github.com/openssl/openssl/pull/8874)
