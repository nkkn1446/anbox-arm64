/*
 * Copyright (C) 2016 Simon Fels <morphis@gravedo.de>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranties of
 * MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ANBOX_RPC_CONSTANTS_H_
#define ANBOX_RPC_CONSTANTS_H_

#include <memory>

namespace anbox {
namespace rpc {
static constexpr const long header_size{4};
static constexpr unsigned int const serialization_buffer_size{2048};

enum MessageType {
  invocation = 0,
  response = 1,
};

struct StrBuffer
{
        std::uint8_t high;
        std::uint8_t medium;
        std::uint8_t low;
        std::uint8_t message_type;

};
inline void enc(unsigned char* dest, const StrBuffer& buffer)
{
    const size_t size = buffer.low;
    const unsigned char header_bytes[header_size] = {
        static_cast<unsigned char>((size >> 16) & 0xff),
        static_cast<unsigned char>((size >> 8) & 0xff),
        static_cast<unsigned char>((size >> 0) & 0xff), MessageType::response,
    };
    std::copy(header_bytes, header_bytes + header_size, dest);
}
inline StrBuffer dec(const unsigned char* buffer)
{
  StrBuffer result;
  result.high = buffer[0];
  result.medium = buffer[1];
  result.low = buffer[2];
  result.message_type = buffer[3];
  return result;
}
}  // namespace rpc
}  // namespace network

#endif
