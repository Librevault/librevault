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
#pragma once
#include "Transformer.h"

namespace librevault::crypto {

namespace alphabet {
static std::string bitcoin = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
}  // namespace alphabet

class Base58 : public TwoWayTransformer {
 private:
  const std::string& current_alphabet;

 public:
  explicit Base58(const std::string& alphabet = alphabet::bitcoin);
  QByteArray to(const QByteArray& data) const override;
  QByteArray from(const QByteArray& data) const override;
};

}  // namespace librevault::crypto
