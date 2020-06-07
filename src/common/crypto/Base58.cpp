/* Written in 2015 by Alexander Shishenko <alex@shishenko.com>
 *
 * LVCrypto - Cryptographic wrapper, used in Librevault.
 * To the extent possible under law, the author(s) have dedicated all copyright
 * and related and neighboring rights to this software to the public domain
 * worldwide. This software is distributed without any warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication
 * along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */
#include "Base58.h"

#include <cryptopp/integer.h>

namespace librevault {
namespace crypto {

Base58::Base58(const std::string& alphabet) : current_alphabet(alphabet) {}

QByteArray Base58::to(const QByteArray& data) const {
  CryptoPP::Integer big_data = conv_bytearray_to_integer(data);

  QByteArray result;
  result.reserve(data.size() * 138 / 100 + 1);

  CryptoPP::word mod;
  CryptoPP::Integer div;
  while (big_data > 0) {
    CryptoPP::Integer::Divide(mod, div, big_data, 58);
    result += current_alphabet[mod];
    big_data = div;
  }

  for (const char* orig_str = data.data(); orig_str < data.data() + data.size() && *orig_str == 0; orig_str++) {
    result += current_alphabet[0];
  }

  std::reverse(result.begin(), result.end());
  return result;
}

QByteArray Base58::from(const QByteArray& data) const {
  CryptoPP::Integer big_data = 0;
  CryptoPP::Integer multi = 1;

  for (int i = data.size() - 1; i >= 0; i--) {
    big_data += multi * current_alphabet.find((char)data.data()[i]);
    multi *= 58;
  }

  int leading_zeros = 0;
  for (const char* orig_str = data.data(); orig_str < data.data() + data.size() && *orig_str == current_alphabet[0];
       orig_str++) {
    leading_zeros++;
  }

  QByteArray decoded(leading_zeros + big_data.MinEncodedSize(), 0);
  big_data.Encode(leading_zeros + (uchar*)decoded.data(), decoded.size());
  return decoded;
}

}  // namespace crypto
}  // namespace librevault
